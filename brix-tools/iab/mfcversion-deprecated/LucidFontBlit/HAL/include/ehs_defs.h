/** @file ehs_defs.h
 * In this file, all of the standard definitions required by EHS are given.
 * Any target-specific type definitions are given in target_types.h, which comes from
 * the target folder.
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 1065 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_DEFS_H
#define EHS_DEFS_H

/* Dummy data types -- dispose of these as we can */

#define structFuncArg EhsFunctionInstanceDataType /* eventually we need to rename this to EhsFunctionInstanceDataType */
#define structData EhsDataConnectionTableType




/* identifiers used in SODL...*/
#define NO_PARAMS "NoParams"
#define SIZE_OF_NO_PARAMS sizeof(NO_PARAMS)
#define OBJECT_BEGIN "BEGIN "
#define OBJECT_END "END"



#endif /* EHS_TYPES_H */

