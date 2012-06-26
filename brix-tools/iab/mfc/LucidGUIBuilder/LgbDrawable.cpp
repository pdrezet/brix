/** @file LgbDrawable.cpp
 * Represents impl of an LGB (rectangular-bordered) icon that knows how to draw itself.
 * @author: Matthew Rutherford
 * @version: $Revision: 577 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */
#include "stdafx.h"
#include "../common/LucidEnums.h"
#include "LgbDrawable.h"
#include "IconSelection.h"
#include "../common/LucidTypedefs.h"
#include <fstream>
#include <cassert>
#include <cmath>

LgbDrawable::LgbDrawable()
: m_bShowTag(true),
m_bIsSelected(false),
m_bIsActive(true),
m_bIsMaster(false),
m_bIsToBeDeleted(false),
m_bIsLastClicked(false),
m_iZPosUser(-1)
//, m_iPerCentOpacity(50)
, m_iZPosProcessed(0)
, m_iDrawLayer(0)
{
	m_cPenSelOutline.CreatePen( PS_SOLID, 1, RGB(255,0,0) );
	m_cPenUnselOutline.CreatePen( PS_SOLID, 1, RGB(0,0,0) );
	m_cPenTagText.CreatePen( PS_SOLID, 1, RGB(0,0,0) );
}

LgbDrawable::LgbDrawable( const LgbDrawable &icon )
{
	*this = icon;
}

LgbDrawable::LgbDrawable(	const CRect		&rect,
							const CString	&type,
							const CString	&tag,
							const int		&zPos
							):
m_bShowTag(true),
m_bIsSelected(false),
m_bIsActive(true),
m_bIsMaster(false),
m_bIsToBeDeleted(false),
m_bIsLastClicked(false)
{
	m_cPenSelOutline.CreatePen( PS_SOLID, 1, RGB(255,0,0) );
	m_cPenUnselOutline.CreatePen( PS_SOLID, 1, RGB(0,0,0) );
	m_cPenTagText.CreatePen( PS_SOLID, 1, RGB(0,0,0) );

	m_iZPosUser		= zPos;
	m_cRect		= rect;
	m_csTag		= tag;
	m_csType	= type;
}

void LgbDrawable::saveToFile( std::ofstream &rFile )
{}

void LgbDrawable::UpdateProjectMetaData()
{}

LgbDrawable::~LgbDrawable(void)
{ int i=0;}

void LgbDrawable::drawTag(CDC * pDC)
{
	int bgMode = pDC->SetBkMode(OPAQUE);
	int mode = pDC->SetROP2( R2_COPYPEN);
	
	COLORREF oldTextCol = pDC->SetTextColor( RGB( 255, 255, 255 ) );
	COLORREF oldBGCol = pDC->SetBkColor( RGB( 0, 0, 255 ) );

	pDC->SetTextAlign(TA_LEFT);
	pDC->TextOutA( (m_cRectShown.left ) + 0 , m_cRectShown.top -15 , " " + m_csTag + " " );

	pDC->SetBkColor( oldBGCol);
	pDC->SetTextColor( oldTextCol );
	pDC->SetBkMode( bgMode );
	pDC->SetROP2( mode );
}


