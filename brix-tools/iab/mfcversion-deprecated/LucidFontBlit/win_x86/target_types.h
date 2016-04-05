/** @file target_types.h
 * In this file, all of the target-specifc type definitions required by EHS are given.
 * This file is normally used by being included by ehs_types.h.
 * This applies to the win_x86 target.
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 885 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_TARGET_TYPES_H
#define EHS_TARGET_TYPES_H
/*lint -e(829) Project permitted derogation from the standard */
#include <stdio.h>
/*line +e(829) */

/* standard types */
typedef unsigned long	ehs_uint32; /**< standard 32-bit unsigned type */
typedef long			ehs_sint32; /**< standard 32-bit signed type */
typedef unsigned short	ehs_uint16; /**< standard 16-bit unsigned type */
typedef short			ehs_sint16; /**< standard 16-bit signed type */
typedef unsigned char	ehs_uint8; /**< standard 8-bit unsigned type */
typedef char			ehs_sint8; /**< standard 8-bit signed type */
typedef int				ehs_bool; /**< Standard boolean type */
typedef char			ehs_char; /**< Standard char type */
typedef double			ehs_float; /**< Standard EHS floating point type */



#define EHS_TRUE	1	/**< allows target-specific boolean types to be used */
#define EHS_FALSE	0	/**< allows target-specific boolean types to be used */

#ifdef __cplusplus
#define EHS_GLOBAL extern "C" /**< allows target-specific definition of global (i.e extern) types */
#else
#define EHS_GLOBAL extern
#endif

#ifdef EHS_UNIT_TEST
#define EHS_LOCAL
#else
#define EHS_LOCAL static /**< allows target-specific definition of local (i.e. static) types */
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif

#endif /* EHS_TARGET_TYPES_H */
