/** @file ehs_types.h
 * In this file, all of the standard type definitions required by EHS are given.
 * Any target-specific type definitions are given in target_types.h, which comes from
 * the target folder.
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 808 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_TYPES_H
#define EHS_TYPES_H
#include "ehs_defs.h"
#include "target_types.h"
#include "ehs_fb_types.h"
#include "fid.h"

/*********************************************************************************************/
/**
 * These are the valid states for EHS. Empty indicates that no application is loaded,
 * Ready indicates that an application is loaded, but EHS is not currently executing it,
 * Running indicates that an application is loaded and EHS is running it.
 */
typedef enum EhsStateEnum {EHS_STATE_EMPTY, EHS_STATE_READY, EHS_STATE_RUNNING} EhsStateType;

/*********************************************************************************************/
/* Connection type definitions */
typedef enum {EHS_TYPE_ID_INT = 'I', EHS_TYPE_ID_BOL = 'B', EHS_TYPE_ID_DBL = 'F', EHS_TYPE_ID_STR = 'S', EHS_TYPE_ID_UNDEF = 0xff} EhsDataTypeEnum;


#endif /* EHS_TYPES_H */