void LgbDrawable::DrawSelectionBlobs( CDC *pDC )
{

	if(m_bIsSelected){

		CPen *oldPen = pDC->GetCurrentPen();
		CBrush *oldBrush = pDC->GetCurrentBrush();
		int oldPenMode = pDC->GetROP2();

		CPen masterPen(PS_SOLID, 1, RGB(0, 0, 0));
		CBrush masterBrush( RGB(255,0,0) );

		CPen nonMasterPen(PS_SOLID, 1, RGB(255, 0, 0));
		CBrush nonMasterBrush( RGB(0,0,0) );

		const int MASTER_BLOB_SZ = 6;
		const int SELN_BLOB_SZ = MASTER_BLOB_SZ - 2;
		LgbRect dum;
		CPoint p1;
		CPoint p2;

		if(m_bIsMaster){
			pDC->SelectObject( masterPen );
			pDC->SelectObject( masterBrush );
		} else {
			pDC->SelectObject( nonMasterPen );
			pDC->SelectObject( nonMasterBrush );
		}

		// Top left
		p1.SetPoint( m_cRectShown.left - MASTER_BLOB_SZ, m_cRectShown.top - MASTER_BLOB_SZ );
		dum.SetRect(p1,p1);
		m_bIsMaster ? dum.InflateRect( MASTER_BLOB_SZ, MASTER_BLOB_SZ ) : dum.InflateRect( SELN_BLOB_SZ, SELN_BLOB_SZ);
		pDC->Rectangle(dum);

		// Top right
		p1.SetPoint( m_cRectShown.right + MASTER_BLOB_SZ, m_cRectShown.top - MASTER_BLOB_SZ );
		dum.SetRect(p1,p1);
		m_bIsMaster ? dum.InflateRect( MASTER_BLOB_SZ, MASTER_BLOB_SZ ) : dum.InflateRect( SELN_BLOB_SZ, SELN_BLOB_SZ);
		pDC->Rectangle(dum);

		// Bottom right
		p1.SetPoint( m_cRectShown.right + MASTER_BLOB_SZ, m_cRectShown.bottom + MASTER_BLOB_SZ );
		dum.SetRect(p1,p1);
		m_bIsMaster ? dum.InflateRect( MASTER_BLOB_SZ, MASTER_BLOB_SZ ) : dum.InflateRect( SELN_BLOB_SZ, SELN_BLOB_SZ);
		pDC->Rectangle(dum);

		// Bottom Left
		p1.SetPoint( m_cRectShown.left - MASTER_BLOB_SZ, m_cRectShown.bottom + MASTER_BLOB_SZ );
		dum.SetRect(p1,p1);
		m_bIsMaster ? dum.InflateRect( MASTER_BLOB_SZ, MASTER_BLOB_SZ ) : dum.InflateRect( SELN_BLOB_SZ, SELN_BLOB_SZ);
		pDC->Rectangle(dum);

		pDC->SetROP2( oldPenMode );
		pDC->SelectObject(oldPen);
		pDC->SelectObject(oldBrush);

	} 



}


bool LgbDrawable::operator==( const LgbDrawable &rhs )
{
	if( m_csTag!=rhs.m_csTag ) return false;
	if( m_csType!=rhs.m_csType) return false;

	return true;
}


/*
Drawa the widgets somwhow!
*/
void LgbDrawable::Draw(		
				CDC *pDC, 
				const int &zLower, 
				const int &zUpper, 
				const int &leanDispPerZLevel
						)
{
//AfxMessageBox("IS THIS ONE");
	//Ehy is this function here?
}

void LgbDrawable::DrawFrame( CDC *pDC )
{	
	int oldPenMode = pDC->SetROP2( R2_XORPEN );

	CPen outlinePen( PS_SOLID, 1, RGB(255,255,255) );

	CPen *oldPen = pDC->SelectObject( &outlinePen );

	m_cRectShown.Draw(0, pDC);

	pDC->SetROP2( oldPenMode );
	pDC->SelectObject(oldPen);

}

void LgbDrawable::Draw3DPerspective( 
									CDC *pDC, 
									const int &zLower, 
									const int &zUpper, 
									const int &leanDispPerZLevel
									)
{

	// Draw the dashed lines from the 'shown' pos to the 'actual' pos
	int oldPenMode = pDC->SetROP2( R2_XORPEN );
	CPen shadowPen(PS_DASH, 1, RGB(255, 255, 255));

	CPen *oldPen;
	oldPen = pDC->SelectObject(&shadowPen);

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// The 'pseudo 3D' stuff.
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	// Vector from any corner of actual rect to equiv corner of '3d' rect
	CPoint Total3DDispVec = m_cRectShown.TopLeft() - m_cRect.TopLeft();

	CPoint Disp3DVecPerZ( Total3DDispVec.x / m_iZPosProcessed, Total3DDispVec.y / m_iZPosProcessed );

	// Start-point of the lean-line for this z-range, relative 
	// to an equiv point on the base pos of icon.
	CPoint initialDisp( Disp3DVecPerZ.x * zLower, Disp3DVecPerZ.y * zLower );

	// End-point of the lean-line
	CPoint finalDisp( Disp3DVecPerZ.x * zUpper, Disp3DVecPerZ.y * zUpper );

	// Is there an lean?
	bool b_Lean = (Disp3DVecPerZ.x!= 0) || (Disp3DVecPerZ.y!= 0);

	if(b_Lean){

		pDC->MoveTo( m_cRect.TopLeft() + initialDisp );
		pDC->LineTo( m_cRect.TopLeft() + finalDisp );

		pDC->MoveTo( CPoint(m_cRect.right, m_cRect.top) + initialDisp );
		pDC->LineTo( CPoint(m_cRect.right, m_cRect.top) + finalDisp  );

		pDC->MoveTo( m_cRect.BottomRight() + initialDisp );
		pDC->LineTo( m_cRect.BottomRight() + finalDisp );

		pDC->MoveTo( CPoint(m_cRect.left, m_cRect.bottom) + initialDisp  );
		pDC->LineTo( CPoint(m_cRect.left, m_cRect.bottom )+ finalDisp );

	}

	// Outline rectangle in 'actual' pos.
	if( (zLower == 0)					// This cond occurs at the base layer
						&& b_Lean )		// don't draw base rect if no 3d-lean is apparent
		
		m_cRect.Draw(0, pDC);


	pDC->SetROP2( oldPenMode );
	pDC->SelectObject(oldPen);

}


