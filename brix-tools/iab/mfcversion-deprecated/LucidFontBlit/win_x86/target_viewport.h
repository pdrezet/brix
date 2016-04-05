/** @file target_viewport.h
 * The target-specific declarations required to support the HAL for viewport services
 * are defined here. This file should only be included by hal_viewport.h
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 1127 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_TARGET_VIEWPORT_H
#define EHS_TARGET_VIEWPORT_H

#ifndef EHS_HAL_VIEWPORT_H
#error "This file should only be included by hal_viewport.h"
#endif

/*****************************************************************************/
/* Included files */

#include <windows.h>

/*****************************************************************************/
/* Define macros  */

/**
 * Provide access to pixels representing the surface
 */
#define EhsTgtViewportSurface_pixels(pSurface) ((pSurface)->uSurface.pPixels)

/**
 * Provide access to the bitmap representing the surface
 */
#define EhsTgtViewportSurface_bitmap(pSurface) ((pSurface)->uSurface.pBitmap)

/**
 * Return the number of pixels across (allows direct addressing in the array of pixels - 
 * index = x + y * pitch
 */
#define EhsTgtViewportSurface_pitch(pSurface) ((pSurface)->nWid)

/*****************************************************************************/
/* Define types */

/**
 * Define a surface - using for blitting from
 */
struct EhsTgtViewportSurfaceStruct
{
	union {
		EhsGraphicsColourClass* pPixels;	/**< Contains the array of colours used to represent the bitmap */
		ehs_uint8* pBitmap;					/**< contains the array of pixels used for LUT-based surfaces */
	} uSurface;
	EhsGraphicsColourClass* pPalette;		/**< Contains the array of colours required for a lookup table */
	ehs_uint16 nPaletteSize;				/**< Contains the number of entries in the lookup table */
	EhsGraphicsColourFormatEnum eFormat;	/**< The format in which the pixels are presented */
	ehs_uint16 nWid;						/**< Width of the surface */
	ehs_uint16 nHt;							/**< Height of the surface */
};


/*****************************************************************************/
/* Declare global variables */

/*****************************************************************************/
/* Declare function prototypes  */

#ifdef EHS_TARGET_CODE
/**
 * Repaint all viewports
 */
EHS_GLOBAL void EhsTgtViewport_paint(HWND hWnd, LPPAINTSTRUCT lpPS);
#endif

#endif /* EHS_TARGET_VIEWPORT_H */
