/** @file target_viewport.c
 * This file provides the definitions necessary for simulating the target_viewport code
 * 
 *
 * @author: Andrew Coombes
 * @version: $Revision: 1137 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */

#include "hal_viewport.h"
#include "widget.h"
#include "mem.h"
#include "messages.h"
#include "hal_string.h"

/**
 * Convert EHS specific colour type to windows specific colour type
 */
EHS_LOCAL COLORREF EhsTgtViewport_getColour(EhsGraphicsColourClass);

/**
 * Reference to the main window handle. This is necessary to be able
 * to refresh the window when we change the bitmaps we wish to display
 */
HWND EhsTgtMainWindowHandle;

/**
 * Define the target viewport type
 */
struct EhsTgtViewportStruct
{
	/**
	 * Reference to current device context. This is set at the start of the
	 * painting process, and reset to null when painting has finished.
	 */
	HDC hdc;
	/**
	 * Bitmap info needed every time blit is called. Some properties remain the
	 * same every call, therefore initialised once, rather than every blit
	 */
	BITMAPINFO bmi;
	/**
	 * Structure needed for alpha blending of bitmaps. Initialised once.
	 */
	BLENDFUNCTION bf; 

	ehs_uint32 init; /**< set to a special pattern to prove that we've been
					 * initialised - avoids a race condition where paint occurs before
					 * EHS is initialized */

};

/**
 * Define the target viewport. Only one viewport is defined at this
 * stage.
 */
EhsTgtViewportClass EhsTgtViewport = {0};

/**
 * Initialise the target viewport
 */
ehs_bool EhsTgtViewport_init(EhsTgtViewportClass* pViewport)
{
	/* initialise fixed bitmap header parameters */
    ZeroMemory(&(pViewport->bmi), sizeof(BITMAPINFO));
	pViewport->bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pViewport->bmi.bmiHeader.biPlanes = 1;
    pViewport->bmi.bmiHeader.biBitCount = 32;         /* four 8-bit components */
    pViewport->bmi.bmiHeader.biCompression = BI_RGB;

	/* intialise our blend function */
	pViewport->bf.BlendOp = AC_SRC_OVER;
    pViewport->bf.BlendFlags = 0;
    pViewport->bf.SourceConstantAlpha = 0xff;  // half of 0xff = 50% transparency
    pViewport->bf.AlphaFormat = AC_SRC_ALPHA;             // ignore source alpha channel
	pViewport->init = -1;

	return EHS_TRUE;
}

/**
 *  Terminate the use of the target viewport. This function
 * releases resources occupied by the viewport.
 */
 void EhsTgtViewport_term(EhsTgtViewportClass* pViewport)
 {
 	/* not currently used, therefore not implemented */
 }

/**
 * Indicate to the target that the viewport needs updating.
 * This will eventually result in EhsTgtViewport_paint being called
 */
void EhsTgtViewport_update(EhsTgtViewportClass* pViewport)
{
	InvalidateRect(EhsTgtMainWindowHandle, NULL, FALSE);
}

/**
 * Indicate to the target that a rectangle on the viewport needs updating.
 * This will eventually result in EhsTgtViewport_paint being called
 */
void EhsTgtViewport_updateRect(EhsTgtViewportClass* pViewport, ehs_uint16 nX, ehs_uint16 nY, ehs_uint16 nWidth, ehs_uint16 nHeight)
{
	InvalidateRect(EhsTgtMainWindowHandle, NULL, FALSE);
	return;
	/*
	RECT r;

	r.left = nX;
	r.top = nY;
	r.right = nX + nWidth;
	r.bottom = nY + nHeight;

	InvalidateRect(EhsTgtMainWindowHandle, &r, FALSE);
	*/
}

/**
 * Clear the target viewport
 */
void EhsTgtViewport_clear(EhsTgtViewportClass* pViewport)
{
	InvalidateRect(EhsTgtMainWindowHandle, NULL, FALSE);
}

/**
 * Display the specified text at the specified X,Y position in the
 * specified foreground/background colours
 *
 * @todo Deal with strings longer than 100 characters
 * @todo Remove non-MISRA compliant code for "local" #define
 * @param pViewport Current viewport
 * @param szText Text to display
 * @param nX Left side of text box
 * @param nY Top side of text box
 * @param nWid Width of text box
 * @param nHt Height of text box
 * @param xFgColour Foreground colour (colour of letters)
 * @param xBgColour Background colour (colour behind letters)
 */


