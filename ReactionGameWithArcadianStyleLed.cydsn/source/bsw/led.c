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

#include "project.h"
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


static LED_ONOFF_t LED__state[LED_ALL] = {LED_OFF, LED_OFF, LED_OFF}; /**< On/Off State of the LED, TRUE is on */

const static uint16 LED__Pulse_Width[256] = {
    0,256,512,768,1024,1280,1536,1792,2048,
2304,2560,2816,3072,3328,3584,3840,4096,
4352,4608,4864,5120,5376,5632,5888,6144,
6400,6656,6912,7168,7424,7680,7936,8192,
8448,8704,8960,9216,9472,9728,9984,10240,
10496,10752,11008,11264,11520,11776,12032,
12288,12544,12800,13056,13312,13568,13824,
14080,14336,14592,14848,15104,15360,15616,
15872,16128,16384,16640,16896,17152,17408,
17664,17920,18176,18432,18688,18944,19200,
19456,19712,19968,20224,20480,20736,20992,
21248,21504,21760,22016,22272,22528,22784,
23040,23296,23552,23808,24064,24320,24576,
24832,25088,25344,25600,25856,26112,26368,
26624,26880,27136,27392,27648,27904,28160,
28416,28672,28928,29184,29440,29696,29952,
30208,30464,30720,30976,31232,31488,31744,
32000,32256,32512,32768,33024,33280,33536,
33792,34048,34304,34560,34816,35072,35328,
35584,35840,36096,36352,36608,36864,37120,
37376,37632,37888,38144,38400,38656,38912,
39168,39424,39680,39936,40192,40448,40704,
40960,41216,41472,41728,41984,42240,42496,
42752,43008,43264,43520,43776,44032,44288,
44544,44800,45056,45312,45568,45824,46080,
46336,46592,46848,47104,47360,47616,47872,
48128,48384,48640,48896,49152,49408,49664,
49920,50176,50432,50688,50944,51200,51456,
51712,51968,52224,52480,52736,52992,53248,
53504,53760,54016,54272,54528,54784,55040,
55296,55552,55808,56064,56320,56576,56832,
57088,57344,57600,57856,58112,58368,58624,
58880,59136,59392,59648,59904,60160,60416,
60672,60928,61184,61440,61696,61952,62208,
62464,62720,62976,63232,63488,63744,64000,
64256,64512,64768,65024,65280
};

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

/**
 * Inverts the parameter
 * @param LED_ONOFF_t ledOnOff - Value to be inverted
 * @return inverted parameter
 */
static inline LED_ONOFF_t LED__toggleValue(LED_ONOFF_t ledOnOff);


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * Initialises the LED's and turns them off
 * @return RC_SUCCESS if function was executed as exepected, other error code in case of error
 */
RC_t LED_Init()
{
    RC_t result = RC_SUCCESS;
    
    for (LED_id_t i = LED_RED; i < LED_ALL; i++)
    {
        LED__state[i] = OFF;
        
        RC_t clearResult;
        clearResult = LED_Set(i, LED_OFF);
        
        if (clearResult != RC_SUCCESS)
        {
            //memorize error
            result = clearResult;
        }
    }
    
    //Init RGB
    RGB_PWM_blue_Start();
    RGB_PWM_green_Start();
    RGB_PWM_red_Start();
    LED_PWM_RED_Start();
    LED_PWM_GREEN_Start();
    LED_PWM_YELLOW_Start();
    
    return result;
}

/**
 * Sets the required LED
 * @param LED_t ledId - Identifier for the LED, ALL will change all LED's
 * @param LED_ONOFF_t ledOnOff - Trun the led on or off
 * @return RC_SUCCESS if function was executed as exepected, other error code in case of error
 */
