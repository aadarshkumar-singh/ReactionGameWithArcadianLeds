/**
* \file <displayLog.c>
* \author Aadarsh Kumar Singh <aadarsh.k.singh@stud.h-da.de>
* \date <26.11.2019>
*
* \brief <displayLog.c>
* Driver Source File for UART peripheral to print the Debug Logs/ Messages to the user
* Only Char and string is supported to be printed via UART.
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "displayLog.h"

/**
 * \brief  API To initialize and start UART Communication
 * @param  <None>
 * @return void 
 */
void displayLog_Start()
{
    UART_LOG_Start();
}

/**
 * \brief  API to stop UART communication
 * @param  <None>
 * @return void 
 */
void displayLog_Stop()
{
    UART_LOG_Stop();   
}

/**
 * \brief  API to print string messages via UART.
 * @param  <None>
 * @return void 
 */
void displayLog_PrintString(char * const statements)
{
    UART_LOG_PutString(statements);
}

/**
 * \brief  API to print charecter message via UART.
 * @param  <None>
 * @return void 
 */
void displayLog_PrintChar(uint8_t value)
{
    UART_LOG_PutChar(value);
}