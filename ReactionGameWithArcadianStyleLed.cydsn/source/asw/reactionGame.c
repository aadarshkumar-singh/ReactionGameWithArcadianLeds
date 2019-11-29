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
#include "reactionGame.h"
#include <stdlib.h>
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



/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/
static char displayInt[10];
/**
 * <Description>
 * @param <first para>
 * @return <return value>
 */
void processEventReactionGame(EventMaskType event, uint8_t pressedButton)
{
    static reactionGameState_t state = isIdle;
    static uint8_t gameRounds = 0;
    static uint16_t randomTime = 0;
    static uint8_t displayValue = 0 ;
    static uint16_t totalTime = 0;
    static uint16_t averageTime = 0;
    static uint16_t timePerRound = 0;
    static uint8_t score = 0;
    switch(state)
    {
        case isIdle :
            if (event & ev_Button)
            {
                ++gameRounds;
                itoa(gameRounds,displayInt,10);
                displayLog_PrintString("\nRound::");
                displayLog_PrintString(displayInt);
                randomTime = getTimerValue();
                setTimerValue((randomTime % 2000)+ 500);
                resetTimerValue();             
                state = isTimeout ;     
            }
            break;
                
        case isTimeout:
            if (event & ev_Timeout)
            {
                if (randomTime % 2 == 0)
                {
                    displayValue = 2;        
                }
                else
                {
                    displayValue = 1;
                }
                SEVEN_SetHex(displayValue);
                setTimerValue(1000);
                resetTimerValue();                
                state =isButtonPressed ;
            }
            break;
            
        case isButtonPressed:
            if (event & ev_Button && pressedButton == displayValue && gameRounds<=10)
            {
                ++score ;
                timePerRound = getTimerValue();
                totalTime =totalTime + timePerRound ;
                itoa(timePerRound,displayInt,10);
                displayLog_PrintString("\nCorrect button Pressed, Elapsed time::");
                displayLog_PrintString(displayInt);
            }
            else if (event & ev_Button && pressedButton !=displayValue && gameRounds<=10)
            {
                displayLog_PrintString("\n InCorrect button Pressed");
            }
            else if(event & ev_Timeout && gameRounds<=10)
            {
                displayLog_PrintString("\n Too Slow:: Did not press button in 1 second");
            }
            else if(gameRounds == 11)
            {
                averageTime = totalTime/10 ;
                displayLog_PrintString("\n Score out of 10 got ");
                itoa(score,displayInt,10);
                displayLog_PrintString(displayInt);
                itoa(totalTime,displayInt,10);
                displayLog_PrintString("\n Total Time ::> ");
                displayLog_PrintString(displayInt);
                itoa(averageTime,displayInt,10);
                displayLog_PrintString("\n Average Time ::>");
                displayLog_PrintString(displayInt);
            }
            displayLog_PrintString("\n\nRound Over, press any button ::");
            displayValue = 0;
            SEVEN_SetHex(displayValue);
            state = isIdle;
            
            break;                
    }       
}
