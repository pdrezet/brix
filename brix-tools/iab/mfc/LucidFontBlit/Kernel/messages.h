/** @file messages.h
 * All messages are gathered into a single place (this file) to support global changes,
 * setting specific message styles, and to support internationalization.
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 1135 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

/**
 * @page Verification Verification report
 * @section messages_h
 * @anchor messages_h
 * @subsection misra MISRA compliance:
 * Demonstrated MISRA compliant on 
 * Last modified on $Date:$
 *
 * This file contained the following derogations to the MISRA standard:
 * - none.
 */

#ifndef EHS_MESSAGES_H
#define EHS_MESSAGES_H

#include "hal_console.h"
/*lint -emacro( (534), EhsError ) Ignore return code of printf here */
#define EhsError(err)
/* #define EhsError(err) EhsConsolePrintf("**Error at: %s:%d\n",__FILE__,__LINE__,);EhsConsolePrintf(err); */
#define EhsWarning(err)

/* Console messages */
#define EHS_MSG_STATENAME_READY "Ready\n"
#define EHS_MSG_STATENAME_RUNNING "Running\n"
#define EHS_MSG_STATENAME_EMPTY "Empty\n"

#define EHS_MSG_DEBUG_ON "=+ (on)\n"
#define EHS_MSG_DEBUG_OFF "=- (off)\n"

#define EHS_MSG_ERROR_SET_INVALID_TRIGGER(x) "**Error: no such trigger id, %d\n",x
#define EHS_MSG_ERROR_SET_INVALID_DATA(x,y) "**Error: no such data line %d,%c",x,y
#define EHS_MSG_ERROR_TRIGGER_IDX_INVALID "**Error: trigger index invalid - IDF finish port doesn't match source code\n"
#define EHS_MSG_ERROR_SET_EVENT_PARAM "**Error: Set event requires integer as trigger id\n"
#define EHS_MSG_ERROR_SET_EVENT_STATE "**Error: Set event does not work with no application loaded\n"
#define EHS_MSG_ERROR_SET_DATA_PARAM "**Error: Set data requires =D<id:int>,<type:char>=<value:*>\n"
#define EHS_MSG_ERROR_SET_DATA_STATE "**Error: Set data does not work with no application loaded\n"
#define EHS_MSG_ERROR_SET_MONITOR_PARAM "**Error: Set monitor lines requires =M+<id:int>,<type:char> or =M-<id:int>,<type:char>\n"
#define EHS_MSG_ERROR_SET_MONITOR_STATE "**Error: Set monitor line works only in debug mode\n"
#define EHS_MSG_ERROR_GET_UNRECOG "**Error: Unrecognised option to Get command\n"
#define EHS_MSG_ERROR_SET_UNRECOG "**Error: Unrecognised option to Set command\n"
#define EHS_MSG_ERROR_ALREADY_RUNNING "**Error: Already running\n"
#define EHS_MSG_ERROR_NO_APP "**Error: No application loaded\n"
#define EHS_MSG_ERROR_SET_INVALID "**Error: Unrecognised option to modify breakpoints command\n"
#define EHS_MSG_ERROR_NOT_RUNNING "**Error: Application not running\n"
#define EHS_MSG_ERROR_LOAD_FAILED "**Error: Failed to load file\n"
#define EHS_MSG_ERROR_LOAD_GIF_FAILED(x) "**Error: Failed to load gif %s\n",x
#define EHS_MSG_ERROR_INVALIDFILENAME "**Error: Invalid filename\n"
#define EHS_MSG_ERROR_EVENT_QUEUE_EMPTY(x) "**Error: EHS event queue unexpectedly empty for group %-d\n",x
#define EHS_MSG_ERROR_FILE_NOT_OPEN(x) "**Error: Failed to open file %s\n",x
#define EHS_MSG_ERROR_FILE_NOT_CLOSE(x) "**Error: Close failed for file %s\n",x
#define EHS_MSG_ERROR_FILE_NOT_WRITE(x) "**Error: Write failed for file %s\n",x
#define EHS_MSG_ERROR_FILE_TIMEOUT(name, nSizeRemaining, nSize) "**Error: Timeout in receiving file %s -- %d bytes (%d%%) remaining\n",name,nSizeRemaining,((nSizeRemaining*100u)/nSize)
#define EHS_MSG_ERROR_MEMORY "**Error: Out of memory in EHS\n"
#define EHS_MSG_ERROR_MEMORY_INIT "**Error: Out of memory when initialising components\n"
#define EHS_MSG_ERROR_MEMORY_ALLOC_DURING_RUN "**Error: Can't allocate readonly or writeable memory in run mode\n"
#define EHS_MSG_ERROR_INIT_FAIL(x) "**Error: Initialization failed for block %s\n",x
#define EHS_MSG_ERROR_TOOLKITS "**Error: Too many toolkits - increase EHS_MAX_TOOLKITS if necessary\n"
#define EHS_MSG_ERROR_CONFIG_FILE "**Error: Couldn't create config file - using default values\n"
#define EHS_MSG_ERROR_CONFIG_IDENTITY "**Error: Couldn't read identity from config file - using default value\n"
#define EHS_MSG_FATAL_NO_STATE "**FATAL: EHS State is unknown\n"
#define EHS_MSG_ERROR_INVALID_FORMAT(x) "**Error: Invalid format to printf(%s)\n",x
#define EHS_MSG_ERROR_MEMORY_OVERWRITE "**Error: Attempt to overwrite beyond allocated memory\n"
#define EHS_MSG_ERROR_NOT_YET_IMPLEMENTED(x) "**Error: Feature %s not yet implemented\n",x
#define EHS_MSG_ERROR_INVALID_STRING_CONNECTION(y) "**Error: Invalid string connection at %x (%s)\n",y,y

