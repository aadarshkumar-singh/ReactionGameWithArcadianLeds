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
#include "ledGlower.h"
#include "led.h"
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
const RG__Glow_t RG_glowtable[LED_GLOWER_TABLE_LENGTH] = 
    {
        //Red Green Blue TimeInMS
        {255, 0, 0, 500},
        {0, 255, 0, 500},
        {0, 0, 255, 500},
        {0, 0, 0, 100},
        {255, 255, 255, 100},
        {0, 0, 0, 100},
        {255, 255, 255, 100},
        {0, 0, 0, 100},
        {255, 255, 255, 100}
    };

static uint16_t glowerCounter = 0;

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/
/*
 * Triggered by a Task Led fader which is triggered every 5ms
 */
void glowRGBPwmLedInSequence()
{
    glowerCounter = glowerCounter + LED_GLOWER_COUNT_STEP_VALUE;
    static uint8_t index = 0;
    
    
    if (index < LED_GLOWER_TABLE_LENGTH)
    {   //ToDo: Error Handling of division, Step value can never be zero
        //Also the Multiplying factor will also change if step changes
        if (((RG_glowtable[index].elapsedTime) / (glowerCounter*5)) == 1)
        {
            LED_RGB_Set(RG_glowtable[index].rgbRedPwmVal,RG_glowtable[index].rgbYellowPwmVal,RG_glowtable[index].rgbGreenPwmVal);
            glowerCounter = 0;
            index++;
        }      
    }
    else
    {
     index = 0;   
    }
    
       
}