/*******************************************************************************
* File Name: LED_PWM_YELLOW.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_LED_PWM_YELLOW_H)
#define CY_PWM_LED_PWM_YELLOW_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 LED_PWM_YELLOW_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define LED_PWM_YELLOW_Resolution                     (16u)
#define LED_PWM_YELLOW_UsingFixedFunction             (0u)
#define LED_PWM_YELLOW_DeadBandMode                   (0u)
#define LED_PWM_YELLOW_KillModeMinTime                (0u)
#define LED_PWM_YELLOW_KillMode                       (0u)
#define LED_PWM_YELLOW_PWMMode                        (0u)
#define LED_PWM_YELLOW_PWMModeIsCenterAligned         (0u)
#define LED_PWM_YELLOW_DeadBandUsed                   (0u)
#define LED_PWM_YELLOW_DeadBand2_4                    (0u)

#if !defined(LED_PWM_YELLOW_PWMUDB_genblk8_stsreg__REMOVED)
    #define LED_PWM_YELLOW_UseStatus                  (0u)
#else
    #define LED_PWM_YELLOW_UseStatus                  (0u)
#endif /* !defined(LED_PWM_YELLOW_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(LED_PWM_YELLOW_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define LED_PWM_YELLOW_UseControl                 (1u)
#else
    #define LED_PWM_YELLOW_UseControl                 (0u)
#endif /* !defined(LED_PWM_YELLOW_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define LED_PWM_YELLOW_UseOneCompareMode              (1u)
#define LED_PWM_YELLOW_MinimumKillTime                (1u)
#define LED_PWM_YELLOW_EnableMode                     (0u)

#define LED_PWM_YELLOW_CompareMode1SW                 (0u)
#define LED_PWM_YELLOW_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define LED_PWM_YELLOW__B_PWM__DISABLED 0
#define LED_PWM_YELLOW__B_PWM__ASYNCHRONOUS 1
#define LED_PWM_YELLOW__B_PWM__SINGLECYCLE 2
#define LED_PWM_YELLOW__B_PWM__LATCHED 3
#define LED_PWM_YELLOW__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define LED_PWM_YELLOW__B_PWM__DBMDISABLED 0
#define LED_PWM_YELLOW__B_PWM__DBM_2_4_CLOCKS 1
#define LED_PWM_YELLOW__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define LED_PWM_YELLOW__B_PWM__ONE_OUTPUT 0
#define LED_PWM_YELLOW__B_PWM__TWO_OUTPUTS 1
#define LED_PWM_YELLOW__B_PWM__DUAL_EDGE 2
#define LED_PWM_YELLOW__B_PWM__CENTER_ALIGN 3
#define LED_PWM_YELLOW__B_PWM__DITHER 5
#define LED_PWM_YELLOW__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define LED_PWM_YELLOW__B_PWM__LESS_THAN 1
#define LED_PWM_YELLOW__B_PWM__LESS_THAN_OR_EQUAL 2
#define LED_PWM_YELLOW__B_PWM__GREATER_THAN 3
#define LED_PWM_YELLOW__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define LED_PWM_YELLOW__B_PWM__EQUAL 0
#define LED_PWM_YELLOW__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!LED_PWM_YELLOW_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!LED_PWM_YELLOW_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!LED_PWM_YELLOW_PWMModeIsCenterAligned) */
        #if (LED_PWM_YELLOW_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (LED_PWM_YELLOW_UseStatus) */

        /* Backup for Deadband parameters */
        #if(LED_PWM_YELLOW_DeadBandMode == LED_PWM_YELLOW__B_PWM__DBM_256_CLOCKS || \
            LED_PWM_YELLOW_DeadBandMode == LED_PWM_YELLOW__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(LED_PWM_YELLOW_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (LED_PWM_YELLOW_KillModeMinTime) */

        /* Backup control register */
        #if(LED_PWM_YELLOW_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (LED_PWM_YELLOW_UseControl) */

    #endif /* (!LED_PWM_YELLOW_UsingFixedFunction) */

}LED_PWM_YELLOW_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    LED_PWM_YELLOW_Start(void) ;
void    LED_PWM_YELLOW_Stop(void) ;

