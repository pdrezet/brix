/** @file html.c
 * Declares features needed to parse/handle HTML-like text for rendering.
 *
 * @author: Andrew Coombes
 * @version: $Revision: 1136 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */


/**
 * @page Verification Verification report
 * @section hal_graphics_font
 * @anchor hal_graphics_font
 * @subsection misra MISRA compliance:
 * test.c demonstrated MISRA compliant on 
 * Last modified on $Date:$
 *
 * This file contained no derogations to the MISRA standard.
 */

/*****************************************************************************/
/* Included files */

#include "html.h"
#include "mem.h"
#include "hal_string.h"
#include "messages.h"

/*****************************************************************************/
/* Declare macros and local typedefs used by this file */

#define EHSL_MAX_ENTITY_LEN 20 /**< Longer than the longest entity name (see EhsL_szSpecialEntityTable) */

#define EHSL_MAX_TAG_LEN 20 /**< Longer than the longest tag name (see EhsL_szTagTable) */

#define EHSL_MAX_TAG_PARAM_LEN 50 /**< Longest tag param permitted */

/**
 * Detect whether the next character in the parsed Html string
 * is a tag
 */
#define EHSL_IS_TAG(cChr) (((cChr) & 0xd8) == 0xd8)


/*****************************************************************************/
/* Declare prototypes of local functions */

/**
 * Convert a special entity (of the form "&<name>;" into the equivalent utf-8
 * character string.
 * @param[in] start of the string to convert
 * @param[out] pointer to the converted string
 * @return pointer to the character after the special entity
 */ 
EHS_LOCAL const ehs_char* EhsL_getSpecialEntity(const ehs_char* szRawString, const ehs_char** szSpecial);

/**
 * Convert an HTML tag into a special utf-8 character string.
 * @param[in] start of the string to convert
 * @param[out] pointer to the converted string
 * @return pointer to the character after the special entity
 */ 
EHS_LOCAL const ehs_char* EhsL_getTag(const ehs_char* szRawString, const ehs_char** szSpecial);

/*****************************************************************************/
/* Variables defined with file-scope */

/**
 * Look up table for the set of special entities that we support 
 */
EHS_LOCAL struct {
	const ehs_char* szName;
	const ehs_char* szValue;
} EhsL_szSpecialEntityTable[] = {
  {"quot", "\x22"}, 	/* quotation mark = APL quote */
  {"amp", "\x26"}, 		/* ampersand */
  {"lt", "\x3C"}, 		/* less-than sign  */
  {"gt", "\x3E"}, 		/* greater-than sign  */
  {0}					/* end of table */
};

/**
 * Look up table for the HTML tags that we support
 */
EHS_LOCAL struct {
	const ehs_char* szName;
	EhsHGHtmlWordType eTagId;
} EhsL_szTagTable[] = {
		{"p", EHSHG_HTML_WORD_PARA},			/* paragraph */
		{"br",EHSHG_HTML_WORD_BREAK},			/* line break */
		{"img", EHSHG_HTML_WORD_IMG},		/* image */
		{"span", EHSHG_HTML_WORD_STYLE_START},	/* start of an alternate style */
		{"/span", EHSHG_HTML_WORD_STYLE_END}, 	/* end of an alternate style */
		{0}										/* end of table */
};

/*****************************************************************************/
/* Variables defined with global-scope */

/*****************************************************************************/
/* Function definitions */

/**
 * Initialise the HtmlString.
 * @param[in,out] pHtml HtmlString to initialise
 * @param [in] nMaxLen Maximum length of the HTML string. 0 means unknown
 */
ehs_bool EhsHGHtmlString_init(EhsHGHtmlStringClass* pHtml, ehs_uint32 nMaxLen)
{
	ehs_bool bRet = EHS_FALSE;
	
	if (pHtml) {
		if (nMaxLen > 0u) {
			pHtml->szHtml = (ehs_char*)EhsMemWriteable_alloc(nMaxLen);
			if (pHtml->szHtml) {
				pHtml->bFixedMaxLen = EHS_TRUE;
				bRet = EHS_TRUE;
				pHtml->nMaxLen = nMaxLen;
			}
		} else { /* variable length, dynamically allocated string */
			pHtml->szHtml = NULL;
			pHtml->bFixedMaxLen = EHS_FALSE;
			pHtml->nMaxLen = 0u;
		}
		pHtml->szWord = NULL;
		pHtml->nWordLen = 0u;
	}
	
	return bRet;
}

