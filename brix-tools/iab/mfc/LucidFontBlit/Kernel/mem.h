/** @file memory.h
 * In this file, an interface for memory allocation is defined.
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 1127 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_MEMORY_H
#define EHS_MEMORY_H

#include "ehs_types.h"

/**
 * Allocate memory to be used to hold information that is readonly 
 * during the application execution.
 */
EHS_GLOBAL void* EhsMemReadonly_alloc(ehs_uint32 sizeToAllocate);

/**
 * Allocate memory to be used to hold information that is read/writeable 
 * during the application execution.
 */
#define EhsMemWriteable_alloc EhsMemReadonly_alloc

/**
 * Free recently allocated memory. More of an aspiration than an actual
 * request at the moment... 
 */
#define EhsMemWriteable_free(x)

/**
 * Allocate memory that is used prior to runtime for temporary use
 * e.g. expanding compressed data, parsing SODL files etc.
 */
EHS_GLOBAL void* EhsMemScratchpad_alloc(ehs_uint32 sizeToAllocate);

/**
 * Defines the type of a marker used to allow scratch pad allocations
 * to be grouped together to allow a single free to release a group
 */
typedef ehs_uint32 EhsMemScratchpadMarkerType;
/**
 * Indicate that memory allocated from now is to be released upon
 * a corresponding EhsMemScratchpad_freeMarker
 */
EHS_GLOBAL EhsMemScratchpadMarkerType EhsMemScratchpad_setMarker(void);

/**
 * Release all scratchpad memory allocated since the specified marker
 * was set
 */
EHS_GLOBAL void EhsMemScratchpad_freeMarker(EhsMemScratchpadMarkerType xMarker);

/**
 * Free all allocated memory
 */
EHS_GLOBAL void EhsMem_freeAll(void);


/**
 * Allocate memory to the application. Memory is held until EhsApplicationInit is next called.
 * Kept for legacy support
 */
#define EhsMalloc EhsMemWriteable_alloc

/**
 * Free all allocated memory
 */
#define EhsFreeall EhsMem_freeAll

#endif /* EHS_MEMORY_H */
