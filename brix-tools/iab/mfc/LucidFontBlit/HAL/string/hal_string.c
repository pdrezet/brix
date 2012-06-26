/** @file hal_string.c
 * In this file, target-indpendent code used by the hardware abstraction layer is defined.
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 1120 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

/**
 * @page Verification Verification report
 * @section hal_string_c
 * @anchor hal_string_c
 * @subsection misra MISRA compliance:
 * Demonstrated MISRA compliant on 
 * Last modified on $Date:$
 *
 * This file contained the following derogations to the MISRA standard.
 * - Rule 16.1 Functions shall not have variable number of arguments. Required for target library functions.
 */

/*****************************************************************************/
/* Included files */
#include "hal_string.h"
#include "globals.h"
#include "messages.h"

/*****************************************************************************/
/* Declare macros and local typedefs used by this file */

/*****************************************************************************/
/* Declare prototypes of local functions */
/*****************************************************************************/
/* Variables defined with file-scope */
/*****************************************************************************/
/* Variables defined with global-scope */
/*****************************************************************************/
/* Function definitions */

/**
 * Trim the whitespace from the left hand end of a string. The
 * argument and return value can safely be const because trimming can be
 * done by changing the pointer.
 * 
 * @param[in] pSrc Pointer to the string to trim
 * @return pointer to the trimmed string or NULL if error.
 */
const ehs_char* EhsStrTrimL(const ehs_char* pSrc)
{
	if (pSrc)
	{
		while (EhsStrIsSpace(*pSrc))
			pSrc++;
	}
	
	return pSrc;
}

/**
 * Trim the whitespace from the right hand end of a string
 * 
 * @param[in] pSrc Pointer to the string to trim
 * @return pointer to the trimmed string (or NULL if error)
 */
ehs_char* EhsStrTrimR(ehs_char* pSrc)
{
	ehs_sint16 nLast; /* index of last character */
	
	if (pSrc)
	{
		nLast = EhsStrlen(pSrc); /* get last character */
		
		while (nLast > 0u) /* go backwards until we get to the first character */
		{
			nLast--;
			if (EhsStrIsSpace(pSrc[nLast]))
			{
				pSrc[nLast] = '\0'; /* overwrite spaces with line terminator */
			}
			else
			{
				break; /* if it's not a space we stop trimming */
			}
			
		}
	}
	
	return pSrc;
}

/**
 * Trim the whitespace from both ends of a string
 * 
 * @param[in] pSrc Pointer to the string to trim
 * @return pointer to the trimmed string (or NULL if error)
 */
ehs_char* EhsStrTrimLR(ehs_char* pSrc)
{
	pSrc = (ehs_char*)EhsStrTrimL(pSrc); /* discard const-ness of EhsStrTrimL return value */
	pSrc = EhsStrTrimR(pSrc);
	
	return pSrc;
}

/**
 * Determine if character is a-z or A-Z
 */
EHS_GLOBAL ehs_bool EhsIsAlpha(char c)
{
	return (EHS_TO_LOWER(c) >= 'a' && EHS_TO_LOWER(c) <= 'z');
}

/**
 * Determine if character is a-z or A-Z or 0-9
 */
EHS_GLOBAL ehs_bool EhsIsAlNum(char c)
{
	return ((EHS_TO_LOWER(c) >= 'a' && EHS_TO_LOWER(c) <= 'z')||
		    (c >= '0' && c <= '9'));

}


/**
 * Read an unsigned 32-bit integer from a line of the SODL file.
 * Generates an error message and sets EhsParseFailed if the value
 * exceeds EHS_UINT32_MAX
 *
 * @todo make this into a general-purpose function (not parse-only). It's already used that way.
 * @todo Move console printf into parser
 *
 * @param output Integer read from input (0 if integer can't be found).
 * @param input String containing SODL input.
 * @return Pointer to updated input string (i.e. after reading the integer)
 */
char* EhsGetUint32FromString(ehs_uint32 * output, char* input) 
{
	ehs_uint16 i;
	ehs_uint32 digit;

	input = EhsStrTrimL(input);

	*output=0;

	if ((NULL == input) || (*input < '0') || (*input > '9'))
	{
		input = NULL;
	}
	else
	{
		/* convert any numbers into an integer */
		for (i=0;(i<EHS_STRING_LENGTH_MAX)&&((*input >= '0') && (*input <= '9'));i++) 
		{
			digit = (*input - '0');
			if (*output >= (EHS_UINT32_MAX/10u))
			{
				if ((*output != (EHS_UINT32_MAX/10u)) ||
					((EHS_UINT32_MAX % 10u) < digit))
				{
					//EhsConsolePrintf(EHS_MSG_PARSER_UINT32_RANGE(*output,digit));
				}
			}
			*output = (*output * 10) + (*input - '0');
			input++;
		}
	}

	/* check for end-of-file */
	if ((NULL != input) && (*input == 25))
	{
		input = NULL;
	}

	return input;
}