#if (LED_PWM_YELLOW_UseStatus || LED_PWM_YELLOW_UsingFixedFunction)
    void  LED_PWM_YELLOW_SetInterruptMode(uint8 interruptMode) ;
    uint8 LED_PWM_YELLOW_ReadStatusRegister(void) ;
#endif /* (LED_PWM_YELLOW_UseStatus || LED_PWM_YELLOW_UsingFixedFunction) */

#define LED_PWM_YELLOW_GetInterruptSource() LED_PWM_YELLOW_ReadStatusRegister()

#if (LED_PWM_YELLOW_UseControl)
    uint8 LED_PWM_YELLOW_ReadControlRegister(void) ;
    void  LED_PWM_YELLOW_WriteControlRegister(uint8 control)
          ;
#endif /* (LED_PWM_YELLOW_UseControl) */

#if (LED_PWM_YELLOW_UseOneCompareMode)
   #if (LED_PWM_YELLOW_CompareMode1SW)
       void    LED_PWM_YELLOW_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (LED_PWM_YELLOW_CompareMode1SW) */
#else
    #if (LED_PWM_YELLOW_CompareMode1SW)
        void    LED_PWM_YELLOW_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (LED_PWM_YELLOW_CompareMode1SW) */
    #if (LED_PWM_YELLOW_CompareMode2SW)
        void    LED_PWM_YELLOW_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (LED_PWM_YELLOW_CompareMode2SW) */
#endif /* (LED_PWM_YELLOW_UseOneCompareMode) */

#if (!LED_PWM_YELLOW_UsingFixedFunction)
    uint16   LED_PWM_YELLOW_ReadCounter(void) ;
    uint16 LED_PWM_YELLOW_ReadCapture(void) ;

    #if (LED_PWM_YELLOW_UseStatus)
            void LED_PWM_YELLOW_ClearFIFO(void) ;
    #endif /* (LED_PWM_YELLOW_UseStatus) */

    void    LED_PWM_YELLOW_WriteCounter(uint16 counter)
            ;
#endif /* (!LED_PWM_YELLOW_UsingFixedFunction) */

void    LED_PWM_YELLOW_WritePeriod(uint16 period)
        ;
uint16 LED_PWM_YELLOW_ReadPeriod(void) ;

#if (LED_PWM_YELLOW_UseOneCompareMode)
    void    LED_PWM_YELLOW_WriteCompare(uint16 compare)
            ;
    uint16 LED_PWM_YELLOW_ReadCompare(void) ;
#else
    void    LED_PWM_YELLOW_WriteCompare1(uint16 compare)
            ;
    uint16 LED_PWM_YELLOW_ReadCompare1(void) ;
    void    LED_PWM_YELLOW_WriteCompare2(uint16 compare)
            ;
    uint16 LED_PWM_YELLOW_ReadCompare2(void) ;
#endif /* (LED_PWM_YELLOW_UseOneCompareMode) */


#if (LED_PWM_YELLOW_DeadBandUsed)
    void    LED_PWM_YELLOW_WriteDeadTime(uint8 deadtime) ;
    uint8   LED_PWM_YELLOW_ReadDeadTime(void) ;
#endif /* (LED_PWM_YELLOW_DeadBandUsed) */

#if ( LED_PWM_YELLOW_KillModeMinTime)
    void LED_PWM_YELLOW_WriteKillTime(uint8 killtime) ;
    uint8 LED_PWM_YELLOW_ReadKillTime(void) ;
#endif /* ( LED_PWM_YELLOW_KillModeMinTime) */

