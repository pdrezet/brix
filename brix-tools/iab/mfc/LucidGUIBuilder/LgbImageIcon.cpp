/** @file LgbImageIcon.cpp
 * Inplementation of class LgbImageIcon
 * @author: Matthew Rutherford
 * @version: $Revision: 577 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */

#include "stdafx.h"
#include "DrawGUI.h"
#include "LgbImageIcon.h"
#include "ColourStatic.h"
#include "../common/LucidConstants.h"
#include "LgbResizedDrawable.h"

#include "../../environment/PngImage/PngImage.h"
#include <cassert>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
LgbImageIcon::ImageTypeEnum LgbImageIcon::getFileNameType( 
	const CString &fileName ) const
{

	ImageTypeEnum eType;

	if( (fileName.Right(3)=="png") || (fileName.Right(3)=="PNG") )
		eType = k_Png;
	else if( (fileName.Right(3)=="bmp") || (fileName.Right(3)=="BMP") )
		eType = k_Bitmap;
	else if( (fileName.Right(3)=="gif") || (fileName.Right(3)=="GIF") )
		eType = k_Gif;
	else
		eType = k_NULL;

	return eType;

}

LgbImageIcon::LgbImageIcon( const LgbImageIcon &icon )
:LgbResizedDrawable( icon )
{
	*this = icon;
}


LgbImageIcon::LgbImageIcon(	
					const CRect		&rect,
					const CString	&type,
					const CString	&tag,
					const int		&zPos,
					const int		&alpha,
					const CString	&projDir,
					const CString	&fileName,
					const int		&lockApect
				)
: LgbResizedDrawable( rect, type, tag, zPos )
, m_pPreMultBGRA(NULL)
, m_iAlpha(alpha)
, m_pPngImage(NULL)
, m_iLockApect(lockApect)
{

	m_csProjectDir = projDir;
	m_csFileName = "";// This must be set in setImageFile, otherwise on initial opening of
						// gui file the image isn't loaded, as the present file name and name to be
						// loaded are the same.

	ImageTypeEnum eType = getFileNameType( fileName );
	setImageFile( fileName, eType, false );
}

void LgbImageIcon::changeImageFile( 
				const CString &fileName
				)
{
	ImageTypeEnum eType = getFileNameType( fileName );
	setImageFile( fileName, eType, true );
}


CBitmap * LgbImageIcon::getBitmapFromPng( PngImage &png, CDC* pDC )
{

	CBitmap *pBmp = NULL;

	// get size
	int width  = png.getWidth();
	int height = png.getHeight();

	// get blue, green, red and alpha
	unsigned char* data = png.getBGRA();

	// RGB + Alpha
	int size = width * height * 4;

	// create bitmap
	//CBitmap* bmp = new CBitmap;

	// get device context
	//CDC* pDC = pCompatibleWindow->GetDC();

	// initialize
	pBmp->CreateCompatibleBitmap(pDC, width, height);

	// set pixels
	pBmp->SetBitmapBits(size, data);

	// release device context
	//pCompatibleWindow->ReleaseDC(pDC);

	// return object
	return pBmp;

}


