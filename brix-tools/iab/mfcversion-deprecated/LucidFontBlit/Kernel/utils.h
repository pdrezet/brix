/** @file utils.c
 * In this file, declaration for useful utilities for EHS are given
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 1120 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_UTILS_H
#define EHS_UTILS_H
#include "ehs_types.h"

/**
 * Convert a value into uint16, saturating where limits are reached
 */
#define EHS_CONVERT_UINT16_SATURATE(x) (ehs_uint16)(x < 0?0:(((x) > EHS_UINT16_MAX))?EHS_UINT16_MAX:(x))

/**
 * Get current type from a string
 */
EHS_GLOBAL const ehs_char * EhsGetType(EhsDataTypeEnum * output, const ehs_char* input);


#endif /* EHS_UTILS_H */