void LED_PWM_YELLOW_Init(void) ;
void LED_PWM_YELLOW_Enable(void) ;
void LED_PWM_YELLOW_Sleep(void) ;
void LED_PWM_YELLOW_Wakeup(void) ;
void LED_PWM_YELLOW_SaveConfig(void) ;
void LED_PWM_YELLOW_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define LED_PWM_YELLOW_INIT_PERIOD_VALUE          (65535u)
#define LED_PWM_YELLOW_INIT_COMPARE_VALUE1        (0u)
#define LED_PWM_YELLOW_INIT_COMPARE_VALUE2        (63u)
#define LED_PWM_YELLOW_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    LED_PWM_YELLOW_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    LED_PWM_YELLOW_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    LED_PWM_YELLOW_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    LED_PWM_YELLOW_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define LED_PWM_YELLOW_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  LED_PWM_YELLOW_CTRL_CMPMODE2_SHIFT)
#define LED_PWM_YELLOW_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  LED_PWM_YELLOW_CTRL_CMPMODE1_SHIFT)
#define LED_PWM_YELLOW_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (LED_PWM_YELLOW_UsingFixedFunction)
   #define LED_PWM_YELLOW_PERIOD_LSB              (*(reg16 *) LED_PWM_YELLOW_PWMHW__PER0)
   #define LED_PWM_YELLOW_PERIOD_LSB_PTR          ( (reg16 *) LED_PWM_YELLOW_PWMHW__PER0)
   #define LED_PWM_YELLOW_COMPARE1_LSB            (*(reg16 *) LED_PWM_YELLOW_PWMHW__CNT_CMP0)
   #define LED_PWM_YELLOW_COMPARE1_LSB_PTR        ( (reg16 *) LED_PWM_YELLOW_PWMHW__CNT_CMP0)
   #define LED_PWM_YELLOW_COMPARE2_LSB            (0x00u)
   #define LED_PWM_YELLOW_COMPARE2_LSB_PTR        (0x00u)
   #define LED_PWM_YELLOW_COUNTER_LSB             (*(reg16 *) LED_PWM_YELLOW_PWMHW__CNT_CMP0)
   #define LED_PWM_YELLOW_COUNTER_LSB_PTR         ( (reg16 *) LED_PWM_YELLOW_PWMHW__CNT_CMP0)
   #define LED_PWM_YELLOW_CAPTURE_LSB             (*(reg16 *) LED_PWM_YELLOW_PWMHW__CAP0)
   #define LED_PWM_YELLOW_CAPTURE_LSB_PTR         ( (reg16 *) LED_PWM_YELLOW_PWMHW__CAP0)
   #define LED_PWM_YELLOW_RT1                     (*(reg8 *)  LED_PWM_YELLOW_PWMHW__RT1)
   #define LED_PWM_YELLOW_RT1_PTR                 ( (reg8 *)  LED_PWM_YELLOW_PWMHW__RT1)

