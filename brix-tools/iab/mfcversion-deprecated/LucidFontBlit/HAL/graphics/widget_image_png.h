/** @file widget_image_gif.h
 * Declarations for the image file class specifically for handling the PNG file type.
 * 
 * @author: Andrew Coombes
 * @version: $Revision: 1120 $
 * @date: $Date: 2006-10-30 05:05:44 +0000 (Mon, 30 Oct 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_GRAPHICS_IMAGEPNG_H
#define EHS_GRAPHICS_IMAGEPNG_H
#include "hal_viewport.h"

/**
 * Obtain the png specific properties of EhsWidgetImage
 */
#define EHS_IMAGE_PNG(pImage) ((EHS_WIDGET_IMAGE(pImage)).specific.png)

/**
 * EHS representation of a png image
 */
typedef struct {
	EhsTgtViewportSurfaceClass* pSurface; /* image data is stored as a surface */
} EhsWidgetImagePngSubclass;

/**
 * Load an image from a file
 *
 * @param pImage image to load png into
 * @param szFilename File to load image from
 * @return true if load was successful
 */
EHS_GLOBAL ehs_bool EhsWidgetImagePng_load(EhsWidgetClass* pImage, const ehs_char* szFilename);

/**
 * Display the gif onto the viewport (if it's ready to be shown)
 *
 * @param pWidget Widget to display
 * @param pViewport Viewport to display image in
 * @param pClipRect Specifies the bounds for drawing the widget
 */
EHS_GLOBAL void EhsWidgetImagePng_draw(EhsWidgetClass* pWidget, EhsTgtViewportClass* pViewport, EhsGraphicsRectangleClass* pClipRect);


#endif /* EHS_GRAPHICS_IMAGEPNG_H */

