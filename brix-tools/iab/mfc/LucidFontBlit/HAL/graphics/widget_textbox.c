/** @file widget_textbox.c
 * Definitions for the textbox widget handling functions
 * 
 * @author: Andrew Coombes
 * @version: $Revision: 1138 $
 * @date: $Date: 2006-10-30 05:05:44 +0000 (Mon, 30 Oct 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */

#include "widget.h"
#include "messages.h"
#include "hal_string.h"
#include "font.h"

/**
 * Insert a widget itno the Z-ordered list of widgets. This is called
 * after a widget has been initialized, but before the index to the widget
 * table has been updated
 */
EHS_GLOBAL void EhsWidgetTable_updateZOrder(EhsWidgetTableClass* pWidgetTable, EhsWidgetClass* pWidget);

/**
 * Create the widget. This is a necessary step prior to showing the widget.
 * NOTE: This must only be called by EhsWidget_create via the widget's
 * pfCreate function.
 */
EHS_LOCAL void EhsWidgetTextbox_create(struct EhsWidgetStruct* pWidget);

/**
 * Destroy the widget. Required after the widget has been finished with.
 * NOTE: This must only be called by EhsWidget_destroy via the widget's 
 * pfDestroy function.
 */
EHS_LOCAL void EhsWidgetTextbox_destroy(struct EhsWidgetStruct* pWidget);

/**
 * Fade the textbox according to an opacity value
 *
 * @return true if the textbox needs to be redrawn (because it's appearance has changed)
 */
EHS_LOCAL ehs_bool EhsWidgetTextbox_fade(struct EhsWidgetStruct* pWidget, ehs_uint8 nOpacity);

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
EhsWidgetClass* EhsWidgetTextbox_init(ehs_uint16 nX, ehs_uint16 nY, ehs_uint16 nZ, 
									  ehs_uint16 nWidth, ehs_uint16 nHeight, 
									  EhsGraphicsColourClass xFgColour, EhsGraphicsColourClass xBgColour,
									  EhsGraphicsFontClass* pFont)
{
	EhsWidgetClass* pWidget = EhsWidgetTable_new(&EhsWidgetTable);

	if (pWidget)
	{
		pWidget->eWidgetKind = EHS_WIDGET_KIND_TEXTBOX;
		pWidget->nState = EHS_WIDGET_STATE_INIT;
		pWidget->xOrigRect.nLeft = nX;
		pWidget->xOrigRect.nTop = nY;
		pWidget->xOrigRect.nWidth = nWidth;
		pWidget->xOrigRect.nHeight = nHeight;
		pWidget->bOptimiseForSpeed = EHS_FALSE;
		EhsMemcpy(&(pWidget->xCurRect),&(pWidget->xOrigRect),sizeof(EhsGraphicsRectangleClass));

		pWidget->nZ = nZ;
		pWidget->pfCreateFunc = EhsWidgetTextbox_create;
		pWidget->pfDestroyFunc = EhsWidgetTextbox_destroy;
		pWidget->pfFadeFunc = EhsWidgetTextbox_fade;
		pWidget->pfDrawFunc = EhsWidgetTextbox_draw;
		EHS_WIDGET_TEXTBOX(pWidget).xFgColour = xFgColour;
		EHS_WIDGET_TEXTBOX(pWidget).nFgBaseAlpha = xFgColour.sComp.nAlpha;
		EHS_WIDGET_TEXTBOX(pWidget).xBgColour = xBgColour;
		EHS_WIDGET_TEXTBOX(pWidget).nBgBaseAlpha = xBgColour.sComp.nAlpha;
		EhsHGHtmlString_init(&(EHS_WIDGET_TEXTBOX(pWidget).xText), EHS_STRING_LENGTH_MAX);
		EHS_WIDGET_TEXTBOX(pWidget).pFont = pFont;
#define DEFAULT_INDENT 0
		EHS_WIDGET_TEXTBOX(pWidget).xTextRect.nHeight = pWidget->xOrigRect.nHeight - (2*DEFAULT_INDENT);
		EHS_WIDGET_TEXTBOX(pWidget).xTextRect.nWidth = pWidget->xOrigRect.nWidth - (2*DEFAULT_INDENT);
		EHS_WIDGET_TEXTBOX(pWidget).xTextRect.nLeft = pWidget->xOrigRect.nLeft + DEFAULT_INDENT;
		EHS_WIDGET_TEXTBOX(pWidget).xTextRect.nTop = pWidget->xOrigRect.nTop + DEFAULT_INDENT;
		EhsWidgetTable_updateZOrder(&EhsWidgetTable, pWidget);
	}
	return pWidget;
}



