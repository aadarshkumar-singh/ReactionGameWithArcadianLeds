/**
* \file <timer.h>
* \author Aadarsh Kumar Singh <aadarsh.k.singh@stud.h-da.de>
* \date <26.11.2019>
*
* \brief <timer.h>
* Header file for implementation of 1 ms timer. One can set timer,
* reset timer, increment timer ticks , and check if timeout has occured
* or not.
*/

#ifndef TIMER_H
#define TIMER_H

#include "global.h"
    
/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

//####################### Defines/Macros
/** 
 * \brief Macro to define the expire time for the Cyclic Alarm (alarm_Timer)
          to trigger every 1 ms
 */
#define ONE_MS_TIMER 1    

/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/


/**
 * \brief  API to set the timer value.
 * @param  setTime : type<uint16_t> timer value to be set
 * @return void 
 */    
void setTimerValue(uint16_t setTime);

/**
 * \brief  API to increment the timer value.
 * @param  <none>
 * @return void 
 */
void incrementTimerValue();

/**
 * \brief  API to reset the timer Value
 * @param  <none>
 * @return void 
 */
void resetTimerValue();

/**
 * \brief  API to get the current timer ticks
 * @param  <none>
 * @return uint16_t
 */
uint16_t getTimerValue();

/**
 * \brief  API checks if timeout has occured , it checks if current ticks
 *         exceeds the time value which is set by using setTimerValue
 * @param  <none>
 * @return uint16_t 1 : If time out has occured
 *                  0 : If time out has not occured
 */
uint8_t timeOutOccured();

#endif /* TIMER_H */
