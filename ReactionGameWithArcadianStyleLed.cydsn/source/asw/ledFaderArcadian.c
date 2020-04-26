/**
* \file <ledFaderArcadian.c>
* \author Aadarsh Kumar Singh <aadarsh.k.singh@stud.h-da.de>
* \date <26.11.2019>
*
* \brief <ledFaderArcadian.c>
* Source file for implementation of Led Fader Sequence in Arcadian Style.
* Leds Red, Yellow and Green produce Arcadian LED Fader Pattern
* using PWM.  
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "ledFaderArcadian.h"

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/

/**
 * \brief A counter which is incremented with step of LED_INCREMENT_PULSE_WIDTH
 *        every 5 ms
 */
static int arcadianCounter = 0;

/**
 * \brief  API which implements the pattern for Arcadian Style Led Fader.
 * @return void 
 * \note   The Task ledFader Calls this API every 5 ms. 
 */
void ledArcadianStart()
{
    /* The counter counts with step of LED_INCREMENT_PULSE_WIDTH and can
       never be negative*/
    if (LED_INCREMENT_PULSE_WIDTH > 0)
    {
        arcadianCounter = arcadianCounter + LED_INCREMENT_PULSE_WIDTH ;    
    }
    else
    {
        arcadianCounter = arcadianCounter + 1 ;
    }
   
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

/**
 * \brief  sets a given Pulse width value to a Led specified in the parameter 
 * @param  faderLedType : type<faderLed_t> Enum for type of Led Fader
 * @param  ledPulseWidthValue : The Pulse width value to be set in given Led 
 * @return void 
 * \note   maximum led value 65535 minimum led value is 0.
 *         Supported for red,yellow,green Led.
 */
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