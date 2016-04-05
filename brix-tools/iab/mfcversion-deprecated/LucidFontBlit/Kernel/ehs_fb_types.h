/** @file ehs_fb_types.h
 * In this file, all of the type definitions required by EHS function blocks are given.
 * Any target-specific type definitions are given in target_types.h, which comes from
 * the target folder.
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 957 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_FB_TYPES_H
#define EHS_FB_TYPES_H

#define EHS_FUNCTION_SIZE 32 /**< Maximum length of a function name */
/* This is duplicated from globals.h */
/*********************************************************************************************/
/* Function block definitions */

/**
 * Defines a pointer to a standard identify function (which appears within a function block).
 *
 * @param[in] params Points to the text containing the parameters block
 * @param[out] bytesRequired Used by the identify function to determine how many bytes the context area requires.
 * @param[out] priority I think this is no longer used
 */
typedef void (*EhsIdentifyFuncType)(const ehs_char* params, ehs_uint32* bytesRequired, ehs_uint16* priority);

struct EhsFunctionInstanceDataStruct;

/**
 * Defines a pointer to a standard initialise function appearing within a function block.
 *
 * @param[in] params Points to the text containing the parameters block
 * @param[in] context Points to an area of memory used to store the context for the current instance of the function block
 * @param[in] pCallbackTable Points to the first callback function for this function block
 * @return true if successful
 */
typedef ehs_bool (*EhsInitFuncType)(const ehs_char* params, void* context, struct EhsFunctionInstanceDataStruct* pCallbackTable);

/**
 * Defines a pointer to a standard generic function appearing within a function block.
 *
 * @param[in,out] context Points to an area of memory used to store the context for the current instance of the function block.
 * It's a pointer to a pointer to allow the context area to be reallocated if necessary.
 */
typedef void (*EhsRunFuncType)(struct EhsFunctionInstanceDataStruct* context);

/*lint -e961 ## Required to provide API to allow 3rd parties to create function blocks without clashing in namespace */
#define EHS_FB_IDENTIFY_NAME(fb) (EhsIdentify ## fb) /**< Maps the function block name onto a identify function name */
/*lint +e961 */

/**
 * Macro for defining a function block identity function. Use of macros ensures ease of ability to change parameter lists for all 
 * function blocks should the need arise
 */
#define EHS_FB_IDENTIFY_FUNCTION(x) void EHS_FB_IDENTIFY_NAME(x) (const ehs_char* params, ehs_uint32* bytesRequired, ehs_uint16* priority)
#define EHS_FB_IDENTIFY_PARAMETERS (params) /**< Provides access to the parameters during identification */
#define EHS_FB_IDENTIFY_MEMORY (*bytesRequired) /**< Provides access to the memory requirements during identification */

/*lint -e961 suppress complaint about ##. See definition of EHS_FB_IDENTIFY_NAME */
#define EHS_FB_INIT_NAME(fb) (EhsInit ## fb) /**< Maps the function block name onto an init function name */
/*lint +e961 */

/**
 * Macro for defining a function block initialise function. Use of macros ensures ease of ability to change parameter lists for all 
 * function blocks should the need arise
 */
#define EHS_FB_INIT_FUNCTION(x) ehs_bool EHS_FB_INIT_NAME(x) (const ehs_char* params, EhsFunctionInstanceDataType* pFIdata, EhsFunctionInstanceDataType* pCallbackTable)
#define EHS_FB_INIT_CONTEXT (pFIdata->pObjData) /**< Provides access to the context during initialization */
#define EHS_FB_INIT_PARAMETERS (params) /**< Provides access to the parameters during initialization */
#define EHS_FB_INIT_CALLBACK_FUNCTION_INSTANCE(x) (&(pCallbackTable[-1-(x)])) /**< Provides access to the function instance data for callback functions */

/*lint -e961 suppress complaint about ##. See definition of EHS_FB_IDENTIFY_NAME */
#define EHS_FB_RUN_NAME(fb) (EhsRun ## fb) /**< Maps the function block name onto an run function name */
/*lint +e961 */

/**
 * Macro for defining a function block general-purpose run function. Use of macros ensures ease of ability to change parameter lists for all 
 * function blocks should the need arise
 */