void LgbImageIcon::setImageFile( 
				const CString &fileName,
				const ImageTypeEnum &fileType,
				bool bChangedImage
				)
{

	if( fileName == m_csFileName)
		return;

	else{

		CSize tempSize;

		m_csFileName = fileName;
		m_eImageType = fileType;

		// dummy.bmp is the name of a file used initally to show icons frsh out of LAB, before the user
		// has had a chance to import /allocate his own bitmap

		// The user's own choices are under the proj folder.
		CString projectDir;
		CDrawGUIApp *pApp = ( CDrawGUIApp *  )AfxGetApp();
		pApp->m_ProjectMetaData.getProjectDir(projectDir);

		if( m_eImageType == k_Bitmap ){

			tempSize = m_cBitmap.Init( projectDir + GUIDIR + m_csFileName );

		}else if( m_eImageType == k_Png ){

			if(m_pPngImage != NULL){
				delete m_pPngImage;
				m_pPngImage = NULL;
			}

			m_pPngImage = new PngImage();
			assert( NULL != m_pPngImage );

			bool good = m_pPngImage->load(  projectDir + GUIDIR + m_csFileName );

			if(!good){
				CString dum = "Problem with loading image file: \n" + projectDir + GUIDIR + m_csFileName;
				AfxMessageBox(dum);
			}
			assert(good); // blow up if in debug mode.

			m_pPreMultBGRA = m_pPngImage->getPreMultBGRA();
			//m_cPngImage.
			//m_pDrawnThing = getBitmapFromPng( m_cPngImage, AfxGetApp()->m_pMainWnd->GetDC() );
			tempSize.cx = m_pPngImage->getWidth();
			tempSize.cy = m_pPngImage->getHeight();
		}
		// changed the image, resize widget to image size
		if (bChangedImage) {
			CPoint dumPt = m_cRect.TopLeft();
			dumPt += CPoint(tempSize.cx, tempSize.cy);
			m_cRect=CRect( m_cRect.TopLeft(), dumPt );
		}
		iImageHeight = tempSize.cy;
		iImageWidth = tempSize.cx;
		dImageHtoW = float(iImageHeight) / float(iImageWidth);
	}

}

void LgbImageIcon::setProjectDir( const CString &projDir )
{
	m_csProjectDir = projDir;
}

LgbImageIcon::ImageTypeEnum LgbImageIcon::getImageType() const
{
	return m_eImageType;
}

CString LgbImageIcon::getFileName() const
{
	return m_csFileName;
}

LgbImageIcon::~LgbImageIcon()
{ 
	if(m_pPngImage!= NULL)
		delete m_pPngImage;

	//LgbResizedDrawable::~LgbResizedDrawable();
}


void LgbImageIcon::Draw( CDC *pMemDC, const int &zLower, const int &zUpper , const int &leanDispPerZLevel )
{
	if( m_eImageType==k_Bitmap ){

		m_cBitmap.Draw(pMemDC, m_cRectShown.TopLeft() );
			

	} else if( m_eImageType==k_Png ){


		LgbDrawable::Draw( pMemDC, zLower, zUpper , leanDispPerZLevel );

		// create memory device context
		CDC* srcMemDC = new CDC;
		assert( NULL != srcMemDC );

		srcMemDC->CreateCompatibleDC(pMemDC);


		// create bitmap
		CBitmap* pSrcBmp = new CBitmap;
		assert( NULL != pSrcBmp );

		// initialize
		pSrcBmp->CreateCompatibleBitmap( pMemDC, m_pPngImage->getWidth(), m_pPngImage->getHeight() );
		int size = m_pPngImage->getWidth() * m_pPngImage->getHeight() * 4;
		unsigned char* srcDataBGRA = m_pPngImage->getPreMultBGRA();
		// set pixels
		pSrcBmp->SetBitmapBits( size, srcDataBGRA );

		// buffer bitmap
		srcMemDC->SelectObject(pSrcBmp);

		//LgbDrawable::Draw( pMemDC, zLower, zUpper, leanDispPerZLevel );

		if(m_bShowTag){
			drawTag(pMemDC);
		}

		BLENDFUNCTION bf;
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = m_iAlpha;
		bf.AlphaFormat = AC_SRC_ALPHA; 
	
		AlphaBlend(
			pMemDC->GetSafeHdc(),
			m_cRectShown.left, 
			m_cRectShown.top, 
			m_cRect.Width(),
			m_cRect.Height(),
			srcMemDC->GetSafeHdc(),
			0,
			0,
			m_pPngImage->getWidth(),
			m_pPngImage->getHeight(),
			bf );

		pSrcBmp->DeleteObject();
		srcMemDC->DeleteDC();

		delete pSrcBmp;
		delete srcMemDC;

	}



}

LgbClassIDEnum LgbImageIcon::getClassId(){ return k_LgbImageIcon; }


