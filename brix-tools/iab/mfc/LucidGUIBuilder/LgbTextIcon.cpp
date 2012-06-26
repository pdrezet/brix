#include "stdafx.h"
#include "LgbTextIcon.h"
#include "LucidConstants.h"
#include "LucidTypedefs.h"
#include "mem.h"
#include "widget.h"
#include "DrawGUI.h"
#include "ExtBdfFile.h"

#include <cassert>

const int LgbTextIcon::LgbTextIcon_FlagText = 1;
const int LgbTextIcon::LgbTextIcon_FlagBackground = 2;
vector<InlineText> LgbTextIcon::c_vInlineTextVec;
bool LgbTextIcon::c_bIsTextStyleSaved = false;
vector<LgbFont> LgbTextIcon::c_vFontVec;

LgbTextIcon::LgbTextIcon()
{
}

LgbTextIcon::LgbTextIcon( const LgbTextIcon &icon ):
LgbResizedDrawable( icon )
{
	*this = icon;
}

LgbTextIcon::LgbTextIcon(	
					const CRect			&rect,
					const CString		&type,
					const CString		&tag,
					const int			&zPos
					) : 
LgbResizedDrawable( rect, type, tag,  zPos )
,m_iFontSize(10)
,m_csFont(_T("lsr") )
,m_iLeftIndent(10)
,m_iRightIndent(10)
,m_iTopIndent(10)
,m_iBottomIndent(10)
,m_iLineSpacing(12)
,m_iNumberOfLines(3)
{
	m_cColors.init();
}


LgbTextIcon::LgbTextIcon(	
					const CRect			&rect,
					const CString		&type,
					const CString		&tag,
					const int			&zPos,
					const LgbColorsDef	&colors
				)  : 
LgbResizedDrawable( rect, type, tag, zPos )
,m_iFontSize(10)
,m_csFont(_T("lsr") )
,m_iLeftIndent(10)
,m_iRightIndent(10)
,m_iTopIndent(10)
,m_iBottomIndent(10)
,m_iLineSpacing(12)
,m_iNumberOfLines(3)
{
	m_cColors = colors;
}


LgbTextIcon::~LgbTextIcon(void)
{
	//LgbResizedDrawable:: ~LgbResizedDrawable();
}

LgbClassIDEnum LgbTextIcon::getClassId(){ return k_LgbTextIcon; }

	

