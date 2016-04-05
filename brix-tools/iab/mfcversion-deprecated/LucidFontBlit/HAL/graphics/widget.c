/** @file widget.c
 * Definitions for the generic widget handling functions
 * 
 * @author: Andrew Coombes
 * @version: $Revision: 1120 $
 * @date: $Date: 2006-10-30 05:05:44 +0000 (Mon, 30 Oct 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 *
 * @todo Make this module threadsafe - EhsWidget_draw may run in a separate thread to other functions
 */

/**
 * @page Verification Verification report
 * @section widget
 * @anchor widget
 * @subsection misra MISRA compliance:
 * test.c demonstrated MISRA compliant on 2007-10-16
 * Last modified on $Date$
 *
 * This file contained no derogations to the MISRA standard.
 */

/*****************************************************************************/
/* Included files */
#include "widget.h"
#include "messages.h"
#include "utils.h"

#include "hal_string.h"

/*****************************************************************************/
/* Declare macros and local typedefs used by this file */
/*****************************************************************************/
/* Declare prototypes of local functions */

/**
 * Change the widget's state, and test whether it needs to be redrawn:
 * either because it is now no longer visible, or because it
 * has become visible. Redraw the widget if appropriate.
 *
 * @param pWidget Widget to test
 * @param nNewState Value of the state before now
 */
EHS_LOCAL void EhsWidget_setState(EhsWidgetClass* pWidget, ehs_uint8 nNewState);

/*****************************************************************************/
/* Variables defined with file-scope */
/*****************************************************************************/
/* Variables defined with global-scope */

/**
 * Define the global widget table
 */
EhsWidgetTableClass EhsWidgetTable;

/*****************************************************************************/
/* Function definitions */

/**
 * Obtain a new widget. The widget comes from EhsWidgetTable
 * and updates the number of allocated widgets.
 *
 * @return Pointer to a new widget, or zero if this fails
 */
EhsWidgetClass* EhsWidgetTable_new(EhsWidgetTableClass* pTable)
{
	EhsWidgetClass* pWidget = NULL;

	if ((pTable->nSize+1) < EHS_MAX_WIDGET_INSTANCES)
	{
		pWidget = &(pTable->xWidget[pTable->nSize++]);
	}
	else
	{
		EhsError(EHS_MSG_ERROR_WIDGET_TOO_MANY);
	}

	return pWidget;
}

/**
 * Create the widget. This is a necessary step prior to showing the widget
 */
void EhsWidget_create(EhsWidgetClass* pWidget)
{

	/* check that the widget has been initialised by the subclass */
	if (EHS_WIDGET_STATE_INITIALIZED(pWidget->nState))
	{
		/* widget specific creation */
		pWidget->pfCreateFunc(pWidget);
		EhsWidget_setState(pWidget, pWidget->nState | EHS_WIDGET_STATE_CREATED);
	}
	else
	{
		EhsError(EHS_MSG_ERROR_WIDGET_NOT_INIT);
	}

}

/**
 * Destroy the widget. Required after the widget has been finished with.
 * Destroy does not hide the widget.
 */
void EhsWidget_destroy(EhsWidgetClass* pWidget)
{
	/* check that the widget has been initialised by the subclass */
	if (EHS_WIDGET_STATE_INITIALIZED(pWidget->nState))
	{
		/* widget specific destruction */
		pWidget->pfDestroyFunc(pWidget);
		EhsWidget_setState(pWidget, pWidget->nState & ~EHS_WIDGET_STATE_CREATED);
	}
	else
	{
		EhsError(EHS_MSG_ERROR_WIDGET_NOT_INIT);
	}
}

/**
 * Cause the widget to be displayed (assuming it's already been created). If
 * it hasn't been created, there are no ill effects.
 */
void EhsWidget_show(EhsWidgetClass* pWidget)
{
	EhsWidget_setState(pWidget, pWidget->nState | EHS_WIDGET_STATE_SHOW);
}

/**
 * Cause the widget to be hidden (assuming it's already been created and shown).
 * No ill effects are caused if this is called before the object is created or shown.
 */
void EhsWidget_hide(EhsWidgetClass* pWidget)
{
	EhsWidget_setState(pWidget, pWidget->nState & (~EHS_WIDGET_STATE_SHOW));
}

