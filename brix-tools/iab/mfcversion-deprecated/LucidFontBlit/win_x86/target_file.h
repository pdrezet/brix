/** @file target_file.h
 * The target-specific declarations required to support the HAL for file services
 * are defined here. This file should only be included by hal_file.h
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 892 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_TARGET_FILE_H
#define EHS_TARGET_FILE_H

/*****************************************************************************/
/* Included files */
#include <stdio.h> /* required for malloc, exit */

/*****************************************************************************/
/* Define macros  */

/* These macros provide a mapping to the stdio file functions.
 * If the target cannot use the stdio version, the #define is removed from target_file,
 * and the declaration provided in hal_file is used instead
 */
#define EHS_EOF EOF /**< Defines end of file */

#define EhsFopen(fname,fmode) fopen(fname,fmode) /**< Open file. */

#define EhsFclose(f) fclose(f) /**< Close file. */

#define EhsFgetc(f) fgetc(f) /**< Get character from file. */

#define EhsFprintf fprintf /**< Print to file */

#define EhsFscanf fscanf /**< Read variables from file */

#define EhsFgets fgets /**< Read string from file */

/**
 * Write block of data to file
 */
#define EhsFwrite(ptr,size,num,stream) (ehs_sint16)fwrite((const void*)ptr, (size_t)size, (size_t)num, stream)

/**
 * Read block of data from file
 */
#define EhsFread(ptr,size,num,stream) (ehs_sint16)fread((void*)ptr, (size_t)size, (size_t)num, stream)

/**
 * Write character to file
 */
#define EhsFputc fputc

/*****************************************************************************/
/* Define types */

typedef FILE ehs_FILE; /**< File type used for file handling */

/*****************************************************************************/
/* Declare global variables */

/*****************************************************************************/
/* Declare function prototypes  */


#endif /* EHS_TARGET_FILE_H */