#define EHS_FB_RUN_FUNCTION(x) void EHS_FB_RUN_NAME(x) (EhsFunctionInstanceDataType* pFIdata)
#define EHS_FB_RUN_CONTEXT (pFIdata->pObjData) /**< Provides access to the context within the run function, 
  including the ability to assign new context blocks in its place. */
#define EHS_FB_RUN_CONTEXT_REF (pFIdata)
#define EHS_FB_RUN_FUNCTION_INSTANCE (pFIdata)

/**
 * Declares a single instance of a function that appears within a function block.
 */
typedef struct {
	const ehs_char szName[EHS_FUNCTION_SIZE]; /**< Function name */
	EhsRunFuncType fpRunFunc; /**< Pointer to the function corresponding to the name */
} EhsFuncRefType;

/*lint -e961 suppress complaint about ##. See definition of EHS_FB_IDENTIFY_NAME */
#define EHS_FB_FUNCTABLE_NAME(fb) (EhsFuncTable ## fb) /**< Creates the name for the table of functions */
/*lint +e961 */
#define EHS_FB_FUNCTIONS_START(fb) EhsFuncRefType EHS_FB_FUNCTABLE_NAME(fb)[] = {
#define EHS_FB_FUNCTION_ENTRY(n,f) {n,EHS_FB_RUN_NAME(f)},
#define EHS_FB_FUNCTIONS_END {0}};

#define EHS_FB_FUNCTIONS(fb) EHS_GLOBAL EhsFuncRefType EHS_FB_FUNCTABLE_NAME(fb)[];

/*********************************************************************************************/
typedef ehs_sint16 EhsFunctionInstanceIndexType; /**< Provides the index of a specific start event. Indexes into EhsFunctionInstanceDataTable */
#define EHS_START_INDEX_INVALID ((EhsTriggerIdType)(-1))

typedef ehs_sint16 EhsTriggerIdType; /**< Used to identify a specific trigger id */

/**
 * This type holds the array of start ports that are activated when a single finish port is notified.
 * Each instance of this type corresponds to a specific trigger id.
 */
typedef struct {
	EhsTriggerIdType nTriggerId; /**< Identifies the Id of this trigger */
	ehs_uint16 nStartPorts; /**< Number of start ports connected to the finish port */
	EhsFunctionInstanceIndexType *piComp; /**< Index of each start port */
	ehs_bool bMonitor;		/**< True if this trigger is monitored */
} EhsTriggerType;
/**
 *
 */

typedef ehs_sint32 EhsDataflowIntType;
#define EHS_DATAFLOW_INT_MAX EHS_SINT32_MAX

typedef ehs_bool EhsDataflowBoolType;
typedef char* EhsDataflowStringType;
typedef double EhsDataflowFloatType;

/*********************************************************************************************/
/* Connection macros used by components */

/**
 * Get input x - generic version - needs to be casted before use
 */
#define EHS_FB_IN(x) EHS_FB_RUN_FUNCTION_INSTANCE->pIn[x]

/**
 * Check whether input x is connected or not
 */
#define EHS_FB_IN_CONNECTED(x) (EHS_FB_IN(x) != EhsDataConnectionTable.xDummy)

/**
 * Get input x as an integer
 */
#define EHS_FB_IN_I(x) *(EhsDataflowIntType*)EHS_FB_IN(x)

/**
 * Get input x as a float
 */
#define EHS_FB_IN_F(x) *(EhsDataflowFloatType*)EHS_FB_IN(x)

/**
 * Get input x as a bool
 */
#define EHS_FB_IN_B(x) *(ehs_bool*)EHS_FB_IN(x)

/**
 * Get input x as a string
 */
#define EHS_FB_IN_S(x) (char*)EHS_FB_IN(x)

/**
 * Get output x - generic version
 */
#define EHS_FB_OUT(x) (EHS_FB_RUN_FUNCTION_INSTANCE->pOut[x])

/**
 * Get output x as a bool
 */
#define EHS_FB_OUT_B(x) *(ehs_bool*)EHS_FB_OUT(x)

/**
 *  Get output x as an integer
 */
#define EHS_FB_OUT_I(x) *(EhsDataflowIntType*)EHS_FB_OUT(x)

/**
 * Get output x as a float
 */
#define EHS_FB_OUT_F(x) *(EhsDataflowFloatType*)EHS_FB_OUT(x)

/**
 * Get output x as a string
 */
#define EHS_FB_OUT_S(x) (char*)EHS_FB_OUT(x)

