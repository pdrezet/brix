/** @file font.c
 * Definitions for EhsGraphicsFontClass
 *
 * @author: Andrew Coombes
 * @version: $Revision: 1138 $
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
#include "font.h"
#include "hal_file.h"
#include "hal_string.h"
#include "messages.h"
#include "mem.h"

/*****************************************************************************/
/* Declare macros and local typedefs used by this file */

#define MAX_LEN_BDF_KEYWORD 15 /**< Number of characters in the longest bdf keyword.
	* 15 is longest in specification */
#define MAX_LEN_BDF_PARAMETER 255 /**< The longest set of BDF parameters we can 
	* usefully deal with */

#define BDF_STARTFONT 	0 /**< Indicates the position of STARTFONT in pszBdfKeywords */
#define BDF_FONT		1 /**< Indicates the position of FONT in pszBdfKeywords */
#define BDF_SIZE		2 /**< Indicates the position of SIZE in pszBdfKeywords */
#define BDF_FONTBBOX	3 /**< Indicates the position of FONTBOUNDINGBOX in pszBdfKeywords */
#define BDF_CHARS		4 /**< Indicates the position of CHARS in pszBdfKeywords */
#define BDF_ENDFONT		5 /**< Indicates the position of ENDFONT in pszBdfKeywords */

#define BDF_STARTCHAR 0 /**< Indicates the position of STARTCHAR in pszBdfGlyphKeywords */
#define BDF_ENCODING 1 /**< Indicates the position of ENCODING in pszBdfGlyphKeywords */
#define BDF_SWIDTH0 2 /**< Indicates the position of SWIDTH in pszBdfGlyphKeywords */
#define BDF_DWIDTH0 		3 /**< Indicates the position of DWIDTH in pszBdfGlyphKeywords */
#define BDF_SWIDTH1 	4 /**< Indicates the position of SWIDTH1 in pszBdfGlyphKeywords */
#define BDF_DWIDTH1 	5 /**< Indicates the position of DWIDTH1 in pszBdfGlyphKeywords */
#define BDF_VVECTOR 	6 /**< Indicates the position of VVECTOR in pszBdfGlyphKeywords */
#define BDF_BBX 		7 /**< Indicates the position of BBX in pszBdfGlyphKeywords */
#define BDF_BITMAP 		8 /**< Indicates the position of BITMAP in pszBdfGlyphKeywords */
#define BDF_ENDCHAR 9 /**< Indicates the position of ENDCHAR in pszBdfGlyphKeywords */

#define LOAD_GLOBAL_CONTINUE 	0	/**< keep reading file */
#define LOAD_GLOBAL_ERROR 		1	/**< an error has occured, abandon the file */
#define LOAD_GLOBAL_GLYPHS 		2	/**< the individual glyph data now needs to be loaded */
#define LOAD_GLOBAL_EOF 		3	/**< Indicates end of file */

#define LOAD_GLYPH_CONTINUE 	0	/**< keep reading file (shouldn't be returned) */
#define LOAD_GLYPH_MINOR_ERROR 	1	/**< an error has been detected, try to read the rest of the glyph */
#define LOAD_GLYPH_COMPLETE 	2	/**< the individual glyph data now needs to be loaded */
#define LOAD_GLYPH_EOF 			3	/**< Indicates end of file */
#define LOAD_GLYPH_ERROR 		4	/**< An error was detected in processing the file */

/*****************************************************************************/
/* Declare global variables */

/**
 * Contains all fonts defined for application
 */
EhsGraphicsFontTableClass EhsGraphicsFontTable;

/*****************************************************************************/
/* Declare prototypes of local functions */

/**
 * Load a single glyph from a file
 * @param[in] pFile Pointer to the file to load the glyph from
 * @param[in,out] pGlyph Pointer to the glyph object to populate with data
 * @return Integer indicates current status of reading:
 * - LOAD_GLYPH_CONTINUE keep reading file (shouldn't be returned)
 * - LOAD_GLYPH_MINOR_ERROR an error has been detected, try to read the rest of the glyph
 * 	This won't get returned.
 * - LOAD_GLYPH_COMPLETE the individual glyph data now needs to be loaded
 * - LOAD_GLYPH_EOF Indicates end of file
 * - LOAD_GLYPH_ERROR An error was detected in processing the file
 */
