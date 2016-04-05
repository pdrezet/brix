/** @file callback_queue.h
 * In this file, the callback queue type is defined and the associated functions to
 * operate upon it are declared. 
 *
 * @author: Dr Andrew Coombes
 * @version: $Revision: 808 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_CALLBACK_QUEUE_H
#define EHS_CALLBACK_QUEUE_H

#include "ehs_types.h"
#include "fid.h"

/**
 * Callback queue entry type. This is a single element of a linked list
 *
 * Unlike the event queue, indices are uint32. We assume that updates are atomic
 * (i.e. writing to them is not store low 16-bits, store high 16-bits (or vice-versa)
 * Otherwise an interrupt between one instruction and the other could cause havoc
 * if the interrupt results in another queue operation.
 */
typedef struct EhsCallbackQueueEntryStruct {
	EhsRunFuncType fpRunFunc;				/**< Pointer to function to run when callback is called */
	EhsFunctionInstanceDataType* pFuncInst;	/**< Pointer to function context to use when callback is called */
	struct EhsCallbackQueueEntryStruct* pNext;		/**< Pointer to next callback to process when callback is called */
} EhsCallbackQueueEntryType;

/**
 * Callback queue type. This contains a pointer to the first callback queue 
 * entry element.
 */
typedef EhsCallbackQueueEntryType *EhsCallbackQueueType;

/**
 * Add a new function to the callback queue.
 * @param pQueue Pointer to a start of the queue
 * @param fpFunc Pointer to the function to run when the callback is called
 * @param pFuncInst Pointer to the data to use when the callback is called.
 * @param pEntry Pointer to the struct to hold this instances data (presumably
 * held in the function instance data type)
 */
EHS_GLOBAL void EhsCallbackQueue_register(EhsCallbackQueueType* pQueue, 
										  EhsRunFuncType fpRunFunc, 
										  EhsFunctionInstanceDataType* pFuncInst,
										  EhsCallbackQueueEntryType *pEntry);


/**
 * Execute the contents of the callback queue.
 * @param pQueue Pointer to the start of the queue
 */
EHS_GLOBAL void EhsCallbackQueue_execute(EhsCallbackQueueType* pQueue);

#endif /* EHS_CALLBACK_QUEUE_H */