/**
 * Change the widget's state, and test whether it needs to be redrawn:
 * either because it is now no longer visible, or because it
 * has become visible. Redraw the widget if appropriate.
 *
 * @param pWidget Widget to test
 * @param nNewState Value of the state before now
 */
EHS_LOCAL void EhsWidget_setState(EhsWidgetClass* pWidget, ehs_uint8 nNewState)
{
	/* check for state change, and that previous state was showing widget
	 * update viewport if both have occurred */
	if (EHS_WIDGET_STATE_SHOWN(nNewState) != EHS_WIDGET_STATE_SHOWN(pWidget->nState))
	{
		pWidget->nState = nNewState; /* update the state before calling _updateRect */
		EhsTgtViewport_updateRect(&EhsTgtViewport, pWidget->xCurRect.nLeft, pWidget->xCurRect.nTop, pWidget->xCurRect.nWidth, pWidget->xCurRect.nHeight);
	}
	else
	{
		pWidget->nState = nNewState;
	}

}

/**
 * Cause the widget to be moved and/or resized. We assume that the position that the widget is moved to
 * (almost) always overlaps its current position, thus we do a redraw that includes the original
 * widget position and the new widget position. If we frequently moved the widget outside its
 * original position, it would be more economical to do two draws (old widget position and
 * new widget position).
 *
 * @param[in,out] pWidget Widget data
 * @param[in] nX new relative X position to move widget to
 * @param[in] nY new relative Y position to move widget to
 * @param[in] nWid Change in width for the widget
 * @param[in] nHt change in height for the widget
 */
void EhsWidget_move(EhsWidgetClass* pWidget, EhsDataflowIntType nX, EhsDataflowIntType nY, EhsDataflowIntType nDeltaWid, EhsDataflowIntType nDeltaHt)
{
	EhsGraphicsRectangleClass xOldPos; /* contains the previous position of the widget */
	
	/* get the current rectangle position */
	EhsMemcpy(&xOldPos,&(pWidget->xCurRect),sizeof(EhsGraphicsRectangleClass));
	/* calculate the new position of the widget */
	pWidget->xCurRect.nLeft = EHS_CONVERT_UINT16_SATURATE(pWidget->xOrigRect.nLeft + nX);
	pWidget->xCurRect.nTop = EHS_CONVERT_UINT16_SATURATE(pWidget->xOrigRect.nTop + nY);
	pWidget->xCurRect.nWidth = EHS_CONVERT_UINT16_SATURATE(pWidget->xOrigRect.nWidth + nDeltaWid);
	pWidget->xCurRect.nHeight = EHS_CONVERT_UINT16_SATURATE(pWidget->xOrigRect.nHeight + nDeltaHt);
	
	/* check if we have moved or resized - if we haven't we don't need to repaint
	 * this avoids unnecessary updates to the viewport.
	 *
	 * NOTE: We must NOT test "is the widget within the current viewport?" here.
	 * Initially this seemed to be an optimization to avoid unnecessary repainting
	 * when the widget is no longer visible. However a move
	 * function might change a widget from being positioned within the viewport to
	 * outside the viewport - this must result in a call to EhsTgtViewport_update */
	if ((pWidget->xCurRect.nLeft != xOldPos.nLeft) || 
			(pWidget->xCurRect.nTop != xOldPos.nTop) ||
			(pWidget->xCurRect.nHeight != xOldPos.nHeight) ||
			(pWidget->xCurRect.nWidth != xOldPos.nWidth))
	{
		/* if pWidget is visible, update viewport */
		if (EHS_WIDGET_STATE_SHOWN(pWidget->nState))
		{
			/* do we do two updates (clear previous position of widget, set new position of widget)
			 * or one update (single rectangle containing new and old position)?
			 * That depends if we have an overlap
			 */
			if (EhsGraphicsRectangle_overlap(&(pWidget->xCurRect),&xOldPos))
			{
				EhsGraphicsRectangle_union(&xOldPos,&(pWidget->xCurRect),&xOldPos);
				EhsTgtViewport_updateRect(&EhsTgtViewport, xOldPos.nLeft, xOldPos.nTop, xOldPos.nWidth, xOldPos.nHeight);
			}
			else
			{
				EhsTgtViewport_updateRect(&EhsTgtViewport, xOldPos.nLeft, xOldPos.nTop, xOldPos.nWidth, xOldPos.nHeight);
				EhsTgtViewport_updateRect(&EhsTgtViewport, pWidget->xCurRect.nLeft, pWidget->xCurRect.nTop, pWidget->xCurRect.nWidth, pWidget->xCurRect.nHeight);
			}
		}
	}
}