EHS_LOCAL ehs_uint16 EhsGraphicsFontGlyph_load(ehs_FILE* pFile, EhsGraphicsFontGlyphClass* pGlyph); 

/**
 * read a single line of the global font info from the file into the font structure
 * @param[in] pFile File to read from
 * @param[in,out] pFont Font structure to read to
 * @return Integer indicates current status of reading:
 * - LOAD_GLOBAL_CONTINUE keep reading file
 * - LOAD_GLOBAL_ERROR an error has occured, abandon the file
 * - LOAD_GLOBAL_GLYPHS the individual glyph data now needs to be loaded
 * - LOAD_GLOBAL_EOF Indicates end of file
 */ 
EHS_LOCAL ehs_uint16 EhsGraphicsFont_loadGlobalLine(ehs_FILE* pFile, EhsGraphicsFontClass* pFont);

/**
 * Control the overall activity of reading the glyph data from the file
 * individual glyph structures
 * @param[in] pFile File to read from
 * @param[in,out] pFont Font structure to read to
 * @return true if glyphs loaded correctly
 */
EHS_LOCAL ehs_bool EhsGraphicsFont_loadGlyphs(ehs_FILE* pFile, EhsGraphicsFontClass* pFont);


/*****************************************************************************/
/* Variables defined with file-scope */

/** below are the keywords that we recognise at global scope. The strings need to be at the specified
 * indices, otherwise the constants (BDF_...) defined above aren't correct */
static const ehs_char* pszBdfKeywords[] = {
		"STARTFONT", 		/* index 0 */
		"FONT", 			/* index 1 */
		"SIZE", 			/* index 2 */
		"FONTBOUNDINGBOX", 	/* index 3 */
		"CHARS", 			/* index 4 */
		"ENDFONT", 			/* index 5 */
		NULL};
		/* The following are valid BDF keywords, but we ignore them:
		 * "COMMENT", "METRICSSET" SWIDTH, DWIDTH, SWIDTH1, DWIDTH1, STARTPROPERTIES, ENDPROPERTIES
		 */

/** 
 * These are the keywords we recognise at glyph scope. The strings need to be 
 * at the specified indices, otherwise the constants (BDF_...) define above
 * aren't correct */
static const ehs_char* pszBdfGlyphKeywords[] = {
		"STARTCHAR",	/* index 0 */
		"ENCODING",		/* index 1 */
		"SWIDTH",		/* index 2 */
		"DWIDTH",		/* index 3 */
		"SWIDTH1",		/* index 4 */
		"DWIDTH1",		/* index 5 */
		"VVECTOR",		/* index 6 */
		"BBX",			/* index 7 */
		"BITMAP",		/* index 8 */
		"ENDCHAR",		/* index 9 */
		NULL
};
/*****************************************************************************/
/* Variables defined with global-scope */

/*****************************************************************************/
/* Function definitions */

/**
 * Draw a glyph onto a 1 bit depth bitmap. Attempting to draw outside the bitmap causes
 * the function to return false (no character is drawn).
 * 
 * @param[in] pGlyph Glyph to draw
 * @param[in,out] pBitmap Bitmap to draw glyph onto
 * @param[in] nWid Width of the bitmap (in pixels)
 * @param[in] nHt Height of the bitmap
 * @param[in] nTxtWid Width of the text drawing area (pixels). Must be less than or equal to nWid
 * @param[in] nTxtHt Height of the text drawing area (pixels). Must be less than or equal to nHt
 * @param[in,out] pnX Start drawing position of next character - leftmost point (advanced after draw operation)
 * @param[in,out] pnY Start drawing position of next character - bottom-most point(advanced after draw operation)
 * @return true if the character was successfully drawn in the bitmap, false if it would have overflowed.
 */
