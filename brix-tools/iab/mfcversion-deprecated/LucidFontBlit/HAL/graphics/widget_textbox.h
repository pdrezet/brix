/** @file widget_textbox.h
 * Declarations for the textbox widget functions. Intended to be included from widget.h. Don't include
 * this file directly.
 * 
 * @author: Andrew Coombes
 * @version: $Revision: 1138 $
 * @date: $Date: 2006-10-30 05:05:44 +0000 (Mon, 30 Oct 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_WIDGETTEXTBOX_H
#define EHS_WIDGETTEXTBOX_H

#include "ehs_types.h"
#include "globals.h"
#include "graphics.h"
#include "font.h"
#include "html.h"

/**
 * Obtain the textbox specific properties of EhsWidgetTextbox
 */
#define EHS_WIDGET_TEXTBOX(pWidget) ((pWidget)->specific.textbox)

/**
 * Widget textbox subclass. This contains textbox-specific properties.
 * This is always accessed from a widget
 * class using the EHS_WIDGET_TEXTBOX(pWidget)
 * macro
 */
typedef struct {
	EhsGraphicsColourClass xFgColour; /**< Foreground colour */
	EhsGraphicsColourClass xBgColour; /**< Background colour */
	EhsGraphicsRectangleClass xTextRect; /**< Holds the indents of the text from the outer box */
	EhsGraphicsFontClass* pFont; /**< The font to display the string in */
	ehs_uint8 nFgBaseAlpha; /**< The starting alpha value for the foreground colour - this can be modified by the fade function */
	ehs_uint8 nBgBaseAlpha; /**< The starting alpha value for the background colour - this can be modified by the fade function */
	EhsHGHtmlStringClass xText; /**< String to display */
} EhsWidgetTextboxSubclass;

/**
 * Initialise the widget with the general widget and textbox specific properties including 
 * position, dimensions, z-ordering and colour.
 *
 * @param[in] nX X-coordinate for initial position of widget
 * @param[in] nY Y-coordinate for initial position of widget
 * @param[in] nZ Z order for widget
 * @param[in] nWidth Widget's width for display
 * @param[in] nHeight Widget's height for display
 * @param[in] xFgColour Widget's foreground colour
 * @param[in] xBgColour Widget's background colour
 * @param[in] pFont Pointer to the font to use for this textbox
 * @return pointer to initialised widget, or NULL
 */
EHS_GLOBAL EhsWidgetClass* EhsWidgetTextbox_init(ehs_uint16 nX, ehs_uint16 nY, ehs_uint16 nZ, 
		ehs_uint16 nWidth, ehs_uint16 nHeight, 
		EhsGraphicsColourClass xFgColour, EhsGraphicsColourClass xBgColour, 
		EhsGraphicsFontClass* pFont);


/**
 * Set the text to be displayed onto a specific textbox. This function can be called
 * directly by any functions
 *
 * @param pWidget Textbox to display text
 * @param szText String to be displayed
 */
EHS_GLOBAL void EhsWidgetTextbox_write(struct EhsWidgetStruct* pWidget, const ehs_char* szText);

/**
 * Cause the widget to be displayed (assuming it's already been created). If
 * it hasn't been created, there are no ill effects.
 *
 * NOTE: This function must only be called by EhsWidget_draw via the widget's
 * pfDraw function.
 * callers listed below.
 *
 * @param pWidget. Widget to display.
 * @param pViewport. Viewport to display the widget on.
 * @param pClipRect Specifies the bounds for drawing the widget
 */
EHS_GLOBAL void EhsWidgetTextbox_draw(struct EhsWidgetStruct* pWidget, EhsTgtViewportClass* pViewport, EhsGraphicsRectangleClass* pClipRect, EhsTgtViewportSurfaceClass* pSurface);

#endif /* EHS_WIDGETTEXTBOX_H */

