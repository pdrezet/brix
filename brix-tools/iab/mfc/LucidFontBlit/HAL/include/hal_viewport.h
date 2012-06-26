/** @file hal_viewport.h
 * In this file, all of the hardware abstraction layer functions relating to graphics are given.
 *
 * @todo Move this to services/graphics and rename to EhsSvcViewportXXX
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 1127 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_HAL_VIEWPORT_H
#define EHS_HAL_VIEWPORT_H

/*****************************************************************************/
/* Included files */

#include "graphics.h"
#include "target_viewport.h"

/*****************************************************************************/
/* Define macros  */

#ifndef EHS_TGT_VIEWPORT_ALPHA8_SCALE
/**
 * Macro used to rescale alpha value if target cannot support full 8 bit range of alphas.
 * Default behaviour is no rescaling.
 */
#define EHS_TGT_VIEWPORT_ALPHA8_SCALE(x) (x)
#endif
/*****************************************************************************/
/* Define types */

/**
 * Indicates the properties contained within the target viewport type
 */
typedef struct EhsTgtViewportStruct EhsTgtViewportClass;

/**
 * Container for the piece of data used to represent images/bitmaps etc.
 */
typedef struct EhsTgtViewportSurfaceStruct EhsTgtViewportSurfaceClass;


/*****************************************************************************/
/* Declare global variables */

/**
 * Define the target viewport. Only one viewport is defined at this
 * stage.
 */
EHS_GLOBAL EhsTgtViewportClass EhsTgtViewport;

/*****************************************************************************/
/* Declare function prototypes  */



/**
 * Indicate to the target that the viewport needs updating.
 * This will eventually result in EhsTgtViewport_paint being called
 */
EHS_GLOBAL void EhsTgtViewport_update(EhsTgtViewportClass* pViewport);

/**
 * Indicate to the target that a rectangle on the viewport needs updating.
 * This will eventually result in EhsTgtViewport_paint being called
 */
EHS_GLOBAL void EhsTgtViewport_updateRect(EhsTgtViewportClass* pViewport, ehs_uint16 nX, ehs_uint16 nY, ehs_uint16 nWidth, ehs_uint16 nHeight);

/**
 * Display the specified text at the specified X,Y position in the
 * specified foreground/background colours
 *
 * @param[in] pViewport Current viewport
 * @param[in] szText Text to display
 * @param[in] pImgBounds Bounds of text box
 * @param[in] xFgColour Foreground colour (colour of letters)
 * @param[in] xBgColour Background colour (colour behind letters)
 */
EHS_GLOBAL void EhsTgtViewport_displayText(EhsTgtViewportClass* pViewport, const ehs_char* szText, 
					const EhsGraphicsRectangleClass* pImgBounds, EhsGraphicsColourClass xFgColour, EhsGraphicsColourClass xBgColour);

#ifndef EhsTgtViewport_blit
/**
 * Blit an arbitrary surface to the screen. Uses the surface's format type to determine how to do the blitting
 * 
 * @param[in] pViewport Current viewport
 * @param[in] pSurface The image to blit
 * @param[in] pImgBounds The bounding box for the image
 * @param[in] nAlpha The global alpha level
 * @todo Replace the blitXXX functions with this one.
 */
EHS_GLOBAL void EhsTgtViewport_blit(EhsTgtViewportClass* pViewport,
					const EhsTgtViewportSurfaceClass* pSurface, 
					const EhsGraphicsRectangleClass* pImgBounds, 
					ehs_uint8 nImageAlpha);
#endif

#ifndef EhsTgtViewport_blitArgb8888
/**
 * Display a single line of an image to the specified X,Y position in the
 * specified viewport. The image is represented in ARGB8888 format
 * 
 * @param[in] pViewport Viewport to blit into
 * @param[in] pSurface The image to blit.
 * @param[in] pImgBounds The bounding box for the image
 * @param[in] nAlpha The global alpha level
 * 
 */
EHS_GLOBAL void EhsTgtViewport_blitArgb8888(EhsTgtViewportClass* pViewport,
					const EhsTgtViewportSurfaceClass* pSurface, const EhsGraphicsRectangleClass* pImgBounds, ehs_uint8 nImageAlpha);
#endif