/**
 * Parse a raw string into an instance of this class
 * @param[in,out] pHtml Pointer to the HTML structure that has been parsed
 * @param[in] szRawString The initial string to convert
 * @return true if parsing has been successful
 */ 
ehs_bool EhsHGHtmlString_parse(EhsHGHtmlStringClass* pHtml, const ehs_char* szRawString)
{
	ehs_bool bRet = EHS_TRUE;
	ehs_uint32 nHtmlIdx;
	const ehs_char* szSpecial; /* special characters or the compressed HTML tag */
	
	if (pHtml) {
		if (((EhsStrlen(szRawString)+1) > pHtml->nMaxLen)
				&& (!pHtml->bFixedMaxLen)) {
			/* increase string length for pHtml. This increases monotonically over time.
			 * The underlying assumption is that it will converge on an application-specific
			 * maxima. */
			if (pHtml->szHtml) {
				EhsMemWriteable_free(pHtml->szHtml);
			}
			pHtml->nMaxLen = EhsStrlen(szRawString)+1;
			pHtml->szHtml = (ehs_char*)EhsMemWriteable_alloc(pHtml->nMaxLen);
			if (!pHtml->szHtml) {
				pHtml->nMaxLen = 0;
				bRet = EHS_FALSE;
			}
		}
		
		/* copy and translate raw string into pHtml->szHtml */
		for (nHtmlIdx = 0u; *szRawString && nHtmlIdx < pHtml->nMaxLen;) {
			switch(*szRawString) {
			case '&': /* special character - replace with regular character */
				szRawString = EhsL_getSpecialEntity(szRawString, &szSpecial);
				if (szSpecial) {
					EhsStrcpy_s(&(pHtml->szHtml[nHtmlIdx]), pHtml->nMaxLen - nHtmlIdx, szSpecial);
					nHtmlIdx += EhsStrlen(szSpecial);
				}
				break;
			case '<': /* start of a tag */
				szRawString = EhsL_getTag(szRawString, &szSpecial);
				if (szSpecial) {
					EhsStrcpy_s(&(pHtml->szHtml[nHtmlIdx]), pHtml->nMaxLen - nHtmlIdx, szSpecial);
					nHtmlIdx += EhsStrlen(szSpecial);
				}
				break;
			default: /* regular character - copy unchanged */
				pHtml->szHtml[nHtmlIdx++] = *(szRawString++);
				break;
			}
		}
		pHtml->szHtml[nHtmlIdx] = '\0';
		
	} else {
		bRet = EHS_FALSE;
	}
	
	return bRet;
}

/**
 * Get a word from the HTML string ready to render.
 * @param[in] pHtml Pointer to the HTML structure to read from.
 * @param[out] pszWord Pointer to the word that we've just read.
 * @param[out] peType Type of the word.
 * @param[in,out] ppCurrent Pointer to the start of the next word (used for internal purposes only).
 * If NULL when calling, starts the search from the beginning of the string.
 * @return NULL when there are no more words to return.
 */