LgbRectSelTypeEnum LgbDrawable::getSelectionMode( const CPoint &pt , const int &tolerance )
{

	// Make it easier for the user to resize even very small icons.
	const int MIN_SELECTABLE_DIMENSION	= 15;
	const int ARBITRARY_EXPANSION		= 5;

	//int tol = tolerance < ARBITRARY_SMALLNESS ? 5: ARBITRARY_SMALLNESS;

	CRect outerRect = m_cRectShown;
	CRect innerRect = m_cRectShown;

	if( (m_cRect.Width() < MIN_SELECTABLE_DIMENSION ) ){

		innerRect.InflateRect( ARBITRARY_EXPANSION,0 );
		outerRect = innerRect;
		outerRect.InflateRect( ARBITRARY_EXPANSION,0 );

	} else {
		innerRect.InflateRect( -ARBITRARY_EXPANSION,0 );

	}

	if( (m_cRect.Height() < MIN_SELECTABLE_DIMENSION ) ){

		innerRect.InflateRect( 0,ARBITRARY_EXPANSION );
		outerRect = innerRect;
		outerRect.InflateRect( 0,ARBITRARY_EXPANSION );

	} else {
		innerRect.InflateRect( 0,-ARBITRARY_EXPANSION );

	}

	//Ensure the inner rect (ie for dragging, rather than resizing) is not too small.
/*
	if( (m_cRect.Width() < tolerance*3 ) ){
		innerRect.InflateRect( -m_cRect.Width()/3, 0 );
	}else{
		innerRect.InflateRect( -(tol+1), 0 );
	}

	if( (m_cRect.Height() < tolerance*3 ) ){
		innerRect.InflateRect( 0, -m_cRect.Width()/3 );
	}else{
		innerRect.InflateRect( 0, -(tol+1) );
	}
*/
	if( !outerRect.PtInRect(pt) ){

		return k_LgbDrawableOutside;

	}else if(  innerRect.PtInRect(pt) ){

		return k_LgbDrawableInterior;

	} else {

		return k_LgbDrawableError;
	}

}

void LgbDrawable::move( const CPoint &vec)
{
	m_cRect.OffsetRect( vec );
	m_cRectShown.OffsetRect( vec );
	return;
}

void LgbDrawable::offsetRgt(const int &mov ){}

void LgbDrawable::offsetLft(const int &mov ){}

void LgbDrawable::offsetTop(const int &mov ){}

void LgbDrawable::offsetBtm(const int &mov ){}

void LgbDrawable::offsetTopRgt(const CPoint &mov ){}

void LgbDrawable::offsetTopLft(const CPoint &mov ){}

void LgbDrawable::offsetBtmLft(const CPoint &mov ){}

void LgbDrawable::offsetBtmRgt(const CPoint &mov ){}



LgbClassIDEnum LgbDrawable::getClassId(){ return k_LgbDrawable; }


