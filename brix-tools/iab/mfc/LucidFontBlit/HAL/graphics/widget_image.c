/** @file widget_image.c
 * Definitions for the image widget handling functions
 * 
 * @author: Andrew Coombes
 * @version: $Revision: 1120 $
 * @date: $Date: 2006-10-30 05:05:44 +0000 (Mon, 30 Oct 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */

#include "widget.h"
#include "messages.h"
#include "hal_string.h"


/**
 * Insert a widget itno the Z-ordered list of widgets. This is called
 * after a widget has been initialized, but before the index to the widget
 * table has been updated. This is only used by subclasses of EhsWidget.
 */
EHS_GLOBAL void EhsWidgetTable_updateZOrder(EhsWidgetTableClass* pWidgetTable, EhsWidgetClass* pWidget);

/**
 * Create the widget. This is a necessary step prior to showing the widget.
 * NOTE: This must only be called by EhsWidget_create via the widget's
 * pfCreate function.
 */
EHS_LOCAL void EhsWidgetImage_create(struct EhsWidgetStruct* pWidget);

/**
 * Destroy the widget. Required after the widget has been finished with.
 * NOTE: This must only be called by EhsWidget_destroy via the widget's 
 * pfDestroy function.
 */
EHS_LOCAL void EhsWidgetImage_destroy(struct EhsWidgetStruct* pWidget);

/**
 * Load the image-specific data into the widget from the specified file
 */
EHS_LOCAL ehs_bool EhsWidgetImage_load(EhsWidgetClass* pWidget, const ehs_char* szFilename);

/**
 * Fade the image according to an opacity value
 *
 * @return true if the image needs to be redrawn (because it's appearance has changed)
 */
EHS_LOCAL ehs_bool EhsWidgetImage_fade(EhsWidgetClass* pWidget, ehs_uint8 nOpacity);

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
EhsWidgetClass* EhsWidgetImage_init(ehs_uint16 nX, ehs_uint16 nY, ehs_uint16 nZ, ehs_uint8 nImageAlpha, const ehs_char* szFilename)
{
	EhsWidgetClass* pWidget = EhsWidgetTable_new(&EhsWidgetTable);

	if (pWidget)
	{
		/* set standard widget properties */
		pWidget->eWidgetKind = EHS_WIDGET_KIND_IMAGE;
		pWidget->xOrigRect.nLeft = nX;
		pWidget->xOrigRect.nTop  = nY;
		pWidget->xOrigRect.nWidth = 0u; /* initialised later */
		pWidget->xOrigRect.nHeight = 0u; /* initialised later */
		EhsMemcpy(&(pWidget->xCurRect),&(pWidget->xOrigRect),sizeof(EhsGraphicsRectangleClass));
		pWidget->nZ = nZ;
		EHS_WIDGET_IMAGE(pWidget).nOrigImageAlpha = nImageAlpha;
		EHS_WIDGET_IMAGE(pWidget).nCurrentImageAlpha = nImageAlpha;

		pWidget->pfCreateFunc = EhsWidgetImage_create;
		pWidget->pfDestroyFunc = EhsWidgetImage_destroy;
		pWidget->pfFadeFunc = EhsWidgetImage_fade;

		/* determine image type by file extension */
		if (EhsWidgetImage_load(pWidget,szFilename))
		{
			pWidget->xOrigRect.nWidth = pWidget->xCurRect.nWidth;
			pWidget->xOrigRect.nHeight = pWidget->xCurRect.nHeight;
			pWidget->nState = EHS_WIDGET_STATE_INIT;
			/* slight break from true OO style here. In theory, we ought to be
			 * getting the draw functions indirectly from EhsImageClass, rather
			 * than examining internal values and getting functions directly. 
			 * However, this avoids unnecessary RAM being wasted.
			 */
			switch(EHS_WIDGET_IMAGE(pWidget).eImageFormat)
			{
			case EHS_WIDGET_IMAGE_FORMAT_GIF:
				pWidget->pfDrawFunc = EhsWidgetImageGif_draw;
				break;
			case EHS_WIDGET_IMAGE_FORMAT_PNG:
				pWidget->pfDrawFunc = EhsWidgetImagePng_draw;
				break;
			default:
				pWidget->nState = EHS_WIDGET_STATE_EMPTY;
				break;
			}
		}
		else
		{
			pWidget->nState = EHS_WIDGET_STATE_EMPTY;
		}

		if (pWidget->nState != EHS_WIDGET_STATE_EMPTY)
		{
			EhsWidgetTable_updateZOrder(&EhsWidgetTable, pWidget);
		}
	}
	return pWidget;
}



/**
 * Create the widget. This is a necessary step prior to showing the widget.
 * NOTE: This must only be called by EhsWidget_create. All widget creation should be
 * handled by EhsWidget_create.
 */
void EhsWidgetImage_create(EhsWidgetClass* pWidget)
{
	/* No specific image creation activities are required */
}

/**
 * Destroy the widget. Required after the widget has been finished with.
 * NOTE: This must only be called by EhsWidget_destroy. All widget destruction should be
 * handled by EhsWidget_destroy.
 */
void EhsWidgetImage_destroy(EhsWidgetClass* pWidget)
{
	/* no specific image destruction activities are required */
}

/**
 * Load the image-specific data into the widget from the specified file
 */
ehs_bool EhsWidgetImage_load(EhsWidgetClass* pWidget, const ehs_char* szFilename)
{
	ehs_bool bRet;
	ehs_char* szExtension = strchr(szFilename,'.');

	if (szExtension != NULL)
	{
		if (EhsStricmp(".gif",szExtension) == 0)
		{
			EHS_WIDGET_IMAGE(pWidget).eImageFormat = EHS_WIDGET_IMAGE_FORMAT_GIF;
			bRet = EhsWidgetImageGif_load(pWidget,szFilename);
		}
		else if (EhsStricmp(".png",szExtension) == 0)
		{
			EHS_WIDGET_IMAGE(pWidget).eImageFormat = EHS_WIDGET_IMAGE_FORMAT_PNG;
			bRet = EhsWidgetImagePng_load(pWidget,szFilename);
		}
		else
		{
			EhsError(EHS_MSG_ERROR_WIDGET_TYPE_NOT_RECOG(strchr(szFilename,'.')));
			bRet = EHS_FALSE;
		}
	}
	else
	{
		EhsError(EHS_MSG_ERROR_WIDGET_TYPE_NOT_RECOG(szFilename));
		bRet = EHS_FALSE;
	}

	return bRet;
}

/**
 * Fade the image according to an opacity value
 *
 * @return true if the image needs to be redrawn (because it's appearance has changed)
 */
ehs_bool EhsWidgetImage_fade(EhsWidgetClass* pWidget, ehs_uint8 nOpacity)
{
	ehs_bool bChanged = EHS_FALSE;

	/* determine the new opacity required by this widget */
	ehs_uint16 nCalcOpacity = (EHS_WIDGET_IMAGE(pWidget).nOrigImageAlpha * nOpacity) / 255;

	/* is it any different to the opacity we have already? */
	if (nCalcOpacity != EHS_WIDGET_IMAGE(pWidget).nCurrentImageAlpha)
	{
		EHS_WIDGET_IMAGE(pWidget).nCurrentImageAlpha = (ehs_uint8)nCalcOpacity;
		bChanged = EHS_TRUE;
	}

	return bChanged;
}