#define NEWTEXTFUNCTION
#ifdef NEWTEXTFUNCTION
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
void EhsTgtViewport_displayText(EhsTgtViewportClass* pViewport, const char* szText, const EhsGraphicsRectangleClass* pImgBounds,
		EhsGraphicsColourClass xFgColour, EhsGraphicsColourClass xBgColour)
{
	//HFONT hNewFont, hOldFont;
	UINT parms;
#define BUFFSIZE 100
	TCHAR buff[BUFFSIZE];
	ehs_uint32 i;
	RECT rBoundingBox; /* defines the extent of the textbox */
	HDC 	hdcBm; // need to paint to mem first
	HBITMAP hbitmap,hbmOld;   // needed for above
	UINT* pPixels;
	BLENDFUNCTION bf;
	HFONT hRegFont; //to save the previous font for the viewport context
	HFONT hNewFont; // the new font that is used for this widgets text
	ehs_uint16 nX = pImgBounds->nLeft;
	ehs_uint16 nY = pImgBounds->nTop;
	ehs_uint16 nWid = pImgBounds->nWidth;
	ehs_uint16 nHt = pImgBounds->nHeight;

	//PD: Can the following be made generic - Otherwise the last bitmap data get used .
	pViewport->bmi.bmiHeader.biWidth = nWid;
	pViewport->bmi.bmiHeader.biHeight = -nHt; 
	pViewport->bmi.bmiHeader.biSizeImage = (nWid * nHt) << 2; /* width * height (=1) * 4 (sizeof(ARGB) */

	if (hNewFont = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"Tahoma")) {
		if (hdcBm=CreateCompatibleDC(pViewport->hdc)) {
			if (hRegFont = (HFONT)SelectObject(hdcBm,hNewFont))	
			{
				/* establish textbox extent */ //PD: changes for buffere alpha blending
				rBoundingBox.bottom = nHt;
				rBoundingBox.left = 0;
				rBoundingBox.right = nWid;
				rBoundingBox.top = 0;
				/* convert utf-8 string into whatever type of string (utf-8/Unicode)
				* this build uses */
				for (i = 0; i < strlen(szText) && i < BUFFSIZE-1; i++)
				{
					buff[i] = (TCHAR)szText[i];
				}
				buff[i+1] = 0;
				if (hbitmap = CreateDIBSection(hdcBm, &(pViewport->bmi), DIB_RGB_COLORS, (void**)&pPixels, NULL, 0x0)) {
					hbmOld = SelectObject(hdcBm, hbitmap);
					/* define blending for font and background */
					bf.BlendOp = AC_SRC_OVER;
					bf.BlendFlags = 0;
					bf.AlphaFormat= AC_SRC_ALPHA;
					bf.SourceConstantAlpha = 255;
					// Create the backgound
					SetBkColor(hdcBm,EhsTgtViewport_getColour(xBgColour));
					SetBkMode(hdcBm,TRANSPARENT);
					SetTextColor(hdcBm,EhsTgtViewport_getColour(xFgColour));
					parms = ( ETO_CLIPPED);
					for (i=0;i<((ehs_uint32)nWid*(ehs_uint32)nHt);i++) {  // set the background alpha to not background colour before blitting
						((EhsGraphicsColourClass*)(pPixels))[i].sComp.nBlue =~xFgColour.sComp.nBlue;
					}
					ExtTextOutA(hdcBm,10,((nHt<20)?10:(nHt/2-15)),parms,&rBoundingBox,szText,strlen(szText),NULL); // cheaper to create patch this way
					//if (szText[0]==0) {
					for (i=0;i<((ehs_uint32)nWid*(ehs_uint32)nHt);i++) {  
						if ( ((EhsGraphicsColourClass*)(pPixels))[i].sComp.nBlue == xFgColour.sComp.nBlue) 
						{
							((EhsGraphicsColourClass*)(pPixels))[i].sComp.nRed  =(xFgColour.sComp.nRed*xFgColour.sComp.nAlpha)>>8 ;
							((EhsGraphicsColourClass*)(pPixels))[i].sComp.nGreen=(xFgColour.sComp.nGreen*xFgColour.sComp.nAlpha)>>8 ;
							((EhsGraphicsColourClass*)(pPixels))[i].sComp.nBlue =(xFgColour.sComp.nBlue*xFgColour.sComp.nAlpha)>>8 ;
							((EhsGraphicsColourClass*)(pPixels))[i].sComp.nAlpha =xFgColour.sComp.nAlpha;
						}
						else { //write background
							((EhsGraphicsColourClass*)(pPixels))[i].sComp.nRed  =(xBgColour.sComp.nRed*xBgColour.sComp.nAlpha)>>8 ;
							((EhsGraphicsColourClass*)(pPixels))[i].sComp.nGreen=(xBgColour.sComp.nGreen*xBgColour.sComp.nAlpha)>>8 ;
							((EhsGraphicsColourClass*)(pPixels))[i].sComp.nBlue =(xBgColour.sComp.nBlue*xBgColour.sComp.nAlpha)>>8 ;
							((EhsGraphicsColourClass*)(pPixels))[i].sComp.nAlpha =xBgColour.sComp.nAlpha;
						} // this is a little clumsy !
					} // end for loop
					//} // string test
					/*else { //just blit the background
						for (i=0;i<((ehs_uint32)nWid*(ehs_uint32)nHt);i++) {
							((EhsGraphicsColourClass*)(pPixels))[i].sComp.nRed  =(xBgColour.sComp.nRed*xBgColour.sComp.nAlpha)>>8 ;
							((EhsGraphicsColourClass*)(pPixels))[i].sComp.nGreen=(xBgColour.sComp.nGreen*xBgColour.sComp.nAlpha)>>8 ;
							((EhsGraphicsColourClass*)(pPixels))[i].sComp.nBlue =(xBgColour.sComp.nBlue*xBgColour.sComp.nAlpha)>>8 ;
							((EhsGraphicsColourClass*)(pPixels))[i].sComp.nAlpha =xBgColour.sComp.nAlpha;
						}
					}
					*/

					AlphaBlend(
							pViewport->hdc,
							nX, 
							nY, 
							nWid,
							nHt,
							hdcBm,
							0,
							0,
							nWid,
							nHt,
							bf );

					if (hbmOld) SelectObject(hdcBm,hbmOld);	
					DeleteObject(hbitmap);
				} // get pixels bitmap successfull
	
			} //if font swap OK.s
			DeleteDC(hdcBm);
		} // end context hdcBm is OK
	} // Created font OK
	DeleteObject(hNewFont); // delete the font for the memory context
