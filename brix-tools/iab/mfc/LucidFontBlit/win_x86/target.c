/** @file target.c
 * In this file, all of the hardware abstraction layer functions provided for EHS are defined.
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 971 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#define EHS_TARGET_CODE /* Ensure header files include target-internal values */

#include "messages.h"
#include "target.h"
#include <math.h>
#include "blockref_table.h"
#include "callback_queue.h"
#include <windows.h>
#include "hal_viewport.h"
#include "hal_console.h"

/* from keypress.c */
extern EhsBlockRefType EhsBlockRefTable_windows[];
extern EhsCallbackQueueType EhsWindowsKeypressCallback;
extern EhsBlockRefType EhsBlockRefTable_Dtv[];

extern EhsConsoleQueueType EhsTgtConsoleInputQueue;
extern EhsConsoleQueueType EhsTgtConsoleOutputQueue;


/**
 * Implementation of asinh as VisualStudio doesn't provide one.
 */
double asinh(double x)
{
	double ret = log(x + sqrt(x*x+1));

	return ret;
}

/**
 * Implementation of acosh as VisualStudio doesn't provide one.
 */
double acosh(double x)
{
	double ret = log(x + sqrt(x*x-1));

	return ret;
}

/**
 * Implementation of atanh as VisualStudio doesn't provide one.
 */
double atanh(double x)
{
	double ret = 0.5 * log((1+x)/(1-x));

	return ret;
}

ehs_FILE* EhsConsoleOutputPointer;

DWORD dwError;

/**
 * Flag to indicate that initialisation has been completed for the target.
 */
ehs_bool EhsTgtInitComplete;
ehs_bool *EhsTgtInitCompleteRef = &EhsTgtInitComplete;

/** 
 * Perform necessary Target Setup upon system initialisation
 *
void EhsTargetInit(void)
{
	dwError = EhsTgtTimer_init();
#ifdef EHS_GUI_SUPPORT
	EhsTgtViewport_init(&EhsTgtViewport);
#endif / * EHS_GUI_SUPPORT * /
	
	EhsConsoleOutputPointer = fopen("consolemsg.txt","w");
	EhsToolkitTable_addTable(EhsBlockRefTable_windows);
	EhsToolkitTable_addTable(EhsBlockRefTable_Dtv);

	EhsTgtConsoleInputQueueRef = &EhsTgtConsoleInputQueue;
	EhsTgtConsoleOutputQueueRef = &EhsTgtConsoleOutputQueue;
	EhsConsoleQueue_reset(EhsTgtConsoleInputQueueRef);
	EhsConsoleQueue_reset(EhsTgtConsoleOutputQueueRef);

	/ * set flag to indicate to other threads that EHS is now in business * /
	EhsTgtInitComplete = EHS_TRUE;
}
*/

/**
 * Perform setup before loading in a new application
 */
void EhsTargetApplicationInit(void)
{
	EhsWindowsKeypressCallback = NULL;
}

/**
 * Perform necessary target setup per application execution
 */
void EhsTargetApplicationReset(void)
{
}

/**
 * Performs sine function using integers.
 *
 * @param nMult multiplier for output
 * @param nAngle angle to find (0 to 360)
 * @return nMult * sin(nAngle % 360)
 */
EHS_GLOBAL ehs_sint32 EhsTgtInt_sin(ehs_sint32 nMult, ehs_sint32 nAngle)
{
	double dAngle = (nAngle / 360.0) * 2 * 3.1415926535897932384626433832795;
	double dRet = sin(dAngle) * nMult;

	return (ehs_sint32)dRet;
}

/**
 * Performs cosine function using integers.
 *
 * @param nMult multiplier for output
 * @param nAngle angle to find (0 to 360)
 * @return nMult * cos(nAngle % 360)
 */
EHS_GLOBAL ehs_sint32 EhsTgtInt_cos(ehs_sint32 nMult, ehs_sint32 nAngle)
{
	double dAngle = (nAngle / 360.0) * 2 * 3.1415926535897932384626433832795;
	double dRet = cos(dAngle) * nMult;

	return (ehs_sint32)dRet;
}
