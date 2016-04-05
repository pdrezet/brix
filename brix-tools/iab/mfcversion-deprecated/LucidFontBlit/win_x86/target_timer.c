/** @file target_timer.c
 * Definitions for target-specific time-related functions
 * 
 *
 * @author: Andrew Coombes
 * @version: $Revision: 885 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */

#define EHS_TGT_CODE /* Ensure header files include target-internal values */
#include "hal_time.h"
#include "timer.h"
#include <windows.h>

#ifndef EHS_TARGET_FIXED_TIMER_RESOLUTION
/**
 * Defines the current clock frequency used for this device
 */
static double EhsClockFrequency;
#endif
	
/**
 * Set up the target timer
 */
ehs_uint32 EhsTgtTimer_init(void)
{
	ehs_uint32 dwError = 0;
	#ifndef EHS_TARGET_FIXED_TIMER_RESOLUTION
	__int64 clockFreq;
	if (!QueryPerformanceFrequency(&clockFreq))
	{
		dwError = GetLastError();
		/** @todo Provide error handling if performance clock isn't supported */
	}
	else
	{
		EhsClockFrequency = clockFreq;
	}
#endif
	return dwError;	
}

/**
 * Return the current time in EHS ticks
 */
EhsTickType EhsTgtTimer_now(void)
{
#ifdef EHS_TARGET_FIXED_TIMER_RESOLUTION
	return (GetTickCount() & EHS_TICKTYPE_MAX);
#else
	EhsTickType ret;

	QueryPerformanceCounter(&ret);

	ret = (EhsTickType)(ret & EHS_TICKTYPE_MAX);

	return ret;
#endif
}

/**
 * Sleep the current thread for a specified duration
 *
 * @param tSleepTime Time to sleep for in target-specific ticks
 */
void EhsSleep(EhsTickType tSleepTime)
{
	Sleep(EhsTgtTimer_tickTous(tSleepTime)/1000);
}

#ifndef EHS_TARGET_FIXED_TIMER_RESOLUTION

/**
 * convert microseconds to target-specific ticks
 *
 * @param us Time in microseconds
 * @return equivalent time in target-specific ticks
 */
EhsTickType EhsTgtTimer_usToTick(ehs_uint32 us)
{
	double ret = (EhsClockFrequency/1e6)*((double)us);

	return (EhsTickType)ret;
}

/**
 * convert target-specific ticks to microseconds 
 *
 * @param tick Time in microseconds
 * @return equivalent time in target-specific ticks
 */
ehs_uint32 EhsTgtTimer_tickTous(EhsTickType tick)
{
	double ret = (1e6/EhsClockFrequency)*((double)tick);

	return (ehs_uint32)ret;
}

#endif

EhsTickType EhsTgtTimerExpiryTime;

/**
 * Initialise the target-specific timer (to be not running)
 */
void EhsTgtTimer_reset(void)
{
	EhsTgtTimer_clear();
}

/*
 * Set the target-specific timer to expire at a specific time.
 * Upon expiry (or periodically if the target's timing facility
 * is unsophisticated), call EhsTimer_tick()
 */
void EhsTgtTimer_set(EhsTickType tExpiryTime)
{
	EhsTgtTimerExpiryTime = tExpiryTime;
}

/**
 * Stop the target-specific timer from calling EhsTimer_tick(), cancel
 * any pending events
 */
void EhsTgtTimer_clear()
{
	EhsTgtTimerExpiryTime = EHS_TICKTYPE_INVALID;
}

/**
 * Report expiry time for current timer
 *
 * @return the time when the timer will call EhsTimer_tick, or EHS_TICKTYPE_INVALID
 * if no timer is running
 */
EhsTickType EhsTgtTimer_expiry()
{
	return EhsTgtTimerExpiryTime;
}

/**
 * This is only needed if we've gone for the application polling method.
 * @returns it *must* return true.
 */
ehs_bool EhsTgtTimer_tick()
{
	if ((EhsTgtTimerExpiryTime != EHS_TICKTYPE_INVALID) &&
		EHS_TARGET_TIME_IS_EARLIER(EhsTgtTimerExpiryTime,EHS_CURRENT_TIME))
	{
		EhsTimer_tick();
	}

	return EHS_TRUE;
}
