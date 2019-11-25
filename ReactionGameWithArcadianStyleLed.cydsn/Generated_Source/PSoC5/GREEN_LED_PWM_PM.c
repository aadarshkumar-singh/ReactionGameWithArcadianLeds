/*******************************************************************************
* File Name: GREEN_LED_PWM_PM.c
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

#include "GREEN_LED_PWM.h"

static GREEN_LED_PWM_backupStruct GREEN_LED_PWM_backup;


/*******************************************************************************
* Function Name: GREEN_LED_PWM_SaveConfig
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
*  GREEN_LED_PWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void GREEN_LED_PWM_SaveConfig(void) 
{

    #if(!GREEN_LED_PWM_UsingFixedFunction)
        #if(!GREEN_LED_PWM_PWMModeIsCenterAligned)
            GREEN_LED_PWM_backup.PWMPeriod = GREEN_LED_PWM_ReadPeriod();
        #endif /* (!GREEN_LED_PWM_PWMModeIsCenterAligned) */
        GREEN_LED_PWM_backup.PWMUdb = GREEN_LED_PWM_ReadCounter();
        #if (GREEN_LED_PWM_UseStatus)
            GREEN_LED_PWM_backup.InterruptMaskValue = GREEN_LED_PWM_STATUS_MASK;
        #endif /* (GREEN_LED_PWM_UseStatus) */

        #if(GREEN_LED_PWM_DeadBandMode == GREEN_LED_PWM__B_PWM__DBM_256_CLOCKS || \
            GREEN_LED_PWM_DeadBandMode == GREEN_LED_PWM__B_PWM__DBM_2_4_CLOCKS)
            GREEN_LED_PWM_backup.PWMdeadBandValue = GREEN_LED_PWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(GREEN_LED_PWM_KillModeMinTime)
             GREEN_LED_PWM_backup.PWMKillCounterPeriod = GREEN_LED_PWM_ReadKillTime();
        #endif /* (GREEN_LED_PWM_KillModeMinTime) */

        #if(GREEN_LED_PWM_UseControl)
            GREEN_LED_PWM_backup.PWMControlRegister = GREEN_LED_PWM_ReadControlRegister();
        #endif /* (GREEN_LED_PWM_UseControl) */
    #endif  /* (!GREEN_LED_PWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: GREEN_LED_PWM_RestoreConfig
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
*  GREEN_LED_PWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void GREEN_LED_PWM_RestoreConfig(void) 
{
        #if(!GREEN_LED_PWM_UsingFixedFunction)
            #if(!GREEN_LED_PWM_PWMModeIsCenterAligned)
                GREEN_LED_PWM_WritePeriod(GREEN_LED_PWM_backup.PWMPeriod);
            #endif /* (!GREEN_LED_PWM_PWMModeIsCenterAligned) */

            GREEN_LED_PWM_WriteCounter(GREEN_LED_PWM_backup.PWMUdb);

            #if (GREEN_LED_PWM_UseStatus)
                GREEN_LED_PWM_STATUS_MASK = GREEN_LED_PWM_backup.InterruptMaskValue;
            #endif /* (GREEN_LED_PWM_UseStatus) */

            #if(GREEN_LED_PWM_DeadBandMode == GREEN_LED_PWM__B_PWM__DBM_256_CLOCKS || \
                GREEN_LED_PWM_DeadBandMode == GREEN_LED_PWM__B_PWM__DBM_2_4_CLOCKS)
                GREEN_LED_PWM_WriteDeadTime(GREEN_LED_PWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(GREEN_LED_PWM_KillModeMinTime)
                GREEN_LED_PWM_WriteKillTime(GREEN_LED_PWM_backup.PWMKillCounterPeriod);
            #endif /* (GREEN_LED_PWM_KillModeMinTime) */

            #if(GREEN_LED_PWM_UseControl)
                GREEN_LED_PWM_WriteControlRegister(GREEN_LED_PWM_backup.PWMControlRegister);
            #endif /* (GREEN_LED_PWM_UseControl) */
        #endif  /* (!GREEN_LED_PWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: GREEN_LED_PWM_Sleep
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
*  GREEN_LED_PWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void GREEN_LED_PWM_Sleep(void) 
{
    #if(GREEN_LED_PWM_UseControl)
        if(GREEN_LED_PWM_CTRL_ENABLE == (GREEN_LED_PWM_CONTROL & GREEN_LED_PWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            GREEN_LED_PWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            GREEN_LED_PWM_backup.PWMEnableState = 0u;
        }
    #endif /* (GREEN_LED_PWM_UseControl) */

    /* Stop component */
    GREEN_LED_PWM_Stop();

    /* Save registers configuration */
    GREEN_LED_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: GREEN_LED_PWM_Wakeup
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
*  GREEN_LED_PWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void GREEN_LED_PWM_Wakeup(void) 
{
     /* Restore registers values */
    GREEN_LED_PWM_RestoreConfig();

    if(GREEN_LED_PWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        GREEN_LED_PWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
