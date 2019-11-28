/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "global.h"

//#include "button.h"
#include "led.h"
#include "seven.h"
#include "ledFaderArcadian.h"
#include "ledGlower.h"

ISR(systick_handler)
{
    CounterTick(cnt_systick); //application counter
}


int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
//Set systick period to 1 ms. Enable the INT and start it.
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
	EE_systick_enable_int();
	EE_systick_start();
   
    // Start Operating System
    StartOS(OSDEFAULTAPPMODE);
    for(;;)
    {
        asm("bkpt");   
    }
}
/*********************************************************************
***********
* Task Definitions
**********************************************************************
**********/

TASK(tsk_init)
{
    //Init MCAL Drivers
    LED_Init();
    SEVEN_Init();
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver
    //initialization!
    EE_system_init();
    // Must be started after interrupt reconfiguration
    EE_systick_start();
    //Start the alarm with 100ms cycle time
    SetRelAlarm(alarm_ledFader,FADER_ALARM_EXPIRE_TIME,FADER_ALARM_EXPIRE_TIME);
    
    TerminateTask();
}

TASK(tsk_ledFader)
{
    ledArcadianStart();
    glowRGBPwmLedInSequence();    
    TerminateTask();
}

TASK(tsk_Background)
{
    while(1)
    {
        //do something with low prioroty
        asm("nop");
    }
}


/* [] END OF FILE */
