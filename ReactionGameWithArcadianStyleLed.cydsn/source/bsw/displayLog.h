/**
* \file <displayLog.h>
* \author Aadarsh Kumar Singh <aadarsh.k.singh@stud.h-da.de>
* \date <26.11.2019>
*
* \brief <displayLog.h>
* Driver Header File for UART peripheral to print the Debug Logs/ Messages to the user
* Only Char and string is supported to be printed via UART.
*/

#ifndef DISPLAYLOG_H
#define DISPLAYLOG_H

#include "UART_LOG.h"
    
//####################### Defines/Macros
/** 
 * \brief a brief description of what the define is representing
*
* If needed, a more detailed description can be given below */

//####################### Enumerations
/**
* \brief Enumerations. Use brief, otherwise the index won't have a brief explanation.
*
* Detailed explaination of the enumeration.
*/

//####################### Structures
/**
* \brief The purpose as well as the members of a structure have to be documented.
*
* Make clear what the structure is used for and what is the purpose of the members.
*/


/*****************************************************************************/
/* Extern global variables                                                   */
/*****************************************************************************/

/**
 * <description>
 */


/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/**
 * \brief  API To initialize and start UART Communication
 * @param  <None>
 * @return void 
 */   
void displayLog_Start();

/**
 * \brief  API to stop UART communication
 * @param  <None>
 * @return void 
 */
void displayLog_Stop();

/**
 * \brief  API to print string messages via UART.
 * @param  <None>
 * @return void 
 */
void displayLog_PrintString(char * const statements) ;

/**
 * \brief  API to print charecter message via UART.
 * @param  <None>
 * @return void 
 */
void displayLog_PrintChar(uint8_t value);

#endif /* DISPLAYLOG_H */