void LgbImageIcon::saveToFile( ofstream &rFile )
{
	char type[STD_LINE_LENGTH];
	char tag[STD_LINE_LENGTH];
	char fileName[STD_LINE_LENGTH];
	const int LOCATION = 1;
	const int OPTION = 1;


	strcpy_s( type,				STD_LINE_LENGTH, m_csType			);
	strcpy_s( tag,				STD_LINE_LENGTH, m_csTag			);
	strcpy_s( fileName,	STD_LINE_LENGTH, m_csFileName );
	//strcpy_s( option,			STD_LINE_LENGTH, option				);

	rFile 
		<<tag<<","
		<<type<<","
		<<m_cRect.left<<","
		<<m_cRect.top<<","
		<<m_cRect.Width()<<","
		<<m_cRect.Height()<<","
		<<m_iZPosUser<<","
		<<( (int) m_iAlpha )<<","
		<<fileName<<","
		<<( (int) m_iLockApect )
		<<endl;

	return;

}

void LgbImageIcon::Scan::init()
{
	m_cDrblScan.init();
	m_bSameFileName = true;
	m_bSameLockAspect = true;
	m_bSameAlpha = true;
}

bool LgbImageIcon::Scan::allScanFieldsFalse()
{
	return		m_cDrblScan.allScanFieldsFalse() && !m_bSameFileName && !m_bSameLockAspect && !m_bSameAlpha;
}
	

LgbImageIcon::Scan LgbImageIcon::scanFieldEquality( 
				LgbImageIcon *pBmpIcon, 
				LgbImageIcon::Scan &scanSoFar )
{

	scanSoFar.m_cDrblScan = LgbDrawable::scanFieldEquality( pBmpIcon, scanSoFar.m_cDrblScan );
	
	// Only find out about latest comparison if previous comparisons are still 
	// favourable.

	//-----------------------------------
	// Bitmap file name
	//-----------------------------------
	if( scanSoFar.m_bSameFileName ){
		if( m_csFileName != pBmpIcon->m_csFileName )
		{ 
			scanSoFar.m_bSameFileName = false;
		}
	}

	//-----------------------------------
	// Lock Aspect Ratio
	//-----------------------------------
	if( scanSoFar.m_bSameLockAspect ){
		if( m_iLockApect != pBmpIcon->m_iLockApect )
		{ 
			scanSoFar.m_bSameLockAspect = false;
		}
	}

	//-----------------------------------
	// Alpha
	//-----------------------------------
	if( scanSoFar.m_bSameAlpha ){
		if( m_iAlpha != pBmpIcon->m_iAlpha )
		{ 
			scanSoFar.m_bSameAlpha = false;
		}
	}

	return scanSoFar;
}

void LgbImageIcon::changeAlpha(const int & increment)
{
	if( (m_iAlpha + increment) > 255)
		m_iAlpha = 255;
	else if( (m_iAlpha + increment) < 0)
		m_iAlpha = 0;
	else
		m_iAlpha += increment;
}

// Change alpha value
void LgbImageIcon::setAlpha( const int &val )
{
	if(val>255)
		m_iAlpha  = 255;
	else if(val<0)
		m_iAlpha  = 0;
	else
		m_iAlpha = val;
}


// Get alpha value
int	 LgbImageIcon::getAlpha() const
{
	return m_iAlpha;
}

// Change lock aspect
void LgbImageIcon::setLockAspect( const int &val )
{
	if(val>1)
		m_iLockApect  = 1;
	else if(val<0)
		m_iLockApect  = 0;
	else
		m_iLockApect = val;
}


// Get lock aspect
int	 LgbImageIcon::getLockAspect() const
{
	return m_iLockApect;
}

// Get image height
long LgbImageIcon::getImageHeight() const
{	
	return iImageHeight;
}

// Get image width
long LgbImageIcon::getImageWidth() const
{
	return iImageWidth;
}

// Get image aspect ratio
float LgbImageIcon::getImageHtoW() const
{
	return dImageHtoW;
}