ehs_bool EhsGraphicsFontGlyph_draw(const EhsGraphicsFontGlyphClass* pGlyph, ehs_uint8* pBitmap, ehs_uint32 nWid, ehs_uint32 nHt, ehs_uint32 nTxtWid, ehs_uint32 nTxtHt, ehs_uint32* pnX, ehs_uint32* pnY)
{
	ehs_uint16 nRow;		/* index into the glyph data */
	ehs_uint16 nByteCol;	/* index into the glyph data */
	ehs_uint16 nRowOffset;	/* offset from current index into bitmap data */
	ehs_uint16 nColOffset;  /* offset from current index into bitmap data */
	ehs_uint8 nPixelOffset; /* number of bits to offset glyph data */
	ehs_uint16 nBmpBytesPerRow = (nWid + 7)/8;	/* number of bytes per row for the bitmap */
	ehs_bool bOverflow = EHS_FALSE;		/* has the character overflowed out of the bitmap? */
	
	union {
		ehs_uint16 nWord;
		struct {
#ifdef EHS_TARGET_BIGENDIAN
			ehs_uint8 nUpper;
			ehs_uint8 nLower;
#else
			ehs_uint8 nLower;
			ehs_uint8 nUpper;
#endif
		} nByte;
	} uConvertor;			/* this helps us to copy bits from glyph data into bitmap data,
							 * especially if the data needs to be shifted, and it straddles
							 * byte boundaries */
	
	/* calculate offsets from glyph into bitmap */
	nColOffset = (ehs_uint16)(*pnX + pGlyph->nXOff) / 8u;
	nPixelOffset = (ehs_uint16)(*pnX + pGlyph->nXOff) % 8u;
	nRowOffset = (ehs_uint16)*pnY;
	
	/* check that we're not out of range */
	if ((*pnX + pGlyph->nGlyphWid) >= nTxtWid) {
		/* we might "wrap" onto the next column, depending upon the value of nPixelOffset */
		if (nPixelOffset + pGlyph->nPixWid > 8u) {
			bOverflow = EHS_TRUE;
		}
	} else if (((pGlyph->nXOff + (ehs_sint16)(*pnX)) < 0)  
			|| (nRowOffset > nTxtHt)) {
		bOverflow = EHS_FALSE;	
	}
	
	if (!bOverflow) {
		for (nRow = 0; nRow < pGlyph->nPixHt; nRow++)
		{
			ehs_uint16 nGlyphIdx = (pGlyph->nPixHt - (nRow+1)) * pGlyph->nBytesPerRow;
			ehs_uint16 nBmpIdx = (ehs_uint16)((nRowOffset - (pGlyph->nYOff+nRow)) * nBmpBytesPerRow + nColOffset);
			
			for (nByteCol = 0; nByteCol < pGlyph->nBytesPerRow; nByteCol++)
			{
				/* shift the glyph pixels to the appropriate position */
				uConvertor.nByte.nUpper = pGlyph->xPixels[nGlyphIdx+nByteCol];
				uConvertor.nByte.nLower = 0u;
				uConvertor.nWord >>= nPixelOffset;
				
				/* add them to the bitmap */
				pBitmap[nBmpIdx + nByteCol] |= uConvertor.nByte.nUpper; /* write lhs of glyph in current column */
				pBitmap[nBmpIdx + nByteCol + 1] |= uConvertor.nByte.nLower;
			}
		}
		
		/* update drawing position */
		*pnX += pGlyph->nGlyphWid;
		*pnY += pGlyph->nGlyphHt;
	}
	
	return (!bOverflow);
}

/**
 * Load a single glyph from a file
 * @param[in] pFile Pointer to the file to load the glyph from
 * @param[in,out] pGlyph Pointer to the glyph object to populate with data
 * @return Integer indicates current status of reading:
 * - LOAD_GLYPH_CONTINUE keep reading file (shouldn't be returned)
 * - LOAD_GLYPH_MINOR_ERROR an error has been detected, try to read the rest of the glyph
 * 	This won't get returned.
 * - LOAD_GLYPH_COMPLETE the individual glyph data now needs to be loaded
 * - LOAD_GLYPH_EOF Indicates end of file
 * - LOAD_GLYPH_ERROR An error was detected in processing the file
 */
