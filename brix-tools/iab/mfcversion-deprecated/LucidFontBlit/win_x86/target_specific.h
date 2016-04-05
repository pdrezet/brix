/** @file target.h
 * In this file, all of the hardware abstraction layer functions provided for EHS are given.
 * Applies to win_x86 target.
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 892 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_TARGET_SPECIFIC_H
#define EHS_TARGET_SPECIFIC_H

#include <stdlib.h> /* required for malloc, exit */

/**
 * Whenever a pointer is accessed from a ROM data table, it should
 * be handled through this function
 */
#define EHS_TGT_ROM_PTR(type,x) (type)(x)
/**
 * Forces the declared variable to be aligned in the way specified by EHS_TGT_MEMORY_ALLOC_ALIGN
 */
#define EHS_TGT_MEMORY_ALIGNED(type,name) type name

#define EHS_TRACE_FUNCTION(x)

#define EhsExit exit

/* Debug support */
#define EhsDebugInfo EhsConsolePrintf

/**
 * Performs sine function using integers.
 *
 * @param nMult multiplier for output
 * @param nAngle angle to find (0 to 360)
 * @return nMult * sin(nAngle % 360)
 */
EHS_GLOBAL ehs_sint32 EhsTgtInt_sin(ehs_sint32 nMult, ehs_sint32 nAngle);
/**
 * Performs cosine function using integers.
 *
 * @param nMult multiplier for output
 * @param nAngle angle to find (0 to 360)
 * @return nMult * cos(nAngle % 360)
 */
EHS_GLOBAL ehs_sint32 EhsTgtInt_cos(ehs_sint32 nMult, ehs_sint32 nAngle);

/* The following functions are also onlu used by function blocks and should be seperated into another target support header
 * designed for FB development
 */

/* math functions not implemented in Windows */
EHS_GLOBAL ehs_float asinh(ehs_float x);
EHS_GLOBAL ehs_float acosh(ehs_float x);
EHS_GLOBAL ehs_float atanh(ehs_float x);

/*****************************************************************************/
/* Internal implementation-specific functions. These functions are only used 
 * by other functions within this target, and aren't part of the global scope 
 * of EHS
 */

/**
 * Main function handling TCP/IP for this implementation
 */
EHS_GLOBAL ehs_uint32 EhsTgtTcp(void);


#endif /* EHS_TARGET_SPECIFIC_H */