#ifndef EhsTgtViewport_blitArgb1888
/**
 * Display a single line of an image to the specified X,Y position in the
 * specified viewport. The image is represented in ARGB1888 format
 *
 * @param[in] pViewport Viewport to blit into
 * @param[in] pSurface The image to blit.
 * @param[in] pImgBounds The bounding box for the image
 * @param[in] nAlpha The global alpha level
 */
 EHS_GLOBAL void EhsTgtViewport_blitArgb1888(EhsTgtViewportClass* pViewport,
					const EhsTgtViewportSurfaceClass* pSurface, const EhsGraphicsRectangleClass* pImgBounds, ehs_uint8 nAlpha);
#endif

#ifndef EhsTgtViewport_blitRgb888
/**
 * Display a single line of an image to the specified X,Y position in the
 * specified viewport. The image is represented in RGB888 format
 *
 * @param[in] pViewport Viewport to blit into
 * @param[in] pSurface The image to blit.
 * @param[in] pImgBounds The bounding box for the image
 * @param[in] nAlpha The global alpha level
 */
EHS_GLOBAL void EhsTgtViewport_blitRgb888(EhsTgtViewportClass* pViewport,
					const EhsTgtViewportSurfaceClass* pSurface, const EhsGraphicsRectangleClass* pImgBounds, ehs_uint8 nAlpha);
#endif

#ifndef EhsTgtViewport_fillRect
/**
 * Fill a rectangle with a specified colour in the specified viewport.
 * 
 * @param[in] pViewport Viewport to fill rectangle into
 * @param[in] pRect position and size of rectangle to fill
 * @param[in] pColour Colour to use for filling rectangle (includes global alpha value)
 */
EHS_GLOBAL void EhsTgtViewport_fillRect(EhsTgtViewportClass* pViewport,
				const EhsGraphicsRectangleClass* pRect, const EhsGraphicsColourClass* pColour);
#endif

/**
 * Initialise the target viewport.
 * 
 * @return true if initialisation was successful.
 */
EHS_GLOBAL ehs_bool EhsTgtViewport_init(EhsTgtViewportClass* pViewport);

/**
 *  reset the use of the target viewport. This function is called between
 * applications. It releases application-specific resources occupied by the viewport.
 */
EHS_GLOBAL void EhsTgtViewport_reset(EhsTgtViewportClass* pViewport);

/**
 *  Terminate the use of the target viewport. This function is called as part of shutting
 * down EHS. It releases all resources occupied by the viewport.
 */
EHS_GLOBAL void EhsTgtViewport_term(EhsTgtViewportClass* pViewport);

/**
 * Clear the target viewport
 */
EHS_GLOBAL void EhsTgtViewport_clear(EhsTgtViewportClass* pViewport);

/**
 * Allocate memory for images (to subsequently blit to screen)
 * 
 * @param[in] pViewport Viewport where surface will be used
 * @param[in] nWidth Width of the viewport
 * @param[in] nHeight Height of the viewport
 * @param[in] eFormat format that is to be used for the bitmap
 * @param[in] pPalette array of ARGB8888 colours to use for the palette (NULL if not required)
 * @param[in] nPaletteSize number of entries in the palette
 * @return pointer to the surface, or null if an error occured.
 */
EHS_GLOBAL EhsTgtViewportSurfaceClass* EhsTgtViewportSurface_create(EhsTgtViewportClass* pViewport, 
		ehs_uint16 nWidth, ehs_uint16 nHeight, EhsGraphicsColourFormatEnum eFormat,
		EhsGraphicsColourClass* pPalette, ehs_uint16 nPaletteSize);

#ifndef EhsTgtViewportSurface_destroy
/**
 * Free memory used by a surface
 */
EHS_GLOBAL void EhsTgtViewportSurface_destroy(EhsTgtViewportClass* pViewport, EhsTgtViewportSurfaceClass *pSurface);
#endif

#ifndef EhsTgtViewportSurface_pixels
/**
 * Provide access to the array of pixels that makes up the surface
 */
EHS_GLOBAL EhsGraphicsColourClass* EhsTgtViewportSurface_pixels(EhsTgtViewportSurfaceClass* pSurface);
#endif

#ifndef EhsTgtViewportSurface_pitch
/**
 * Return the number of pixels across (allows direct addressing in the array of pixels - 
 * index = x + y * pitch
 */
EHS_GLOBAL ehs_uint16 EhsTgtViewportSurface_pitch(EhsTgtViewportSurfaceClass* pSurface);
#endif

#endif /* EHS_HAL_VIEWPORT_H */