ehs_uint16 EhsGraphicsFontGlyph_load(ehs_FILE* pFile, EhsGraphicsFontGlyphClass* pGlyph) 
{
	ehs_char szKeyword[MAX_LEN_BDF_KEYWORD]; 
	ehs_char szTempBuffer[MAX_LEN_BDF_PARAMETER];
	ehs_uint16 i;
	ehs_uint16 nRet = LOAD_GLYPH_CONTINUE; /* assume we keep reading */
	ehs_uint32 nIdx;
	
	/* reset the glyph */
	pGlyph->nId = EHS_UINT32_MAX;
		
	do {
		ehs_sint16 nKeyword = -1;
		/* read keyword and rest of line */
		ehs_char *szTemp = szTempBuffer;
		ehs_bool bEndOfLine = (0 == EhsFgetWord(pFile, szKeyword, MAX_LEN_BDF_KEYWORD, NULL));
		if (!bEndOfLine) {
			if (!EhsFgets(szTemp, MAX_LEN_BDF_PARAMETER, pFile)) {
				nRet = LOAD_GLYPH_EOF;
			}
			EhsStrTrimLR(szTemp);
		} else {
			if (EhsStrlen(szKeyword) == 0)
				nRet = LOAD_GLYPH_EOF;
			szTemp[0] = '\0';
		}
		
		/* which keyword is it? */
		for (i = 0; pszBdfGlyphKeywords[i]; i++)	{
			if (EhsStricmp(szKeyword, pszBdfGlyphKeywords[i]) == 0) {
				nKeyword = i;
				break;
			}
		}
		
		/* handle the keyword */
		switch(nKeyword) {
		
		case BDF_STARTCHAR:	/* string argument identifies the glyph - we don't use it, 
			ENCODING gives an integer value */
			break;

		case BDF_ENCODING: /*  1 (poss 2) integers representing Adobe standard encoding */
			szTemp = EhsGetUint32FromString(&pGlyph->nId, szTemp);
			if (!szTemp) {
				EhsError(EHS_MSG_FONT_MISSING_CODE);
				nRet = LOAD_GLYPH_MINOR_ERROR;
			}
			break;
			
		case BDF_BBX: /* bounding box: width, height, xoff, yoff from current origin to bottom left hand corner of this glyph */ 
			szTemp = EhsGetUint16FromString(&pGlyph->nPixWid, szTemp);
			if (szTemp) {
				szTemp = EhsGetUint16FromString(&pGlyph->nPixHt, szTemp);
				if (szTemp) {
					szTemp = EhsGetSint16FromString(&pGlyph->nXOff, szTemp);
					if (szTemp) {
						szTemp = EhsGetSint16FromString(&pGlyph->nYOff, szTemp);
						/* even if there wasn't a valid sint16 at the end of the string
						 * nYOff will default to zero, which isn't terrible, so we need
						 * to put a value in szTemp so that the below test doesn;t fail */
						szTemp = szTempBuffer;
					} 
				}
			}
			
			if (!szTemp) {
				EhsError(EHS_MSG_FONT_MISSING_BBX_PARAM(pGlyph->nId));
				nRet = LOAD_GLYPH_MINOR_ERROR; /* set a failed flag */
			} else {
				/* find number of bytes required to represent a single row of pixels
				 * = width / 8 rounded up */
				pGlyph->nBytesPerRow = (pGlyph->nPixWid + 7u) / 8u;
			}
			break;
			
		case BDF_BITMAP: /* read bitmap data */
			pGlyph->xPixels = (ehs_uint8 *)EhsMemReadonly_alloc(pGlyph->nBytesPerRow * pGlyph->nPixHt);
			if (pGlyph->xPixels) {
				for (nIdx = 0; nIdx < (pGlyph->nBytesPerRow * pGlyph->nPixHt); nIdx++) {
					ehs_sint16 nChr;
					ehs_uint8 nUpper;
					ehs_uint8 nLower;
					/* get pairs of hex digits - possibly beginning with whitespace */
					do {
						nChr = EhsFgetc(pFile);
					} while (EhsStrIsSpace(nChr) && nChr != EHS_EOF);
					if (EhsStrchr("0123456789ABCDEFabcdef",nChr)) {
						nUpper = (ehs_uint8)((nChr <= '9')?(nChr - '0'):((nChr <= 'F')?(nChr + 10 - 'A'):(nChr + 10 - 'a')));		
						nChr = EhsFgetc(pFile);
						if (EhsStrchr("0123456789ABCDEFabcdef",nChr)) {
							nLower = (ehs_uint8)((nChr <= '9')?(nChr - '0'):((nChr <= 'F')?(nChr + 10 - 'A'):(nChr + 10 - 'a')));
							pGlyph->xPixels[nIdx] = (nUpper << 4u) | nLower;
						} else {
							EhsError(EHS_MSG_FONT_BITMAP(pGlyph->nId));	
							nRet = LOAD_GLYPH_MINOR_ERROR;
						}
					} else {
						EhsError(EHS_MSG_FONT_BITMAP(pGlyph->nId));
						nRet = LOAD_GLYPH_MINOR_ERROR;
					}
				}
			}
			EhsFconsumeLine(pFile); /* gobble up white space after bitmap */
			break;
			
		case BDF_ENDCHAR:
			if (nRet == LOAD_GLYPH_MINOR_ERROR) {
				nRet = LOAD_GLYPH_ERROR;
			} else {
				nRet = LOAD_GLYPH_COMPLETE;
			}
			break;
			
		case BDF_DWIDTH0: /* 2 integers (x, y) device width of glyph in pixels in writing mode 0 represents origin of next glyph relative to this one */
			szTemp = EhsGetUint16FromString(&pGlyph->nGlyphWid, szTemp);
			if (szTemp) {
				szTemp = EhsGetUint16FromString(&pGlyph->nGlyphHt, szTemp);
			}
			
			if (!szTemp) {
				EhsError(EHS_MSG_FONT_MISSING_DWIDTH_PARAM(pGlyph->nId));
				nRet = LOAD_GLYPH_MINOR_ERROR; /* set a failed flag */
			}
			break; 
			
		case BDF_SWIDTH0: /*  2 integers (x and y) scaleable width in writing mode 0 */
		case BDF_SWIDTH1: /* SWIDTH for writing mode 1: vertical direction */
		case BDF_DWIDTH1: /* DWIDTH for writing mode 1: vertical direction */
		case BDF_VVECTOR:
			 /* x,y specifies offset from BBX offset to offset needed in writing mode 1 */
			 /* ignore these params for now */
		default: /* ignore this */
			break;
		}
	} while ((nRet == LOAD_GLYPH_CONTINUE) || (nRet == LOAD_GLYPH_MINOR_ERROR));
	
	return nRet;
}