#undef BUFFSIZE
}
#endif


//EhsGraphicsColourClass EhsTgtViewport_screen[1024];

/**
 * Convert EhsColourType to colour format used by Windows.
 * EhsColourType appears as 0xbbggrraa, Windows requires 0xaarrbbgg.
 * ASM is used to avoid 320% instruction increase (or 800% depending
 * upon code used). Specifically, I can't get VC to generate the BSWAP
 * instruction, which does just what I need.
 */
EHS_LOCAL void EhsTgtViewport_convertColour(void* pD, void* pS, int size)
{
	int i;
	register char* pDst = pD;
	register char* pSrc = pS;
	for (i = 0; i < size; i+=4, pDst+=4, pSrc+=4)
	{
		__asm {
			mov ecx, dword ptr [pSrc]
			mov edx, dword ptr [pDst]
			mov eax, dword ptr [ecx]
			bswap eax
			mov dword ptr [edx], eax
		}
	}
}

EHS_LOCAL EhsTgtViewport_blitARGB8888(UINT* pPixels, 
		EhsTgtViewportSurfaceClass* pSurface,
		const EhsGraphicsRectangleClass* pImgBounds, 
		ehs_uint8 nImageAlpha)
{
	ehs_uint16 i;
	EhsGraphicsColourClass* pLine = EhsTgtViewportSurface_pixels(pSurface); 
	for (i=0;i<(pImgBounds->nWidth*pImgBounds->nHeight-1);i++) {  
		((EhsGraphicsColourClass*)(pPixels))[i].sComp.nRed  =(pLine[i].sComp.nRed * pLine[i].sComp.nAlpha * nImageAlpha)/0xFFFF; // do all in one step as 32 bit processing 
		((EhsGraphicsColourClass*)(pPixels))[i].sComp.nGreen=(pLine[i].sComp.nGreen * pLine[i].sComp.nAlpha* nImageAlpha)/0xFFFF;
		((EhsGraphicsColourClass*)(pPixels))[i].sComp.nBlue =(pLine[i].sComp.nBlue* pLine[i].sComp.nAlpha* nImageAlpha)/0xFFFF;
		((EhsGraphicsColourClass*)(pPixels))[i].sComp.nAlpha = pLine[i].sComp.nAlpha*nImageAlpha/0xFF;
	}

}