void* EhsHGHtmlString_getWord(EhsHGHtmlStringClass* pHtml, const ehs_char** pszWord, EhsHGHtmlWordType* peType, void** ppCurrent)
{
	ehs_char* pRet = NULL;
	
	if (pHtml) {
		ehs_uint32 nLen = 0u;
		/* check to see if we're starting at the beginning, or carrying on
		 * from where we left off */
		if (!(*ppCurrent)) {
			pRet = pHtml->szHtml;
		} else {
			pRet = (ehs_char*)(*ppCurrent);
		}
		
		/* Get start of current word (temporarily) */
		pRet = EhsStrTrimL(pRet);
		*pszWord = pRet;
		
		/* handle the situation if we have a tag */
		if (EHSL_IS_TAG(*pRet)) {
			ehs_uint16 nHigh, nLow;
			nHigh = (ehs_uint8)(pRet[0]);
			nLow = (ehs_uint8)(pRet[1]);
			*peType = (EhsHGHtmlWordType)(((ehs_uint16)(nHigh) << 8u) | nLow); /* convert the two characters into a tag value */
			pRet += 2; /* skip tag part */
			
			/* extract parameters (if applicable) */
			switch(*peType) {
			case EHSHG_HTML_WORD_BREAK:
			case EHSHG_HTML_WORD_PARA:
			case EHSHG_HTML_WORD_STYLE_END:
				/* no parameters expected */
				*pszWord = NULL;
				*ppCurrent = pRet; /* consume tag */
				break;
			case EHSHG_HTML_WORD_STYLE_START:
			case EHSHG_HTML_WORD_IMG:
				/* Put the start of the parameter string into pszWord,
				 * the length goes into nLen, and the character just after the
				 * parameter terminator goes into pRet */
				*pszWord = pRet;
				for (nLen = 0u; (*pRet); nLen++) {
					pRet++;
					if (((ehs_uint8)(pRet[0]) == (0xff & (EHSHG_HTML_WORD_PARAM_END >> 8))) &&
							((ehs_uint8)(pRet[1]) == (EHSHG_HTML_WORD_PARAM_END & 0xff))) {
						nLen++;
						pRet += 2;
						break;
					}
				}
				break;
			default:
				EhsWarning(EHS_MSG_WARNING_HGHTML_IGNORED_INVALID_TAG);
				break;
			}
		} else {
			*peType = EHSHG_HTML_WORD_STYLE_TEXT;
			/* find end (and length) of current word */
			for (nLen = 0u; (*pRet) && !EhsStrIsSpace(*pRet) && !EHSL_IS_TAG(*pRet); nLen++) {
				pRet++;
			}
		}
		
		/* copy the word we've found into pHtml->szWord, then refer to it in pszWord */
		if (nLen > 0u) { /* not end of string, continue */
			*ppCurrent = (void*)pRet;
			
			/* ensure that we have enough space to store the word */
			if ((nLen+1) > pHtml->nWordLen) {
				if (pHtml->szWord) {
					EhsMemWriteable_free(pHtml->szWord);
				}
				pHtml->szWord = EhsMemWriteable_alloc(nLen+1);
				if (pHtml->szWord) {
					pHtml->nWordLen = nLen+1;
				} else {
					pHtml->nWordLen = 0u;
				}
			}
			
			/* copy the word */
			if (pHtml->szWord) {
				EhsStrncpy_s(pHtml->szWord, pHtml->nWordLen, *pszWord, nLen);
				*pszWord = pHtml->szWord;
			} else {
				*pszWord = NULL;
				EhsWarning(EHS_MSG_WARNING_HGHTML_NO_MEM);
			}
		} else if (!(*pRet)) {
			pRet = NULL;
			*ppCurrent = NULL;
			*pszWord = NULL;
		}
	}
	
	return (void *)pRet;
}

/**
 * Convert a special entity (of the form "&<name>;" into the equivalent utf-8
 * character string.
 * @param[in] start of the string to convert
 * @param[out] pointer to the converted string
 * @return pointer to the character after the special entity
 */ 
const ehs_char* EhsL_getSpecialEntity(const ehs_char* szRawString, const ehs_char** szSpecial) {
	ehs_char szEntityName[EHSL_MAX_ENTITY_LEN];
	ehs_uint32 nIdx;
	
	szRawString++; /* we know the first character is '&' */
	
	/* extract the name part of the entity */
	for (nIdx = 0; (nIdx < EHSL_MAX_ENTITY_LEN) && (*szRawString) && (*szRawString != ';'); szRawString++) {
		szEntityName[nIdx++] = *szRawString;
	}
	if (*szRawString == ';') { /* skip trailing ; */
		szRawString++;
	}
	szEntityName[nIdx] = '\0';
	
	/* look up the extracted name */
	*szSpecial = NULL;
	for (nIdx = 0; EhsL_szSpecialEntityTable[nIdx].szName; nIdx++) {
		if (!EhsStricmp(szEntityName,EhsL_szSpecialEntityTable[nIdx].szName)) {
			*szSpecial = EhsL_szSpecialEntityTable[nIdx].szValue;
			break;
		}
	}
	
	if (!(*szSpecial)) {
		EhsWarning(EHS_MSG_WARNING_HGHTML_NO_SPECIAL(szEntityName));
	}
	
	return szRawString;
}


