/** @file widget.h
 * Declarations for the widget functions.
 * 
 * @author: Andrew Coombes
 * @version: $Revision: 1135 $
 * @date: $Date: 2006-10-30 05:05:44 +0000 (Mon, 30 Oct 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

/**
 * @page Verification Verification report
 * @section widget_h
 * @anchor widget_h
 * @subsection misra MISRA compliance:
 * test.c demonstrated MISRA compliant on 2007-10-12
 * Last modified on $Date$
 *
 * This file contained the following derogations to the MISRA standard.
 * - Rule 18.4 Unions shall not be used. Acceptable derogation to implement variant records provided 
 * common field differentiates variant.
 * - Rule 19.1 Only preprocessor statements and comments before #include. Derogation necessary to allow declaration
 * of a type that is defined in this file.
 */

#ifndef EHS_WIDGET_H
#define EHS_WIDGET_H
/*****************************************************************************/
/* Included files */

/**
 * Pre-use declaration of the Widget class
 */
typedef struct EhsWidgetStruct EhsWidgetClass; /*lint !e961 Only preprocessor statements and comments before #include.
											    Derogation necessary to allow declaration of a type that is defined in this file. */

#include "hal_viewport.h"
#include "target_config.h"
#include "graphics.h"
#include "widget_textbox.h"
#include "ehs_fb_types.h"

/*****************************************************************************/
/* Define macros  */
#define EHS_WIDGET_STATE_EMPTY		0x00 /**< No image is ready */
#define EHS_WIDGET_STATE_INIT		0x80 /**< Image has been initialised */

/**
 * Init value occurs if top bit is set, second bit isn't set. This means 
 * we don't fall foul of Windows uninitialized value 0xcccc 
 */
#define EHS_WIDGET_STATE_INIT_MASK	0xc0 
#define EHS_WIDGET_STATE_CREATED	0x01 /**< Image has been created */
#define EHS_WIDGET_STATE_SHOW		0x02 /**< Image has been shown */

/** test if the widget has been initialized */
#define EHS_WIDGET_STATE_INITIALIZED(x) (((x) & EHS_WIDGET_STATE_INIT_MASK) == EHS_WIDGET_STATE_INIT)

/** test if the widget is being shown */
#define EHS_WIDGET_STATE_SHOWN(x) (((x) & (EHS_WIDGET_STATE_INIT_MASK | EHS_WIDGET_STATE_CREATED | EHS_WIDGET_STATE_SHOW)) \
	== (EHS_WIDGET_STATE_INIT | EHS_WIDGET_STATE_CREATED | EHS_WIDGET_STATE_SHOW))

/*****************************************************************************/
/* Define types */
/**
 * Type of widget defined in the widget structure
 */
typedef enum { EHS_WIDGET_KIND_IMAGE, EHS_WIDGET_KIND_TEXTBOX, EHS_WIDGET_KIND_PATCH } EhsWidgetKindEnum;

/**
 * Type of widget defined in the widget structure
 */
typedef enum { ARGB8888, ARGB1888, RGB888 } EhsBlitMethodEnum;

/**
 * Generic widget structure. This represents the superclass of all widget types.
 * EhsWidgetImageType "inherit" and EhsWidgetTextboxType "inherit" from this class.
 * In C terms, this means that functions that don't know what type of widget they're
 * dealing with will simply call EhsWidget_ functions, and it will sort out what
 * specific functions to call. Currently this only applies to the draw function.
 *
 * As we will see in the definition of EhsWidget_Image_ and EhsWidget_Textbox_ functions,
 * they take EhsWidgetClass pointers as parameters, not EhsWidget_ImageType or EhsWidget_TextboxType
 */
struct EhsWidgetStruct {
	EhsGraphicsRectangleClass xOrigRect;	/**< Initial bounding rectangle (as defined in properties file) */
	EhsGraphicsRectangleClass xCurRect;	/**< current bounding rectangle for the widget */
	ehs_uint16 nZ;  /**< Z order */
	ehs_bool bOptimiseForSpeed;		/**< Do we want this widget to be time-, or memory-efficient? */
	EhsWidgetKindEnum eWidgetKind; /**< Type of graphic object contained within this widget */
	EhsBlitMethodEnum eBlitMethod; /**< Blit method used to draw widget */
	/*lint -e960 18.4 Unions shall not be used. Acceptable derogation to use variants - eWidgetKind shows which union member to use */
	union {
		EhsWidgetTextboxSubclass textbox; 	/**< textbox specific attributes */
	} specific;
	/*line +e960 */
	ehs_uint8 nState; /**< Widget state defined by EHS_WIDGET_STATE_ macros */
	void (*pfDrawFunc)(EhsWidgetClass* pWidget, EhsTgtViewportClass* pViewport, EhsGraphicsRectangleClass *pClipRect); /**< Implementation of method "draw" */
	void (*pfCreateFunc)(EhsWidgetClass* pWidget); /**< Implementation of method "create" */
	void (*pfDestroyFunc)(EhsWidgetClass* pWidget); /**< Implementation of method "destroy" */
	ehs_bool (*pfFadeFunc) (EhsWidgetClass* pWidget, ehs_uint8 nOpacity);	/**< Implementation of method "fade" */
};

