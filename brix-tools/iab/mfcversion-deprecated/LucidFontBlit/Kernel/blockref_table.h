/** @file blockref_table.h
 * Contains the declaration of the function block reference table for EHS
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 780 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_BLOCKREF_TABLE_H
#define EHS_BLOCKREF_TABLE_H

/*****************************************************************************/
/* Included files */

#include "ehs_types.h"
#include "target.h"
#include "globals.h"

/*****************************************************************************/
/* declare macros */

/**
 * Creates a macro for defining a single entry in the block reference table
 */
#define EHS_BLOCKREF_ENTRY(name,x) {(name),(EhsInitFuncType)EHS_FB_INIT_NAME(x), (EhsIdentifyFuncType)EHS_FB_IDENTIFY_NAME(x), EHS_FB_FUNCTABLE_NAME(x)}
/**
 * Allows a single entry in the block reference table with a different init/identify name.
 * Allows for init/identify to be shared between blocks 
 */
#define EHS_BLOCKREF_ENTRY_EX(name, x, init, ident) {name,init,ident,EHS_FB_FUNCTABLE_NAME(x)}


/*****************************************************************************/
/* Declare typedefs and struct definitions */

/**
 * Declares a type representing a single instance of a function block
 */
typedef const struct
{
	const ehs_char *szName; /**< Function block name */
	EhsInitFuncType fpInitFunc; /**< The initialise function for this function block */
	EhsIdentifyFuncType fpIdentifyFunc; /**< The identify function for this function block */
	EhsFuncRefType *xFunctions; /**< The set of functions contained within this function block */
} EhsBlockRefType;

/**
 * Declares a type containing a set of block reference tables, each corresponding to a toolkit
 */
typedef struct
{
	EhsBlockRefType* pxRefTable[EHS_MAX_TOOLKITS];  /**< Reference to the toolkits */
	ehs_uint16 nNumToolkits; /**< Number of toolkits in the table */
} EhsToolkitTableType;

/*****************************************************************************/
/* Declare globals */

/**
 * Declares a function block reference table 
 */
typedef EhsBlockRefType EhsBlockRefTableType[];

/**
 * Declares a table containing all of the toolkits
 */
EHS_GLOBAL EhsToolkitTableType EhsToolkitTable;

/**
 * Declares the block reference table containing all functions held within EHS 
 */
EHS_GLOBAL EhsBlockRefTableType EhsBlockRefTable_core;

/**
 * Declares the core GUI function block toolkit
 */
#ifdef EHS_GUI_SUPPORT
EHS_GLOBAL EhsBlockRefTableType EhsBlockRefTable_coreGui;
#endif

/**
 * Declares a toolkit that is used to hold deprecated components
 */
#ifdef EHS_TOOLKIT_DEPRECATED
EHS_GLOBAL EhsBlockRefTableType EhsBlockRefTable_deprecated;
#endif

/**
 * Declares a toolkit that is used to hold experimental components
 */
#ifdef EHS_TOOLKIT_SANDBOX
EHS_GLOBAL EhsBlockRefTableType EhsBlockRefTable_sandbox;
#endif

/*****************************************************************************/
/* Declare function prototypes */

/**
 * Reset EhsToolkitTable to be empty.
 */
EHS_GLOBAL void EhsToolkitTable_reset(void);

/**
 * Add a new block reference table (aka toolkit) to the list of toolkits that we search.
 * @param pTable Pointer to the table to add
 * @return true if the table was added successfully.
 */
EHS_GLOBAL ehs_bool EhsToolkitTable_addTable(EhsBlockRefType* pTable);

/**
 * Search the EhsBlockRefTable for a function block with a specific name. Search is case-insensitive.
 *
 * @param szName Name to search table for
 * @return NULL if name not found, or pointer to block reference if it is found.
 */
EHS_GLOBAL EhsBlockRefType* EhsBlockRefTable_findObject(const ehs_char* szName);

/**
 * Search an EhsBlockRefType for a function with a specific name. Search is case-insensitive.
 *
 * @param block Function block to search
 * @param szName Function name to search table for
 * @return NULL if name not found, or pointer to EhsFuncRefType reference if it is found.
 */
EHS_GLOBAL EhsFuncRefType* EhsBlockRef_findFunction(EhsBlockRefType* block, const ehs_char* szName);

#endif /* EHS_BLOCKREF_TABLE_H */

