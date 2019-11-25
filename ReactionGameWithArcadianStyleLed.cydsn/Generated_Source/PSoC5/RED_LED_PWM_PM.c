/*******************************************************************************
* File Name: RED_LED_PWM_PM.c
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

#include "RED_LED_PWM.h"

static RED_LED_PWM_backupStruct RED_LED_PWM_backup;


/*******************************************************************************
* Function Name: RED_LED_PWM_SaveConfig
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
*  RED_LED_PWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void RED_LED_PWM_SaveConfig(void) 
{

    #if(!RED_LED_PWM_UsingFixedFunction)
        #if(!RED_LED_PWM_PWMModeIsCenterAligned)
            RED_LED_PWM_backup.PWMPeriod = RED_LED_PWM_ReadPeriod();
        #endif /* (!RED_LED_PWM_PWMModeIsCenterAligned) */
        RED_LED_PWM_backup.PWMUdb = RED_LED_PWM_ReadCounter();
        #if (RED_LED_PWM_UseStatus)
            RED_LED_PWM_backup.InterruptMaskValue = RED_LED_PWM_STATUS_MASK;
        #endif /* (RED_LED_PWM_UseStatus) */

        #if(RED_LED_PWM_DeadBandMode == RED_LED_PWM__B_PWM__DBM_256_CLOCKS || \
            RED_LED_PWM_DeadBandMode == RED_LED_PWM__B_PWM__DBM_2_4_CLOCKS)
            RED_LED_PWM_backup.PWMdeadBandValue = RED_LED_PWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(RED_LED_PWM_KillModeMinTime)
             RED_LED_PWM_backup.PWMKillCounterPeriod = RED_LED_PWM_ReadKillTime();
        #endif /* (RED_LED_PWM_KillModeMinTime) */

        #if(RED_LED_PWM_UseControl)
            RED_LED_PWM_backup.PWMControlRegister = RED_LED_PWM_ReadControlRegister();
        #endif /* (RED_LED_PWM_UseControl) */
    #endif  /* (!RED_LED_PWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: RED_LED_PWM_RestoreConfig
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
*  RED_LED_PWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void RED_LED_PWM_RestoreConfig(void) 
{
        #if(!RED_LED_PWM_UsingFixedFunction)
            #if(!RED_LED_PWM_PWMModeIsCenterAligned)
                RED_LED_PWM_WritePeriod(RED_LED_PWM_backup.PWMPeriod);
            #endif /* (!RED_LED_PWM_PWMModeIsCenterAligned) */

            RED_LED_PWM_WriteCounter(RED_LED_PWM_backup.PWMUdb);

            #if (RED_LED_PWM_UseStatus)
                RED_LED_PWM_STATUS_MASK = RED_LED_PWM_backup.InterruptMaskValue;
            #endif /* (RED_LED_PWM_UseStatus) */

            #if(RED_LED_PWM_DeadBandMode == RED_LED_PWM__B_PWM__DBM_256_CLOCKS || \
                RED_LED_PWM_DeadBandMode == RED_LED_PWM__B_PWM__DBM_2_4_CLOCKS)
                RED_LED_PWM_WriteDeadTime(RED_LED_PWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(RED_LED_PWM_KillModeMinTime)
                RED_LED_PWM_WriteKillTime(RED_LED_PWM_backup.PWMKillCounterPeriod);
            #endif /* (RED_LED_PWM_KillModeMinTime) */

            #if(RED_LED_PWM_UseControl)
                RED_LED_PWM_WriteControlRegister(RED_LED_PWM_backup.PWMControlRegister);
            #endif /* (RED_LED_PWM_UseControl) */
        #endif  /* (!RED_LED_PWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: RED_LED_PWM_Sleep
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
*  RED_LED_PWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void RED_LED_PWM_Sleep(void) 
{
    #if(RED_LED_PWM_UseControl)
        if(RED_LED_PWM_CTRL_ENABLE == (RED_LED_PWM_CONTROL & RED_LED_PWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            RED_LED_PWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            RED_LED_PWM_backup.PWMEnableState = 0u;
        }
    #endif /* (RED_LED_PWM_UseControl) */

    /* Stop component */
    RED_LED_PWM_Stop();

    /* Save registers configuration */
    RED_LED_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: RED_LED_PWM_Wakeup
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
*  RED_LED_PWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void RED_LED_PWM_Wakeup(void) 
{
     /* Restore registers values */
    RED_LED_PWM_RestoreConfig();

    if(RED_LED_PWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        RED_LED_PWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
