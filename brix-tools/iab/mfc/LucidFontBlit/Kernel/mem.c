/** @file target.c
 * In this file, the memory interface is defined.
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 1087 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#include "mem.h"
#include "messages.h"
#include "globals.h"
#include "target_config.h"
#include "target_specific.h"

/**
 * Number of long words to use for padding either side of the memory allocation region
 */
#define EHS_MEM_PADDING_SIZE 4
/**
 * Special pattern to put into memory padding
 */
#define EHS_MEM_PADDING_PATTERN 0xa5a5c3c3

typedef struct
{
	ehs_uint32 nPadding1[EHS_MEM_PADDING_SIZE]; /**< Padding to allow us to check for memory underruns */
	EHS_TGT_MEMORY_ALIGNED(ehs_uint8, xPool[EHS_MEMORY_POOL_SIZE]); /**< Memory pool used for dynamic allocation */
	ehs_uint32 nPadding2[EHS_MEM_PADDING_SIZE]; /** padding to allow us to check for memory overruns */
	ehs_uint32 nAllocated;	/**< readonly/writeable memory allocated so far */
	ehs_uint32 nTempAlloc; /**< scratchpad memory allocated so far */
} EhsMemClass;

/**
 * EHS memory class containing memory to allocate
 */
EHS_LOCAL EhsMemClass EhsMem;

/**
 * Check that memory patterns are intact
 */
ehs_bool EhsMem_selfTest()
{
	ehs_bool bRet = EHS_TRUE;
	ehs_uint32 i;
	EHS_TRACE_FUNCTION(EhsMem_selfTest);

	for (i = 0; i < EHS_MEM_PADDING_SIZE; i++)
	{
		if ((EhsMem.nPadding1[i] != EHS_MEM_PADDING_PATTERN)
		  ||(EhsMem.nPadding2[i] != EHS_MEM_PADDING_PATTERN))
		{
			bRet = EHS_FALSE;
		}
	}

	if (*(ehs_uint32*)&EhsMem.xPool[EhsMem.nAllocated] != EHS_MEM_PADDING_PATTERN)
	{
		bRet = EHS_FALSE;
	}

	if (*(ehs_uint32*)&EhsMem.xPool[EHS_MEMORY_POOL_SIZE - (EhsMem.nTempAlloc+sizeof(ehs_uint32))] != EHS_MEM_PADDING_PATTERN)
	{
		bRet = EHS_FALSE;
	}

	if (!bRet)
	{
		
		EhsError(EHS_MSG_ERROR_MEMORY_OVERWRITE);
	}

	return bRet;
}
/**
 * Allocate memory to the application. Memory is held until EhsApplicationInit is next called.
 */
void* EhsMemReadonly_alloc(ehs_uint32 sizeToAllocate)
{
	void *pAllocated = NULL;
	EHS_TRACE_FUNCTION(EhsMemReadonly_alloc);

	if (EhsMem_selfTest())
	{
		//if (EhsState != EHS_STATE_RUNNING)
		if (1)
		{
			if ((sizeToAllocate + EhsMem.nAllocated + EhsMem.nTempAlloc + (EHS_TGT_MEMORY_ALLOC_ALIGN-1) + sizeof(ehs_uint32)) < EHS_MEMORY_POOL_SIZE)
			{
				//@todo - review this code, it is allocating a large chunk of mem on every paint of a surface. Is this an efficient way to handle surfaces?
				pAllocated = (void*)&(EhsMem.xPool[EhsMem.nAllocated]);

				EhsMem.nAllocated += sizeToAllocate;
				/* Force alignment to the target's preferred alignment types */
				if (EhsMem.nAllocated & (EHS_TGT_MEMORY_ALLOC_ALIGN-1))
				{
					EhsMem.nAllocated = (EhsMem.nAllocated & ~(EHS_TGT_MEMORY_ALLOC_ALIGN-1))+EHS_TGT_MEMORY_ALLOC_ALIGN;
				}
				/* update padding pattern to prevent memory overruns */
				*(ehs_uint32*)&(EhsMem.xPool[(EhsMem.nAllocated)]) = EHS_MEM_PADDING_PATTERN;
			}
			else
			{
				EhsError(EHS_MSG_ERROR_MEMORY);
			}
		}
		else
		{
			EhsError(EHS_MSG_ERROR_MEMORY_ALLOC_DURING_RUN);
		}
	}
	return pAllocated;
}

