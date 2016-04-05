/** @file hal_process.h
 * In this file, all of the hardware abstraction layer declarations relating to process control
 * and related OS interactions are given.
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 1120 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

/**
 * @page Verification Verification report
 * @section hal_process_h
 * @anchor hal_process_h
 * @subsection misra MISRA compliance:
 * Demonstrated MISRA compliant on 
 * Last modified on $Date$
 *
 * This file contained the following derogations to the MISRA standard.
 */

#ifndef EHS_HAL_PROCESS_H
#define EHS_HAL_PROCESS_H

/*****************************************************************************/
/* Included files */

#include "target_process.h"

/*****************************************************************************/
/* Define macros  */

/*****************************************************************************/
/* Define types */

/* ehs_FILE is defined in target_file.h */
typedef EhsOsMutexStruct EhsOsMutexClass;

/*****************************************************************************/
/* Declare global variables */

/**
 * Flag to indicate that EhsTgtInit has completed. This is required so that other threads
 * can see that EHS is now ready to work with them. This must be set to false by the main function.
 * This is declared as a pointer to allow shared memory systems to point to some kind of shared
 * memory.
 */
EHS_GLOBAL ehs_bool* EhsTgtInitCompleteRef;

/**
 * Mutex resource used to control access to the function block inputs and outputs
 * @todo Initialise this mutex
 */
EhsOsMutexClass* EhsOsMutex_fbIO;

/*****************************************************************************/
/* Declare function prototypes  */

/**
 * Perform necessary target set-up 
 */
EHS_GLOBAL void EhsTargetInit(void);

/**
 * Perform setup before loading in a new application
 */
EHS_GLOBAL void EhsTargetApplicationInit(void);

/**
 * Reset application-specific parts of target
 */
EHS_GLOBAL void EhsTargetApplicationReset(void);


/* within target_process.h, process functions are normally #def'd to their stddef equivalents.
 * If the target cannot use the standard version, the #define is removed from target_process,
 * and the below function is used. The declarations below also provide a secondary
 * purpose - they show the prototype of the function in question.
 */
 
#ifndef EhsExit
/**
 * Exit from EHS. Exact behaviour of this function is target defined.
 */
EHS_GLOBAL void EhsExit(ehs_uint16 exitCode);
#endif


#ifndef EhsOsMutex_lock
/**
 * Lock a mutex to indicate the start of a region where we perform exclusive handling by a thread/process
 * 
 * @param[in] pMutexRef Indicates the identity of the mutex we are locking
 */
EHS_GLOBAL void EhsOsMutex_lock(EhsOsMutexClass* pMutexRef);
#endif

#ifndef EhsOsMutex_unlock
/**
 * Release a mutex indicating the end of a unique access region
 * 
 * @param[in] pMutexRef Indicates the identity of the mutex we are releasing
 */
EHS_GLOBAL void EhsOsMutex_unlock(EhsOsMutexClass* pMutexRef);
#endif

#ifndef EhsTgtProcess_isOrphan
/**
 * Called by the TCP/IP thread to see if it is an orphan process
 * 
 * @return true if the current parent process Id is different to the original parent process id 
 * and this process is the TCP/IP process
 */
EHS_GLOBAL ehs_bool EhsTgtProcess_isOrphan(void);
#endif

#endif /* EHS_HAL_PROCESS_H */