#else
   #if (LED_PWM_YELLOW_Resolution == 8u) /* 8bit - PWM */

       #if(LED_PWM_YELLOW_PWMModeIsCenterAligned)
           #define LED_PWM_YELLOW_PERIOD_LSB      (*(reg8 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define LED_PWM_YELLOW_PERIOD_LSB_PTR  ((reg8 *)   LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define LED_PWM_YELLOW_PERIOD_LSB      (*(reg8 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define LED_PWM_YELLOW_PERIOD_LSB_PTR  ((reg8 *)   LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (LED_PWM_YELLOW_PWMModeIsCenterAligned) */

       #define LED_PWM_YELLOW_COMPARE1_LSB        (*(reg8 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define LED_PWM_YELLOW_COMPARE1_LSB_PTR    ((reg8 *)   LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define LED_PWM_YELLOW_COMPARE2_LSB        (*(reg8 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define LED_PWM_YELLOW_COMPARE2_LSB_PTR    ((reg8 *)   LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define LED_PWM_YELLOW_COUNTERCAP_LSB      (*(reg8 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define LED_PWM_YELLOW_COUNTERCAP_LSB_PTR  ((reg8 *)   LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define LED_PWM_YELLOW_COUNTER_LSB         (*(reg8 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define LED_PWM_YELLOW_COUNTER_LSB_PTR     ((reg8 *)   LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define LED_PWM_YELLOW_CAPTURE_LSB         (*(reg8 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define LED_PWM_YELLOW_CAPTURE_LSB_PTR     ((reg8 *)   LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(LED_PWM_YELLOW_PWMModeIsCenterAligned)
               #define LED_PWM_YELLOW_PERIOD_LSB      (*(reg16 *) LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define LED_PWM_YELLOW_PERIOD_LSB_PTR  ((reg16 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define LED_PWM_YELLOW_PERIOD_LSB      (*(reg16 *) LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define LED_PWM_YELLOW_PERIOD_LSB_PTR  ((reg16 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (LED_PWM_YELLOW_PWMModeIsCenterAligned) */

            #define LED_PWM_YELLOW_COMPARE1_LSB       (*(reg16 *) LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define LED_PWM_YELLOW_COMPARE1_LSB_PTR   ((reg16 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define LED_PWM_YELLOW_COMPARE2_LSB       (*(reg16 *) LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define LED_PWM_YELLOW_COMPARE2_LSB_PTR   ((reg16 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define LED_PWM_YELLOW_COUNTERCAP_LSB     (*(reg16 *) LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define LED_PWM_YELLOW_COUNTERCAP_LSB_PTR ((reg16 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define LED_PWM_YELLOW_COUNTER_LSB        (*(reg16 *) LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define LED_PWM_YELLOW_COUNTER_LSB_PTR    ((reg16 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define LED_PWM_YELLOW_CAPTURE_LSB        (*(reg16 *) LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define LED_PWM_YELLOW_CAPTURE_LSB_PTR    ((reg16 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(LED_PWM_YELLOW_PWMModeIsCenterAligned)
               #define LED_PWM_YELLOW_PERIOD_LSB      (*(reg16 *) LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define LED_PWM_YELLOW_PERIOD_LSB_PTR  ((reg16 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define LED_PWM_YELLOW_PERIOD_LSB      (*(reg16 *) LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define LED_PWM_YELLOW_PERIOD_LSB_PTR  ((reg16 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (LED_PWM_YELLOW_PWMModeIsCenterAligned) */

            #define LED_PWM_YELLOW_COMPARE1_LSB       (*(reg16 *) LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define LED_PWM_YELLOW_COMPARE1_LSB_PTR   ((reg16 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define LED_PWM_YELLOW_COMPARE2_LSB       (*(reg16 *) LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define LED_PWM_YELLOW_COMPARE2_LSB_PTR   ((reg16 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define LED_PWM_YELLOW_COUNTERCAP_LSB     (*(reg16 *) LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define LED_PWM_YELLOW_COUNTERCAP_LSB_PTR ((reg16 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define LED_PWM_YELLOW_COUNTER_LSB        (*(reg16 *) LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define LED_PWM_YELLOW_COUNTER_LSB_PTR    ((reg16 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define LED_PWM_YELLOW_CAPTURE_LSB        (*(reg16 *) LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define LED_PWM_YELLOW_CAPTURE_LSB_PTR    ((reg16 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define LED_PWM_YELLOW_AUX_CONTROLDP1          (*(reg8 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define LED_PWM_YELLOW_AUX_CONTROLDP1_PTR      ((reg8 *)   LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (LED_PWM_YELLOW_Resolution == 8) */

   #define LED_PWM_YELLOW_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define LED_PWM_YELLOW_AUX_CONTROLDP0          (*(reg8 *)  LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define LED_PWM_YELLOW_AUX_CONTROLDP0_PTR      ((reg8 *)   LED_PWM_YELLOW_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (LED_PWM_YELLOW_UsingFixedFunction) */

#if(LED_PWM_YELLOW_KillModeMinTime )
    #define LED_PWM_YELLOW_KILLMODEMINTIME        (*(reg8 *)  LED_PWM_YELLOW_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define LED_PWM_YELLOW_KILLMODEMINTIME_PTR    ((reg8 *)   LED_PWM_YELLOW_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (LED_PWM_YELLOW_KillModeMinTime ) */

