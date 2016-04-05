/** @file target_process.h
 * The target-specific declarations required to support the HAL for process services
 * and related OS interations are defined here. 
 * This file should only be included by hal_process.h
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 1087 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_TARGET_PROCESS_H
#define EHS_TARGET_PROCESS_H

#ifndef EHS_HAL_PROCESS_H
#error "This file should only be included by hal_process.h"
#endif

/*****************************************************************************/
/* Included files */

/*****************************************************************************/
/* Define macros  */

/**
 * Returns true if the TCP/IP process is an orphan. For the PC, the TCP/IP work
 * is done in a thread, which cannot be orphaned by the process stopping
 */
#define EhsTgtProcess_isOrphan() (EHS_FALSE)

/**
 * Lock a mutex to indicate the start of a region where we perform exclusive handling by a thread/process
 * @todo Provide an implementation for EhsOsMutex_lock
 * 
 * @param[in] pMutexRef Indicates the identity of the mutex we are locking
 */
#define EhsOsMutex_lock(pMutexRef)

/**
 * Release a mutex indicating the end of a unique access region
 * @todo Provide an implmentation for EhsOsMutex_unlock.
 * 
 * @param[in] pMutexRef Indicates the identity of the mutex we are releasing
 */
#define EhsOsMutex_unlock(pMutexRef)

/*****************************************************************************/
/* Define types */

/**
 * Dummy type definition for the mutex - these aren't yet implemented
 */
typedef ehs_uint8 EhsOsMutexStruct;

/*****************************************************************************/
/* Declare global variables */

/*****************************************************************************/
/* Declare function prototypes  */

#endif /* EHS_TARGET_STRING_H */