/**
 * Fade the image in or out by scaling its global alpha level by the specified amount
 *
 * @param nOpacity amount of opacity for image. 0 = minimum opacity, 255 maximum opacity.
 */
void EhsWidget_fade(EhsWidgetClass* pWidget, ehs_uint8 nOpacity)
{
	ehs_bool bUpdate = pWidget->pfFadeFunc(pWidget, nOpacity);

	if (EHS_WIDGET_STATE_SHOWN(pWidget->nState) && bUpdate)
	{
		EhsTgtViewport_updateRect(&EhsTgtViewport, pWidget->xCurRect.nLeft, pWidget->xCurRect.nTop, pWidget->xCurRect.nWidth, pWidget->xCurRect.nHeight);
	}
}


/**
 * Display the widget onto the viewport (if it's ready to be shown)
 *
 * @param pWidget Widget to display
 * @param pViewport Viewport to display it on
 * @param pClipRect Specifies the bounds for drawing the widget
 */
void EhsWidget_draw(EhsWidgetClass* pWidget, EhsTgtViewportClass* pViewport, EhsGraphicsRectangleClass* pClipRect, EhsTgtViewportSurfaceClass* pSurface)
{
	if (EHS_WIDGET_STATE_SHOWN(pWidget->nState))
	{
		if (EhsGraphicsRectangle_overlap(&(pWidget->xCurRect), pClipRect))
		{
			/* only display widgets if there is an overlap between the clip rectangle and the bounding rectangle for the widget */
			pWidget->pfDrawFunc(pWidget, pViewport, pClipRect);
		}
	}
}

/**
 * Initialise the widget table. 
 */
void EhsWidgetTable_init(EhsWidgetTableClass* pWidgetTable)
{
	ehs_uint16 nIndex;
	pWidgetTable->nSize = 0;

	for (nIndex = 0; nIndex < EHS_MAX_WIDGET_INSTANCES; nIndex++)
	{
		pWidgetTable->pZOrderedWidget[nIndex] = NULL;
		EhsMemset(&(pWidgetTable->xWidget[nIndex]),0,sizeof(struct EhsWidgetStruct));
	}
}

/**
 * Insert a widget itno the Z-ordered list of widgets. This is called
 * after a widget has been initialized, but before the index to the widget
 * table has been updated
 */
void EhsWidgetTable_updateZOrder(EhsWidgetTableClass* pWidgetTable, EhsWidgetClass* pWidget)
{
	EhsWidgetClass* pZTable = pWidgetTable->pZOrderedWidget[0];
	ehs_uint16 nIndex = 0;

	/* We don't need to worry about overruns because the number of allocated slots in pZOrderedWidget
	 * are equal to nSize-1 at this point */
	while ((pZTable != NULL) &&
		(pZTable->nZ <= pWidget->nZ))
	{
		pZTable = pWidgetTable->pZOrderedWidget[++nIndex];
	}
	memmove(&(pWidgetTable->pZOrderedWidget[nIndex+1]),
		&(pWidgetTable->pZOrderedWidget[nIndex]),
		((pWidgetTable->nSize-1) - nIndex)*sizeof(EhsWidgetClass*));
	pWidgetTable->pZOrderedWidget[nIndex] = pWidget;
}

/**
 * Draw a widget list in response to a draw command from the target viewport
 * Widgets are drawn in z-order (lowest first).
 *
 * @param pWidgetTable Set of widgets to redraw
 * @param pViewport Physical viewport to write to
 * @param pClipRect Specifies the bounds of what is drawn
 */
void EhsWidgetTable_draw(const EhsWidgetTableClass* pWidgetTable, EhsTgtViewportClass *pViewport, EhsGraphicsRectangleClass* pClipRect)
{
	EhsWidgetClass* pWidget;
	ehs_uint16 nIndex;
		
	for (nIndex = 0; 
		nIndex < pWidgetTable->nSize; 
		nIndex++)
	{
		pWidget = (pWidgetTable->pZOrderedWidget[nIndex]);
		if (pWidget)
		{
			EhsWidget_draw(pWidget, pViewport, pClipRect, NULL);
		}
		else
		{
			break;
		}
	}
}