#if(LED_PWM_YELLOW_DeadBandMode == LED_PWM_YELLOW__B_PWM__DBM_256_CLOCKS)
    #define LED_PWM_YELLOW_DEADBAND_COUNT         (*(reg8 *)  LED_PWM_YELLOW_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define LED_PWM_YELLOW_DEADBAND_COUNT_PTR     ((reg8 *)   LED_PWM_YELLOW_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define LED_PWM_YELLOW_DEADBAND_LSB_PTR       ((reg8 *)   LED_PWM_YELLOW_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define LED_PWM_YELLOW_DEADBAND_LSB           (*(reg8 *)  LED_PWM_YELLOW_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(LED_PWM_YELLOW_DeadBandMode == LED_PWM_YELLOW__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (LED_PWM_YELLOW_UsingFixedFunction)
        #define LED_PWM_YELLOW_DEADBAND_COUNT         (*(reg8 *)  LED_PWM_YELLOW_PWMHW__CFG0)
        #define LED_PWM_YELLOW_DEADBAND_COUNT_PTR     ((reg8 *)   LED_PWM_YELLOW_PWMHW__CFG0)
        #define LED_PWM_YELLOW_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << LED_PWM_YELLOW_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define LED_PWM_YELLOW_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define LED_PWM_YELLOW_DEADBAND_COUNT         (*(reg8 *)  LED_PWM_YELLOW_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define LED_PWM_YELLOW_DEADBAND_COUNT_PTR     ((reg8 *)   LED_PWM_YELLOW_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define LED_PWM_YELLOW_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << LED_PWM_YELLOW_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define LED_PWM_YELLOW_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (LED_PWM_YELLOW_UsingFixedFunction) */
#endif /* (LED_PWM_YELLOW_DeadBandMode == LED_PWM_YELLOW__B_PWM__DBM_256_CLOCKS) */