/* Graphics subsystem */
#define EHS_MSG_ERROR_WIDGET_NOT_INIT "**Error: Widget hasn't been initialised\n"
#define EHS_MSG_ERROR_WIDGET_TYPE_NOT_RECOG(x) "**Error: Widget file type isn't recognised (%s)\n",x
#define EHS_MSG_ERROR_WIDGET_TOO_MANY "**Error: Too many widgets allocated\n"

/* Calculator messages */
#define EHS_MSG_ERROR_DIV0 "**Error: Attempt to divide by zero - result set to maxint\n"

#define EHS_MSG_CMD_RESP "> \n"

/* Parser messages */
#define EHS_MSG_PARSER_FAILED "***** Failed to load SODL *****\n"
#define EHS_MSG_PARSER_NO_OPEN(x) "**Error: Couldn't open SODL file %s\n",x
#define EHS_MSG_PARSER_TOO_BIG "**Error: SODL file too large to hold in memory\n"
#define EHS_MSG_PARSER_NO_OBJECTS "**Error: No objects found in SODL file\n"
#define EHS_MSG_PARSER_TOO_MANY_GROUPS "**Error: Too many groups defined in SODL file\n"
#define EHS_MSG_PARSER_DUPLICATE_GROUPID "**Error: Group ID duplicated in SODL file\n"
#define EHS_MSG_PARSER_SINT32_RANGE(x) "**Error: Signed value out of range, value: %d\n",x
#define EHS_MSG_PARSER_UINT32_RANGE(x,c) "**Error: Value out of range, value: %d%d...\n",x,c
#define EHS_MSG_PARSER_SINT16_RANGE(x) "**Error: signed 16-bit value out of range, value: %d\n",x
#define EHS_MSG_PARSER_UINT16_RANGE(x) "**Error: unsigned 16-bit value out of range, value: %d\n",x
#define EHS_MSG_PARSER_UINT8_RANGE(x) "**Error: unsigned 8-bit value out of range, value: %d\n",x
#define EHS_MSG_PARSER_GROUP_FAILED(x) "**Error: Failed to read %dth group\n",x
#define EHS_MSG_PARSER_INVALID_GROUP(x) "**Error: Group %d defined with period < allocation\n",x
#define EHS_MSG_PARSER_MINIMUM_PERIOD(x) "**Error: Period for group %d too small\n",x
#define EHS_MSG_PARSER_PARAMS_NO_OPEN(x) "**Error: Couldn't open params file %s\n",x
#define EHS_MSG_PARSER_PARAMS_MISSING "**Error: Parameters missing when parameter file was expected\n"
#define EHS_MSG_PARSER_PARAMS_TAG_NOT_FOUND(x) "**Error: Parameter file didn't contain tag %s\n",x
#define EHS_MSG_PARSER_PARAMS_TAG_MULTIPLE(x) "**Error: Parameter file contained multiple instances of tag %s\n",x
#define EHS_MSG_PARSER_BLOCK_NAME_INVALID(x) "**Error: Function block name %s not recognised\n",x
#define EHS_MSG_PARSER_FUNCTION_NAME_INVALID(x) "**Error: Function name %s not recognised\n",x
#define EHS_MSG_PARSER_ATOMIC_FLAG_MISSING "**Error: Atomic flag missing from function definition\n"
#define EHS_MSG_PARSER_GROUPID_MISSING "**Error: Group ID missing from function definition\n"
#define EHS_MSG_PARSER_GROUPID_INVALID(x) "**Error: Group ID %-d specified by function doesn't exist\n",x
#define EHS_MSG_PARSER_TRIGGERID_MISSING "**Error: Trigger ID missing from function definition\n"
#define EHS_MSG_PARSER_NUM_INPUTS_MISSING "**Error: Number of inputs missing from function definition\n"
#define EHS_MSG_PARSER_TOO_MANY_TRIGGERS "**Error: Too many triggers declared in SODL\n"
#define EHS_MSG_PARSER_TOO_MANY_FUNCTIONS "**Error: Too many functions declared in SODL\n"
#define EHS_MSG_PARSER_TOO_MANY_BLOCKS "**Error: Too many function blocks declared in SODL\n"

