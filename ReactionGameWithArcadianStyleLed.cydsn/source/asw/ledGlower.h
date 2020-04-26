/**
* \file <ledGlower.h>
* \author Aadarsh Kumar Singh <aadarsh.k.singh@stud.h-da.de>
* \date <26.11.2019>
*
* \brief <ledGlower.h>
* Source file for implementation to glow RGB Led in a sequence
* given in the form of glow table.
*/

#ifndef LEDGLOWER_H
#define LEDGLOWER_H

#include "global.h"    

/**
 * \brief Structure to define the Glow table for
 *        the RGB led to create glowing pattern.
 */    
typedef struct
{
    uint8_t rgbRedPwmVal;   //!< Pulse Width Value of Red in RGB Led.
    uint8_t rgbGreenPwmVal; //!< Pulse Width Value of Green in RGB Led.
    uint8_t rgbBluePwmVal;  //!< Pulse Width Value of Blue in RGB Led.
    uint16_t elapsedTime;
}RG__Glow_t;
    
/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/**
 * \brief  API which Glows the RGB Led in a sequence specified in the 
 *         Glow table(RG_glowtable).
 * @return void 
 * \note   The Task ledFader Calls this API every 5 ms. 
 */
void glowRGBPwmLedInSequence();

#endif /* LEDGLOWER_H */