/**
 * Assert event x
 */
#define EHS_FB_FINISH(x) EhsFunctionInstanceData_triggerEvent(EHS_FB_RUN_CONTEXT_REF,(x))

/*********************************************************************************************/
/******************************************************/
/* MACROS  	used in components                    */
/******************************************************/

/*The following should be but in an 'API header' for use by function c modules */
/* useful (side effect free!) #define macros for the API...*/
/* useful starting #defines to work with...*/

#define NCAPSA_pMain (structFuncArg*)(&EHS_FB_RUN_CONTEXT)

/* quantities first...*/
#define NCAPSA_nNumIns EHS_FB_RUN_FUNCTION_INSTANCE->nNumInputs
#define NCAPSA_nNumOuts EHS_FB_RUN_FUNCTION_INSTANCE->nNumOutputs

#define NCAPSA_nNumComps(x) EHS_FB_RUN_FUNCTION_INSTANCE->nNumCompletes[x]

/* useful debugging location #defines...*/
#define NCAPSA_pIn(x) EHS_FB_IN(x)
#define NCAPSA_pOut(x) EHS_FB_RUN_FUNCTION_INSTANCE->pOut[x]
#define NCAPSA_pComp1(x) EHS_FB_RUN_FUNCTION_INSTANCE->pComp[0][x]
#define NCAPSA_pComp2(x) EHS_FB_RUN_FUNCTION_INSTANCE->pComp[1][x]
#define NCAPSA_pComp3(x) EHS_FB_RUN_FUNCTION_INSTANCE->pComp[2][x]
#define NCAPSA_pComp4(x) EHS_FB_RUN_FUNCTION_INSTANCE->pComp[3][x]
#define NCAPSA_pComp5(x) EHS_FB_RUN_FUNCTION_INSTANCE->pComp[4][x]
#define NCAPSA_pComp6(x) EHS_FB_RUN_FUNCTION_INSTANCE->pComp[5][x]
#define NCAPSA_pComp7(x) EHS_FB_RUN_FUNCTION_INSTANCE->pComp[6][x]
#define NCAPSA_pComp8(x) EHS_FB_RUN_FUNCTION_INSTANCE->pComp[7][x]

/* data accessor macros - inputs...*/
#define NCAPSA_nIn(x) EHS_FB_IN_I(x)
#define NCAPSA_dIn(x) EHS_FB_IN_F(x)
#define NCAPSA_bIn(x) EHS_FB_IN_B(x)
#define NCAPSA_szIn(x) EHS_FB_IN_S(x)
/* data accessor macros - outputs...*/
#define NCAPSA_nOut(x) EHS_FB_OUT_I(x)
#define NCAPSA_dOut(x) EHS_FB_OUT_F(x)
#define NCAPSA_bOut(x) EHS_FB_OUT_B(x)
#define NCAPSA_szOut(x) EHS_FB_OUT_S(x)
/* data accessor macors  - completes...*/
#define NCAPSA_bComp1(x) *(ehs_bool*)NCAPSA_pComp1(x)
#define NCAPSA_bComp2(x) *(ehs_bool*)NCAPSA_pComp2(x)
#define NCAPSA_bComp3(x) *(ehs_bool*)NCAPSA_pComp3(x)
#define NCAPSA_bComp4(x) *(ehs_bool*)NCAPSA_pComp4(x)
#define NCAPSA_bComp5(x) *(ehs_bool*)NCAPSA_pComp5(x)
#define NCAPSA_bComp6(x) *(ehs_bool*)NCAPSA_pComp6(x)
#define NCAPSA_bComp7(x) *(ehs_bool*)NCAPSA_pComp7(x)
#define NCAPSA_bComp8(x) *(ehs_bool*)NCAPSA_pComp8(x)
#define NCAPSA_pLocState (((ehs_uint8*)(pByte[0])))

/* data accessor macros - data type ids and data table element locations
 * char cDataType[MAX_NUM_OUTPUTS];
	int nLocation[MAX_NUM_OUTPUTS];
 */
#define NCAPSA_cDataType(x) EHS_FB_RUN_FUNCTION_INSTANCE->cDataType[x]
#define NCAPSA_nLocation(x) EHS_FB_RUN_FUNCTION_INSTANCE->nLocation[x]

#endif /* EHS_TYPES_H */

