/** @file target_dtv.h
 * The target-specific declarations required to support the HAL for DTV services
 * are defined here. This file should only be included by hal_dtv.h
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 1087 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_TARGET_DTV_H
#define EHS_TARGET_DTV_H

#ifndef EHS_HAL_DTV_H
#error "This file should only be included by hal_dtv.h"
#endif

/*****************************************************************************/
/* Included files */

/*****************************************************************************/
/* Define macros  */

/**
 * Longest possible path name (excluding filename, but including separators and
 * terminating zero).
 */
#define EHS_TGT_DTV_FILES_MAX_PATH 1024

/**
 * Longest possible filename
 */
#define EHS_TGT_DTV_FILES_MAX_FILENAME 256

/**
 * Path separator for this target
 */
#define EHS_TGT_DTV_FILES_SEPARATOR '\\'


/*****************************************************************************/
/* Define types */


/*****************************************************************************/
/* Declare global variables */


/*****************************************************************************/
/* Declare function prototypes  */

#endif /* EHS_TARGET_DTV_H */