void LgbTextIcon::Draw( CDC *pMemDC, const int &zLower, const int &zUpper , const int &leanDispPerZLevel )
{

	// create memory device context
	CDC* pSrcMemDC = new CDC;
	assert( NULL != pSrcMemDC );

	pSrcMemDC->CreateCompatibleDC(pMemDC);

	// RGB + Alpha
	int totalBytes = m_cRect.Width() * m_cRect.Height() * 4;

	// create bitmap
	CBitmap* pSrcBmp = new CBitmap;
	assert( NULL != pSrcBmp );

	// initialize
	pSrcBmp->CreateCompatibleBitmap( pMemDC, m_cRect.Width(), m_cRect.Height() );
	pSrcMemDC->SelectObject(pSrcBmp);

	void *byteArr = new BYTE [ totalBytes ];
	assert( NULL != byteArr );

	BYTE *tmp = (BYTE *) byteArr;

	//if(m_bShowTag){

	// Textboxes used to show their tag as demo text.  This meant that with the introduction
	// of patch icons, th user couldn't distuinguish patch from text widgets.
	// So now show 'Sample text' on text icons everytime.

		// showing the tag is significant, as we then need to not overwrite the
		// pixels that have the text, with background color

		//UINT32 *i32 = ( UINT32 * ) byteArr;

		// Use the blue pixel as a flag to see where text has been drawn.
		// 1st initialise to not 'text-blue'
		/*
		int byte = 0;
		while(byte<totalBytes){
			tmp[byte] = ~m_cColors.m_iFgBlue;
			byte += 4;
		}
		*/
		// set the flagged array to the bitmap
		pSrcBmp->SetBitmapBits( totalBytes, byteArr );

		// now write the text
		/*
		pSrcMemDC->SetBkMode(TRANSPARENT);

		pSrcMemDC->SetTextColor( RGB( m_cColors.m_iFgRed, m_cColors.m_iFgGreen, m_cColors.m_iFgBlue ) );
		pSrcMemDC->SetTextAlign(TA_LEFT);
		pSrcMemDC->TextOutA( 10, 10, "Sample_Text" );
		*/
		// Write text using EHS font blitter
		EhsWidgetClass* pWidget;
		EhsTgtViewportSurfaceClass* pSurface;
		EhsGraphicsColourClass xFgColour, xBgColour;
		EhsGraphicsFontClass* pFont = GetFontPtr(m_csFont);
		
		if (pFont) {

			// to fix rendering bug where if text box, cuts text in half, corrupts fonts
			//@todo - without this code will break on a memory deallocation error in EhsTgtViewportSurface_destroy, free(EhsTgtViewportSurface_bitmap(pSurface)); we could set the bitmap to null when freed and test this to avoid this error
			if (m_cRect.Height() < (pFont->nMaxHt + 10)) {
				pSrcMemDC->DeleteDC();
				delete pSrcMemDC;

				pSrcBmp->DeleteObject();
				delete pSrcBmp;

				delete [] byteArr;

				return;
			}


			xFgColour = EhsGraphicsColour_argb(m_cColors.m_iFgRed, m_cColors.m_iFgGreen, m_cColors.m_iFgBlue, m_cColors.m_iFgAlpha);
			xBgColour = EhsGraphicsColour_argb(m_cColors.m_iBgRed, m_cColors.m_iBgGreen, m_cColors.m_iBgBlue, m_cColors.m_iBgAlpha);
			EhsWidgetTable_init(&EhsWidgetTable);
			pWidget = EhsWidgetTextbox_init(m_cRect.left, m_cRect.top, m_iZPosUser, m_cRect.Width(), m_cRect.Height(), xFgColour, xBgColour, pFont);
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
		
				for (y = 0; y < m_cRect.Height(); y++) {
					int nPixIdx = y * m_cRect.Width() * 4;
					int nBmpIdx = y * ((pSurface->nWid+7)/8);
					for (x = 0; x < m_cRect.Width(); x++) {
						int nBit = 1 << (7u - (x % 8u));
						int nX = x*4;
						if ((nBit & EhsTgtViewportSurface_bitmap(pSurface)[nBmpIdx + x/8]) == nBit) {
							tmp[nPixIdx+nX] = (unsigned char) m_cColors.m_iFgBlue;
							tmp[nPixIdx+nX+1] = (unsigned char) m_cColors.m_iFgGreen;
							tmp[nPixIdx+nX+2] = (unsigned char) m_cColors.m_iFgRed;
							tmp[nPixIdx+nX+3] = (unsigned char) m_cColors.m_iFgAlpha;
						} else {
							tmp[nPixIdx+nX] = (unsigned char) m_cColors.m_iBgBlue;
							tmp[nPixIdx+nX+1] = (unsigned char) m_cColors.m_iBgGreen;
							tmp[nPixIdx+nX+2] = (unsigned char) m_cColors.m_iBgRed;
							tmp[nPixIdx+nX+3] = (unsigned char) m_cColors.m_iBgAlpha;
						}
					}
				}
		
				if (!pWidget->bOptimiseForSpeed) {
					EhsTgtViewportSurface_destroy(NULL, pSurface);
				}
			}
		}

		/*
		int byte = 0;
		while(byte<totalBytes){

			// has anything text been drawn to pixel?
			// if so, it must be text: set alpha to f/g alpha
			if( tmp[byte] == (unsigned char) m_cColors.m_iFgBlue) 
			{
				tmp[byte+3] = (unsigned char) m_cColors.m_iFgAlpha;
			}else{
				// this pixel doesnt have text on it - ie it is background.
				tmp[byte] = (unsigned char) m_cColors.m_iBgBlue;
				tmp[byte+1] = (unsigned char) m_cColors.m_iBgGreen;
				tmp[byte+2] = (unsigned char) m_cColors.m_iBgRed;
				tmp[byte+3] = (unsigned char) m_cColors.m_iBgAlpha;
			}
			byte += 4;
		}
		*/

//	} else {

		// There was no text ...Fill the whole thing with b/g

//		int byte = 0;
//		while(byte<totalBytes){

			// this pixel doesnt have text on it - ie it is background.
//			tmp[byte] = (unsigned char) m_cColors.m_iBgBlue;
//			tmp[byte+1] = (unsigned char) m_cColors.m_iBgGreen;
//			tmp[byte+2] = (unsigned char) m_cColors.m_iBgRed;
//			tmp[byte+3] = (unsigned char) m_cColors.m_iBgAlpha;

//			byte += 4;
//		}

//	}

