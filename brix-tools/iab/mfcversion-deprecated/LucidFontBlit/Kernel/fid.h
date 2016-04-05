/** @file fid.h
 * Declarations for the EhsFunctionInstanceDataType and related functions
 * 
 * @author: Andrew Coombes
 * @version: $Revision: 983 $
 * @date: $Date: 2006-10-30 05:05:44 +0000 (Mon, 30 Oct 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef _FUNCTION_INSTANCE_DATA_H
#define _FUNCTION_INSTANCE_DATA_H

#include "ehs_defs.h"
#include "target_types.h"
#include "ehs_fb_types.h"

typedef struct EhsFunctionInstanceDataStruct {
	void* pObjData;
	EhsRunFuncType fpRunFunc; /**< Pointer to the function to run when this function is invoked */
	ehs_uint8 nNumInputs; /**< Number of data inputs to this function block */
	ehs_uint8 nNumOutputs; /**< Number of data outputs to this function block */
	ehs_uint8 nFinishPorts; /**< The number of finish ports that can be accessed by this function */
	EhsTriggerType** pFinishPort; /**< Provides access to the set of start ports that are connected to each finish port */
	void** pIn;
	void** pOut;
	ehs_char* cDataOutType; /**< The type of each output data port */
	ehs_bool bMonitored;	/**< Indicates whether we should tell the debugger about the start and finish of this function */
} EhsFunctionInstanceDataType;

/**
 * Set the monitor flag of the specified function instance
 */
#define EhsFunctionInstanceData_monitorFunction(pFunc,bMntr) (pFunc)->bMonitored = (bMntr)

#define EhsFunctionInstanceData_triggerEventReversedParams(x,pByte) EhsFunctionInstanceData_triggerEvent(pByte,x)

#define SetCompletes(p) EhsFunctionInstanceData_triggerEvent(p,1)
#define SetCompletes1(p) EhsFunctionInstanceData_triggerEvent(p,1)
#define SetCompletes2(p) EhsFunctionInstanceData_triggerEvent(p,2)
#define SetCompletes3(p) EhsFunctionInstanceData_triggerEvent(p,3)
#define SetCompletes4(p) EhsFunctionInstanceData_triggerEvent(p,4)
#define SetCompletes5(p) EhsFunctionInstanceData_triggerEvent(p,5)
#define SetCompletes6(p) EhsFunctionInstanceData_triggerEvent(p,6)
#define SetCompletes7(p) EhsFunctionInstanceData_triggerEvent(p,7)
#define SetCompletes8(p) EhsFunctionInstanceData_triggerEvent(p,8)
/* default is to only reset one event - no multiple event */

EHS_GLOBAL void EhsFunctionInstanceData_triggerEvent(EhsFunctionInstanceDataType* pByte, ehs_uint32 x);


#endif /* _FUNCTION_INSTANCE_DATA_H */

