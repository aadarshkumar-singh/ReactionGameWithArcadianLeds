/**
* \file <reactionGame.h>
* \author Aadarsh Kumar Singh <aadarsh.k.singh@stud.h-da.de>
* \date <26.11.2019>
*
* \brief <reactionGame.h>
* Header file for implementation of the state machine for the reaction Game.
* It contains API to process and react to the events which occurs during the
* course of the game.
*/ 
#ifndef REACTIONGAME_H
#define REACTIONGAME_H

#include "project.h"
#include "timer.h"
#include "seven.h"
#include "button.h"
#include "displayLog.h"

/**
 * \brief Enum for states of the Reaction Game State machine (FSM).
 */
typedef enum reactionGameState_e
{
   isIdle,
   isTimeout,
   isButtonPressed,
}reactionGameState_t;

/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/**
 * \brief  API which implements state machine to process and react to events of 
 *         reaction game.
 * @param  event : type<EventMaskType> Events to which the state maschine reacts.
 * @return void 
 * \note   reaction Game has 10 rounds, next round is started by press of a button.  
 */
void processEventReactionGame(EventMaskType event);

/**
 * \brief  API to display welcome message and game rules.
 * @return void 
 */
void displayWelcomeMessage();

/**
 * \brief  API to display messages with mumbers and strings together
 * @param  statements : type <char * const> : the string to be added
 * @param  value: type <int>: Integer number to be added .
 * @return void
 */
void displayMessage(char * const statements, int value);

/**
 * \brief  API to display messages with mumbers and strings together
 * @param  score :    type<uint8_t>  : Number of times button pressed correctly
 * @param  totalTime: type <uint16_t>: Total times for the correct buttons 
 *                    to be pressed in an entire game
 * @return void
 */
void displayScore(uint8_t score, uint16_t totalTime);

#endif /* REACTIONGAME_H */