#if (LED_PWM_YELLOW_UsingFixedFunction)
    #define LED_PWM_YELLOW_STATUS                 (*(reg8 *) LED_PWM_YELLOW_PWMHW__SR0)
    #define LED_PWM_YELLOW_STATUS_PTR             ((reg8 *) LED_PWM_YELLOW_PWMHW__SR0)
    #define LED_PWM_YELLOW_STATUS_MASK            (*(reg8 *) LED_PWM_YELLOW_PWMHW__SR0)
    #define LED_PWM_YELLOW_STATUS_MASK_PTR        ((reg8 *) LED_PWM_YELLOW_PWMHW__SR0)
    #define LED_PWM_YELLOW_CONTROL                (*(reg8 *) LED_PWM_YELLOW_PWMHW__CFG0)
    #define LED_PWM_YELLOW_CONTROL_PTR            ((reg8 *) LED_PWM_YELLOW_PWMHW__CFG0)
    #define LED_PWM_YELLOW_CONTROL2               (*(reg8 *) LED_PWM_YELLOW_PWMHW__CFG1)
    #define LED_PWM_YELLOW_CONTROL3               (*(reg8 *) LED_PWM_YELLOW_PWMHW__CFG2)
    #define LED_PWM_YELLOW_GLOBAL_ENABLE          (*(reg8 *) LED_PWM_YELLOW_PWMHW__PM_ACT_CFG)
    #define LED_PWM_YELLOW_GLOBAL_ENABLE_PTR      ( (reg8 *) LED_PWM_YELLOW_PWMHW__PM_ACT_CFG)
    #define LED_PWM_YELLOW_GLOBAL_STBY_ENABLE     (*(reg8 *) LED_PWM_YELLOW_PWMHW__PM_STBY_CFG)
    #define LED_PWM_YELLOW_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) LED_PWM_YELLOW_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define LED_PWM_YELLOW_BLOCK_EN_MASK          (LED_PWM_YELLOW_PWMHW__PM_ACT_MSK)
    #define LED_PWM_YELLOW_BLOCK_STBY_EN_MASK     (LED_PWM_YELLOW_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define LED_PWM_YELLOW_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define LED_PWM_YELLOW_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define LED_PWM_YELLOW_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define LED_PWM_YELLOW_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define LED_PWM_YELLOW_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define LED_PWM_YELLOW_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define LED_PWM_YELLOW_CTRL_ENABLE            (uint8)((uint8)0x01u << LED_PWM_YELLOW_CTRL_ENABLE_SHIFT)
    #define LED_PWM_YELLOW_CTRL_RESET             (uint8)((uint8)0x01u << LED_PWM_YELLOW_CTRL_RESET_SHIFT)
    #define LED_PWM_YELLOW_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << LED_PWM_YELLOW_CTRL_CMPMODE2_SHIFT)
    #define LED_PWM_YELLOW_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << LED_PWM_YELLOW_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define LED_PWM_YELLOW_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define LED_PWM_YELLOW_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << LED_PWM_YELLOW_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define LED_PWM_YELLOW_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define LED_PWM_YELLOW_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define LED_PWM_YELLOW_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define LED_PWM_YELLOW_STATUS_TC_INT_EN_MASK_SHIFT            (LED_PWM_YELLOW_STATUS_TC_SHIFT - 4u)
    #define LED_PWM_YELLOW_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define LED_PWM_YELLOW_STATUS_CMP1_INT_EN_MASK_SHIFT          (LED_PWM_YELLOW_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define LED_PWM_YELLOW_STATUS_TC              (uint8)((uint8)0x01u << LED_PWM_YELLOW_STATUS_TC_SHIFT)
    #define LED_PWM_YELLOW_STATUS_CMP1            (uint8)((uint8)0x01u << LED_PWM_YELLOW_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define LED_PWM_YELLOW_STATUS_TC_INT_EN_MASK              (uint8)((uint8)LED_PWM_YELLOW_STATUS_TC >> 4u)
    #define LED_PWM_YELLOW_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)LED_PWM_YELLOW_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define LED_PWM_YELLOW_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define LED_PWM_YELLOW_RT1_MASK              (uint8)((uint8)0x03u << LED_PWM_YELLOW_RT1_SHIFT)
    #define LED_PWM_YELLOW_SYNC                  (uint8)((uint8)0x03u << LED_PWM_YELLOW_RT1_SHIFT)
    #define LED_PWM_YELLOW_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define LED_PWM_YELLOW_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << LED_PWM_YELLOW_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define LED_PWM_YELLOW_SYNCDSI_EN            (uint8)((uint8)0x0Fu << LED_PWM_YELLOW_SYNCDSI_SHIFT)


