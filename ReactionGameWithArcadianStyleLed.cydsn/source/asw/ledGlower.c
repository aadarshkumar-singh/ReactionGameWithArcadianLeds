/**
* \file <ledGlower.c>
* \author Aadarsh Kumar Singh <aadarsh.k.singh@stud.h-da.de>
* \date <26.11.2019>
*
* \brief <ledGlower.c>
* Source file for implementation to glow RGB Led in a sequence
* given in the form of glow table.
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "ledGlower.h"
#include "led.h"

//####################### Defines/Macros

/**
 * \brief Length of the glow table for creating RGB Led Glow patterns.
 */    
#define LED_GLOWER_TABLE_LENGTH 9

/**
 * \brief Step size by which the counter of glower is incremented.   
 */
#define LED_GLOWER_COUNT_STEP_VALUE 1
    
/**
 * \brief Scaling factor for the counter of glower 
 */
#define LED_GLOWER_SCALING_FACTOR 5

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/

/**
 * \brief A counter which is incremented with step of LED_GLOWER_COUNT_STEP_VALUE
 *        every 5 ms
 */    
static uint16_t glowerCounter = 0;

/**
 * \brief The pattern to glow the Leds is mentioned in the table below.
 *        The table is of enum type RG__Glow_t.
 */
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

/**
 * \brief  API which Glows the RGB Led in a sequence specified in 
 *         the Glow table(RG_glowtable).
 * @return void 
 * \note   The Task ledFader Calls this API every 5 ms. 
 */
void glowRGBPwmLedInSequence()
{
    static uint8_t index = 0;
    
    /* The counter counts with step of LED_GLOWER_COUNT_STEP_VALUE and can
       never be negative*/    
    if (LED_GLOWER_COUNT_STEP_VALUE > 0)
    {
        glowerCounter = glowerCounter + LED_GLOWER_COUNT_STEP_VALUE;
    }
    else
    {
        glowerCounter = glowerCounter + 1;
    }
    /*
    * Each Value from the glow table is passed to RGB set to create a pattern.
    * Once the max length is reached , index is reset and hence the pattern
    * is repeated again.
    */
    if (index < LED_GLOWER_TABLE_LENGTH)
    {   
        if (((RG_glowtable[index].elapsedTime) / (glowerCounter*LED_GLOWER_SCALING_FACTOR)) == 1)
        {
            LED_RGB_Set(RG_glowtable[index].rgbRedPwmVal,RG_glowtable[index].rgbGreenPwmVal,RG_glowtable[index].rgbBluePwmVal);
            glowerCounter = 0;
            index++;
        }      
    }
    else
    {
     index = 0;   
    }   
}