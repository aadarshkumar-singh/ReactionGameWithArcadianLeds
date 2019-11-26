/**
* \file <filename>
* \author <author-name>
* \date <date>
*
* \brief <Symbolic File name>
*
* \copyright Copyright ©2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "ledFaderArcadian.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/
typedef enum faderLed_e
{
    LED_RED_STATE,
    LED_GREEN_STATE,
    LED_YELLOW_STATE,
}faderLed_t;


/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/
static int ledWidthCountRed = 0;
static int ledWidthCountGreen = 0;
static int ledWidthCountYellow = 0;
static faderLed_t faderLedState = LED_RED_STATE;

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

void ledArcadianStart()
{
    switch(faderLedState)
    {
     case LED_RED_STATE :      
        if (ledWidthCountRed <= 255)
        {
            LED_PWM_RED_SetPulseWidth(ledWidthCountRed);
            ledWidthCountRed = ledWidthCountRed + INCREMENT_PULSE_WIDTH ;
            
            ledWidthCountGreen = ledWidthCountGreen - INCREMENT_PULSE_WIDTH ;
            if(ledWidthCountGreen >= 0)
            {
            LED_PWM_GREEN_SetPulseWidth(ledWidthCountGreen);    
            }
   
        }
        else
        {
           faderLedState = LED_YELLOW_STATE ; 
           ledWidthCountGreen = 0;
        }
        break;
        
     case LED_YELLOW_STATE :
        if (ledWidthCountYellow <= 255)
        {
            ledWidthCountRed = ledWidthCountRed - INCREMENT_PULSE_WIDTH ;
            if(ledWidthCountRed >= 0)
            {
                LED_PWM_RED_SetPulseWidth(ledWidthCountRed);    
            }
                    
            LED_PWM_YELLOW_SetPulseWidth(ledWidthCountYellow);
            ledWidthCountYellow = ledWidthCountYellow + INCREMENT_PULSE_WIDTH ;
        }
        else
        {
           faderLedState = LED_GREEN_STATE ; 
        }
        
        break;

        case LED_GREEN_STATE :
        if (ledWidthCountGreen <= 255)
        {
            ledWidthCountYellow = ledWidthCountYellow - INCREMENT_PULSE_WIDTH ;
            if(ledWidthCountYellow >= 0)
            {
                LED_PWM_YELLOW_SetPulseWidth(ledWidthCountYellow);
            }
            
            LED_PWM_GREEN_SetPulseWidth(ledWidthCountGreen);
            ledWidthCountGreen = ledWidthCountGreen + INCREMENT_PULSE_WIDTH ;        
        }
        else
        {
           faderLedState = LED_RED_STATE ; 
        }
        break;
    }    
    
}