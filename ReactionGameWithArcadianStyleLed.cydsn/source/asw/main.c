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
#include "button.h"
#include "led.h"
#include "seven.h"
#include "ledFaderArcadian.h"
#include "ledGlower.h"
#include "displayLog.h"
#include "button.h"
#include "reactionGame.h"
#include "timer.h"

/**
 * \brief ISR which will increment the systick counter every ms
 */
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
    /** Init MCAL Drivers */
    LED_Init();  /** Led Initialisation */
    SEVEN_Init(); /** Seven Segment Initialisation*/
    displayLog_Start(); /** Initialise UART */
        
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver
    //initialization!
    EE_system_init();
    // Must be started after interrupt reconfiguration
    EE_systick_start();
    
    /** Displays the Welcome Message at start of every game.*/
    displayWelcomeMessage();    
    
    /** Start Cyclic alarm for Led Fader and RGB Glower every FADER_ALARM_EXPIRE_TIME ms*/
    SetRelAlarm(alarm_ledFader,FADER_ALARM_EXPIRE_TIME,FADER_ALARM_EXPIRE_TIME);
    
    /** Start Alarm for ONE_MS_TIMER */
    SetRelAlarm(alarm_Timer,ONE_MS_TIMER,ONE_MS_TIMER);

    /** Activate Extended Task for Reaction Game Control */
    ActivateTask(tsk_gameControl);
    
    /** Activate Extended Background Task */
    ActivateTask(tsk_Background);
    
    /** Terminates initialisation Task*/
    TerminateTask();
}

/**
 * \brief Task to execute Led Fader and Led Glower every 5 ms.
 */
TASK(tsk_ledFader)
{
    /** Led Fader with Arcadian Style*/
    ledArcadianStart();
    
    /** Glow RGB Led in specified sequence in Glow table*/
    glowRGBPwmLedInSequence(); 
    
    TerminateTask();
}

/**
 * \brief Task to increment timer count every 1 ms and set event when a timeout occurs.
 */
TASK(tsk_Timer)
{
    incrementTimerValue();
    if (timeOutOccured())
    {
       SetEvent(tsk_gameControl, ev_Timeout);
    }
    
    TerminateTask();
}

/**
 * \brief Ideal Tasks which does no operation
 */
TASK(tsk_Background)
{
    while(1)
    {
        //do something with low prioroty
        asm("nop");
    }
}

/**
 * \brief Task which process and responds to all events that occur 
 *        During the course of the reaction game.
 */
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
/**
 * \brief ISR to check if button 1/2 is pressed.
 */
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