/**
 * Convert an HTML tag into a special utf-8 character string.
 * @param[in] szRawString of the string to convert
 * @param[out] pszTag to the tag
 * @return pointer to the character after the tag
 */ 
const ehs_char* EhsL_getTag(const ehs_char* szRawString, const ehs_char** pszTag)
{
	ehs_char szTagName[EHSL_MAX_TAG_LEN];
	ehs_char* szParams = NULL; /* are there any parameters associated with the tag? */
	ehs_uint32 nIdx;
	EhsHGHtmlWordType eTagId; /* the type of the tag we've recognised */
	static ehs_char szTagString[EHSL_MAX_TAG_PARAM_LEN];
	szRawString++; /* we know the first character is '<' */
	
	/* extract tag name & point to start of parameters (if any) */
	for (nIdx = 0; (nIdx < EHSL_MAX_TAG_LEN) 
					&& (*szRawString) 
					&& (*szRawString != '>') 
					&& (EhsStrncmp(szRawString,"/>",2)); 
				szRawString++) {
		if ((!szParams) && EhsStrIsSpace(*szRawString)) {
			szRawString = EhsStrTrimL(szRawString);
			szParams = szRawString;
		} else if (!szParams) {
			szTagName[nIdx++] = *szRawString;
		}
	}
	szTagName[nIdx] = '\0';
		
	if (*szRawString == '>') { /* skip trailing ">" */
		szRawString++;
	} else if (!EhsStrncmp(szRawString,"/>",2)) { /* skip trailing "/> */
		szRawString += 2;
	}
	
	/* look up the tag name */
	*pszTag = NULL;
	for (nIdx = 0; EhsL_szTagTable[nIdx].szName; nIdx++) {
		if (!EhsStricmp(szTagName,EhsL_szTagTable[nIdx].szName)) {
			
			eTagId = EhsL_szTagTable[nIdx].eTagId;
			szTagString[0] = eTagId >> 8;
			szTagString[1] = eTagId & 0xff;
			szTagString[2] = '\0';
			*pszTag = szTagString;
			break;
		}
	}
	
	/* process parameters - ignore everything apart from the string
	 * enclosed in quotes */
	switch (eTagId) {
	case EHSHG_HTML_WORD_STYLE_START:
		/* need to extract class name from " class="<name>"> */
	case EHSHG_HTML_WORD_IMG:	
		/* need to extract img name from <img src="<name>"> */
		/* find open quote */
		szParams = EhsStrchr(szParams,'"');
		if (szParams) {
			szParams++;
			for (nIdx = 2; nIdx < (EHSL_MAX_TAG_PARAM_LEN-3) && *szParams && *szParams != '"'; nIdx++) {
				szTagString[nIdx] = *(szParams++);
			}
			if (nIdx < (EHSL_MAX_TAG_PARAM_LEN-3)) {
				szTagString[nIdx++] = EHSHG_HTML_WORD_PARAM_END >> 8;
				szTagString[nIdx++] = EHSHG_HTML_WORD_PARAM_END & 0xff;
				szTagString[nIdx] = '\0';
			} else {
				szTagString[EHSL_MAX_TAG_PARAM_LEN-3];
				EhsWarning(EHS_MSG_WARNING_HGHTML_TRUNC_PARAM(szTagString));
			}
		} else {
			EhsWarning(EHS_MSG_WARNING_HGHTML_MISSING_PARAM);
		}
		break;
	case EHSHG_HTML_WORD_BREAK:
	case EHSHG_HTML_WORD_PARA:
	case EHSHG_HTML_WORD_STYLE_END:
	case EHSHG_HTML_WORD_PARAM_END:
		if (szParams) {
			EhsWarning(EHS_MSG_WARNING_HGHTML_IGNORED_PARAMS(szParams));
		}
		break;
	}
	
	return szRawString;
}