/**
 * Declare a table of widgets
 */
typedef struct
{
	ehs_uint16 nSize; /**< Number of widgets currently defined */
	EhsWidgetClass xWidget[EHS_MAX_WIDGET_INSTANCES]; /**< Array of widgets put in creation order */
	EhsWidgetClass* pZOrderedWidget[EHS_MAX_WIDGET_INSTANCES]; /**< Array of pointers to widgets in Z-order */
} EhsWidgetTableClass;

/*****************************************************************************/
/* Declare global variables */

/**
 * Declare the global widget table
 */
EHS_GLOBAL EhsWidgetTableClass EhsWidgetTable;

/*****************************************************************************/
/* Declare function prototypes  */

/**
 * Obtain a new widget. The widget comes from EhsWidgetTable
 * and updates the number of allocated widgets.
 *
 * @return Pointer to a new widget, or zero if this fails
 */
EHS_GLOBAL EhsWidgetClass* EhsWidget_new(void);

/**
 * Create the widget. This is a necessary step prior to showing the widget
 */
EHS_GLOBAL void EhsWidget_create(EhsWidgetClass* pWidget);

/**
 * Destroy the widget. Required after the widget has been finished with
 */
EHS_GLOBAL void EhsWidget_destroy(EhsWidgetClass* pWidget);

/**
 * Cause the widget to be displayed (assuming it's already been created). If
 * it hasn't been created, there are no ill effects.
 */
EHS_GLOBAL void EhsWidget_show(EhsWidgetClass* pWidget);

/**
 * Cause the widget to be hidden (assuming it's already been created and shown).
 * No ill effects are caused if this is called before the object is created or shown.
 */
EHS_GLOBAL void EhsWidget_hide(EhsWidgetClass* pWidget);

/**
 * Update the widget X,Y parameters. Indicates whether
 *
 * @param[in,out] pWidget Widget data
 * @param[in] nX new relative X position to move widget to
 * @param[in] nY new relative Y position to move widget to
 * @param[in] nWid Change in width for the widget
 * @param[in] nHt change in height for the widget
 */
EHS_GLOBAL void EhsWidget_move(EhsWidgetClass* pWidget, EhsDataflowIntType nX, EhsDataflowIntType nY, EhsDataflowIntType nWid, EhsDataflowIntType nHt);

/**
 * Fade the image in or out by scaling its global alpha level by the specified amount
 *
 * @param nOpacity amount of opacity for image. 0 = minimum opacity, 255 maximum opacity.
 */
EHS_GLOBAL void EhsWidget_fade(EhsWidgetClass* pWidget, ehs_uint8 nOpacity);

/**
 * Display the widget onto the viewport (if it's ready to be shown)
 *
 * @param pWidget Widget to display
 * @param pViewport Viewport to display it on
 * @param pClipRect Specifies the bounds for drawing the widget
 */
EHS_GLOBAL void EhsWidget_draw(EhsWidgetClass* pWidget, EhsTgtViewportClass* pViewport, EhsGraphicsRectangleClass* pClipRect, EhsTgtViewportSurfaceClass* pSurface);

/**
 * Initialise the widget table
 */
EHS_GLOBAL void EhsWidgetTable_init(EhsWidgetTableClass* pWidgetTable);

/**
 * Obtain a new widget. The widget comes from EhsWidgetTable
 * and updates the number of allocated widgets.
 *
 * @return Pointer to a new widget, or zero if this fails
 */
EHS_GLOBAL EhsWidgetClass* EhsWidgetTable_new(EhsWidgetTableClass* pWidgetTable);

/**
 * Draw a widget list in response to a draw command from the target viewport
 *
 * @param pWidgetTable Set of widgets to redraw
 * @param pViewport Physical viewport to write to
 * @param pClipRect Specifies the bounds of what is drawn
 */
EHS_GLOBAL void EhsWidgetTable_draw(const EhsWidgetTableClass* pWidgetTable, EhsTgtViewportClass *pViewport, EhsGraphicsRectangleClass* pClipRect);

/**
 * Insert a widget itno the Z-ordered list of widgets. This is called
 * after a widget has been initialized, but before the index to the widget
 * table has been updated. This is called only by subclasses of EhsWidget.
 */
EHS_GLOBAL void EhsWidgetTable_updateZOrder(EhsWidgetTableClass* pWidgetTable, EhsWidgetClass* pWidget);


#endif /* EHS_WIDGET_H */

