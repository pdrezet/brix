/** @file globals.h
 * Declarations of EHS-wide globals.
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 971 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

/**
 * @page Verification Verification report
 * @section hal_process_h
 * @anchor hal_process_h
 * @subsection misra MISRA compliance:
 * Demonstrated MISRA compliant on 
 * Last modified on $Date$
 *
 * This file contained the following derogations to the MISRA standard:
 * - Rule 19.12 Multiple use of #/## operators in macro definition. This is used in a debug build of EHS
 * - Rule 19.13 Use of #/## operator. This is used only in a debug build of EHS
 */

#ifndef EHS_GLOBALS
#define EHS_GLOBALS

/*****************************************************************************/
/* Included files */

#include "target_config.h" /* special include required before macro definitions */
#include "ehs_types.h"
/*****************************************************************************/
/* Define macros  */

/* Defines system-wide, target-independent limits */
#define EHS_STRING_LENGTH_MAX 256u
#define EHS_SINT32_MAX 2147483647 
#define EHS_SINT32_MIN -2147483648
#define EHS_UINT32_MAX 4294967295u
#define EHS_UINT32_MIN 0u
#define EHS_SINT16_MAX 32767
#define EHS_SINT16_MIN -32768
#define EHS_UINT16_MAX 65535u
#define EHS_UINT16_MIN 0u
#define EHS_UINT8_MAX 255u
#define EHS_UINT8_MIN 0u
#define EHS_SINT8_MAX 127
#define EHS_SINT8_MIN -128

/* character constants */
#define EHS_CHAR_LF (0xau)
#define EHS_CHAR_CR (0xdu)
#define EHS_CHAR_ESC (0x1bu)

#define EHS_PARAM_SEPARATOR 0x01 /**< Used to separate fields in parameters */

/* define special values */
#define EHS_FUNCTION_ID_START 0 /**< Id of the start event */
#define EHS_TRIG_ID_START 0 /**< Id of the triggering event */

/* define file size limits */
#define EHS_DEFAULT_SODL_NAME "t.sdl" /**< Defines the standard name for anonymous SODL files */
#define EHS_DEFAULT_CONFIG_NAME "t.cnf" /**< Defines the standard name for the EHS config file */
#define EHS_FILENAME_SIZE 8 /**< Defines the size of the part of filename before the '.' */
#define EHS_FILEEXT_SIZE 3 /**< Defines the size of the part of the filename after the '.' */
#define EHS_FILESTRING_SIZE (EHS_FILENAME_SIZE + EHS_FILEEXT_SIZE + 2) /**< 2 comes from 1 character separator + 1 null character */
#define EHS_FONT_FILESTRING_SIZE 256 // Has a full path in the case of LGB
#define EHS_DEFAULT_FILENAME "default.txt" /**< Used when an invalid filename is given */
#define EHS_SODL_EXTENSION "sdl"
#define EHS_SODL_EXT_SIZE 3

/* General timing constants */

/**
 * How long to wait before polling console input (when no application is executing)
 */
#define EHS_IDLE_PERIOD EHS_TIME_ms(200u) 

/**
 * How long to wait between reading chunks of input file before concluding that
 * nothing else is coming
 */
#define EHS_TIMEOUT_READ_FILE EHS_TIME_s(10u)

/**
 * How long to wait where no event input is available (i.e. how long it takes
 * application to wake up after a new event first appears
 */
#define EHS_WAKEUP_TIME EHS_TIME_ms(20u)

/**
 * Checks whether x (a pointer to an object) is the final entry in a table.
 * The final entry is initialized with {0}, which sets all fields to zero.
 * Casting the first part of the structure to void* means that we can check
 * whether this is initialized to NULL.
 */
#define EHS_TABLE_END(x) (NULL == *(void**)(x))

#ifdef EHS_TARGET_ENABLE_FUNCTION_TRACING
#define EHS_TRACE_FLAG_ATOM 0x8000 /**< Applies to functions that are called at the lowest level: bytes (file handling), tokens (parser), events (kernel) ... */
#define EHS_TRACE_FLAG_ITEM 0x4000 /**< Applies to items at the next level: lines (file handling), statements (parser),...*/ 
#define EHS_TRACE_FLAG_GROUP 0x2000 /**< Applies to "group" level items: function blocks (parser) ... */
#define EHS_TRACE_FLAG_TOPLEVEL 0x1000