/**
 * Create the widget. This is a necessary step prior to showing the widget.
 * NOTE: This must only be called by EhsWidget_create. All widget creation should be
 * handled by EhsWidget_create.
 */
void EhsWidgetTextbox_create(EhsWidgetClass* pWidget)
{
	/* No specific textbox creation activities are required */
}

/**
 * Destroy the widget. Required after the widget has been finished with.
 * NOTE: This must only be called by EhsWidget_destroy. All widget destruction should be
 * handled by EhsWidget_destroy.
 */
void EhsWidgetTextbox_destroy(EhsWidgetClass* pWidget)
{
	/* no specific textbox destruction activities are required */
}

/**
 * Cause the widget to be displayed (assuming it's already been created). If
 * it hasn't been created, there are no ill effects.
 *
 * NOTE: This function must only be called by EhsWidget_draw.
 *
 * @param pWidget. Widget to display.
 * @param pViewport. Viewport to display the widget on.
 * @param pClipRect Specifies the bounds for drawing the widget
 */
void EhsWidgetTextbox_draw(struct EhsWidgetStruct* pWidget, EhsTgtViewportClass* pViewport, EhsGraphicsRectangleClass* pClipRect, EhsTgtViewportSurfaceClass* pSurface)
{
	ehs_bool bOk = EHS_TRUE; /* true so long as we can continue drawing to the surface */
	
	if (!pWidget->bOptimiseForSpeed) {
		EhsGraphicsColourClass xPalette[2];
		xPalette[0] = EHS_WIDGET_TEXTBOX(pWidget).xBgColour;
		xPalette[1] = EHS_WIDGET_TEXTBOX(pWidget).xFgColour;
		//pSurface = EhsTgtViewportSurface_create(pViewport,pWidget->xCurRect.nWidth,pWidget->xCurRect.nHeight,EHS_GRAPHICS_COLOUR_A1,xPalette,2);
		if (pSurface) {
			if (EHS_WIDGET_TEXTBOX(pWidget).pFont) {
				ehs_uint32 nXPos, nYPos;
				void* pCurrentWord;
				ehs_bool bToggle = EHS_TRUE;
				ehs_char* szWord = "Sample";
				EhsHGHtmlWordType eType = EHSHG_HTML_WORD_STYLE_TEXT;
				
				nXPos = EHS_WIDGET_TEXTBOX(pWidget).xTextRect.nLeft - pWidget->xCurRect.nLeft;
				nYPos = (EHS_WIDGET_TEXTBOX(pWidget).xTextRect.nTop - pWidget->xCurRect.nTop)+EHS_WIDGET_TEXTBOX(pWidget).pFont->nMaxHt;
	
				pCurrentWord = NULL;
//				while(bOk && EhsHGHtmlString_getWord(&(EHS_WIDGET_TEXTBOX(pWidget).xText), &szWord, &eType, &pCurrentWord)) {
				while(bOk) {
					if (bToggle) {
						szWord = "Sample";
					}
					else {
						szWord = "Text";
					}
					bToggle = !bToggle;
					switch (eType) {
					case EHSHG_HTML_WORD_STYLE_TEXT:
						bOk = EhsGraphicsFont_drawWord(EHS_WIDGET_TEXTBOX(pWidget).pFont, pSurface, 
								&(pWidget->xCurRect),
								&(EHS_WIDGET_TEXTBOX(pWidget).xTextRect), 
								&nXPos, &nYPos, szWord);
						break;
					case EHSHG_HTML_WORD_BREAK:
						bOk = EhsGraphicsFont_newLine(EHS_WIDGET_TEXTBOX(pWidget).pFont, &(EHS_WIDGET_TEXTBOX(pWidget).xTextRect), &nXPos, &nYPos);
						break;
					case EHSHG_HTML_WORD_PARA:
						bOk = EhsGraphicsFont_newLine(EHS_WIDGET_TEXTBOX(pWidget).pFont, &(EHS_WIDGET_TEXTBOX(pWidget).xTextRect), &nXPos, &nYPos);
						bOk = bOk && EhsGraphicsFont_newLine(EHS_WIDGET_TEXTBOX(pWidget).pFont, &(EHS_WIDGET_TEXTBOX(pWidget).xTextRect), &nXPos, &nYPos);
						break;
					case EHSHG_HTML_WORD_STYLE_START:
						/*@todo implement support for styles */
					case EHSHG_HTML_WORD_STYLE_END:
					case EHSHG_HTML_WORD_IMG:
						/*@todo implement support for in-line images */
					default:
						break;
					}
				}
			}
		}
	} else {
		/**< @todo replace this with a real surface */
		pSurface = NULL;
	}
	
	if (pSurface) {
		//EhsTgtViewport_blit(pViewport, pSurface, &(pWidget->xCurRect),255u);
	}

	
	if (!pWidget->bOptimiseForSpeed) {
		//EhsTgtViewportSurface_destroy(pViewport, pSurface);
	}
}