/**
 * Update the X and Y positions to reflect a line break
 * @param[in] pFont Font used for the line break
 * @param[in] pTextBoxRect rectangle in which the bounding box appears
 * @param[in,out] pnX Position of drawing point
 * @param[in,out] pnY Position of drawing point
 * @return true if we haven't gone off the bottom of the textbox
 */
ehs_bool EhsGraphicsFont_newLine(const EhsGraphicsFontClass* pFont, 
		const EhsGraphicsRectangleClass* pTextBoxRect, 
		ehs_uint32* pnX, ehs_uint32* pnY) {
	ehs_bool bRet = EHS_TRUE; /* assume newLine is successful */
	*pnX = 0u;
	*pnY += pFont->nMaxHt;
	/* does the current y position leave us enough space to draw text
	 * (remember, pnY is the top of the drawn text) */
	if ((*pnY + pFont->nMaxHt) > pTextBoxRect->nHeight) {
		bRet = EHS_FALSE;
	}
	return bRet;
}

/**
 * Draw a word onto a bitmap, performs word wrap if possible, otherwise prints
 * ellipsis (...)
 * @param[in] pFont Font to draw word with
 * @param[in,out] pSurface surface to draw the word onto
 * @param[in] pTextBoxRect Rectangle representing bounding box in which text 
 * appears (should be smaller than pBitmapRect)
 * @param[in,out] pnX Start drawing position of the next character - leftmost
 *  point from left hand edge of pTextBoxRect (advanced after draw operation)
 * @param[in,out] pnY Start drawing position of the next character - topmost
 *  point from top edge of pTextBox (advanced after draw operation)
 * @param[in] szWord Word to write - utf8 string
 * @return true if word was drawn onto the bitmap
 */