#define EHS_TRACE_FLAG_HAL_FILE 0x0001
#define EHS_TRACE_FLAG_KERNEL 0x0010
#define EHS_TRACE_FLAG_PARSER 0x0020
#define EHS_TRACE_FLAG_GLOBAL 0x0800 /* unspecified functions */

#define EHS_TRACE_FLAG_SET(x) (((x) & EhsTraceFlags) == (x))

#define EHS_TRACE_FUNCTION(name) EHS_TRACE_FUNC0(EHS_TRACE_FLAG_GLOBAL,name)

/** Conditional trace a function with no args */
/*lint -save -e960 -e961 #/## used only in debug build */
#define EHS_TRACE_FUNC0(subsys,name) {if (EHS_TRACE_FLAG_SET(subsys)) EhsConsolePrintf("%s()\n\r",#name); } 
/** Conditional trace a function with one argument */
#define EHS_TRACE_FUNC1(subsys,name,fmt,A) {if (EHS_TRACE_FLAG_SET(subsys)) EhsConsolePrintf("%s("##fmt##")\n\r",#name,A); }
/** Conditional trace a function with two arguments */
#define EHS_TRACE_FUNC2(subsys,name,fmt,A,B) {if (EHS_TRACE_FLAG_SET(subsys)) EhsConsolePrintf("%s("##fmt##")\n\r",#name,A,B); }
/** Conditional trace a function with three arguments */
#define EHS_TRACE_FUNC3(subsys,name,fmt,A,B,C) {if (EHS_TRACE_FLAG_SET(subsys)) EhsConsolePrintf("%s("##fmt##")\n\r",#name,A,B,C); }
/** Conditional trace a function with four arguments */
#define EHS_TRACE_FUNC4(subsys,name,fmt,A,B,C,D) {if (EHS_TRACE_FLAG_SET(subsys)) EhsConsolePrintf("%s("##fmt##")\n\r",#name,A,B,C,D); }

