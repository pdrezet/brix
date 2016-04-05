/** @file widget_image.h
 * Declarations for the textbox widget functions. Intended to be included from widget.h
 * Don't include this file directly.
 * 
 * @author: Andrew Coombes
 * @version: $Revision: 1120 $
 * @date: $Date: 2006-10-30 05:05:44 +0000 (Mon, 30 Oct 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

/**
 * @page Verification Verification report
 * @section widget_image_h
 * @anchor widget_image_h
 * @subsection misra MISRA compliance:
 * test.c demonstrated MISRA compliant on 2007-10-12
 * Last modified on $Date$
 *
 * This file contained the following derogations to the MISRA standard.
 * - Rule 18.4 Unions shall not be used. Acceptable derogation to use variants - 
 * eImageFormat shows which union member to use.
 */

#ifndef EHS_WIDGETIMAGE_H
#define EHS_WIDGETIMAGE_H

/*****************************************************************************/
/* Included files */

#include "ehs_types.h"
#include "globals.h"
#include "graphics.h"
#include "widget_image_gif.h"
#include "widget_image_png.h"

/*****************************************************************************/
/* Define macros  */

/**
 * Obtain the textbox specific properties of EhsWidgetTextbox
 */
#define EHS_WIDGET_IMAGE(pWidget) ((pWidget)->specific.image)

/*****************************************************************************/
/* Define types */

/**
 * Determines the type of the image
 */
typedef enum { EHS_WIDGET_IMAGE_FORMAT_UNKNOWN, EHS_WIDGET_IMAGE_FORMAT_GIF, EHS_WIDGET_IMAGE_FORMAT_PNG } EhsWidgetImageFormatEnum;

/**
 * Widget image subclass. This contains image-specific properties.
 * This is always accessed from a widget
 * class using the EHS_WIDGET_IMAGE(pWidget)
 * macro
 */
typedef struct {
	ehs_uint8 nOrigImageAlpha; /**< Original opacity value for the image */
	ehs_uint8 nCurrentImageAlpha; /**< Current opacity value for the image */
	EhsWidgetImageFormatEnum eImageFormat; /**< Determines the image format held within this structure */
	/*lint -e960 18.4 Unions shall not be used. Acceptable derogation to use variants - eImageFormat shows which union member to use */
	union {
		EhsWidgetImageGifSubclass gif;
		EhsWidgetImagePngSubclass png;
	} specific;
	/*lint +e960 */
} EhsWidgetImageSubclass;

/*****************************************************************************/
/* Declare global variables */

/*****************************************************************************/
/* Declare function prototypes  */


/**
 * Initialise the widget with the general widget and image specific properties, including 
 * position, dimensions, z-ordering and filename containing image.
 *
 * @param nX X-coordinate for initial position of widget
 * @param nY Y-coordinate for initial position of widget
 * @param nZ Z order for widget
 * @param szFilename Name of file containing widget image data
 * @return Pointer to initialised widget, or NULL
 */
EHS_GLOBAL EhsWidgetClass* EhsWidgetImage_init(ehs_uint16 nX, ehs_uint16 nY, ehs_uint16 nZ, ehs_uint8 nImageAlpha,const ehs_char* szFilename);


#endif /* EHS_WIDGETIMAGE_H */

