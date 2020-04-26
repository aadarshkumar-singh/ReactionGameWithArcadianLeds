/**
* \file <timer.c>
* \author Aadarsh Kumar Singh <aadarsh.k.singh@stud.h-da.de>
* \date <26.11.2019>
*
* \brief <timer.c>
* Source file for implementation of 1 ms timer. One can set timer,
* reset timer, increment timer ticks , and check if timeout has occured
* or not.
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "timer.h"

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/

/**
 * \brief  Stores the timer value to be set
 */
static uint16_t timeTobeSet = 0;

/**
 * \brief  Stores the timer count
 */
static uint16_t timerCount = 0;

/**
 * \brief  API to set the timer value.
 * @param  setTime : type<uint16_t> timer value to be set
 * @return void 
 */
void setTimerValue(uint16_t setTime)
{
    timeTobeSet = setTime;
}

/**
 * \brief  API to increment the timer value.
 * @param  <none>
 * @return void 
 */
void incrementTimerValue()
{
    ++timerCount;    
}

/**
 * \brief  API to reset the timer Value
 * @param  <none>
 * @return void 
 */
void resetTimerValue()
{
    timerCount = 0 ;
}

/**
 * \brief  API checks if timeout has occured , it checks if current ticks
 *         exceeds the time value which is set by using setTimerValue
 * @param  <none>
 * @return uint16_t 1 : If time out has occured
 *                  0 : If time out has not occured
 */
uint8_t timeOutOccured()
{
   if (timerCount == timeTobeSet)
        return 1 ;
    else
        return 0;
}

/**
 * \brief  API to get the current timer ticks
 * @param  <none>
 * @return uint16_t
 */
uint16_t getTimerValue()
{
    return timerCount ;
}