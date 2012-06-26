/** @file LgbResizedDrawable.cpp
 * Implemeentaation of class LgbResizedDrawable
 * @author: Matthew Rutherford
 * @version: $Revision: 577 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */

#include "stdafx.h"
#include <cassert>
#include "LgbResizedDrawable.h"

LgbResizedDrawable::LgbResizedDrawable(void)
{
}

LgbResizedDrawable::LgbResizedDrawable(	const LgbResizedDrawable &icon )
: LgbDrawable( icon )
{
}

LgbResizedDrawable::LgbResizedDrawable(	
					const CRect			&rect,
					const CString		&type,
					const CString		&tag,
					const int			&zPos
					) : LgbDrawable( rect, type, tag,  zPos )
{
}


LgbResizedDrawable::~LgbResizedDrawable(void)
{
	//LgbDrawable:: ~LgbDrawable();
}

LgbClassIDEnum LgbResizedDrawable::getClassId(){ return k_LgbResizedDrawable; }


void LgbResizedDrawable::Draw( const int &blobSz, CDC *pMemDC, const CRect &clientRect,
							  const int &zLower, const int &zUpper, const int &leanDispPerZLevel )
{

	if(m_bIsSelected){

		// Draw the resize handles...
		pMemDC->SelectObject(m_cPenSelOutline);
		LgbRect dum;

		CPoint p1;
		CPoint p2;

		// Top left
		p1.SetPoint(m_cRectShown.left, m_cRectShown.top);
		p2 = p1;
		dum.SetRect(p1,p2);
		dum.InflateRect( blobSz, blobSz );
		dum.Draw(0, pMemDC);

		// Top middle
		p1.SetPoint(m_cRectShown.CenterPoint().x, m_cRectShown.top);
		p2 = p1;
		dum.SetRect(p1,p2);
		dum.InflateRect( blobSz, blobSz );
		dum.Draw(0, pMemDC);

		// Top right
		p1.SetPoint(m_cRectShown.right, m_cRectShown.top);
		p2 = p1;
		dum.SetRect(p1,p2);
		dum.InflateRect( blobSz, blobSz );
		dum.Draw(0, pMemDC);

		// mid left
		p1.SetPoint(m_cRectShown.left, m_cRectShown.CenterPoint().y);
		p2 = p1;
		dum.SetRect(p1,p2);
		dum.InflateRect( blobSz, blobSz );
		dum.Draw(0, pMemDC);

		// mid right
		p1.SetPoint(m_cRectShown.right, m_cRectShown.CenterPoint().y);
		p2 = p1;
		dum.SetRect(p1,p2);
		dum.InflateRect( blobSz, blobSz );
		dum.Draw(0, pMemDC);

		// lower left
		p1.SetPoint(m_cRectShown.left, m_cRectShown.bottom);
		p2 = p1;
		dum.SetRect(p1,p2);
		dum.InflateRect( blobSz, blobSz );
		dum.Draw(0, pMemDC);

		// lower middle
		p1.SetPoint(m_cRectShown.CenterPoint().x, m_cRectShown.bottom);
		p2 = p1;
		dum.SetRect(p1,p2);
		dum.InflateRect( blobSz, blobSz );
		dum.Draw(0, pMemDC);

		// lower right
		p1.SetPoint(m_cRectShown.right, m_cRectShown.bottom);
		p2 = p1;
		dum.SetRect(p1,p2);
		dum.InflateRect( blobSz, blobSz );
		dum.Draw(0, pMemDC);
	}

	LgbDrawable::Draw( pMemDC, zLower, zUpper, leanDispPerZLevel );

}