// Premultiply alphas etc prior to per-pixel alphablend
	int alpha;
	int bytePos;
	unsigned char val;

	for( int pix = 0; pix<totalBytes/4; pix++)
	{

		bytePos = 4*pix;

		alpha = tmp[bytePos + 3];

		val		= tmp[bytePos];
		val	= (val * alpha) / 255;
		tmp[bytePos++]	= val;

		val		= tmp[bytePos];
		val	= (val * alpha) / 255;
		tmp[bytePos++]	= val;

		val		= tmp[bytePos];
		val	= (val * alpha) / 255;
		tmp[bytePos++]	= val;

	}

	// Copy this data into bitmap
	pSrcBmp->SetBitmapBits( totalBytes, byteArr );

	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA; 

	AlphaBlend(
		pMemDC->GetSafeHdc(),
		m_cRectShown.left, 
		m_cRectShown.top, 
		m_cRectShown.Width(),
		m_cRectShown.Height(),
		pSrcMemDC->GetSafeHdc(),
		0,
		0,
		m_cRectShown.Width(),
		m_cRectShown.Height(),
		bf );


	pSrcMemDC->DeleteDC();
	delete pSrcMemDC;

	pSrcBmp->DeleteObject();
	delete pSrcBmp;

	delete [] byteArr;
}

void LgbTextIcon::drawTag(CDC * pMemDC)
{ 
	LgbDrawable::drawTag( pMemDC );
}

LgbColorsDef LgbTextIcon::getColors()
{
	return m_cColors;
}

void LgbTextIcon::setColors( const LgbColorsDef &colors )
{
	m_cColors.m_iFgRed = colors.m_iFgRed;
	m_cColors.m_iFgGreen = colors.m_iFgGreen;
	m_cColors.m_iFgBlue = colors.m_iFgBlue;

	m_cColors.m_iBgRed = colors.m_iBgRed;
	m_cColors.m_iBgGreen = colors.m_iBgGreen;
	m_cColors.m_iBgBlue = colors.m_iBgBlue;

	// Get current pen for text, and modify it.
	// S Gardner Bug
	// SDG: Commented out the following code, because it caused a crash sometimes.
	// Instead hard coded the values for style and width.
	//LOGPEN logPen;
	//m_cPenTagText.GetLogPen( &logPen );

	//int width = logPen.lopnWidth.x;
	//int style = logPen.lopnStyle;

	COLORREF cRef = RGB( m_cColors.m_iFgRed, m_cColors.m_iFgGreen, m_cColors.m_iFgBlue );
	m_cPenTagText.DeleteObject();
	//m_cPenTagText.CreatePen( style, width, cRef );
	m_cPenTagText.CreatePen( 0, 1, cRef );

}


void LgbTextIcon::saveToFile( std::ofstream &rFile )
{
	char type[STD_LINE_LENGTH];
	char tag[STD_LINE_LENGTH];
	char *fileName = "NULL";
	LgbColorsDef cColors;

	const int LOCATION = 1;
	const int OPTION = 1;;

	strcpy_s(type,		STD_LINE_LENGTH, (LPCTSTR)m_csType);
	strcpy_s(tag,		STD_LINE_LENGTH, (LPCTSTR)m_csTag);

	// save all the Text Styles once
	if (!c_bIsTextStyleSaved) {
		for (size_t i=0; i<c_vInlineTextVec.size(); i++) {
			c_vInlineTextVec[i].GetColors(cColors);
			rFile << c_vInlineTextVec[i].GetClass() << ","
				  << "TextStyle,"
				  << c_vInlineTextVec[i].GetFont() << ","
				  << (int)cColors.m_iFgAlpha << ","
				  << (int)cColors.m_iFgRed << ","
				  << (int)cColors.m_iFgGreen << ","
				  << (int)cColors.m_iFgBlue << endl;
		}
		c_bIsTextStyleSaved = true;
	}

	rFile 
		<<tag<<","
		<<type<<","
		<<m_cRect.left<<","
		<<m_cRect.top<<","
		<<m_cRect.Width()<<","
		<<m_cRect.Height()<<","
		<<m_iZPosUser<<","

		<< (int) m_cColors.m_iFgAlpha<<","
		<< (int) m_cColors.m_iFgRed<<","
		<< (int) m_cColors.m_iFgGreen<<","
		<< (int) m_cColors.m_iFgBlue<<","

		<< (int) m_cColors.m_iBgAlpha<<","
		<< (int) m_cColors.m_iBgRed<<","
		<< (int) m_cColors.m_iBgGreen<<","
		<< (int) m_cColors.m_iBgBlue<<","
		<< m_csFont << ","
		<< m_iLeftIndent << ","
		<< m_iRightIndent << ","
		<< m_iTopIndent << ","
		<< m_iBottomIndent << ","
		<< m_iLineSpacing

		<<std::endl;

	return;

}

