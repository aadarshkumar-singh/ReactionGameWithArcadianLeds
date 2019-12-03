/**
* \file <reactionGame.c>
* \author Aadarsh Kumar Singh <aadarsh.k.singh@stud.h-da.de>
* \date <26.11.2019>
*
* \brief <reactionGame.c>
* Source file for implementation of the state machine for the reaction Game.
* It contains API to process and respond to the events which is set during the
* course of the game.
* 
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

/**
 * \brief Buffer to store integer numbers as string.
 */
static char displayInt[10];

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * \brief  API which implements state machine to process and react to events of 
 *         reaction game.
 * @param  event : type<EventMaskType> Events to which the state maschine reacts.
 * @param  pressedButton : The information about the button pressed by the user.
 * @return void 
 * \note   reaction Game has 10 rounds, next round is started by press of a button.  
 */
void processEventReactionGame(EventMaskType event)
{
    static reactionGameState_t state = isIdle;
    static uint8_t gameRounds = 0;
    static uint16_t randomTime = 0;
    static uint8_t displayValue = 0 ;
    static uint16_t totalTime = 0;
    static uint16_t timePerRound = 0;
    static uint8_t score = 0;

    switch(state)
    {
        case isIdle :
            if (event & ev_Button)
            {
                ++gameRounds;
                displayLog_PrintString("\nPress displayed button");
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
            
            if (gameRounds <=10)
            {   
                displayMessage("\n\nRound",gameRounds);                
                if (event & ev_Button &&  getPressedButton() == displayValue)
                {
                    ++score ;
                    timePerRound = getTimerValue();
                    totalTime =totalTime + timePerRound ;
                    displayMessage("\nCorrect button,\nElapsed time:",timePerRound);
                }
                else if (event & ev_Button && getPressedButton() !=displayValue)
                {
                    displayLog_PrintString("\nInCorrect button");
                }
                else if(event & ev_Timeout)
                {
                    displayLog_PrintString("\nToo Slow");
                }
                
                if (gameRounds == 10)
                {
                    gameRounds = 0;
                    displayScore(score, totalTime);
                    score =0;
                    totalTime =0;
                    displayLog_PrintString("\nPress button to restart GAME");                    
                }
                else
                {
                    displayLog_PrintString("\nPress button for next round");
                }                
            }          
            displayValue = 0;
            SEVEN_SetHex(displayValue);
            state = isIdle;
            break;                
    }       
}

void displayWelcomeMessage()
{
  displayLog_PrintString("\nWelcome to The Reaction Game with Arcadian Style"
                         "\n=================================================="
                         "\nPlayer has to press Correct button displayed on"
                         " Seven Segment Display Within 1 second"
                         "\nA game has 10 rounds , Score and reaction time will"
                         " be displayed at the end of the game"
                         "\n=================================================="
                         "\nPress any Button to start"); 
}

void displayMessage(char * const statements, int value)
{
    displayLog_PrintString(statements);
    itoa(value,displayInt,10);
    displayLog_PrintString(displayInt);    
}

void displayScore(uint8_t score, uint16_t totalTime)
{    
    displayMessage("\nScore: ",score);
    displayMessage("\nTotal Time(ms) for right button press: ",totalTime);
    if (score ==0)
    {
        displayMessage("\n Average Time: ",0);    
    }
    else
    {
        displayMessage("\n Average Time(ms): ",(totalTime/score));
    }
}