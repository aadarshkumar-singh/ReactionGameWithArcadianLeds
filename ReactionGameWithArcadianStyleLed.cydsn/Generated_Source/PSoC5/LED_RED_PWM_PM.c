/*******************************************************************************
* File Name: LED_RED_PWM_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LED_RED_PWM.h"

static LED_RED_PWM_backupStruct LED_RED_PWM_backup;


/*******************************************************************************
* Function Name: LED_RED_PWM_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  LED_RED_PWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void LED_RED_PWM_SaveConfig(void) 
{

    #if(!LED_RED_PWM_UsingFixedFunction)
        #if(!LED_RED_PWM_PWMModeIsCenterAligned)
            LED_RED_PWM_backup.PWMPeriod = LED_RED_PWM_ReadPeriod();
        #endif /* (!LED_RED_PWM_PWMModeIsCenterAligned) */
        LED_RED_PWM_backup.PWMUdb = LED_RED_PWM_ReadCounter();
        #if (LED_RED_PWM_UseStatus)
            LED_RED_PWM_backup.InterruptMaskValue = LED_RED_PWM_STATUS_MASK;
        #endif /* (LED_RED_PWM_UseStatus) */

        #if(LED_RED_PWM_DeadBandMode == LED_RED_PWM__B_PWM__DBM_256_CLOCKS || \
            LED_RED_PWM_DeadBandMode == LED_RED_PWM__B_PWM__DBM_2_4_CLOCKS)
            LED_RED_PWM_backup.PWMdeadBandValue = LED_RED_PWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(LED_RED_PWM_KillModeMinTime)
             LED_RED_PWM_backup.PWMKillCounterPeriod = LED_RED_PWM_ReadKillTime();
        #endif /* (LED_RED_PWM_KillModeMinTime) */

        #if(LED_RED_PWM_UseControl)
            LED_RED_PWM_backup.PWMControlRegister = LED_RED_PWM_ReadControlRegister();
        #endif /* (LED_RED_PWM_UseControl) */
    #endif  /* (!LED_RED_PWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LED_RED_PWM_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  LED_RED_PWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void LED_RED_PWM_RestoreConfig(void) 
{
        #if(!LED_RED_PWM_UsingFixedFunction)
            #if(!LED_RED_PWM_PWMModeIsCenterAligned)
                LED_RED_PWM_WritePeriod(LED_RED_PWM_backup.PWMPeriod);
            #endif /* (!LED_RED_PWM_PWMModeIsCenterAligned) */

            LED_RED_PWM_WriteCounter(LED_RED_PWM_backup.PWMUdb);

            #if (LED_RED_PWM_UseStatus)
                LED_RED_PWM_STATUS_MASK = LED_RED_PWM_backup.InterruptMaskValue;
            #endif /* (LED_RED_PWM_UseStatus) */

            #if(LED_RED_PWM_DeadBandMode == LED_RED_PWM__B_PWM__DBM_256_CLOCKS || \
                LED_RED_PWM_DeadBandMode == LED_RED_PWM__B_PWM__DBM_2_4_CLOCKS)
                LED_RED_PWM_WriteDeadTime(LED_RED_PWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(LED_RED_PWM_KillModeMinTime)
                LED_RED_PWM_WriteKillTime(LED_RED_PWM_backup.PWMKillCounterPeriod);
            #endif /* (LED_RED_PWM_KillModeMinTime) */

            #if(LED_RED_PWM_UseControl)
                LED_RED_PWM_WriteControlRegister(LED_RED_PWM_backup.PWMControlRegister);
            #endif /* (LED_RED_PWM_UseControl) */
        #endif  /* (!LED_RED_PWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: LED_RED_PWM_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  LED_RED_PWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void LED_RED_PWM_Sleep(void) 
{
    #if(LED_RED_PWM_UseControl)
        if(LED_RED_PWM_CTRL_ENABLE == (LED_RED_PWM_CONTROL & LED_RED_PWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            LED_RED_PWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            LED_RED_PWM_backup.PWMEnableState = 0u;
        }
    #endif /* (LED_RED_PWM_UseControl) */

    /* Stop component */
    LED_RED_PWM_Stop();

    /* Save registers configuration */
    LED_RED_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: LED_RED_PWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  LED_RED_PWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void LED_RED_PWM_Wakeup(void) 
{
     /* Restore registers values */
    LED_RED_PWM_RestoreConfig();

    if(LED_RED_PWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        LED_RED_PWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