void LgbTextIcon::Scan::init()
{
	m_cDrblScan.init();
	m_bSameColors = true;
	m_bSameFgAlpha = true;
	m_bSameBgAlpha = true;
	m_bSameFont = true;
	m_bSameLeftIndent = true;
	m_bSameRightIndent = true;
	m_bSameTopIndent = true;
	m_bSameBottomIndent = true;
	m_bSameLineSpacing = true;
	m_bSameNumberOfLines = true;
}

bool LgbTextIcon::Scan::allScanFieldsFalse()
{
	return		m_cDrblScan.allScanFieldsFalse() && !m_bSameColors
		&&		!m_bSameFgAlpha && !m_bSameBgAlpha;
}
	

LgbTextIcon::Scan LgbTextIcon::scanFieldEquality( 
				LgbTextIcon *pTxtIcon, 
				LgbTextIcon::Scan &scanSoFar )
{

	//LgbTextIcon::Scan scn;

	//scn.init();

	scanSoFar.m_cDrblScan = LgbDrawable::scanFieldEquality( pTxtIcon, scanSoFar.m_cDrblScan );
	
	// Only find out about latest comparison if previous comparisons are still 
	// favourable.

	//-----------------------------------
	// Colors
	//-----------------------------------
	if( scanSoFar.m_bSameColors ){
		if( m_cColors.m_iBgRed != pTxtIcon->m_cColors.m_iBgRed ||
			m_cColors.m_iBgGreen != pTxtIcon->m_cColors.m_iBgGreen ||
			m_cColors.m_iBgBlue != pTxtIcon->m_cColors.m_iBgBlue ||
			m_cColors.m_iFgRed != pTxtIcon->m_cColors.m_iFgRed ||
			m_cColors.m_iFgGreen != pTxtIcon->m_cColors.m_iFgGreen ||
			m_cColors.m_iFgBlue != pTxtIcon->m_cColors.m_iFgBlue )
		{ 
			scanSoFar.m_bSameColors = false;
		}
	}

// F/G Alpha
	if( scanSoFar.m_bSameFgAlpha ){
		if( m_cColors.m_iFgAlpha != pTxtIcon->m_cColors.m_iFgAlpha )
		{ 
			scanSoFar.m_bSameFgAlpha = false;
		}
	}

// B/G Alpha
	if( scanSoFar.m_bSameBgAlpha ){
		if( m_cColors.m_iBgAlpha != pTxtIcon->m_cColors.m_iBgAlpha )
		{ 
			scanSoFar.m_bSameBgAlpha = false;
		}
	}


// Font
	if( scanSoFar.m_bSameFont){
		if( m_csFont != pTxtIcon->m_csFont )
		{ 
			scanSoFar.m_bSameFont = false;
		}
	}

// Font Size
	if( scanSoFar.m_bSameFontSize){
		if( m_iFontSize != pTxtIcon->m_iFontSize )
		{ 
			scanSoFar.m_bSameFontSize = false;
		}
	}

// Left Indent
	if( scanSoFar.m_bSameLeftIndent){
		if( m_iLeftIndent != pTxtIcon->m_iLeftIndent )
		{ 
			scanSoFar.m_bSameLeftIndent = false;
		}
	}

// Right Indent
	if( scanSoFar.m_bSameRightIndent){
		if( m_iRightIndent != pTxtIcon->m_iRightIndent )
		{ 
			scanSoFar.m_bSameRightIndent = false;
		}
	}

// Top Indent
	if( scanSoFar.m_bSameTopIndent){
		if( m_iTopIndent != pTxtIcon->m_iTopIndent )
		{ 
			scanSoFar.m_bSameTopIndent = false;
		}
	}

// Bottom Indent
	if( scanSoFar.m_bSameBottomIndent){
		if( m_iBottomIndent != pTxtIcon->m_iBottomIndent )
		{ 
			scanSoFar.m_bSameBottomIndent = false;
		}
	}

// Line Spacing
	if( scanSoFar.m_bSameLineSpacing){
		if( m_iLineSpacing != pTxtIcon->m_iLineSpacing )
		{ 
			scanSoFar.m_bSameLineSpacing = false;
		}
	}

// Number of Lines
	if (scanSoFar.m_bSameNumberOfLines) {
		if (getNumberOfLines() != pTxtIcon->getNumberOfLines()) { 
			scanSoFar.m_bSameNumberOfLines = false;
		}
	}

	return scanSoFar;
}

void LgbTextIcon::setAlpha( unsigned char val, const int & flags )
{
	if( flags & LgbTextIcon_FlagText )
		m_cColors.m_iFgAlpha = val;

	if( flags & LgbTextIcon_FlagBackground )
		m_cColors.m_iBgAlpha = val;

}

