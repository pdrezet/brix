/** @file utils.c
 * In this file, definitions for useful utilities for EHS are given
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 1120 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#include "utils.h"
#include "globals.h"
#include "messages.h"
#include "hal_string.h"

const char * EhsGetType(EhsDataTypeEnum * output, const char* input) 
{
	input = EhsStrTrimL(input);
	*output = *input++;

	switch (*output)
	{
	case EHS_TYPE_ID_INT:
	case EHS_TYPE_ID_BOL:
	case EHS_TYPE_ID_DBL:
	case EHS_TYPE_ID_STR:
		break;
	default:
		*output = EHS_TYPE_ID_UNDEF;
		break;
	}

	return input;
}