EHS_LOCAL EhsTgtViewport_blitA1(EhsGraphicsColourClass* pPixels, 
		EhsTgtViewportSurfaceClass* pSurface,
		const EhsGraphicsRectangleClass* pImgBounds, 
		ehs_uint8 nImageAlpha)
{
	ehs_uint16 x,y;
	EhsGraphicsColourClass xBg = pSurface->pPalette[0];
	EhsGraphicsColourClass xFg = pSurface->pPalette[1];
	
	for (y = 0; y < pImgBounds->nHeight; y++) {
		ehs_uint16 nPixIdx = y * pImgBounds->nWidth;
		ehs_uint16 nBmpIdx = y * ((pSurface->nWid+7)/8);
		for (x = 0; x < pImgBounds->nWidth; x++) {
			ehs_uint8 nBit = 1 << (7u - (x % 8u));
			if ((nBit & EhsTgtViewportSurface_bitmap(pSurface)[nBmpIdx + x/8]) == nBit) {
				pPixels[nPixIdx+x] = xFg;
			} else {
				pPixels[nPixIdx+x] = xBg;
			}
		}
	}
}
/**
 * 
 * @param[in] pViewport Current viewport
 * @param[in] pSurface The image to blit
 * @param[in] pImgBounds The bounding box for the image
 * @param[in] nAlpha The global alpha level
 * @todo Replace the blitXXX functions with this one.
 */
void EhsTgtViewport_blit(EhsTgtViewportClass* pViewport,
					const EhsTgtViewportSurfaceClass* pSurface, 
					const EhsGraphicsRectangleClass* pImgBounds, 
					ehs_uint8 nImageAlpha)

{
	HBITMAP hbmOld;
	HDC hdcBm;
	HBITMAP hbitmap;  
	UINT* pPixels;
	
	/* setup image-specific bitmap info. Common parameters have been set by EhsTgtViewport_init */
	pViewport->bmi.bmiHeader.biWidth = pImgBounds->nWidth;
	pViewport->bmi.bmiHeader.biHeight = -pImgBounds->nHeight; 
	/* imagesize = width * height * sizeof(ARGB) (=4) */
	pViewport->bmi.bmiHeader.biSizeImage = (pImgBounds->nWidth * pImgBounds->nHeight) << 2; 
	
	/* create our DIB section and select the bitmap into the dc */
	if (hdcBm = CreateCompatibleDC(pViewport->hdc)) {
		if (hbitmap = CreateDIBSection(hdcBm, &(pViewport->bmi), DIB_RGB_COLORS, (void**)&pPixels, NULL, 0x0)) {
			hbmOld = SelectObject(hdcBm, hbitmap);
			if (hbmOld) {
	
				switch (pSurface->eFormat) {
				case EHS_GRAPHICS_COLOUR_ARGB8888:
					EhsTgtViewport_blitARGB8888(pPixels, pSurface, pImgBounds, nImageAlpha);
					break;
				case EHS_GRAPHICS_COLOUR_A1:
					EhsTgtViewport_blitA1(pPixels, pSurface, pImgBounds, nImageAlpha);
					break;
				case EHS_GRAPHICS_COLOUR_A8:
					/* @todo support blitting for this kind of image */
				default:
					EhsError(EHS_MSG_TGT_GRAPHICS_UNSUPPORTED_FORMAT("EhsTgtViewport_blit",pSurface->eFormat));
					break;
				}
		
				/* blit in the bitmap */
				if (!AlphaBlend(pViewport->hdc, pImgBounds->nLeft, pImgBounds->nTop, 
					pImgBounds->nWidth, pImgBounds->nHeight, 
					hdcBm, 0, 0, pImgBounds->nWidth, pImgBounds->nHeight, pViewport->bf))
				{
					EhsError(EHS_MSG_TGT_WIN32("EhsTgtViewport_blit", "AlphaBlend() failed"));
				}
		
				/* Now, clean up. A memory DC always has a drawing
				* surface in it. It is created with a 1X1 monochrome
				* bitmap that we saved earlier, and need to put back
				* before we destroy it.
				*/
				SelectObject(hdcBm,hbmOld); 
			}
			DeleteObject(hbitmap);
	
		}
		DeleteDC(hdcBm);
	}

}


