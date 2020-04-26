/*******************************************************************************
* File Name: YELLOW_LED_PWM_PM.c
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

#include "YELLOW_LED_PWM.h"

static YELLOW_LED_PWM_backupStruct YELLOW_LED_PWM_backup;


/*******************************************************************************
* Function Name: YELLOW_LED_PWM_SaveConfig
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
*  YELLOW_LED_PWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void YELLOW_LED_PWM_SaveConfig(void) 
{

    #if(!YELLOW_LED_PWM_UsingFixedFunction)
        #if(!YELLOW_LED_PWM_PWMModeIsCenterAligned)
            YELLOW_LED_PWM_backup.PWMPeriod = YELLOW_LED_PWM_ReadPeriod();
        #endif /* (!YELLOW_LED_PWM_PWMModeIsCenterAligned) */
        YELLOW_LED_PWM_backup.PWMUdb = YELLOW_LED_PWM_ReadCounter();
        #if (YELLOW_LED_PWM_UseStatus)
            YELLOW_LED_PWM_backup.InterruptMaskValue = YELLOW_LED_PWM_STATUS_MASK;
        #endif /* (YELLOW_LED_PWM_UseStatus) */

        #if(YELLOW_LED_PWM_DeadBandMode == YELLOW_LED_PWM__B_PWM__DBM_256_CLOCKS || \
            YELLOW_LED_PWM_DeadBandMode == YELLOW_LED_PWM__B_PWM__DBM_2_4_CLOCKS)
            YELLOW_LED_PWM_backup.PWMdeadBandValue = YELLOW_LED_PWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(YELLOW_LED_PWM_KillModeMinTime)
             YELLOW_LED_PWM_backup.PWMKillCounterPeriod = YELLOW_LED_PWM_ReadKillTime();
        #endif /* (YELLOW_LED_PWM_KillModeMinTime) */

        #if(YELLOW_LED_PWM_UseControl)
            YELLOW_LED_PWM_backup.PWMControlRegister = YELLOW_LED_PWM_ReadControlRegister();
        #endif /* (YELLOW_LED_PWM_UseControl) */
    #endif  /* (!YELLOW_LED_PWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: YELLOW_LED_PWM_RestoreConfig
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
*  YELLOW_LED_PWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void YELLOW_LED_PWM_RestoreConfig(void) 
{
        #if(!YELLOW_LED_PWM_UsingFixedFunction)
            #if(!YELLOW_LED_PWM_PWMModeIsCenterAligned)
                YELLOW_LED_PWM_WritePeriod(YELLOW_LED_PWM_backup.PWMPeriod);
            #endif /* (!YELLOW_LED_PWM_PWMModeIsCenterAligned) */

            YELLOW_LED_PWM_WriteCounter(YELLOW_LED_PWM_backup.PWMUdb);

            #if (YELLOW_LED_PWM_UseStatus)
                YELLOW_LED_PWM_STATUS_MASK = YELLOW_LED_PWM_backup.InterruptMaskValue;
            #endif /* (YELLOW_LED_PWM_UseStatus) */

            #if(YELLOW_LED_PWM_DeadBandMode == YELLOW_LED_PWM__B_PWM__DBM_256_CLOCKS || \
                YELLOW_LED_PWM_DeadBandMode == YELLOW_LED_PWM__B_PWM__DBM_2_4_CLOCKS)
                YELLOW_LED_PWM_WriteDeadTime(YELLOW_LED_PWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(YELLOW_LED_PWM_KillModeMinTime)
                YELLOW_LED_PWM_WriteKillTime(YELLOW_LED_PWM_backup.PWMKillCounterPeriod);
            #endif /* (YELLOW_LED_PWM_KillModeMinTime) */

            #if(YELLOW_LED_PWM_UseControl)
                YELLOW_LED_PWM_WriteControlRegister(YELLOW_LED_PWM_backup.PWMControlRegister);
            #endif /* (YELLOW_LED_PWM_UseControl) */
        #endif  /* (!YELLOW_LED_PWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: YELLOW_LED_PWM_Sleep
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
*  YELLOW_LED_PWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void YELLOW_LED_PWM_Sleep(void) 
{
    #if(YELLOW_LED_PWM_UseControl)
        if(YELLOW_LED_PWM_CTRL_ENABLE == (YELLOW_LED_PWM_CONTROL & YELLOW_LED_PWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            YELLOW_LED_PWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            YELLOW_LED_PWM_backup.PWMEnableState = 0u;
        }
    #endif /* (YELLOW_LED_PWM_UseControl) */

    /* Stop component */
    YELLOW_LED_PWM_Stop();

    /* Save registers configuration */
    YELLOW_LED_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: YELLOW_LED_PWM_Wakeup
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
*  YELLOW_LED_PWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void YELLOW_LED_PWM_Wakeup(void) 
{
     /* Restore registers values */
    YELLOW_LED_PWM_RestoreConfig();

    if(YELLOW_LED_PWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        YELLOW_LED_PWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
