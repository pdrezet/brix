/** @file target_config.h
 * In this file, all of the target-specific configuration required by EHS are given.
 * This file is normally used by being included by target.h
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 1120 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */

#ifndef TARGET_CONFIG_H
#define TARGET_CONFIG_H

/**
 * Defines the default target identifier for this instance of EHS 
 */
#define EHS_TARGET_DEFAULT_ID "(x86/Windows)" 
/* #define EHS_TARGET_EVENT_MODEL */ /**< defined if an external event/interrupt drives the main EHS loop */
/* #define EHS_RTA_TRACE_SUPPORT *//**< Defined if RTA-TRACE is supported by the target */

#define EHS_TARGET_FP_SUPPORT /**< defined if the target has floating point support */
#define EHS_GUI_SUPPORT /**< defined if the target has GUI support */
/* #define EHS_TARGET_TRACE_SUPPORT */ /**< Defined if the target supports RTA-TRACE (experimental) */
/* #define EHS_CALLBACKS_CONFIGURED */ /**< Defined if the target uses callbacks */
/* #define EHS_TARGET_FIXED_TIMER_RESOLUTION */ /**< Defined if the timer resolution cannot be changed during (or before) init */

/* #define EHS_TARGET_BIGENDIAN */ /**< Defined if the target is bigendian */

#define EHS_MAX_FONTS 100 /**< Maximum number of fonts that can be held on this target at one time */


#define EHS_GROUP_PERIOD_MIN 70 /**< Defines the minimum group period (in system ticks) */

#ifdef EHS_TOOLKIT_DEPRECATED
#define EHS_TOOLKIT_DEPRECATED_QTY 1
#else
#define EHS_TOOLKIT_DEPRECATED_QTY 0
#endif
#ifdef EHS_TOOLKIT_SANDBOX
#define EHS_TOOLKIT_SANDBOX_QTY 1
#else
#define EHS_TOOLKIT_SANDBOX_QTY 0
#endif

#define EHS_MAX_TOOLKITS (4+EHS_TOOLKIT_DEPRECATED_QTY+EHS_TOOLKIT_SANDBOX_QTY) /**< Defines the maximum number of toolkits that EHS supports */

#define EHS_MAX_FUNCTION_INSTANCES 4000 /**< Defines the maximum number of function instances that are supported */
#define EHS_MAX_CALLBACK_INSTANCES (EHS_MAX_FUNCTION_INSTANCES) /**< Provided for backwards compatibility */
#define EHS_MAX_WIDGET_INSTANCES 500 /**< Defines the maximum number of widgets that are supported */
#define EHS_MAX_INT_DATA 1000 /**< Defines the maximum number of integer data items supported */
#define EHS_MAX_BOOL_DATA 1000 /**< Defines the maximum number of boolean data items supported */
#define EHS_MAX_STRING_DATA 1000 /**< Defines the maximum number of strings supported */
#define EHS_MAX_FLOAT_DATA 1000 /**< Defines the maximum number of floats supported */
#define EHS_MAX_FUNCBLOCK_INSTANCES 2000 /**< Defines the maximum number of function blocks supported. Required by parser  */

#define EHS_FILE_BUFF_SIZE 1024 /**< Size of buffers used to read/write to files */

/**
 * Defines how allocated memory is to be aligned.
 * 1 is byte aligned, 2 is word aligned, 4 is dword aligned
 */
#define EHS_TGT_MEMORY_ALLOC_ALIGN 1
#define EHS_MEMORY_POOL_SIZE 10000000 /**< Amount of memory that can be dynamically allocated */
/**
 * Maximum event queue size. Due to implementation approach, 
 * this *must* be a power of 2, and less than 2<<15. See EhsEventQueueType 
 */
#define EHS_MAX_EVENT_QUEUE_SIZE (1u<<13) /* 8k */
/**
 * Maximum console queue size. This *must* be a power of 2 and less than 2<<31.
 */
#define EHS_MAX_CONSOLE_QUEUE_SIZE ((ehs_uint32)((ehs_uint32)(1u)<<16)) /* 64k */

#endif /* TARGET_CONFIG_H */