/**
 * Set the text to be displayed onto a specific textbox. This function can be called
 * directly by any functions
 *
 * @param pWidget Textbox to display text
 * @param szText String to be displayed
 */
void EhsWidgetTextbox_write(struct EhsWidgetStruct* pWidget, const ehs_char* szText)
{
	/* @todo check for changes to HTML - don't update viewport if no change has occcured */
	if (EhsHGHtmlString_parse(&(EHS_WIDGET_TEXTBOX(pWidget).xText),szText)) {
		/* if pWidget is visible, update viewport */
		if (EHS_WIDGET_STATE_SHOWN(pWidget->nState))
		{
			EhsTgtViewport_updateRect(&EhsTgtViewport, pWidget->xCurRect.nLeft, pWidget->xCurRect.nTop, pWidget->xCurRect.nWidth, pWidget->xCurRect.nHeight);
		}
	}
}

/**
 * Fade the textbox according to an opacity value
 *
 * @return true if the textbox needs to be redrawn (because it's appearance has changed)
 */
ehs_bool EhsWidgetTextbox_fade(struct EhsWidgetStruct* pWidget, ehs_uint8 nOpacity)
{
	ehs_bool bChanged = EHS_FALSE;

	/* determine the new foreground and background opacity required by this widget */
	ehs_uint16 nCalcFgOpacity = (EHS_WIDGET_TEXTBOX(pWidget).nFgBaseAlpha * nOpacity) / 255;
	ehs_uint16 nCalcBgOpacity = (EHS_WIDGET_TEXTBOX(pWidget).nBgBaseAlpha * nOpacity) / 255;
	/* scale down to 8-bit */
	ehs_uint8 nFgOpacity = (ehs_uint8)nCalcFgOpacity;
	ehs_uint8 nBgOpacity = (ehs_uint8)nCalcBgOpacity;

	/* is it any different to the opacity we have already? */
	if ((nFgOpacity != EHS_WIDGET_TEXTBOX(pWidget).xFgColour.sComp.nAlpha) ||
		(nBgOpacity != EHS_WIDGET_TEXTBOX(pWidget).xBgColour.sComp.nAlpha))
	{
		EHS_WIDGET_TEXTBOX(pWidget).xFgColour.sComp.nAlpha = nFgOpacity;
		EHS_WIDGET_TEXTBOX(pWidget).xBgColour.sComp.nAlpha = nBgOpacity;
		bChanged = EHS_TRUE;
	}

	return bChanged;
}
