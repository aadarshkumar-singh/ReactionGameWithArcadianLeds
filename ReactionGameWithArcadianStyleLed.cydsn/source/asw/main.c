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
#include "displayLog.h"
#include "button.h"
#include "reactionGame.h"
#include "timer.h"

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
    //Initialise UART
    displayLog_Start();
        
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver
    //initialization!
    EE_system_init();
    // Must be started after interrupt reconfiguration
    EE_systick_start();
    
    displayWelcomeMessage();    
    
    //Start the alarm with 100ms cycle time
    SetRelAlarm(alarm_ledFader,10,FADER_ALARM_EXPIRE_TIME);
    SetRelAlarm(alarm_Timer,10,1);

    ActivateTask(tsk_gameControl);
    ActivateTask(tsk_Background);
    
    TerminateTask();
}

TASK(tsk_ledFader)
{
    ledArcadianStart();
    glowRGBPwmLedInSequence();    
    TerminateTask();
}

TASK(tsk_Timer)
{
    incrementTimerValue();
    if (timeOutOccured())
    {
       SetEvent(tsk_gameControl, ev_Timeout);
    }
    
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

TASK(tsk_gameControl)
{
    EventMaskType ev = 0;   
    
    while(1)
    {
        WaitEvent(ev_Button | ev_Timeout);
        GetEvent(tsk_gameControl,&ev);
        ClearEvent(ev);
        processEventReactionGame(ev);
    }
}

/********************************************************************************
 * ISR Definitions
 ********************************************************************************/

ISR2(isr_Button)
{
    if (TRUE == BUTTON_IsPressed(BUTTON_1))
    {
        setButtonPressed(1);
        SetEvent(tsk_gameControl, ev_Button);
    }
    else if(TRUE == BUTTON_IsPressed(BUTTON_2))
    {
        setButtonPressed(2);
        SetEvent(tsk_gameControl, ev_Button);
    }
}

/* [] END OF FILE */