/**
 * Display a single line of an image to the specified X,Y position in the
 * specified viewport. The image is represented in ARGB8888 format
 *
 */
void EhsTgtViewport_blitArgb8888(EhsTgtViewportClass* pViewport,
											const EhsTgtViewportSurfaceClass* pSurface, 
											const EhsGraphicsRectangleClass* pImgBounds, ehs_uint8 nImageAlpha)
{
	EhsTgtViewport_blit(pViewport, pSurface, pImgBounds, nImageAlpha);
}

/**
 * Display a single line of an image to the specified X,Y position in the
 * specified viewport. The image is represented in RGB888 format
 *
 */
void EhsTgtViewport_blitRgb888(EhsTgtViewportClass* pViewport,
		const EhsTgtViewportSurfaceClass* pData, const EhsGraphicsRectangleClass* pImgBounds, ehs_uint8 nAlpha)
{
	EhsTgtViewport_blitArgb8888(pViewport, pData, pImgBounds, nAlpha);
}

/**
 * Display a single line of an image to the specified X,Y position in the
 * specified viewport. The image is represented in ARGB1888 format
 *
 */
void EhsTgtViewport_blitArgb1888(EhsTgtViewportClass* pViewport,
		const EhsTgtViewportSurfaceClass* pData, const EhsGraphicsRectangleClass* pImgBounds, ehs_uint8 nAlpha)
{
	EhsTgtViewport_blitArgb8888(pViewport, pData, pImgBounds, nAlpha);
}

/**
 * Fill a rectangle with a specified colour in the specified viewport.
 * 
 * @param[in] pViewport Viewport to fill rectangle into
 * @param[in] pRect position and size of rectangle to fill
 * @param[in] pColour Colour to use for filling rectangle (includes global alpha value)
 */
void EhsTgtViewport_fillRect(EhsTgtViewportClass* pViewport,
				const EhsGraphicsRectangleClass* pRect, const EhsGraphicsColourClass* pColour)
{
	HBITMAP hbmOld;
	HDC hdcBm;
	HBITMAP hbitmap;  
	UINT* pPixels;
	int i;
	ehs_uint16 nX;
	ehs_uint16 nY;
	ehs_uint16 nWidth;
	ehs_uint16 nHeight;

	/* fill only the intersection of the clipping rectangle and the filling rectangle */
	//if (EhsGraphicsRectangle_intersect(&intersection,&pRect,&(pViewport->viewRect))) {
	/**@todo use the intersection rectangle here */
	nX = pRect->nLeft;
	nY = pRect->nTop;
	nWidth = pRect->nWidth;
	nHeight = pRect->nHeight;

	/* setup image-specific bitmap info. Common parameters have been set by EhsTgtViewport_init */
	pViewport->bmi.bmiHeader.biWidth = nWidth;
	pViewport->bmi.bmiHeader.biHeight = -nHeight; 
	pViewport->bmi.bmiHeader.biSizeImage = (nWidth * nHeight) << 2; /* width * height (=1) * 4 (sizeof(ARGB) */
	
	/* create our DIB section and select the bitmap into the dc */
	if (hdcBm = CreateCompatibleDC(pViewport->hdc)) {
		if (hbitmap = CreateDIBSection(hdcBm, &(pViewport->bmi), DIB_RGB_COLORS, (void**)&pPixels, NULL, 0x0)) {
			EhsGraphicsColourClass xFillColour;
			hbmOld = SelectObject(hdcBm, hbitmap);
			
			xFillColour.sComp.nRed   = (pColour->sComp.nRed   * pColour->sComp.nAlpha) / 0xff;
			xFillColour.sComp.nGreen = (pColour->sComp.nGreen * pColour->sComp.nAlpha) / 0xff;
			xFillColour.sComp.nBlue  = (pColour->sComp.nBlue  * pColour->sComp.nAlpha) / 0xff;
			xFillColour.sComp.nAlpha = pColour->sComp.nAlpha;
	
			for (i=0; i < (nWidth*nHeight-1); i++) {  
				((EhsGraphicsColourClass*)(pPixels))[i].nUint32  = xFillColour.nUint32; 
			}
	
			/* blit in the bitmap */
			if (!AlphaBlend(pViewport->hdc, nX, nY, 
				nWidth, nHeight, 
				hdcBm, 0, 0, nWidth, nHeight, pViewport->bf))
			{
				nX=nX;/* @todo an error occurred - should log/record this */
			}
	
			/* Now, clean up. A memory DC always has a drawing
			* surface in it. It is created with a 1X1 monochrome
			* bitmap that we saved earlier, and need to put back
			* before we destroy it.
			*/
			if (hbmOld) SelectObject(hdcBm,hbmOld); // only swap back if the bitmap was successful
			DeleteObject(hbitmap);
	
		}
		DeleteDC(hdcBm);
	}

}