LgbRectSelTypeEnum LgbResizedDrawable::getSelectionMode( const CPoint &pt , const int &tolerance )
{

	LgbRectSelTypeEnum selMode = LgbDrawable::getSelectionMode( pt, tolerance );

	if(selMode == k_LgbDrawableOutside){

		// The point is outside the rect - that's all we need to know
		return selMode;

	}else {

		// The point is within border of the icon.

		if(m_bIsSelected){

			// If the icon isn't selected, all we need to know is that the point is in the
			// interior.  However, if the icon IS already selected, then we need to know 
			// whether the point is on the top , bottom, left, top=-left etc so that we can
			// change the cursor to a resize one.  This is because of the bus req. that resizes
			// option applies only to things already selected.

			int tol = tolerance;

			tol = (tol > m_cRect.Width()/2) ? m_cRect.Width()/2 : tol;
			tol = (tol > m_cRect.Height()/2) ? m_cRect.Height()/2 : tol;


			bool lft = false;
			bool top = false;
			bool rgt = false;
			bool btm = false;

			// Left / right are mutex
			if(  abs(pt.x - m_cRectShown.left) <=tol){

				lft = true;

			}else if(  abs( m_cRectShown.right - pt.x) <=tol){

				rgt = true;

			}
			
			
			// Top bottom are mutex also
			if(  abs( pt.y - m_cRectShown.top ) <=tol){

				top = true;

			}else if(  abs( m_cRectShown.bottom - pt.y ) <=tol){

				btm = true;

			} 

			// Top Lft/Right etc aren't mutex

			if(top){
				if(lft)return k_LgbDrawableTopLft;
				if(rgt)return k_LgbDrawableTopRgt;
				//if( abs(pt.x - m_cRectShown.CenterPoint().x)<= tol) return k_LgbDrawableTop;
				//return k_LgbDrawableInterior;
				return k_LgbDrawableTop;
			}

			if(btm){
				if(lft)return k_LgbDrawableLwrLft;
				if(rgt)return k_LgbDrawableLwrRgt;
				//if( abs(pt.x - m_cRectShown.CenterPoint().x)<= tol) return k_LgbDrawableBtm;
				//return k_LgbDrawableInterior;
				return k_LgbDrawableBtm;
			}

			if(lft){
			//	if( abs(pt.y - m_cRectShown.CenterPoint().y)<= tol) return k_LgbDrawableLft;
			//	return k_LgbDrawableInterior;
				return k_LgbDrawableLft;
			}

			if(rgt){
				//if( abs(pt.y - m_cRectShown.CenterPoint().y)<= tol) return k_LgbDrawableRgt;
				//return k_LgbDrawableInterior;
				return k_LgbDrawableRgt;
			}

		} // if(m_bIsSelected)

	} // if(selMode != k_LgbDrawableOutside){

	return k_LgbDrawableInterior;

}


void LgbResizedDrawable::offsetRgt(const int &mov )
{
	m_cRect.offsetRgt(mov);
	m_cRectShown.offsetRgt(mov);
}

void LgbResizedDrawable::offsetLft(const int &mov )
{
	m_cRect.offsetLft(mov);
	m_cRectShown.offsetLft(mov);
}

void LgbResizedDrawable::offsetTop(const int &mov )
{
	m_cRect.offsetTop(mov);
	m_cRectShown.offsetTop(mov);
}

void LgbResizedDrawable::offsetBtm(const int &mov )
{
	m_cRect.offsetBtm(mov);
	m_cRectShown.offsetBtm(mov);
}

void LgbResizedDrawable::offsetTopRgt(const CPoint &mov )
{
	offsetTop(mov.y);
	offsetRgt(mov.x);
}


void LgbResizedDrawable::offsetTopLft(const CPoint &mov )
{
	offsetTop(mov.y);
	offsetLft(mov.x);
}

void LgbResizedDrawable::offsetBtmLft(const CPoint &mov )
{
	offsetBtm(mov.y);
	offsetLft(mov.x);
}

void LgbResizedDrawable::offsetBtmRgt(const CPoint &mov )
{
	offsetBtm(mov.y);
	offsetRgt(mov.x);
}