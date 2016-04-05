/** @file hal_file.h
 * In this file, all of the hardware abstraction layer declarations relating to file handling are given.
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 1120 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

/**
 * @page Verification Verification report
 * @section hal_file_h
 * @anchor hal_file_h
 * @subsection misra MISRA compliance:
 * Demonstrated MISRA compliant on 
 * Last modified on $Date$
 *
 * This file contained the following derogations to the MISRA standard.
 * - Rule 16.1 Functions shall not have variable number of arguments. Required for target library functions.
 */

#ifndef EHS_HAL_FILE_H
#define EHS_HAL_FILE_H

/*****************************************************************************/
/* Included files */
#include "target_file.h"
#include "ehs_types.h"

/*****************************************************************************/
/* Define macros  */

/*****************************************************************************/
/* Define types */

/* ehs_FILE is defined in target_file.h */

/*****************************************************************************/
/* Declare global variables */

/*****************************************************************************/
/* Declare function prototypes  */

/* within target_file.h, file functions are normally #def'd to their stdio equivalents.
 * If the target cannot use the stdio version, the #define is removed from target_file,
 * and the below function is used. The declarations below also provide a secondary
 * purpose - they show the prototype of the function in question.
 */
 
#ifndef EhsFopen
EHS_GLOBAL ehs_FILE *EhsFopen(const ehs_char* fname, const ehs_char* fmode);
#endif

#ifndef EhsFread
EHS_GLOBAL ehs_sint16 EhsFread(void* pBuff, ehs_uint16 nSize, ehs_uint16 nCount, ehs_FILE* f);
#endif

#ifndef EhsFwrite
EHS_GLOBAL ehs_sint16 EhsFwrite(void* pBuff, ehs_uint16 nSize, ehs_uint16 nCount, ehs_FILE* f);
#endif

#ifndef EhsFclose
EHS_GLOBAL ehs_sint16 EhsFclose(ehs_FILE* f);
#endif

#ifndef EhsFgetc
EHS_GLOBAL ehs_sint16 EhsFgetc(ehs_FILE *f);
#endif

#ifndef EhsFgets
EHS_GLOBAL ehs_char* EhsFgets(ehs_char* pBuff, ehs_uint16 nSize, ehs_FILE* f);
#endif

#ifndef EhsFprintf
EHS_GLOBAL ehs_sint16 EhsFprintf(ehs_FILE *f, const ehs_char* fmt, ...); /*lint !e960 Variable arguments required to support fprintf */
#endif

#ifndef EhsFscanf
EHS_GLOBAL ehs_sint16 EhsFscanf(ehs_FILE *f, const ehs_char* fmt, ...); /*lint !e960 Variable arguments required to support fscanf */ 
#endif

/* helper functions that are probably found in hal_file.c */

/**
 * Consume the current line up until the end of line character
 * @param[in] pFile Pointer to the file to use
 * @return True if the end of line character was found, false otherwise, we've
 * probably hit the end of the file
 */
EHS_GLOBAL ehs_bool EhsFconsumeLine(ehs_FILE* pFile);

/**
 * Get a single word from the current file. Word is terminated by whitespace unless
 * the szSeparators parameter is set. Doesn't trim leading whitespace/separators
 * @param[in] pFile File to get the word from
 * @param[in,out] szWord Pointer to the area of memory to hold the word we've just read
 * @param[in] nLen Maximum Length of the word we're going to read (including terminator) 
 * @param[in] szSeparators Characters that separate one word from another. NULL means
 * white space. In the NULL case, leading white space is stripped from strings
 * @return Pointer to the characters we've read unless we encounter end of line or end of file.
 */
EHS_GLOBAL ehs_char* EhsFgetWord(ehs_FILE* pFile, ehs_char* szWord, ehs_uint16 nLen, const ehs_char* szSeparators);

#endif /* EHS_HAL_FILE_H */
