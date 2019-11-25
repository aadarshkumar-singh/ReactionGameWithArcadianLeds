/*******************************************************************************
* File Name: LED_PWM_YELLOW_PM.c
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

#include "LED_PWM_YELLOW.h"

static LED_PWM_YELLOW_backupStruct LED_PWM_YELLOW_backup;


/*******************************************************************************
* Function Name: LED_PWM_YELLOW_SaveConfig
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
*  LED_PWM_YELLOW_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void LED_PWM_YELLOW_SaveConfig(void) 
{

    #if(!LED_PWM_YELLOW_UsingFixedFunction)
        #if(!LED_PWM_YELLOW_PWMModeIsCenterAligned)
            LED_PWM_YELLOW_backup.PWMPeriod = LED_PWM_YELLOW_ReadPeriod();
        #endif /* (!LED_PWM_YELLOW_PWMModeIsCenterAligned) */
        LED_PWM_YELLOW_backup.PWMUdb = LED_PWM_YELLOW_ReadCounter();
        #if (LED_PWM_YELLOW_UseStatus)
            LED_PWM_YELLOW_backup.InterruptMaskValue = LED_PWM_YELLOW_STATUS_MASK;
        #endif /* (LED_PWM_YELLOW_UseStatus) */

        #if(LED_PWM_YELLOW_DeadBandMode == LED_PWM_YELLOW__B_PWM__DBM_256_CLOCKS || \
            LED_PWM_YELLOW_DeadBandMode == LED_PWM_YELLOW__B_PWM__DBM_2_4_CLOCKS)
            LED_PWM_YELLOW_backup.PWMdeadBandValue = LED_PWM_YELLOW_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(LED_PWM_YELLOW_KillModeMinTime)
             LED_PWM_YELLOW_backup.PWMKillCounterPeriod = LED_PWM_YELLOW_ReadKillTime();
        #endif /* (LED_PWM_YELLOW_KillModeMinTime) */

        #if(LED_PWM_YELLOW_UseControl)
            LED_PWM_YELLOW_backup.PWMControlRegister = LED_PWM_YELLOW_ReadControlRegister();
        #endif /* (LED_PWM_YELLOW_UseControl) */
    #endif  /* (!LED_PWM_YELLOW_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LED_PWM_YELLOW_RestoreConfig
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
*  LED_PWM_YELLOW_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void LED_PWM_YELLOW_RestoreConfig(void) 
{
        #if(!LED_PWM_YELLOW_UsingFixedFunction)
            #if(!LED_PWM_YELLOW_PWMModeIsCenterAligned)
                LED_PWM_YELLOW_WritePeriod(LED_PWM_YELLOW_backup.PWMPeriod);
            #endif /* (!LED_PWM_YELLOW_PWMModeIsCenterAligned) */

            LED_PWM_YELLOW_WriteCounter(LED_PWM_YELLOW_backup.PWMUdb);

            #if (LED_PWM_YELLOW_UseStatus)
                LED_PWM_YELLOW_STATUS_MASK = LED_PWM_YELLOW_backup.InterruptMaskValue;
            #endif /* (LED_PWM_YELLOW_UseStatus) */

            #if(LED_PWM_YELLOW_DeadBandMode == LED_PWM_YELLOW__B_PWM__DBM_256_CLOCKS || \
                LED_PWM_YELLOW_DeadBandMode == LED_PWM_YELLOW__B_PWM__DBM_2_4_CLOCKS)
                LED_PWM_YELLOW_WriteDeadTime(LED_PWM_YELLOW_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(LED_PWM_YELLOW_KillModeMinTime)
                LED_PWM_YELLOW_WriteKillTime(LED_PWM_YELLOW_backup.PWMKillCounterPeriod);
            #endif /* (LED_PWM_YELLOW_KillModeMinTime) */

            #if(LED_PWM_YELLOW_UseControl)
                LED_PWM_YELLOW_WriteControlRegister(LED_PWM_YELLOW_backup.PWMControlRegister);
            #endif /* (LED_PWM_YELLOW_UseControl) */
        #endif  /* (!LED_PWM_YELLOW_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: LED_PWM_YELLOW_Sleep
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
*  LED_PWM_YELLOW_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void LED_PWM_YELLOW_Sleep(void) 
{
    #if(LED_PWM_YELLOW_UseControl)
        if(LED_PWM_YELLOW_CTRL_ENABLE == (LED_PWM_YELLOW_CONTROL & LED_PWM_YELLOW_CTRL_ENABLE))
        {
            /*Component is enabled */
            LED_PWM_YELLOW_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            LED_PWM_YELLOW_backup.PWMEnableState = 0u;
        }
    #endif /* (LED_PWM_YELLOW_UseControl) */

    /* Stop component */
    LED_PWM_YELLOW_Stop();

    /* Save registers configuration */
    LED_PWM_YELLOW_SaveConfig();
}


/*******************************************************************************
* Function Name: LED_PWM_YELLOW_Wakeup
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
*  LED_PWM_YELLOW_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void LED_PWM_YELLOW_Wakeup(void) 
{
     /* Restore registers values */
    LED_PWM_YELLOW_RestoreConfig();

    if(LED_PWM_YELLOW_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        LED_PWM_YELLOW_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
