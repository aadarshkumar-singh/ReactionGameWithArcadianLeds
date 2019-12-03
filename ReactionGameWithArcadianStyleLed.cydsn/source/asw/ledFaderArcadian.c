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
#define MIN_RANGE_RED_LIGHT 0
#define MAX_RANGE_RED_LIGHT 255
#define MIN_RANGE_YELLOW_LIGHT 255
#define MAX_RANGE_YELLOW_LIGHT 510
#define MIN_RANGE_GREEN_LIGHT 510
#define MAX_RANGE_GREEN_LIGHT 765
#define MAXIMUM_COUNTER_VALUE 1020
/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/
static int arcadianCounter = 0;

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

void ledArcadianStart()
{
    arcadianCounter = arcadianCounter + ARCADIAN_LED_INCREMENT_PULSE_WIDTH ;
    
    if ((arcadianCounter > 0)  &&  (arcadianCounter <=255))
    {
    led_PWM(LED_PWM_RED,arcadianCounter);  
    }
    else if ((arcadianCounter > 255)  &&  (arcadianCounter <=510))
    {
      led_PWM(LED_PWM_RED,(510 - arcadianCounter));
      led_PWM(LED_PWM_YELLOW,arcadianCounter-255);
    }
    else if ((arcadianCounter > 510)  &&  (arcadianCounter <=765))
    {
      led_PWM(LED_PWM_YELLOW,(765 - arcadianCounter));
      led_PWM(LED_PWM_GREEN,arcadianCounter-510);        
    }
    else if ((arcadianCounter > 765) && (arcadianCounter <=1020))
    {
      led_PWM(LED_PWM_GREEN,(1020 - arcadianCounter)); 
      led_PWM(LED_PWM_RED,arcadianCounter-765);
    }
    else
    {
      arcadianCounter = 256;   
    }    
}

void led_PWM(faderLed_t faderLedType, int ledPulseWidthValue )
{
    switch(faderLedType)
    {
        case LED_PWM_RED : 
            LED_PWM_RED_SetPulseWidth(ledPulseWidthValue);
            break;
        
        case LED_PWM_YELLOW :
            LED_PWM_YELLOW_SetPulseWidth(ledPulseWidthValue);
            break;
        
        case LED_PWM_GREEN :
            LED_PWM_GREEN_SetPulseWidth(ledPulseWidthValue);
            break;
    }
}