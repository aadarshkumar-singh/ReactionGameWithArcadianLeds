/**
* \file <reactionGame.c>
* \author Aadarsh Kumar Singh <aadarsh.k.singh@stud.h-da.de>
* \date <26.11.2019>
*
* \brief <reactionGame.c>
* Source file for implementation of the state machine for the reaction Game.
* It contains API to process and react to the events which occurs during the
* course of the game.
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "reactionGame.h"
#include <stdlib.h>


/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/

/**
 * \brief Buffer to store integer numbers as string.
 */
static char displayInt[10];


/**
 * \brief  API which implements state machine to process and react to events of 
 *         reaction game.
 * @param  event : type<EventMaskType> Events to which the state maschine reacts.
 * @return void 
 * \note   reaction Game has 10 rounds, next round is started by press of a button.  
 */
void processEventReactionGame(EventMaskType event)
{
    static reactionGameState_t state = isIdle; /* state of the game */
    static uint8_t gameRounds = 0;             /* Number of Rounds in game */
    static uint16_t randomTime = 0;      /* Random time for which it waits before it displays number (1/2)*/   
    static uint8_t displayValue = 0 ;    /* Random Value to be displayed on Seven Segment Display*/
    static uint16_t totalTime = 0;       /* Total time taken for correct button press in entire game */
    static uint16_t timePerRound = 0;    /* Time taken for correct button Press in a round*/
    static uint8_t score = 0;            /* Number of times correct button is pressed*/

    switch(state)
    {
        /*
         * Waits for button Press to start a round of Reaction Game
         * on button press starts a random Timer between 1s to 3s.
         */
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
        /*
         * Waits for Random wait time to expire
         * On random wait time expiry , displays randomly either 1 or 2
         * on both Seven segment displays
         */            
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
        /*
         * Waits for button to be pressed by user
         * If button pressed within 1 sec , checks if correct/incorrect.
         * else displays too slow.
         * Displays Score , total time and average time in the end of game.
         */            
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

/**
 * \brief  API to display welcome message and game rules.
 * @return void 
 */
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

/**
 * \brief  API to display messages with mumbers and strings together
 * @param  statements : type <char * const> : the string to be added
 * @param  value: type <int>: Integer number to be added .
 * @return void
 */
void displayMessage(char * const statements, int value)
{
    displayLog_PrintString(statements);
    itoa(value,displayInt,10);
    displayLog_PrintString(displayInt);    
}

/**
 * \brief  API to display messages with mumbers and strings together
 * @param  score :    type<uint8_t>  : Number of times button pressed correctly
 * @param  totalTime: type <uint16_t>: Total times for the correct buttons 
 *                    to be pressed in an entire game
 * @return void
 */
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