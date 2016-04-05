/** @file widget_image_gif.h
 * Declarations for the image file class specifically for handling the GIF file type.
 * 
 * @author: Andrew Coombes
 * @version: $Revision: 1120 $
 * @date: $Date: 2006-10-30 05:05:44 +0000 (Mon, 30 Oct 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_GRAPHICS_IMAGEGIF_H
#define EHS_GRAPHICS_IMAGEGIF_H

struct EhsWidgetImageGifScreenStruct;
struct EhsWidgetImageGifBlockStruct;

/**
 * Obtain the gif specific properties of EhsWidgetImage
 */
#define EHS_IMAGE_GIF(pImage) ((EHS_WIDGET_IMAGE(pImage)).specific.gif)

/**
 * EHS representation of a gif image
 */
typedef struct {
	ehs_char        header[8];
    struct EhsWidgetImageGifScreenStruct * screen;
    ehs_uint16         block_count;
    struct EhsWidgetImageGifBlockStruct ** blocks;
} EhsWidgetImageGifSubclass;

/**
 * Test if the file is a gif file
 *
 * @param szFilename File to load image from
 * @return true if file is a gif file
 */
EHS_GLOBAL ehs_bool EhsWidgetImageGif_isGif(const ehs_char* szFilename);

/**
 * Load an image from a file
 *
 * @param pImage image to load gif into
 * @param szFilename File to load image from
 * @return true if load was successful
 */
EHS_GLOBAL ehs_bool EhsWidgetImageGif_load(EhsWidgetClass* pImage, const ehs_char* szFilename);

/**
 * Display the gif onto the viewport (if it's ready to be shown)
 *
 * @param pWidget Widget to display
 * @param pViewport Viewport to display it on
 */
EHS_GLOBAL void EhsWidgetImageGif_draw(EhsWidgetClass* pWidget, EhsTgtViewportClass* pViewport, EhsGraphicsRectangleClass* pClipRect);


#endif /* EHS_GRAPHICS_IMAGEGIF_H */

