#include "StdAfx.h"
#include ".\picdrawc.h"

#include "LgbTextIcon.h"
#include <assert.h>
#include "widget.h"

void CPicDrawC::DrawItem(LPDRAWITEMSTRUCT lpdis, bool bHasFocus)
{
	if (lpdis->itemID==(UINT)-1) return;

	CDC dc;
	CRect rect = lpdis->rcItem;
	
	
	ASSERT( lpdis->itemID >= 0 );
	const int nIndex = lpdis->itemID;

	dc.Attach(lpdis->hDC);

	// Save these value to restore them when done drawing.
	COLORREF crOldTextColor = dc.GetTextColor();
	COLORREF crOldBkColor = dc.GetBkColor();

	if ((lpdis->itemAction | ODA_SELECT) &&
	(lpdis->itemState  & ODS_SELECTED))	{
		dc.FillSolidRect(rect, ::GetSysColor(COLOR_HIGHLIGHT));
		if(bHasFocus) {
			dc.DrawFocusRect(rect);
		}	
	}
	else {      
		dc.FillSolidRect(rect, ::GetSysColor(COLOR_WINDOW));  
	}

	HBITMAP hbmp = (HBITMAP)lpdis->itemData;
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	MemDC.SelectObject(hbmp);
	dc.BitBlt(rect.left+5, rect.top+1, PicSizeX, PicSizeY, &MemDC, 0, 0, SRCCOPY);
	
	// Reset the background color and the text color back to their
	// original values.
	dc.SetTextColor(crOldTextColor);
	dc.SetBkColor(crOldBkColor);	

	dc.Detach();

}

void CPicDrawC::MeasureItem(LPMEASUREITEMSTRUCT lpmis)
{
	lpmis->itemHeight=PicSizeY+2;
	lpmis->itemWidth=PicSizeX+2;
}

int CPicDrawC::AddItemLst(CListBox* pLBox, UINT nItem) { 
	int n;
	n = pLBox->AddString("nu");
	HBITMAP hbmp = (HBITMAP)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(nItem), IMAGE_BITMAP, PicSizeX, PicSizeY, 0L);
	pLBox->SetItemData(n, (DWORD)hbmp);
	return n;
}

int CPicDrawC::AddItemLst(CListBox* pLBox) { 
	int n;
	n = pLBox->AddString("nu");
	//HBITMAP hbmp = (HBITMAP)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(nItem), IMAGE_BITMAP, PicSizeX, PicSizeY, 0L);
	
	CDC* dc = pLBox->GetDC();

	// create memory device context
	CDC* pSrcMemDC = new CDC;
	assert( NULL != pSrcMemDC );

	pSrcMemDC->CreateCompatibleDC(dc);

	// RGB + Alpha
	int iWidth = 50;
	int iHeight = 30;
	CWnd* pWnd = dc->GetWindow();
	CRect rect;
	pWnd->GetClientRect(rect);
	int totalBytes = iWidth * iHeight * 4;

	CBitmap* pSrcBmp = new CBitmap;
	assert( NULL != pSrcBmp );

	// initialize
	pSrcBmp->CreateCompatibleBitmap(dc, iWidth, iHeight);
	pSrcMemDC->SelectObject(pSrcBmp);

	void *byteArr = new BYTE [ totalBytes ];
	assert( NULL != byteArr );

	BYTE *tmp = (BYTE *) byteArr;

	// set the flagged array to the bitmap
	pSrcBmp->SetBitmapBits( totalBytes, byteArr );

	// Write text using EHS font blitter
	LgbTextIcon dumTextIcon;
	//CString csFont = GetFont(csStyle);
	CString csFont = "lsr";
	EhsWidgetClass* pWidget;
	EhsTgtViewportSurfaceClass* pSurface = NULL;
	EhsGraphicsColourClass xFgColour, xBgColour;
	EhsGraphicsFontClass* pFont = dumTextIcon.GetFontPtr(csFont);
	LgbColorsDef cColors;
	cColors.m_iFgAlpha = 255;
	cColors.m_iFgBlue = 255;
	cColors.m_iFgGreen = 0;
	cColors.m_iFgRed = 0;

	//if (0) {
		if (pFont) {
			//xFgColour = EhsGraphicsColour_argb(cColors.m_iFgRed, cColors.m_iFgGreen, cColors.m_iFgBlue, cColors.m_iFgAlpha);
			xFgColour = EhsGraphicsColour_argb(150, 150, 150, 150);
			xBgColour = EhsGraphicsColour_argb(255, 255, 255, 0);
			EhsWidgetTable_init(&EhsWidgetTable);
			pWidget = EhsWidgetTextbox_init(rect.left, rect.top, 0, iWidth, iHeight, xFgColour, xBgColour, pFont);
			EhsWidget_create(pWidget);
			EhsGraphicsColourClass xPalette[2];
			xPalette[0] = EHS_WIDGET_TEXTBOX(pWidget).xBgColour;
			xPalette[1] = EHS_WIDGET_TEXTBOX(pWidget).xFgColour;
		
			pSurface = EhsTgtViewportSurface_create(NULL,pWidget->xCurRect.nWidth,pWidget->xCurRect.nHeight,EHS_GRAPHICS_COLOUR_A1,xPalette,2);

			if (pSurface) {
			EhsWidgetTextbox_draw(pWidget, NULL, NULL, pSurface);

			// Copy the written data back from the bitmap
			pSrcBmp->GetBitmapBits( totalBytes, byteArr );

			// Blit Text
			int x,y;
		
			for (y = 0; y < iHeight; y++) {
				int nPixIdx = y * iWidth * 4;
				int nBmpIdx = y * ((pSurface->nWid+7)/8);
				for (x = 0; x < iWidth; x++) {
					int nBit = 1 << (7u - (x % 8u));
					int nX = x*4;
					if ((nBit & EhsTgtViewportSurface_bitmap(pSurface)[nBmpIdx + x/8]) == nBit) {
						tmp[nPixIdx+nX] = (unsigned char) cColors.m_iFgBlue;
						tmp[nPixIdx+nX+1] = (unsigned char) cColors.m_iFgGreen;
						tmp[nPixIdx+nX+2] = (unsigned char) cColors.m_iFgRed;
						tmp[nPixIdx+nX+3] = (unsigned char) cColors.m_iFgAlpha;
					} else {
						tmp[nPixIdx+nX] = 255;
						tmp[nPixIdx+nX+1] = 255;
						tmp[nPixIdx+nX+2] = 255;
						tmp[nPixIdx+nX+3] = 0;
					}
				}
			}
		
			if (!pWidget->bOptimiseForSpeed) {
				EhsTgtViewportSurface_destroy(NULL, pSurface);
			}
			}
		}

	// Copy this data into bitmap
	pSrcBmp->SetBitmapBits( totalBytes, byteArr );

	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA; 

	AlphaBlend(
		dc->GetSafeHdc(),
		rect.left, 
		rect.top, 
		iWidth,
		iHeight,
		pSrcMemDC->GetSafeHdc(),
		0,
		0,
		iWidth,
		iHeight,
		bf );

	HBITMAP hbmp = (HBITMAP)pSrcBmp;
	pLBox->SetItemData(n, (DWORD)hbmp);
	return n;
}

int CPicDrawC::AddItemCmb(CComboBox* pCombo, UINT nItem) {
	int n;
	n = pCombo->AddString("nu");
	HBITMAP hbmp = (HBITMAP)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(nItem), IMAGE_BITMAP, PicSizeX, PicSizeY, 0L);
	pCombo->SetItemData(n, (DWORD)hbmp);
	return n;
}