/**
 * Free all allocated memory
 */
void EhsMem_freeAll()
{
	ehs_uint32 i;
	EhsMem.nAllocated = 0;
	EhsMem.nTempAlloc = 0;
	memset(EhsMem.xPool,0,EHS_MEMORY_POOL_SIZE);
	for (i = 0; i < EHS_MEM_PADDING_SIZE; i++)
	{
		EhsMem.nPadding1[i] = EHS_MEM_PADDING_PATTERN;
		EhsMem.nPadding2[i] = EHS_MEM_PADDING_PATTERN;
	}

	*(ehs_uint32*)&EhsMem.xPool[EhsMem.nAllocated] = EHS_MEM_PADDING_PATTERN;
	*(ehs_uint32*)&EhsMem.xPool[EHS_MEMORY_POOL_SIZE - (EhsMem.nTempAlloc+sizeof(ehs_uint32))] = EHS_MEM_PADDING_PATTERN;
}

/**
 * Allocate memory that is used prior to runtime for temporary use
 * e.g. expanding compressed data, parsing SODL files etc.
 */
void* EhsMemScratchpad_alloc(ehs_uint32 sizeToAllocate)
{
	void *pAllocated = NULL;

	if (EhsMem_selfTest())
	{
		if ((sizeToAllocate + EhsMem.nAllocated + EhsMem.nTempAlloc + (EHS_TGT_MEMORY_ALLOC_ALIGN-1) + sizeof(ehs_uint32)) < EHS_MEMORY_POOL_SIZE)
		{
			ehs_uint32 nAllocIdx;
			EhsMem.nTempAlloc += sizeToAllocate;
			nAllocIdx = EHS_MEMORY_POOL_SIZE - EhsMem.nTempAlloc;
			/* adjust address of allocated memory to meet alignment requirements of target */
			while (nAllocIdx & (EHS_TGT_MEMORY_ALLOC_ALIGN-1))
			{
				nAllocIdx--;
				EhsMem.nTempAlloc++;
			}
			
			pAllocated = (void*)&(EhsMem.xPool[nAllocIdx]);
			/* update padding pattern to detect overruns */
			*(ehs_uint32*)&EhsMem.xPool[EHS_MEMORY_POOL_SIZE - (EhsMem.nTempAlloc+sizeof(ehs_uint32))] = EHS_MEM_PADDING_PATTERN;
		}
		else
		{
			EhsError(EHS_MSG_ERROR_MEMORY);
		}
	}
	return pAllocated;
}

/**
 * Indicate that memory allocated from now is to be released upon
 * a corresponding EhsMemScratchpad_freeMarker
 */
EhsMemScratchpadMarkerType EhsMemScratchpad_setMarker()
{
	EhsMem_selfTest();
	return (EhsMemScratchpadMarkerType)(EhsMem.nTempAlloc);
}

/**
 * Release all scratchpad memory allocated since the specified marker
 * was set
 */
void EhsMemScratchpad_freeMarker(EhsMemScratchpadMarkerType xMarker)
{
	EhsMem_selfTest();
	EhsMem.nTempAlloc = (ehs_uint32)xMarker;
	*(ehs_uint32*)&EhsMem.xPool[EHS_MEMORY_POOL_SIZE - (EhsMem.nTempAlloc+sizeof(ehs_uint32))] = EHS_MEM_PADDING_PATTERN;
}