/**
 * Paint all of the current EHS objects that need painting. Called by
 * main "Windows" thread.
 *
 * @param hdc Device context in which to paint the window.
 */
void EhsTgtViewport_paint(HWND hWnd, LPPAINTSTRUCT lpPS)
{
	RECT rc; /* client rectangle */
	HBITMAP hbmMem; /* bitmap containing the client rectangle */
	HBITMAP hbmOld; /* ummm... Windows magic - need to keep the old device context to restore later, apparently */
	HBRUSH hbrBkGnd; /* used to set the background colour */
	EhsGraphicsRectangleClass clip;

	GetClientRect(hWnd, &rc);
	if (EhsTgtViewport.hdc = CreateCompatibleDC(lpPS->hdc)) { /* create DC compatible with application's current screen */

		/* create a bitmap that can hold the client rectangle */
		if (hbmMem = CreateCompatibleBitmap(lpPS->hdc, rc.right-rc.left,rc.bottom-rc.top)) {

			/* select the bitmap into the off-screen DC */
			if (hbmOld = SelectObject(EhsTgtViewport.hdc, hbmMem)) {

				/* erase the background */
				if (hbrBkGnd = (HBRUSH)(COLOR_WINDOW+2)) { /* somehow this makes a black brush */
					FillRect(EhsTgtViewport.hdc, &rc, hbrBkGnd);
					DeleteObject(hbrBkGnd);
				}// black vrush OK - we will still paint if this fails.
				if (EhsTgtViewport.init)
				{
					clip.nLeft = rc.left;
					clip.nTop = rc.top;
					clip.nWidth = rc.right - rc.left;
					clip.nHeight = rc.bottom - rc.top;
					EhsWidgetTable_draw(&EhsWidgetTable,&EhsTgtViewport, &clip);

					BitBlt(lpPS->hdc,
						rc.left, rc.top,
						rc.right-rc.left, rc.bottom-rc.top,
						EhsTgtViewport.hdc,
						0, 0,
						SRCCOPY);
					
				} //viewport inited
				SelectObject(EhsTgtViewport.hdc, hbmOld); // do we need this where going to delete .hdc next??
				
			} ////hbmem context OK
			DeleteObject(hbmMem);
		} //compatible bitmap OK
		DeleteDC(EhsTgtViewport.hdc);
		EhsTgtViewport.hdc = NULL;
	} // compatible context OK
	
	
}

/**
 * Convert EHS specific colour type to windows specific colour type
 */
COLORREF EhsTgtViewport_getColour(EhsGraphicsColourClass xColour)
{
	return RGB(xColour.sComp.nRed, xColour.sComp.nGreen, xColour.sComp.nBlue);
}

/**
 * Free memory used by a surface
 */