LgbDrawable::Scan LgbDrawable::scanFieldEquality( 
				LgbDrawable *pDrbl, 
				LgbDrawable::Scan &scanSoFar )
{

	// Only find out about latest comparison if previous comparisons are still 
	// favourable.

	//-----------------------------------
	// Left
	//-----------------------------------
	if( scanSoFar.m_bSameLft ){
		if( m_cRect.left != pDrbl->m_cRect.left ) { 
			scanSoFar.m_bSameLft = false;
		}
	}


	//-----------------------------------
	// Right
	//-----------------------------------
	if( scanSoFar.m_bSameRgt ){
		if( m_cRect.right != pDrbl->m_cRect.right ) { 
			scanSoFar.m_bSameRgt = false;
		}
	}

	//-----------------------------------
	// Top
	//-----------------------------------
	if( scanSoFar.m_bSameTop ){
		if( m_cRect.top != pDrbl->m_cRect.top ) { 
			scanSoFar.m_bSameTop = false;
		}
	}

	//-----------------------------------
	// Bottom
	//-----------------------------------
	if( scanSoFar.m_bSameBtm ){
		if( m_cRect.bottom != pDrbl->m_cRect.bottom ) { 
			scanSoFar.m_bSameBtm = false;
		}
	}


	//-----------------------------------
	// Width
	//-----------------------------------
	if( scanSoFar.m_bSameWidth ){
		if( m_cRect.Width() != pDrbl->m_cRect.Width() ) { 
			scanSoFar.m_bSameWidth = false;
		}
	}


	//-----------------------------------
	// Vertical Extent
	//-----------------------------------

	if( scanSoFar.m_bSameVrtExtnt ){
		if( m_cRect.Height() != pDrbl->m_cRect.Height() ) { 
			scanSoFar.m_bSameVrtExtnt = false;
		}
	}


	//-----------------------------------
	// Type
	//-----------------------------------

	if( scanSoFar.m_bSameType ){
		if( m_csType != pDrbl->m_csType ) { 
			scanSoFar.m_bSameType = false;
		}
	}


	//-----------------------------------
	// Tag
	//-----------------------------------

	if( scanSoFar.m_bSameTag ){
		if( m_csTag != pDrbl->m_csTag ) { 
			scanSoFar.m_bSameTag = false;
		}
	}

	
	//-----------------------------------
	// zPos
	//-----------------------------------

	if( scanSoFar.m_bSameZPos ){
		if( m_iZPosUser != pDrbl->m_iZPosUser ) { 
			scanSoFar.m_bSameZPos = false;
		}
	}
	
	return scanSoFar;
}

bool LgbDrawable::Scan::allScanFieldsFalse()
{
	return		!m_bSameLft && !m_bSameRgt &&
				!m_bSameTop && !m_bSameBtm &&
				!m_bSameWidth && !m_bSameVrtExtnt;
}

void LgbDrawable::Scan::init()
{
	m_bSameZPos			= true;

	m_bSameTag			= true;
	m_bSameType			= true;

	m_bSameLft			= true;
	m_bSameRgt			= true; 
	m_bSameTop			= true; 
	m_bSameBtm			= true; 
	m_bSameWidth		= true; 
	m_bSameVrtExtnt		= true;
}


LgbDrawable & LgbDrawable::operator=( const LgbDrawable &x )
{
	m_cRect				= x.m_cRect;
	m_bIsSelected		= x.m_bIsSelected;
	m_bIsToBeDeleted	= x.m_bIsToBeDeleted;
	m_bShowTag			= x.m_bShowTag;
	m_csTag				= x.m_csTag;
	m_csType			= x.m_csType;
	m_iZPosUser				= x.m_iZPosUser;
	//m_iPerCentOpacity	= x.m_iPerCentOpacity;

	return *this;
}