ehs_bool EhsGraphicsFont_drawWord(const EhsGraphicsFontClass* pFont, 
		EhsTgtViewportSurfaceClass* pSurface, 
		const EhsGraphicsRectangleClass* pSurfaceRect,
		const EhsGraphicsRectangleClass* pTextBoxRect, 
		ehs_uint32* pnX, ehs_uint32* pnY, const ehs_char* szWord) {
/*
			static char doweneedamutx=0;
	assert ( doweneedamutx == 0 );
		doweneedamutx = 1;
*/
	ehs_uint32 nUtf32; /* utf-32 representation of the current character */
	ehs_uint8 nIdx;
	EhsGraphicsFontGlyphClass* pGlyph;
	ehs_uint32 nWordEnd = *pnX; /* calculates where the word will end */
	ehs_bool bRet = EHS_TRUE; /* assume word can be written */
	
	/* calculate space required to draw word */
	for (nIdx = 0; (nIdx < EhsStrlen(szWord)) && (nWordEnd < pTextBoxRect->nWidth); nIdx++) {
		pGlyph = EhsGraphicsFont_findGlyph(pFont, szWord[nIdx]);
		if (pGlyph) {
			nWordEnd += pGlyph->nGlyphWid;
		}
	}
	/* word will overrun - wrap text onto new line - unless this is a new line */
	if ((*pnX > 0) && (nWordEnd >= pTextBoxRect->nWidth)) {
		/* try to do a new line - if it's not possible, we'll just stop */
		bRet = EhsGraphicsFont_newLine(pFont, pTextBoxRect, pnX, pnY);
	}
	/* draw word, if there's space */
	for (nIdx = 0; bRet && (nIdx < EhsStrlen(szWord)); nIdx++) {
		pGlyph = EhsGraphicsFont_findGlyph(pFont, szWord[nIdx]);
		if (pGlyph) {
			if (!EhsGraphicsFontGlyph_draw(pGlyph, EhsTgtViewportSurface_bitmap(pSurface), 
					pSurfaceRect->nWidth,
					pSurfaceRect->nHeight,
					pTextBoxRect->nWidth, 
					pTextBoxRect->nHeight,
					pnX, pnY)) {
				/* in the case of words that are longer than the line, we need to
				 * break the line in the middle of the word */
				bRet = EhsGraphicsFont_newLine(pFont, pTextBoxRect, pnX, pnY);
				if (bRet) {
					bRet = EhsGraphicsFontGlyph_draw(pGlyph, EhsTgtViewportSurface_bitmap(pSurface), 
							pSurfaceRect->nWidth,
							pSurfaceRect->nHeight,
							pTextBoxRect->nWidth, 
							pTextBoxRect->nHeight,
							pnX, pnY);
				}
			}
		}
//		else assert( 1 == 0 );
	}
	/* add a space after the word, if there's space */
	pGlyph = EhsGraphicsFont_findGlyph(pFont, (ehs_uint32)' ');
	if ((pGlyph) && bRet && (*pnX + pGlyph->nGlyphWid) < pTextBoxRect->nWidth) {
		EhsGraphicsFontGlyph_draw(pGlyph, EhsTgtViewportSurface_bitmap(pSurface), 
				pSurfaceRect->nWidth,
				pSurfaceRect->nHeight,
				pTextBoxRect->nWidth, 
				pTextBoxRect->nHeight,
				pnX, pnY);
	}
//	else assert( 1 == 0 );
//	doweneedamutx=0;
	return bRet;
}

/**
 * Load a font from a BDF file.
 * @param[in] szFilename Name of the BDF font to load
 * @return pointer to the font that has been loaded. Null if loading failed
 */