/* font error messages */
#define EHS_MSG_FONT_NAME_MISSING(fname)"**Error: Font in file %s has no font name following FONT statement\n",fname
#define EHS_MSG_FONT_TOO_MANY(fname) "**Effor: Too many fonts loaded - can't load %s. Increase EHS_MAX_FONTS in target_config.h\n",fname
#define EHS_MSG_FONT_NUMGLYPHS_MISSING(fname) "**Error: Font in file %s has no number of glyphs following CHARS statement\n",fname
#define EHS_MSG_FONT_CANT_OPEN(fname) "**Error: Can't open font file %s\n",fname
#define EHS_MSG_FONT_BITMAP(nId) "**Error: .bdf file Problem with bitmap for character %x",nId
#define EHS_MSG_FONT_MISSING_BBX_PARAM(nId) "**Error: .bdf file Missing BBX data for character %x",nId
#define EHS_MSG_FONT_MISSING_CODE "**Error: .bdf file missing parameter for ENCODING statement"
#define EHS_MSG_FONT_MISSING_DWIDTH_PARAM(nId) "**Error: .bdf file DWIDTH statement missing parameters in character %x",nId
#define EHS_MSG_FONT_NON_MONOTONIC(nCurrent,nLast) "**Error: glyph with \"ENCODING %d\" occurs before encoding %d\n",nCurrent,nLast

/* Target-specific error messages */
#define EHS_MSG_TGT_LINE_LENGTH "**Error: Line length read exceeds buffer size. Truncating line\n"
#define EHS_MSG_TGT_INPUT_QUEUE_FULL "**Error: Console input queue is full\n"
#define EHS_MSG_TGT_FILE_WRITE_FAILED(fname) "**Error: Attempt to write to file %s failed\n",fname
#define EHS_MSG_TGT_FILE_CLOSE_FAILED(fname) "**Error: Attempt to close file %s failed\n",fname
#define EHS_MSG_TGT_FILE_OPEN_APPEND(fname) "**Error: Attempted to open file %s using append mode -- not supported\n",fname
#define EHS_MSG_TGT_FILE_TOO_MANY "**Error: Too many files open, can't open any more\n"
#define EHS_MSG_TGT_GRAPHICS_UNSUPPORTED_MODE(mode) "**Error: Unsupported graphics mode (%s)\n",mode
#define EHS_MSG_TGT_GRAPHICS_UNSUPPORTED_FORMAT(fn,fmt) "**Error: Unsupported graphics format in function %s(%d)\n",fn,fmt
#define EHS_MSG_TGT_STAPI(module,error) "**Error: STAPI problem in function %s: %s\n",module,error
#define EHS_MSG_TGT_WIN32(module,error) "**Error: Win32 problem in function %s: %s\n",module,error
#define EHS_MSG_TGT_NO_PALETTE "**Error: No palette supplied"

/* HAL-specific messages */
#define EHS_MSG_WARNING_HGHTML_NO_SPECIAL(szEntity) "**Warning: Unrecognised special entity &%s; - ignored\n",szEntity 
#define EHS_MSG_WARNING_HGHTML_NO_MEM "**Warning: Out of memory HTML rendering terminated early\n"
#define EHS_MSG_WARNING_HGHTML_IGNORED_INVALID_TAG "**Warning: Invalid tag detected in parsed HTML string - ignored\n"
#define EHS_MSG_WARNING_HGHTML_IGNORED_PARAMS(szParams) "**Warning: Ignored parameters in HTML tag (%s)\n",szParams
#define EHS_MSG_WARNING_HGHTML_MISSING_PARAM "**Warning: missing parameters from either <img> or <span> tag\n"
#define EHS_MSG_WARNING_HGHTML_TRUNC_PARAM(szParam) "**Warning: parameter was truncated: \"%s\"\n",szParam
#endif /* EHS_MESSAGES_H */