void EhsTgtViewportSurface_destroy(EhsTgtViewportClass* pViewport, EhsTgtViewportSurfaceClass *pSurface)
{
	switch (pSurface->eFormat) {
	case EHS_GRAPHICS_COLOUR_A1:
	case EHS_GRAPHICS_COLOUR_A8:
//		EhsMemWriteable_free(EhsTgtViewportSurface_bitmap(pSurface));
		free(EhsTgtViewportSurface_bitmap(pSurface));
		EhsTgtViewportSurface_bitmap(pSurface) = NULL;
//		EhsMemWriteable_free(pSurface->pPalette);
		free(pSurface->pPalette);
		pSurface->pPalette = NULL;
		break;
	case EHS_GRAPHICS_COLOUR_ARGB8888:
//		EhsMemWriteable_free(EhsTgtViewportSurface_pixels(pSurface));
		free(EhsTgtViewportSurface_pixels(pSurface));
		EhsTgtViewportSurface_pixels(pSurface) = NULL;
	}
//	EhsMemWriteable_free(pSurface);
	free(pSurface);
}

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
EhsTgtViewportSurfaceClass* EhsTgtViewportSurface_create(EhsTgtViewportClass* pViewport, 
		ehs_uint16 nWidth, ehs_uint16 nHeight, EhsGraphicsColourFormatEnum eFormat,
		EhsGraphicsColourClass* pPalette, ehs_uint16 nPaletteSize)
{
//	EhsTgtViewportSurfaceClass* pSurface = EhsMemWriteable_alloc(sizeof(EhsTgtViewportSurfaceClass));
	EhsTgtViewportSurfaceClass* pSurface = malloc(sizeof(EhsTgtViewportSurfaceClass));
	ehs_uint8 nPixelsPerByte; /* number of pixels that appear in a single byte in the lookup table type formats */
	
	if (pSurface) {
		pSurface->nWid = nWidth;
		pSurface->nHt = nHeight;
		pSurface->eFormat = eFormat;

		switch (eFormat) {
		case EHS_GRAPHICS_COLOUR_A1:
		case EHS_GRAPHICS_COLOUR_A8:
			nPixelsPerByte = (eFormat == EHS_GRAPHICS_COLOUR_A1)?8u:1u;
			/* calculate number of bytes required = (nWidth/(number of pixels per byte) rounded up) * nHeight */
//			EhsTgtViewportSurface_bitmap(pSurface) = (EhsGraphicsColourClass*)EhsMemWriteable_alloc((nWidth+(nPixelsPerByte-1))/nPixelsPerByte*nHeight);
			EhsTgtViewportSurface_bitmap(pSurface) = (EhsGraphicsColourClass*) malloc((nWidth+(nPixelsPerByte-1))/nPixelsPerByte*nHeight);
			if (!EhsTgtViewportSurface_bitmap(pSurface)) {
//				EhsMemWriteable_free(pSurface);
				free(pSurface);
				pSurface = NULL;
			} else {
				/* clear bitmap */
				EhsMemset(EhsTgtViewportSurface_bitmap(pSurface),0,(nWidth+(nPixelsPerByte-1))/nPixelsPerByte*nHeight);
				/* create space for palette */
//				pSurface->pPalette = (EhsGraphicsColourClass*)EhsMemWriteable_alloc(nPaletteSize*sizeof(EhsGraphicsColourClass));
				pSurface->pPalette = (EhsGraphicsColourClass*) malloc(nPaletteSize*sizeof(EhsGraphicsColourClass));
				if (!pSurface->pPalette) {
//					EhsMemWriteable_free(EhsTgtViewportSurface_bitmap(pSurface));
//					EhsMemWriteable_free(pSurface);
					free(EhsTgtViewportSurface_bitmap(pSurface));
					free(pSurface);
					pSurface = NULL;
				}
			} 
			if (pSurface) {
				/* copy palette */
				EhsMemcpy(pSurface->pPalette, pPalette, nPaletteSize*sizeof(EhsGraphicsColourClass));
			}
			break;
		case EHS_GRAPHICS_COLOUR_ARGB8888:
//			EhsTgtViewportSurface_pixels(pSurface) = (EhsGraphicsColourClass*)EhsMemWriteable_alloc(sizeof(EhsGraphicsColourClass) * nWidth * nHeight);
			EhsTgtViewportSurface_pixels(pSurface) = (EhsGraphicsColourClass*) malloc(sizeof(EhsGraphicsColourClass) * nWidth * nHeight);
			pSurface->pPalette = NULL;
			break;
		default:
			EhsError(EHS_MSG_TGT_GRAPHICS_UNSUPPORTED_FORMAT("EhsTgtViewportSurface_create", eFormat));
//			EhsMemWriteable_free(pSurface);
			free(pSurface);
			pSurface = NULL;
		}
	}
	
	return pSurface;
}