void LgbTextIcon::changeAlpha(const int & increment)
{

	if( (m_cColors.m_iFgAlpha + increment) > 255)
		m_cColors.m_iFgAlpha = 255;
	if( (m_cColors.m_iFgAlpha + increment) < 0)
		m_cColors.m_iFgAlpha = 0;
	else
		m_cColors.m_iFgAlpha += increment;

	if( (m_cColors.m_iBgAlpha + increment) > 255)
		m_cColors.m_iBgAlpha = 255;
	if( (m_cColors.m_iBgAlpha + increment) < 0)
		m_cColors.m_iBgAlpha = 0;
	else
		m_cColors.m_iBgAlpha += increment;

}

CString LgbTextIcon::getFont(void)
{
	return m_csFont;
}

int LgbTextIcon::getFontSize(void)
{
	return m_iFontSize;
}

int LgbTextIcon::getLeftIndent(void)
{
	return m_iLeftIndent;
}

int LgbTextIcon::getRightIndent(void)
{
	return m_iRightIndent;
}

int LgbTextIcon::getTopIndent(void)
{
	return m_iTopIndent;
}

int LgbTextIcon::getBottomIndent(void)
{
	return m_iBottomIndent;
}

int LgbTextIcon::getLineSpacing(void)
{
	return m_iLineSpacing;
}

int LgbTextIcon::getNumberOfLines(void)
{
	return (m_cRect.Height() - m_iTopIndent - m_iBottomIndent)/m_iLineSpacing;
}

void LgbTextIcon::setFont( const CString &font)
{
	m_csFont = font;
}

void LgbTextIcon::setFontSize( const int sz)
{
	m_iFontSize = sz;
}

void LgbTextIcon::setLeftIndent(const int iLeftIndent)
{
	m_iLeftIndent = iLeftIndent;
}

void LgbTextIcon::setRightIndent(const int iRightIndent)
{
	m_iRightIndent = iRightIndent;
}

void LgbTextIcon::setTopIndent(const int iTopIndent)
{
	m_iTopIndent = iTopIndent;
}

void LgbTextIcon::setBottomIndent(const int iBottomIndent)
{
	m_iBottomIndent = iBottomIndent;
}

void LgbTextIcon::setLineSpacing(const int iLineSpacing)
{
	m_iLineSpacing = iLineSpacing;
}

// This method loads all the fonts into the class variable c_vFontPairVec
void LgbTextIcon::LoadFonts()
{
	CFileFind finder;
	CString csInstallDir, csFontName, csFontFileName, csFontFilePath;
	CDrawGUIApp *pApp = ( CDrawGUIApp *  )AfxGetApp();
	EhsGraphicsFontClass* pFont;

	EhsMem_freeAll();

	pApp->GetInstallationBaseDir(csInstallDir);
	int bWorking = finder.FindFile(csInstallDir + "\\fonts\\*.bdf");	
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		// Get the font name
		csFontFileName = finder.GetFileName();
		csFontName = csFontFileName.SpanExcluding(".");

		// Get a pointer to the loaded font
		csFontFilePath = finder.GetFilePath();
		pFont = EhsGraphicsFont_load(csFontFilePath.GetBuffer(128));
		csFontFilePath.ReleaseBuffer();
		LgbFont xFont(csFontName, csFontFileName, pFont);
		c_vFontVec.push_back(xFont);
	}
}

// Method that returns a font pointer for the specified font name
EhsGraphicsFontClass* LgbTextIcon::GetFontPtr(CString csFontName)
{
	EhsGraphicsFontClass* pFont = NULL;

	for (size_t i=0; i<c_vFontVec.size(); i++) {
		if (c_vFontVec[i].GetFontName() == csFontName) {
			pFont = c_vFontVec[i].GetFontPtr();
		}
	}

	return pFont;
}

CString LgbTextIcon::GetFontFileName(CString csFontName)
{
	CString csFontFileName = "";

	for (size_t i=0; i<c_vFontVec.size(); i++) {
		if (c_vFontVec[i].GetFontName() == csFontName) {
			csFontFileName = c_vFontVec[i].GetFontFileName();
		}
	}

	return csFontFileName;
}

void LgbTextIcon::UpdateProjectMetaData()
{
	CDrawGUIApp *pApp = ( CDrawGUIApp *  )AfxGetApp();
	CString csFontFileName;
	ExtBdfFile xBdfFile;

	csFontFileName = GetFontFileName(m_csFont);
	xBdfFile.setHostFileName(csFontFileName);
	pApp->m_ProjectMetaData.addBdfFile(xBdfFile);
}
