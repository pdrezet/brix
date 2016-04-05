/** @file widget_patch.h
 * Declarations for the patch widget functions. Intended to be included from widget.h. Don't include
 * this file directly.
 * 
 * @author: Andrew Coombes
 * @version: $Revision: 1120 $
 * @date: $Date: 2006-10-30 05:05:44 +0000 (Mon, 30 Oct 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_WIDGETPATCH_H
#define EHS_WIDGETPATCH_H

#include "ehs_types.h"
#include "globals.h"
#include "graphics.h"

/**
 * Obtain the textbox specific properties of EhsWidgetTextbox
 */
#define EHS_WIDGET_PATCH(pWidget) ((pWidget)->specific.patch)

/**
 * Widget textbox subclass. This contains textbox-specific properties.
 * This is always accessed from a widget
 * class using the EHS_WIDGET_TEXTBOX(pWidget)
 * macro
 */
typedef struct {
	EhsGraphicsColourClass xColour; /**< Patch colour */
	ehs_uint8 nBaseAlpha; /**< The starting alpha value for the patch - this can be modified by the fade function */
} EhsWidgetPatchSubclass;

/**
 * Initialise the widget with the general widget and textbox specific properties including 
 * position, dimensions, z-ordering and colour.
 *
 * @param nX X-coordinate for initial position of widget
 * @param nY Y-coordinate for initial position of widget
 * @param nZ Z order for widget
 * @param nWidth Widget's width for display
 * @param nHeight Widget's height for display
 * @param xFgColour Widget's foreground colour
 * @param xBgColour Widget's background colour
 * @return pointer to initialised widget, or NULL
 */
EHS_GLOBAL EhsWidgetClass* EhsWidgetPatch_init(ehs_uint16 nX, ehs_uint16 nY, ehs_uint16 nZ, ehs_uint16 nWidth, ehs_uint16 nHeight, EhsGraphicsColourClass xColour);

#endif /* EHS_WIDGETPATCH_H */