/** Conditional trace a function with one number argument */
#define EHS_TRACE_FUNCn(subsys,name,A) {if (EHS_TRACE_FLAG_SET(subsys)) EhsConsolePrintf("%s(%d)\n\r",#name,A); }
/** Conditional trace a function with one pointer argument */
#define EHS_TRACE_FUNCp(subsys,name,A) {if (EHS_TRACE_FLAG_SET(subsys)) EhsConsolePrintf("%s(%x)\n\r",#name,A); }
/** Conditional trace a function with one string argument */
#define EHS_TRACE_FUNCs(subsys,name,A) {if (EHS_TRACE_FLAG_SET(subsys)) EhsConsolePrintf("%s(%s)\n\r",#name,A); }
/** Conditional trace a function with arguments: pointer, string */
#define EHS_TRACE_FUNCpp(subsys,name,A,B) {if (EHS_TRACE_FLAG_SET(subsys)) EhsConsolePrintf("%s(%x,%x)\n\r",#name,A,B); }
/** Conditional trace a function with arguments: pointer, string */
#define EHS_TRACE_FUNCps(subsys,name,A,B) {if (EHS_TRACE_FLAG_SET(subsys)) EhsConsolePrintf("%s(%x,%s)\n\r",#name,A,B); }
/** Conditional trace a function with arguments: string, string */
#define EHS_TRACE_FUNCss(subsys,name,A,B) {if (EHS_TRACE_FLAG_SET(subsys)) EhsConsolePrintf("%s(%s,%s)\n\r",#name,A,B); }
/** Conditional trace a function with arguments: pointer, number, pointer */
#define EHS_TRACE_FUNCpnp(subsys,name,A,B,C) {if (EHS_TRACE_FLAG_SET(subsys)) EhsConsolePrintf("%s(%x,%d,%x)\n\r",#name,A,B,C); }
/** Conditional trace a function with arguments: pointer, string, pointer */
#define EHS_TRACE_FUNCpsp(subsys,name,A,B,C) {if (EHS_TRACE_FLAG_SET(subsys)) EhsConsolePrintf("%s(%x,%s,%x)\n\r",#name,A,B,C); }
/** Conditional trace a function with arguments: pointer, number, pointer */
#define EHS_TRACE_FUNCsnp(subsys,name,A,B,C) {if (EHS_TRACE_FLAG_SET(subsys)) EhsConsolePrintf("%s(%s,%d,%x)\n\r",#name,A,B,C); }
/** Conditional trace a function with arguments: pointer, number, number, pointer */
#define EHS_TRACE_FUNCpnnp(subsys,name,A,B,C,D) {if (EHS_TRACE_FLAG_SET(subsys)) EhsConsolePrintf("%s(%x,%d,%d,%x)\n\r",#name,A,B,C,D); }
/*lint restore */
#else
#define EHS_TRACE_FUNC0(subsys,name)
#define EHS_TRACE_FUNC1(subsys,name,fmt,A)
#define EHS_TRACE_FUNC2(subsys,name,fmt,A,B)
#define EHS_TRACE_FUNC3(subsys,name,fmt,A,B,C)
#define EHS_TRACE_FUNC4(subsys,name,fmt,A,B,C,D)
#define EHS_TRACE_FUNCn(subsys,name,A)
#define EHS_TRACE_FUNCp(subsys,name,A)
#define EHS_TRACE_FUNCs(subsys,name,A)
#define EHS_TRACE_FUNCpp(subsys,name,A,B)
#define EHS_TRACE_FUNCps(subsys,name,A,B)
#define EHS_TRACE_FUNCss(subsys,name,A,B)
#define EHS_TRACE_FUNCpnp(subsys,name,A,B,C)
#define EHS_TRACE_FUNCpsp(subsys,name,A,B,C)
#define EHS_TRACE_FUNCsnp(subsys,name,A,B,C)
#define EHS_TRACE_FUNCpnnp(subsys,name,A,B,C,D)

#endif /* EHS_TARGET_ENABLE_FUNCTION_TRACING */

/* define application size limits */
#define EHS_MAX_GROUPS 1
#define EHS_GROUP_DEFAULT_PERIOD		EHS_TIME_ms(1000)
#define EHS_GROUP_DEFAULT_ALLOCATION	EHS_TIME_ms( 800)

/**
 * Defines the states that the debugger can be in
 */
typedef enum {
	EHS_DEBUG_OFF, 		/**< No debug messages are generated */
	EHS_DEBUG_ON, 		/**< Debug messages are generated for every trigger and every data flow */
	EHS_DEBUG_MONITOR	/**< Debug messages are generated only for monitored triggers and events */ 
	} EhsDebugModeType;

/*****************************************************************************/
/* Define types */

/* ehs_FILE is defined in target_file.h */

/*****************************************************************************/
/* Declare global variables */

/**
 * Defines the global state for EHS.
 */
EHS_GLOBAL EhsStateType EhsState;

/**
 * If true, indicates that the main scheduler engine is to run in single step mode.
 */
EHS_GLOBAL ehs_bool EhsSingleStepFlag;

/**
 * If true, indicates that EHS is running in debug mode
 */
EHS_GLOBAL EhsDebugModeType EhsDebugMode;

/**
 * Indicates the sequence number of the current debug message
 */
EHS_GLOBAL ehs_uint32 EhsDebugSequenceNumber;

/**
 * Initialize all global variables to the correct state for startup
 */
EHS_GLOBAL void EhsSystemInit(void);

/**
 * Shut down everything
 */
EHS_GLOBAL void EhsShutdown(void);

/**
 * Used in running debugging EHS via tracing calls. This represents a bitmask
 * of the subsystems that are currently being traced. 0 means trace is disabled.
 */
#ifdef EHS_TARGET_ENABLE_FUNCTION_TRACING
EHS_GLOBAL ehs_uint32 EhsTraceFlags;
#endif

/*****************************************************************************/
/* Declare function prototypes  */

#endif /* EHS_GLOBALS */