EhsGraphicsFontClass* EhsGraphicsFont_load(ehs_char* szFilename)
{
	ehs_uint16 nIdx;
	EhsGraphicsFontClass* pFont = NULL;
	
	/* check to see if the font has already been loaded into the font table */
	// ***REVISIT*** This doesn't seem to work properly. Not sure why. Need to ask Andrew.
	/*
	for (nIdx = 0; nIdx < EhsGraphicsFontTable.nNumFonts; nIdx++) {
		if (0 == EhsStricmp(szFilename,EhsGraphicsFontTable.xFont[nIdx].szFilename)) {
			pFont = &(EhsGraphicsFontTable.xFont[nIdx]);
		}
	}
	*/

	if (!pFont) { /* if it's not already loaded, we need to load it from the file */
		if (EhsGraphicsFontTable.nNumFonts < EHS_MAX_FONTS) {
			ehs_FILE* pFile = EhsFopen(szFilename,"r");
			
			/* grab pointer to font, initialise struct fields */
			pFont = &(EhsGraphicsFontTable.xFont[EhsGraphicsFontTable.nNumFonts++]);
			pFont->szName = NULL;
			EhsStrcpy(pFont->szFilename,szFilename);
			
			if (pFile) {
				ehs_uint16 nStatus;
				
				do {
					nStatus = EhsGraphicsFont_loadGlobalLine(pFile,pFont);
					switch(nStatus)
					{
					case LOAD_GLOBAL_GLYPHS:
						if (!EhsGraphicsFont_loadGlyphs(pFile,pFont)) {
							nStatus = LOAD_GLOBAL_ERROR;
						}
						break;
					default:
						break;
					}
				} while ((nStatus != LOAD_GLOBAL_EOF) && (nStatus != LOAD_GLOBAL_ERROR));
					/* todo at end, check for missing/uninitialised properties */
				
				if (nStatus == LOAD_GLOBAL_ERROR)
				{
					pFont = NULL;
					EhsGraphicsFontTable.nNumFonts--; /* release the font we were going to use */
				}
			} else {
				EhsError(EHS_MSG_FONT_CANT_OPEN(szFilename));
				EhsGraphicsFontTable.nNumFonts--; /* release the font we were going to use */
				pFont = NULL;
			}
		} else {
			EhsError(EHS_MSG_FONT_TOO_MANY(szFilename));
		}
	}
	
	return pFont;
}

/**
 * Control the overall activity of reading the glyph data from the file
 * individual glyph structures
 * @param[in] pFile File to read from
 * @param[in,out] pFont Font structure to read to
 * @return true if glyphs loaded correctly
 */
ehs_bool EhsGraphicsFont_loadGlyphs(ehs_FILE* pFile, EhsGraphicsFontClass* pFont)
{
	ehs_bool bRet = EHS_TRUE; /* assume success */
	
	pFont->pGlyphs = (EhsGraphicsFontGlyphClass*)EhsMemReadonly_alloc(sizeof(EhsGraphicsFontGlyphClass)*pFont->nNumGlyphs);
	if (pFont->pGlyphs) {
		ehs_uint32 nIdx;
		ehs_uint32 nLastGlyphId = 0u; /* check that glyphs are ordered monotonically in the file */
		
		for (nIdx = 0; (nIdx < pFont->nNumGlyphs) && bRet; ++nIdx) {
			ehs_uint16 nRet = EhsGraphicsFontGlyph_load(pFile, &(pFont->pGlyphs[nIdx]));
			if (nRet == LOAD_GLYPH_ERROR) {
				bRet = EHS_FALSE; /* reading this glyph failed, but try to read the others before returning */
			} else if (nRet == LOAD_GLYPH_EOF) {
				bRet = EHS_FALSE; /* no point trying to read more glyphs */
			} else if (nLastGlyphId >= pFont->pGlyphs[nIdx].nId) {
				EhsError(EHS_MSG_FONT_NON_MONOTONIC(nLastGlyphId, pFont->pGlyphs[nIdx].nId));
				bRet = EHS_FALSE;
			} else {
				nLastGlyphId = pFont->pGlyphs[nIdx].nId;
				if (pFont->pGlyphs[nIdx].nPixHt > pFont->nMaxHt) {
					pFont->nMaxHt = pFont->pGlyphs[nIdx].nPixHt;
				}
				if (pFont->pGlyphs[nIdx].nPixHt > pFont->nMaxWid) {
					pFont->nMaxWid = pFont->pGlyphs[nIdx].nPixHt;
				}
			}
		}
	} else {
		/* failed to allocate memory */
		bRet = EHS_FALSE;
	}
	return bRet;
}

/**
 * read a single line of the global font info from the file into the font structure
 * @param[in] pFile File to read from
 * @param[in,out] pFont Font structure to read to
 * @return Integer indicates current status of reading:
 * - LOAD_GLOBAL_CONTINUE keep reading file
 * - LOAD_GLOBAL_ERROR an error has occured, abandon the file
 * - LOAD_GLOBAL_GLYPHS the individual glyph data now needs to be loaded
 * - LOAD_GLOBAL_EOF Indicates end of file
 */ 