#else
    #define LED_PWM_YELLOW_STATUS                (*(reg8 *)   LED_PWM_YELLOW_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define LED_PWM_YELLOW_STATUS_PTR            ((reg8 *)    LED_PWM_YELLOW_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define LED_PWM_YELLOW_STATUS_MASK           (*(reg8 *)   LED_PWM_YELLOW_PWMUDB_genblk8_stsreg__MASK_REG)
    #define LED_PWM_YELLOW_STATUS_MASK_PTR       ((reg8 *)    LED_PWM_YELLOW_PWMUDB_genblk8_stsreg__MASK_REG)
    #define LED_PWM_YELLOW_STATUS_AUX_CTRL       (*(reg8 *)   LED_PWM_YELLOW_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define LED_PWM_YELLOW_CONTROL               (*(reg8 *)   LED_PWM_YELLOW_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define LED_PWM_YELLOW_CONTROL_PTR           ((reg8 *)    LED_PWM_YELLOW_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define LED_PWM_YELLOW_CTRL_ENABLE_SHIFT      (0x07u)
    #define LED_PWM_YELLOW_CTRL_RESET_SHIFT       (0x06u)
    #define LED_PWM_YELLOW_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define LED_PWM_YELLOW_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define LED_PWM_YELLOW_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define LED_PWM_YELLOW_CTRL_ENABLE            (uint8)((uint8)0x01u << LED_PWM_YELLOW_CTRL_ENABLE_SHIFT)
    #define LED_PWM_YELLOW_CTRL_RESET             (uint8)((uint8)0x01u << LED_PWM_YELLOW_CTRL_RESET_SHIFT)
    #define LED_PWM_YELLOW_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << LED_PWM_YELLOW_CTRL_CMPMODE2_SHIFT)
    #define LED_PWM_YELLOW_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << LED_PWM_YELLOW_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define LED_PWM_YELLOW_STATUS_KILL_SHIFT          (0x05u)
    #define LED_PWM_YELLOW_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define LED_PWM_YELLOW_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define LED_PWM_YELLOW_STATUS_TC_SHIFT            (0x02u)
    #define LED_PWM_YELLOW_STATUS_CMP2_SHIFT          (0x01u)
    #define LED_PWM_YELLOW_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define LED_PWM_YELLOW_STATUS_KILL_INT_EN_MASK_SHIFT          (LED_PWM_YELLOW_STATUS_KILL_SHIFT)
    #define LED_PWM_YELLOW_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (LED_PWM_YELLOW_STATUS_FIFONEMPTY_SHIFT)
    #define LED_PWM_YELLOW_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (LED_PWM_YELLOW_STATUS_FIFOFULL_SHIFT)
    #define LED_PWM_YELLOW_STATUS_TC_INT_EN_MASK_SHIFT            (LED_PWM_YELLOW_STATUS_TC_SHIFT)
    #define LED_PWM_YELLOW_STATUS_CMP2_INT_EN_MASK_SHIFT          (LED_PWM_YELLOW_STATUS_CMP2_SHIFT)
    #define LED_PWM_YELLOW_STATUS_CMP1_INT_EN_MASK_SHIFT          (LED_PWM_YELLOW_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define LED_PWM_YELLOW_STATUS_KILL            (uint8)((uint8)0x00u << LED_PWM_YELLOW_STATUS_KILL_SHIFT )
    #define LED_PWM_YELLOW_STATUS_FIFOFULL        (uint8)((uint8)0x01u << LED_PWM_YELLOW_STATUS_FIFOFULL_SHIFT)
    #define LED_PWM_YELLOW_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << LED_PWM_YELLOW_STATUS_FIFONEMPTY_SHIFT)
    #define LED_PWM_YELLOW_STATUS_TC              (uint8)((uint8)0x01u << LED_PWM_YELLOW_STATUS_TC_SHIFT)
    #define LED_PWM_YELLOW_STATUS_CMP2            (uint8)((uint8)0x01u << LED_PWM_YELLOW_STATUS_CMP2_SHIFT)
    #define LED_PWM_YELLOW_STATUS_CMP1            (uint8)((uint8)0x01u << LED_PWM_YELLOW_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define LED_PWM_YELLOW_STATUS_KILL_INT_EN_MASK            (LED_PWM_YELLOW_STATUS_KILL)
    #define LED_PWM_YELLOW_STATUS_FIFOFULL_INT_EN_MASK        (LED_PWM_YELLOW_STATUS_FIFOFULL)
    #define LED_PWM_YELLOW_STATUS_FIFONEMPTY_INT_EN_MASK      (LED_PWM_YELLOW_STATUS_FIFONEMPTY)
    #define LED_PWM_YELLOW_STATUS_TC_INT_EN_MASK              (LED_PWM_YELLOW_STATUS_TC)
    #define LED_PWM_YELLOW_STATUS_CMP2_INT_EN_MASK            (LED_PWM_YELLOW_STATUS_CMP2)
    #define LED_PWM_YELLOW_STATUS_CMP1_INT_EN_MASK            (LED_PWM_YELLOW_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define LED_PWM_YELLOW_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define LED_PWM_YELLOW_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define LED_PWM_YELLOW_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define LED_PWM_YELLOW_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define LED_PWM_YELLOW_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* LED_PWM_YELLOW_UsingFixedFunction */

#endif  /* CY_PWM_LED_PWM_YELLOW_H */


/* [] END OF FILE */
