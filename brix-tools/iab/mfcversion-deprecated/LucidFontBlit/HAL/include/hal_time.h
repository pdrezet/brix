/** @file hal_time.h
 * In this file, all of the hardware abstraction layer functions relating to time are given.
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 1120 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_HAL_TIME_H
#define EHS_HAL_TIME_H

/*****************************************************************************/
/* Included files */
#include "target_types.h"
#include "target_time.h"

/*****************************************************************************/
/* Define macros  */

/******************************************************************************/
/* Time handling functions */

/**
 * Add a time onto the current time. Handles timer wrap-around in the event that
 * current time+offset causes the timer to wrap.
 */
#define EHS_CURRENT_TIME_OFFSET(x) (((x) + EHS_CURRENT_TIME) & EHS_TICKTYPE_MAX)

/**
 * Determine whether one time (x) is earlier than another (y).
 * Relies upon Y and X always being less than or equal to EHS_TICKTYPE_MAX.
 * To deal with roll-over, we assume that no time difference will be greater than
 * half of the largest value that can be represented by EhsTickType (half of EHS_TICKTYPE_MAX).
 * We further assume that unsigned integer arithmetic handles overflows silently: for
 * example (1 - 0xf) % 0x10 should produce 2. 
 */
#define EHS_TARGET_TIME_IS_EARLIER(x,y) ((((y) - (x)) & EHS_TICKTYPE_MAX) <= (EHS_TICKTYPE_MAX/2u))

/**
 * Determine the difference between one time and another.
 */
#define EHS_TGT_TIME_DIFFERENCE(early,later) (((later) - (early)) % EHS_TICKTYPE_MAX)


/**
 * Read current time in target-specific ticks - using a fairly coarse-grained timer
 */
#define EHS_CURRENT_TIME (EhsTgtTimer_now())
/**
 * Provides old definition of Current time function.
 * @todo delete this
 */
#define EhsCurrentTime EhsTgtTimer_now


/* time conversion macros - optimised for the specific timer resolution of this device */ 
#ifdef EHS_TARGET_FIXED_TIMER_RESOLUTION
#define EHS_TIME_us(x) ((EhsTickType)((x)/EHS_uS_PER_TICK))		/**< Convert a time in microseconds to system ticks */
#define EHS_TIME_ms(x) ((EhsTickType)(x)/(EHS_uS_PER_TICK * 1000u))	/**< Convert a time in ms to system ticks */
#define EHS_TIME_s(x) ((EhsTickType)((x) * EHS_TICKS_PER_S))	/**< Convert a time in seconds to system ticks */
#else
#define EHS_TIME_us(x) (EhsTgtTimer_usToTick(x))							/**< Convert a time in microseconds to system ticks */
#define EHS_TIME_ms(x) (EhsTgtTimer_usToTick((x)*1000))					/**< Convert a time in milliseconds to system ticks */
#define EHS_TIME_s(x) (EhsTgtTimer_usToTick((x)*1000000))				/**< Convert a time in seconds to system ticks */
#endif

/**
 * Allow the application to cooperatively test to see if timers
 * have expired. Normally, this is handled in hardware (and
 * the macro is set to 1). However, for dumb targets or for a 
 * quick port, this provides a way of polling the timer
 */
#define EHS_TARGET_TIMER_TICK EhsTgtTimer_tick()


/*****************************************************************************/
/* Define types */

/*****************************************************************************/
/* Declare global variables */

/*****************************************************************************/
/* Declare function prototypes  */

/**
 * Sleep the current thread for a specified duration
 *
 * @param tSleepTime Time to sleep for in target-specific ticks
 */
EHS_GLOBAL void EhsSleep(EhsTickType tSleepTime);

/**
 * convert microseconds to target-specific ticks
 *
 * @param us Time in microseconds
 * @return equivalent time in target-specific ticks
 */
#ifndef EhsTgtTimer_usToTick
EHS_GLOBAL EhsTickType EhsTgtTimer_usToTick(ehs_uint32 us);
#endif

/**
 * Converts target-specific times to microseconds
 *
 * @param ticks time in target-specific ticks
 * @return equivalent time in microseconds
 */
#ifndef EhsTgtTimer_tickTous
EHS_GLOBAL ehs_uint32 EhsTgtTimer_tickTous(EhsTickType tick);
#endif

/**
 * Initialise the target-specific timer (to be not running)
 */
EHS_GLOBAL void EhsTgtTimer_reset(void);

/**
 * This is only needed if we've gone for the application polling method.
 * @returns it *must* return true.
 */
EHS_GLOBAL ehs_bool EhsTgtTimer_tick(void);

/**
 * Set the target-specific timer to expire at a specific time.
 * Upon expiry (or periodically if the target's timing facility
 * is unsophisticated), call EhsTimer_tick()
 */
EHS_GLOBAL void EhsTgtTimer_set(EhsTickType tExpiryTime);

/**
 * Stop the target-specific timer from calling EhsTimer_tick(), cancel
 * any pending events
 */
EHS_GLOBAL void EhsTgtTimer_clear(void);

/**
 * Report expiry time for current timer
 *
 * @return the time when the timer will call EhsTimer_tick, or EHS_TICKTYPE_INVALID
 * if no timer is running
 */
EHS_GLOBAL EhsTickType EhsTgtTimer_expiry(void);

/**
 * Read current time in target-specific ticks - using a fairly coarse-grained timer
 * Returns a value in the range 0 to EHS_TICKTYPE_MAX.
 */
EHS_GLOBAL EhsTickType EhsTgtTimer_now(void);

#endif /* EHS_HAL_TIME_H */
