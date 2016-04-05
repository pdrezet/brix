/** @file hal_console.h
 * In this file, all of the hardware abstraction layer declarations provided for EHS console I/O are given.
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 1120 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_HAL_CONSOLE_H
#define EHS_HAL_CONSOLE_H

/*****************************************************************************/
/* Included files */

#include "console_queue.h"
#include "target_types.h"
#include "target_console.h"

/*****************************************************************************/
/* Define macros  */


/*****************************************************************************/
/* Define types */


/*****************************************************************************/
/* Declare global variables */

/*****************************************************************************/
/* Declare function prototypes  */


/**
 * Read a line of text from the console up to the specified size.
 * Returned text includes the terminating \n.
 * This function only returns content if an entire line has been read
 * (i.e. if a \n is available). Partially received lines are buffered
 * until the end of line character has been received).
 *
 * @param buff Buffer to read the line into. Must be at least "size" long
 * @param size Size of buff
 * @return number of characters read (or zero if no line is available)
 */
EHS_GLOBAL ehs_uint32 EhsConsoleGetLine(ehs_char *buff, ehs_uint16 size);

/**
 * Print text into the console output. This function blocks as long
 * as necessary to send the output.
 *
 * @param fmt Format specifier for output (as per printf)
 */
#ifndef EhsConsolePrintf
EHS_GLOBAL ehs_uint16 EhsConsolePrintf(const ehs_char* fmt, ...); /*lint !e960 Variable arguments required to support generalized printf */
#endif

/**
 * Check whether console input is available
 *
 * @return true if one or more characters is available
 */
EHS_GLOBAL ehs_bool EhsConsoleInputHit(void);

/**
 * Check whether a complete line is available for reading
 *
 * @return true if a line is available
 */
EHS_GLOBAL ehs_bool EhsConsoleLineReady(void);

/**
 * Read a file from the console input into persistent storage.
 *
 * @param size Size to download. If zero, we don't know how big it is
 * keep inputting until there is at least 10 seconds where no input has
 * been received.
 * @param name Name to store file as. This will conform to the EHS filename
 * standard (i.e. 8.3 with leading letter, only letters and digits)
 *
 * @return true if load is successful
 */
EHS_GLOBAL ehs_bool EhsConsoleLoadFile(ehs_uint32 size, const ehs_char* name);

/**
 * Contains input from the console.
 * Initialised by EhsSystemInit
 */
EHS_GLOBAL EhsConsoleQueueType* EhsTgtConsoleInputQueueRef;

/**
 * Contains output to the console
 * Initialised by EhsSystemInit
 */
EHS_GLOBAL EhsConsoleQueueType* EhsTgtConsoleOutputQueueRef;

#endif /* EHS_HAL_CONSOLE_H */