RC_t LED_Set(LED_id_t ledId, LED_ONOFF_t ledOnOff)
{
    //set individual LED
    switch (ledId)
    {
        case LED_RED : 
            LED_red_Write(ledOnOff); 
            LED__state[ledId] = ledOnOff; 
            break;
        
        case LED_YELLOW : 
            LED_yellow_Write(ledOnOff); 
            LED__state[ledId] = ledOnOff;
            break;
            
        case LED_GREEN : 
            LED_green_Write(ledOnOff); 
            LED__state[ledId] = ledOnOff;
            break;
           
        case LED_ALL : 
            for (LED_id_t i = LED_RED; i < LED_ALL; i++)
            {
                LED_Set(i, ledOnOff);
            }
            break;
        default: return RC_ERROR_BAD_PARAM;
    }
    
    return RC_SUCCESS;
}



/**
 * Toggle the required LED
 * @param LED_t ledId - Identifier for the LED, ALL will change all LED's
 * @return RC_SUCCESS if function was executed as exepected, other error code in case of error
 */
RC_t LED_Toggle(LED_id_t ledId)
{
    //set individual LED
    switch (ledId)
    {
        case LED_RED : 
            LED__state[ledId] = LED__toggleValue(LED__state[ledId]); 
            LED_red_Write(LED__state[ledId]);
            break;
        
        case LED_YELLOW : 
            LED__state[ledId] = LED__toggleValue(LED__state[ledId]); 
            LED_yellow_Write(LED__state[ledId]);
            break;
            
        case LED_GREEN : 
            LED__state[ledId] = LED__toggleValue(LED__state[ledId]); 
            LED_green_Write(LED__state[ledId]);
            break;
           
        case LED_ALL : 
            for (LED_id_t i = LED_RED; i < LED_ALL; i++)
            {
                LED_Toggle(i);
            }
            break;
        default: return RC_ERROR_BAD_PARAM;
    }
    
    return RC_SUCCESS;
}


/**
 * Inverts the parameter
 * @param LED_ONOFF_t ledOnOff - Value to be inverted
 * @return inverted parameter
 */
static inline LED_ONOFF_t LED__toggleValue(LED_ONOFF_t ledOnOff)
{
    if (ledOnOff == LED_ON) 
    {
        return LED_OFF;
    }
    else
    {
        return LED_ON;
    }
}

/**
 * Set the RGB LED
 * @param uint16_t red - brightness 
 * @param uint16_t green - brightness 
 * @param uint16_t blue - brightness 
 * @return RC_SUCCESS if function was executed as exepected, other error code in case of error
 */
RC_t LED_RGB_Set(uint8_t red, uint8_t green, uint8_t blue)
{
    RGB_PWM_red_WriteCompare(LED__Pulse_Width[red]);
    RGB_PWM_green_WriteCompare(LED__Pulse_Width[green]);
    RGB_PWM_blue_WriteCompare(LED__Pulse_Width[blue]);
 
    return RC_SUCCESS;
}

/**
 * \brief Set the Pulse width of Red Led
 * @param uint8_t compareCount - Brightness of red Led
 * @return RC_SUCCESS if function was executed as exepected, other error code in case of error
 */
RC_t LED_PWM_RED_SetPulseWidth(uint8_t compareCount)
{
    LED_PWM_RED_WriteCompare(LED__Pulse_Width[compareCount]);

    return RC_SUCCESS;
}

/**
 * \brief Set the Pulse width of Green Led
 * @param uint8_t compareCount - Brightness of Green Led
 * @return RC_SUCCESS if function was executed as exepected, other error code in case of error
 */
RC_t LED_PWM_GREEN_SetPulseWidth(uint8_t compareCount)
{
    LED_PWM_GREEN_WriteCompare(LED__Pulse_Width[compareCount]);
    
    return RC_SUCCESS;    
}

/**
 * \brief Set the Pulse width of Yellow Led
 * @param uint8_t compareCount - Brightness of Yellow Led
 * @return RC_SUCCESS if function was executed as exepected, other error code in case of error
 */
RC_t LED_PWM_YELLOW_SetPulseWidth(uint8_t compareCount)
{
    LED_PWM_YELLOW_WriteCompare(LED__Pulse_Width[compareCount]);
    return RC_SUCCESS;
}