bool LgbDrawable::testPointIsOnEdge()
{
	m_cRect.SetRect(20, 25, 100, 106 ); // l, t, r, b

	bool failed = false;
	int tol;
	CPoint pt;

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	tol = 0;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	// should be outside
	pt.x = 0;
	pt.y = 0;
	failed = failed || (getSelectionMode( pt, tol) != k_LgbDrawableOutside);

	// should be in middle
	pt.x = 60;
	pt.y = 70;
	failed = failed || (getSelectionMode( pt, tol) != k_LgbDrawableInterior);

	// should be left
	pt.x = 20;
	pt.y = 70;
	failed = failed || (getSelectionMode( pt, tol) != k_LgbDrawableLft);

	// should be right
	pt.x = 100;
	pt.y = 70;
	failed = failed || (getSelectionMode( pt, tol) != k_LgbDrawableRgt);

	// should be top
	pt.x = 60;
	pt.y = 25;
	failed = failed || (getSelectionMode( pt, tol) != k_LgbDrawableTop);

	// should be bottom
	pt.x = 60;
	pt.y = 106;
	failed = failed || (getSelectionMode( pt, tol) != k_LgbDrawableBtm);



	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	tol = 5;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	// should be outside
	pt.x = 0;
	pt.y = 0;
	failed = failed || (getSelectionMode( pt, tol) != k_LgbDrawableOutside);

	// should be in middle
	pt.x = 60;
	pt.y = 70;
	failed = failed || (getSelectionMode( pt, tol) != k_LgbDrawableInterior);

	// should be left
	pt.x = 25;
	pt.y = 70;
	failed = failed || (getSelectionMode( pt, tol) != k_LgbDrawableLft);

	// should be right
	pt.x = 96;
	pt.y = 70;
	failed = failed || (getSelectionMode( pt, tol) != k_LgbDrawableRgt);

	// should be top
	pt.x = 55;
	pt.y = 29;
	failed = failed || (getSelectionMode( pt, tol) != k_LgbDrawableTop);

	// should be bottom
	pt.x = 60;
	pt.y = 101;
	failed = failed || (getSelectionMode( pt, tol) != k_LgbDrawableBtm);





	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	tol = 4;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	// should be outside
	pt.x = 0;
	pt.y = 0;
	failed = failed || (getSelectionMode( pt, tol) != k_LgbDrawableOutside);

	// should be in middle
	pt.x = 60;
	pt.y = 70;
	failed = failed || (getSelectionMode( pt, tol) != k_LgbDrawableInterior);

	// should be in middle
	pt.x = 25;
	pt.y = 70;
	failed = failed || (getSelectionMode( pt, tol) != k_LgbDrawableInterior);

	// should be in middle
	pt.x = 94;
	pt.y = 70;
	failed = failed || (getSelectionMode( pt, tol) != k_LgbDrawableInterior);

	// should be in top
	pt.x = 55;
	pt.y = 25;
	failed = failed || (getSelectionMode( pt, tol) != k_LgbDrawableInterior);

	// should be in middle
	pt.x = 60;
	pt.y = 101;
	failed = failed || (getSelectionMode( pt, tol) != k_LgbDrawableInterior);


	return failed;

}
/*
bool LgbDrawable::testEquals()
{

	bool failed = false;

	m_csTag = "99A";
	m_csType = "99B";

	LgbDrawable t1;
	t1.m_csTag = "99A";
	t1.m_csType = "99B";

	LgbDrawable t2;
	t2.m_csTag = "99X";
	t2.m_csType = "99Y";


	failed = failed || !equals(t1);
	failed = failed || equals(t2);

	failed = failed || t1.equals(t2);
	failed = failed || !t1.equals(t1);

	return failed;

}
*/
bool LgbDrawable::test()
{
	bool res;
	//res = testEquals();
	res = testPointIsOnEdge();

	return res;
}


void LgbDrawable::setActive(const bool & state)
{
	m_bIsActive = state;
}

bool LgbDrawable::isActive(void)
{
	return m_bIsActive;
}

void LgbDrawable::setState( MemberTypesEnum eMember, bool state )
{

	if(  eMember==k_MasterSelectedActive ){

		m_bIsActive = state;
		m_bIsSelected = state;
		m_bIsMaster = state;

	} else if(  eMember==k_Active ){

		m_bIsActive = state;

	} else if( eMember==k_Master ){

		m_bIsMaster = state;

	} else if( eMember==k_Selected ){

		m_bIsSelected = state;

	}else if( eMember==k_LastClicked ){

		m_bIsLastClicked = state;

	}

}

bool LgbDrawable::getState( MemberTypesEnum eMember )
{


	if(  eMember==k_Active ){

		return m_bIsActive;

	} else if( eMember==k_Master ){

		return m_bIsMaster;

	} else if( eMember==k_Selected ){

		return m_bIsSelected;

	} else if( eMember==k_LastClicked ){

		return m_bIsLastClicked;

	}else{

		assert (1==0);
		return true; // keep compiler happy about paths returning values.
	}

}


//void LgbDrawable::setPerCentOpacity(const int & val)
//{
//	m_iPerCentOpacity = val;
//}

