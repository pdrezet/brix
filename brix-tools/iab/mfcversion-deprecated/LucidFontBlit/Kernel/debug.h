/** @file debug.h
 * Contains the declaration of debug functions for EHS
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 885 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */

#ifndef EHS_DEBUG_H
#define EHS_DEBUG_H
#include "ehs_types.h"
#include "hal_time.h"

/**
 * Generate a trace event message. Format is:
 * #<seq>#<id>#E#<start>#<end>.
 * where:
 * - <seq> Sequence number of the event. Unsigned 32-bit integer 
 *     (represented as a decimal string) incrementing with every event that is 
 *     transmitted.
 * - <id> Identifies the line number on which the event/data flow occurs. 
 *     Corresponds to the unique function id derived from the SODL 
 * - <start> Start time for the event. Unsigned 32-bit integer (represented 
 *     as a decimal string). Represents the time (in microseconds) at which 
 *     the function block started executing the specified event
 * - <end> End time for the event. Unsigned 32-bit integer, which represents 
 *     the time at which the function block finished execution of the specified
 *     event.
 *
 * @param id Unique function id (EhsFunctionInstanceIndexType) of the event to 
 *    execute next.
 * @param start Time when event started
 * @param end Time when event finished
 */
EHS_GLOBAL void EhsDebugTraceEvent(EhsTriggerIdType id, EhsTickType start, EhsTickType end);

/**
 * Generate a function start trace message. Format is:
 * #<seq>#<id>#S#<start>.
 * where:
 * - <seq> Sequence number of the event. Unsigned 32-bit integer 
 *     (represented as a decimal string) incrementing with every event that is 
 *     transmitted.
 * - <id> Identifies the line number on which the event/data flow occurs. 
 *     Corresponds to the unique function id derived from the SODL 
 * - <start> time at which the function starts executing. Unsigned 32-bit integer (represented 
 *     as a decimal string). Represents the time (in microseconds) at which 
 *     the function block started executing the specified event
 *
 * @param id Unique function id (EhsFunctionInstanceIndexType) of the event to 
 *    execute next.
 * @param start Time when event started
 */
EHS_GLOBAL void EhsDebugTraceFunctionStart(EhsTriggerIdType id, EhsTickType start);

/**
 * Generate a function finish (end) trace message. Format is:
 * #<seq>#<id>#F#<end>.
 * where:
 * - <seq> Sequence number of the event. Unsigned 32-bit integer 
 *     (represented as a decimal string) incrementing with every event that is 
 *     transmitted.
 * - <id> Identifies the line number on which the event/data flow occurs. 
 *     Corresponds to the unique function id derived from the SODL 
 * - <end> time at which the event completes executing. Unsigned 32-bit integer (represented 
 *     as a decimal string). Represents the time (in microseconds) at which 
 *     the function block started executing the specified event
 *
 * @param id Unique function id (EhsFunctionInstanceIndexType) of the event to 
 *    execute next.
 * @param end Time when function execution finished
 */
EHS_GLOBAL void EhsDebugTraceFunctionFinish(EhsTriggerIdType id, EhsTickType end);

/**
 * Generate a message indicating that trace data has been written to a specific 
 * port associated with a given function. Format is:
 * #<seq>#<id>#D#<contents>.
 * where:
 * - <seq> Sequence number of the event. Unsigned 32-bit integer (represented 
 *     as a decimal string) incrementing with every event that is transmitted
 * - <id> Identifies the line number on which the data flow occurs. Corresponds
 *     to the port id specified in the SODL (see Section 3.2.2)
 * - <contents> a textual representation of the contents of the data flow.
 */
EHS_GLOBAL void EhsDebugTraceDataInt(ehs_sint32* pos);
EHS_GLOBAL void EhsDebugTraceDataBool(ehs_bool* pos);
EHS_GLOBAL void EhsDebugTraceDataString(ehs_char* pos);
#ifdef EHS_TARGET_FP_SUPPORT
EHS_GLOBAL void EhsDebugTraceDataFloat(ehs_float* pos);
/**
 * Generate a message indicating that the event queue has overflowed and that 
 * events are being lost.
 * format is:
 * #<seq>#<id>#O#
 * where:
 * - <id> is the unique function number of the event that has been discarded.
 */
EHS_GLOBAL void EhsDebugTraceEventQueueOverflow(EhsFunctionInstanceIndexType id);
#endif /* EHS_TARGET_FP_SUPPORT */

/**
 * Indicate that a break should occur whenever a specified trigger takes place.
 * @param xBreakpoint Trigger Id on which to break.
 */
EHS_GLOBAL void EhsBreakpointSet(EhsTriggerIdType xBreakpoint);

/**
 * Reset the breakpoint at the specified trigger
 * @param xBreakpoint Trigger Id to clear
 */
EHS_GLOBAL void EhsBreakpointReset(EhsTriggerIdType xBreakpoint); 

/**
 * Reset all currently set breakpoints
 */
EHS_GLOBAL void EhsBreakpointsClear(); 

#endif /* EHS_DEBUG_H */