ehs_uint16 EhsGraphicsFont_loadGlobalLine(ehs_FILE* pFile, EhsGraphicsFontClass* pFont)
{
	ehs_char szKeyword[MAX_LEN_BDF_KEYWORD]; 
	ehs_char szTempBuffer[MAX_LEN_BDF_PARAMETER];
	ehs_char *szTemp = szTempBuffer;
	ehs_sint16 nKeyword = -1;
	ehs_uint16 i;
	ehs_uint16 nRet = LOAD_GLOBAL_CONTINUE; /* assume we keep reading */
	
	/* read keyword and rest of line */
	ehs_bool bEndOfLine = (0 == EhsFgetWord(pFile, szKeyword, MAX_LEN_BDF_KEYWORD, NULL));
	if (!bEndOfLine) {
		if (!EhsFgets(szTemp, MAX_LEN_BDF_PARAMETER, pFile)) {
			nRet = LOAD_GLOBAL_EOF;
		}
		EhsStrTrimLR(szTemp);
	} else {
		if (EhsStrlen(szKeyword) == 0)
			nRet = LOAD_GLOBAL_EOF;
		szTemp[0] = '\0';
	}
	
	/* which keyword is it? */
	for (i = 0; pszBdfKeywords[i]; i++)	{
		if (EhsStricmp(szKeyword, pszBdfKeywords[i]) == 0) {
			nKeyword = i;
			break;
		}
	}
	
	/* handle the keyword */
	switch(nKeyword)
	{
	case BDF_FONT: /* get the font name */
		if (EhsStrlen(szTemp) > 0) {
			pFont->szName = (ehs_char*)EhsMemReadonly_alloc((EhsStrlen(szTemp)+1)*(ehs_uint32)sizeof(ehs_char));
			if (pFont->szName) {
				EhsStrcpy(pFont->szName,szTemp);
			}
		} else {
			EhsError(EHS_MSG_FONT_NAME_MISSING(pFont->szFilename));
			nRet = LOAD_GLOBAL_ERROR;
		}
			
		break;
	case BDF_CHARS: /* get the number of glyphs in the font and start reading glyphs */
		if (!EhsGetUint32FromString(&pFont->nNumGlyphs, szTemp)) {
			EhsError(EHS_MSG_FONT_NUMGLYPHS_MISSING(pFont->szFilename));
			nRet = LOAD_GLOBAL_ERROR;
		} else {
			nRet = LOAD_GLOBAL_GLYPHS;
		}
		break;
	case BDF_STARTFONT: /** @todo Check whether the file version really is 2.2, for now we assume it is */
		break;
	case BDF_SIZE:
		break;
	case BDF_FONTBBOX: /** @todo use this for the actual height of the font */
		break;
	case BDF_ENDFONT:
		break;
	default:
		break;
	}
	
	return nRet;
}

/**
 * Finds a glyph from a character value. Characters are utf-32 (unicode) characters.
 * @param pFont Font to search for glyph
 * @param nChar Character to search for
 * @return Pointer to the glyph, or NULL if character cannot be found.
 */
EhsGraphicsFontGlyphClass* EhsGraphicsFont_findGlyph(const EhsGraphicsFontClass* pFont, ehs_uint32 nChar)
{
	ehs_uint32 nMin = 0u; /* lower bound of the search space. Search from nMin */
	ehs_uint32 nMax = pFont->nNumGlyphs; /* just above the upper bound of the search space. Search up to nMax-1 */
	EhsGraphicsFontGlyphClass* pRet = NULL; /* assume we haven't found a correct return value */
	
	/* binary chop to find glyph in small number of steps */
	while (nMin < nMax)
	{
		ehs_uint32 nIdx = (nMin + nMax)/2; /* ensures if nMin < nMax, nIdx is never = nMax */
		if (pFont->pGlyphs[nIdx].nId < nChar) {
			if (nIdx == nMin) {
				/* if we set nMin = nIdx again, we'll just repeat the same test.
				 * There is no match here */
				break;
			}
			nMin = nIdx;
		} else if (pFont->pGlyphs[nIdx].nId > nChar) {
			nMax = nIdx;
		} else {
			pRet = &(pFont->pGlyphs[nIdx]);
			break;
		}
	}
//	assert (pRet =! 0); 
	return pRet;
}


/**
 * Initialise the table of fonts
 */
void EhsGraphicsFontTable_init()
{
	EhsGraphicsFontTable.nNumFonts = 0u;
}
