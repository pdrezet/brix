#include "LgbPatchIcon.h"
#include "stdafx.h"
#include "LgbPatchIcon.h"
#include "../common/LucidConstants.h"
#include "../common/LucidTypedefs.h"

#include <cassert>

//const int LgbPatchIcon::LgbPatchIcon_FlagText = 1;
const int LgbPatchIcon::LgbPatchIcon_FlagBackground = 2;

LgbPatchIcon::LgbPatchIcon( const LgbPatchIcon &icon )
{
	*this = icon;
}

LgbPatchIcon::LgbPatchIcon(	
					const CRect			&rect,
					const CString		&type,
					const CString		&tag,
					const int			&zPos
					) : 
LgbResizedDrawable( rect, type, tag,  zPos )
{
	m_cColors.init();
}


LgbPatchIcon::LgbPatchIcon(	
					const CRect			&rect,
					const CString		&type,
					const CString		&tag,
					const int			&zPos,
					const LgbColorsDef	&colors
				)  : 
LgbResizedDrawable( rect, type, tag, zPos )
{
	m_cColors = colors;
}


LgbPatchIcon::~LgbPatchIcon(void)
{
	//LgbResizedDrawable:: ~LgbResizedDrawable();
}

LgbClassIDEnum LgbPatchIcon::getClassId(){ return k_LgbPatchIcon; }


void LgbPatchIcon::Draw(	CDC *pMemDC, 
							const int &zLower, 
							const int &zUpper , 
							const int &leanDispPerZLevel
						)
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



	// There was no text ...Fill the whole thing with b/g

	int byte = 0;
	while(byte<totalBytes){

		// this pixel doesnt have text on it - ie it is background.
		tmp[byte] = (unsigned char) m_cColors.m_iBgBlue;
		tmp[byte+1] = (unsigned char) m_cColors.m_iBgGreen;
		tmp[byte+2] = (unsigned char) m_cColors.m_iBgRed;
		tmp[byte+3] = (unsigned char) m_cColors.m_iBgAlpha;

		byte += 4;
	}



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

	// Copy his data into bitmap
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

void LgbPatchIcon::drawTag(CDC * pMemDC)
{ 	
	LgbDrawable::drawTag( pMemDC );
}

LgbColorsDef LgbPatchIcon::getColors()
{
	return m_cColors;
}

void LgbPatchIcon::setColors( const LgbColorsDef &colors )
{
	m_cColors.m_iFgRed = colors.m_iFgRed;
	m_cColors.m_iFgGreen = colors.m_iFgGreen;
	m_cColors.m_iFgBlue = colors.m_iFgBlue;

	m_cColors.m_iBgRed = colors.m_iBgRed;
	m_cColors.m_iBgGreen = colors.m_iBgGreen;
	m_cColors.m_iBgBlue = colors.m_iBgBlue;

	// Get current pen for text, and modify it.
	LOGPEN logPen;
	m_cPenTagText.GetLogPen( &logPen );

	int width = logPen.lopnWidth.x;
	int style = logPen.lopnStyle;

	COLORREF cRef = RGB( m_cColors.m_iFgRed, m_cColors.m_iFgGreen, m_cColors.m_iFgBlue );
	m_cPenTagText.DeleteObject();
	m_cPenTagText.CreatePen( style, width, cRef );

}


void LgbPatchIcon::saveToFile( std::ofstream &rFile )
{
	char type[STD_LINE_LENGTH];
	char tag[STD_LINE_LENGTH];
	char *fileName = "NULL";

	const int LOCATION = 1;
	const int OPTION = 1;;

	strcpy_s(type,		STD_LINE_LENGTH, (LPCTSTR)m_csType);
	strcpy_s(tag,		STD_LINE_LENGTH, (LPCTSTR)m_csTag);


	rFile 
		<<tag<<","
		<<type<<","
		<<m_cRect.left<<","
		<<m_cRect.top<<","
		<<m_cRect.Width()<<","
		<<m_cRect.Height()<<","
		<<m_iZPosUser<<","

		<< (int) m_cColors.m_iBgAlpha<<","
		<< (int) m_cColors.m_iBgRed<<","
		<< (int) m_cColors.m_iBgGreen<<","
		<< (int) m_cColors.m_iBgBlue

		<<std::endl;

	return;

}

void LgbPatchIcon::Scan::init()
{
	m_cDrblScan.init();
	m_bSameColors	=true;
	//m_bSameFgAlpha = true;
	m_bSameBgAlpha = true;
}

bool LgbPatchIcon::Scan::allScanFieldsFalse()
{
	return		m_cDrblScan.allScanFieldsFalse() && !m_bSameColors
			//	&& !m_bSameFgAlpha 
				&& !m_bSameBgAlpha;
}
	

LgbPatchIcon::Scan LgbPatchIcon::scanFieldEquality( 
				LgbPatchIcon *pTxtIcon, 
				LgbPatchIcon::Scan &scanSoFar )
{

	//LgbPatchIcon::Scan scn;

	//scn.init();

	scanSoFar.m_cDrblScan = LgbDrawable::scanFieldEquality( 
												pTxtIcon, 
												scanSoFar.m_cDrblScan
												);
	
	// Only find out about latest comparison if previous comparisons are still 
	// favourable.

	//-----------------------------------
	// Colors
	//-----------------------------------
	if( scanSoFar.m_bSameColors ){
		if( m_cColors.m_iBgRed != pTxtIcon->m_cColors.m_iBgRed ||
			m_cColors.m_iBgGreen != pTxtIcon->m_cColors.m_iBgGreen ||
			m_cColors.m_iBgBlue != pTxtIcon->m_cColors.m_iBgBlue //||
			//m_cColors.m_iFgRed != pTxtIcon->m_cColors.m_iFgRed ||
			//m_cColors.m_iFgGreen != pTxtIcon->m_cColors.m_iFgGreen ||
			//m_cColors.m_iFgBlue != pTxtIcon->m_cColors.m_iFgBlue 
			)
		{ 
			scanSoFar.m_bSameColors = false;
		}
	}

// F/G Alpha
//	if( scanSoFar.m_bSameFgAlpha ){
	//	if( m_cColors.m_iFgAlpha != pTxtIcon->m_cColors.m_iFgAlpha )
	//	{ 
	//		scanSoFar.m_bSameFgAlpha = false;
	//	}
	//}

// B/G Alpha
	if( scanSoFar.m_bSameBgAlpha ){
		if( m_cColors.m_iBgAlpha != pTxtIcon->m_cColors.m_iBgAlpha )
		{ 
			scanSoFar.m_bSameBgAlpha = false;
		}
	}


	return scanSoFar;
}

void LgbPatchIcon::setAlpha( unsigned char val, const int & flags )
{
//	if( flags & LgbPatchIcon_FlagText )
//		m_cColors.m_iFgAlpha = val;

	if( flags & LgbPatchIcon_FlagBackground )
		m_cColors.m_iBgAlpha = val;

}

void LgbPatchIcon::changeAlpha(const int & increment)
{

/*
if( (m_cColors.m_iFgAlpha + increment) > 255)
		m_cColors.m_iFgAlpha = 255;
	if( (m_cColors.m_iFgAlpha + increment) < 0)
		m_cColors.m_iFgAlpha = 0;
	else
		m_cColors.m_iFgAlpha += increment;
		*/

	if( (m_cColors.m_iBgAlpha + increment) > 255)
		m_cColors.m_iBgAlpha = 255;
	if( (m_cColors.m_iBgAlpha + increment) < 0)
		m_cColors.m_iBgAlpha = 0;
	else
		m_cColors.m_iBgAlpha += increment;

}