/**
 * Read a signed 32-bit integer from a line of the SODL file.
 * Generates an error message and sets EhsParseFailed if the value
 * falls outside EHS_SINT32_MIN .. EHS_SINT32_MAX
 * @todo Move console printf into parser
 *
 * @param output Integer read from input (0 if integer can't be found).
 * @param input String containing SODL input.
 * @return Pointer to updated input string (i.e. after reading the integer)
 */
const char* EhsGetSint32FromString(ehs_sint32 * output, const char* input) 
{
	int i=0;
	ehs_bool isNegative = EHS_FALSE;
	ehs_uint32 nAbsVal; /* unsigned value from SODL_GetUint */

	input = EhsStrTrimL(input);

	/* check for leading '-' */
	if ((NULL != input) && (*input == '-'))
	{
		isNegative = EHS_TRUE;
		input++;
	}

	input = EhsGetUint32FromString(&nAbsVal,input); 

	if (input)
	{
		if ((nAbsVal <= EHS_SINT32_MAX) ||
			(isNegative && (nAbsVal <= (ehs_uint32)(-1 * EHS_SINT32_MAX))))
		{
			*output = (isNegative)?nAbsVal*-1:nAbsVal;
		}
		else
		{
			//EhsConsolePrintf(EHS_MSG_PARSER_SINT32_RANGE(nAbsVal));
			input = NULL;
		}

		/* check for end-of-file */
		if (*input == 25)
		{
			input = NULL;
		}
	}

	return input;
}

/**
 * Read a signed 16-bit integer from a line of the SODL file.
 * Generates an error message and sets EhsParseFailed if the value
 * exceeds EHS_SINT16_MAX
 * @todo Move console printf into parser
 *
 * @param output Integer read from input (0 if integer can't be found).
 * @param input String containing SODL input.
 * @return Pointer to updated input string (i.e. after reading the integer), or null if parse fails
 */
char* EhsGetSint16FromString(ehs_sint16* output, const char* input)
{
	ehs_sint32 nValue;

	input = EhsGetSint32FromString(&nValue, input);

	if (input)
	{
		if ((nValue > EHS_SINT16_MAX) || (nValue < EHS_SINT16_MIN))
		{
			//EhsConsolePrintf(EHS_MSG_PARSER_UINT16_RANGE(nValue));
			input = NULL;
		}
		else
		{
			*output = (ehs_uint16)nValue;
		}
	}

	return input;
}


/**
 * Read an unsigned 16-bit integer from a line of the SODL file.
 * Generates an error message and sets EhsParseFailed if the value
 * exceeds EHS_UINT16_MAX
 * @todo Move console printf into parser
 *
 * @param output Integer read from input (0 if integer can't be found).
 * @param input String containing SODL input.
 * @return Pointer to updated input string (i.e. after reading the integer), or null if parse fails
 */
char* EhsGetUint16FromString(ehs_uint16* output, const char* input)
{
	ehs_uint32 nValue;

	input = EhsGetUint32FromString(&nValue, input);

	if (input)
	{
		if (nValue > EHS_UINT16_MAX)
		{
			//EhsConsolePrintf(EHS_MSG_PARSER_UINT16_RANGE(nValue));
			input = NULL;
		}
		else
		{
			*output = (ehs_uint16)nValue;
		}
	}

	return input;
}

/**
 * Read an unsigned 8-bit integer from a line of the SODL file.
 * Generates an error message and sets EhsParseFailed if the value
 * exceeds EHS_UINT8_MAX
 * @todo Move console printf into parser
 *
 * @param output Integer read from input (0 if integer can't be found).
 * @param input String containing SODL input.
 * @return Pointer to updated input string (i.e. after reading the integer)
 */
const char* EhsGetUint8FromString(ehs_uint8* output, const char* input)
{
	ehs_uint32 nValue;

	input = EhsGetUint32FromString(&nValue, input);

	if (input)
	{
		if (nValue > EHS_UINT8_MAX)
		{
			//EhsConsolePrintf(EHS_MSG_PARSER_UINT8_RANGE(nValue));
			input = NULL;
		}
		else
		{
			*output = (ehs_uint8)nValue;
		}
	}

	return input;
}


/**
 * Return a pointer to the character after the end of line character,
 * or null. The end of line character can be CR (0x0d), LF (0x0a) or CRLF.
 */
const ehs_char* EhsGetEol(const ehs_char* input)
{
	ehs_char* pEol = strchr(input,0x0d);
	if (pEol)
	{
		/* is CR followed by LF? */
		if (pEol[1] == 0xa)
		{
			pEol++;
		}
	}
	else
	{
		pEol = strchr(input, 0x0a);
	}
	if (pEol)
	{
		pEol++;
	}
	return pEol;
}


