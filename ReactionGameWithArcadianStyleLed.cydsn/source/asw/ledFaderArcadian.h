/**
* \file <ledFaderArcadian.h>
* \author Aadarsh Kumar Singh <aadarsh.k.singh@stud.h-da.de>
* \date <26.11.2019>
*
* \brief <ledFaderArcadian.h>
* Header file for implementation of Led Fader Sequence in Arcadian Style.
* Leds Red, Yellow and Green produce Arcadian LED Fader Pattern
* using PWM.  
*/
 
#ifndef LEDFADERARCADIAN_H
#define LEDFADERARCADIAN_H

#include "led.h"

//####################### Defines/Macros
    
/**
 * \brief Step Size to increment the Pulse width value supplied to Leds.
 */
#define LED_INCREMENT_PULSE_WIDTH 1 

/**
 * \brief Expiry time of cyclic Fader Alarm
 */
#define FADER_ALARM_EXPIRE_TIME 5    

//####################### Enumerations
    
/**
 * \brief Enum for type of Fader Leds
 */    
typedef enum faderLed_e
{
    LED_PWM_RED,    //!< Red Fader Led connected to PWM
    LED_PWM_GREEN,  //!< Green Fader Led connected to PWM
    LED_PWM_YELLOW, //!< Yellow Fader Led connected to PWM
}faderLed_t;

/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/**
 * \brief  API which implements the pattern for Arcadian Style Led Fader.
 * @return void 
 * \note   The Task led Fader Calls this API every 5 ms. 
 */
void ledArcadianStart();

/**
 * \brief  sets a given Pulse width value to a Led specified in the parameter 
 * @param  faderLedType : type<faderLed_t> Enum for type of Led Fader
 * @param  ledPulseWidthValue : The Pulse width value to be set in given Led 
 * @return void 
 * \note   maximum led value 65535 minimum led value is 0.
 *         Supported for red,yellow,green Led.
 */
void led_PWM(faderLed_t faderLedType,int ledPulseWidthValue);

#endif /* LEDFADERARCADIAN_H */
