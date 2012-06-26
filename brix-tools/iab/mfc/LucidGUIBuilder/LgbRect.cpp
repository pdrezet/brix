/** @file LgbRect.cpp
 * Implementation of LgbRect class
 * @author: Matthew Rutherford
 * @version: $Revision: 577 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */
#include "stdafx.h"
#include "atltypes.h"
#include "LgbDrawableBag.h"
#include "LgbRect.h"

LgbRect::LgbRect(void)
{
	SetRect(50, 50, 100, 100);
}


LgbRect::LgbRect( const CPoint &pt1, const CPoint &pt2 )
{

	left	= min( pt1.x, pt2.x);
	right	= max( pt1.x, pt2.x);

	top	= min( pt1.y, pt2.y);
	bottom	= max( pt1.y, pt2.y);

}

LgbRect LgbRect::makeConventional() const
{

	CRect dum;

	dum.left	= min( left, right);
	dum.right	= max( left, right);

	dum.top		= max( top, bottom);
	dum.bottom	= min( top, bottom);

	return dum;

}

LgbRect::LgbRect(const CRect &rect)
{
	bottom	= rect.bottom;
	top		= rect.top;
	right	= rect.right;
	left	= rect.left;
}

LgbRect::~LgbRect(void)
{
}

void LgbRect::Draw(const int &selOffset, CDC *dc) const
{

		dc->MoveTo( left-selOffset, top-selOffset );

		dc->LineTo( right+selOffset, top-selOffset );

		dc->LineTo( right+selOffset, bottom+selOffset);

		dc->LineTo( left-selOffset, bottom+selOffset);

		dc->LineTo( left-selOffset, top-selOffset);

		return;

}

void LgbRect::offsetRgt(const int &mov)
{
	int newRgt = right + mov;
	if(newRgt<left){
		right = left;
		left = newRgt;
	}else{
		right=newRgt;
	}
}

void LgbRect::offsetLft(const int &mov)
{
	int newLft = left + mov;
	if(newLft>right){
		left = right;
		right = newLft;
	}else{
		left=newLft;
	}
}

void LgbRect::offsetTop(const int &mov)
{
	int newTop = top + mov;
	// In windows drawing-rectangles, the 'top' SHOULD BE < the bottom!
	if(newTop>bottom){
		top = bottom;
		bottom = newTop;
	}else{
		top=newTop;
	}
}

void LgbRect::offsetBtm(const int &mov)
{
	int newBtm = bottom + mov;
	if(newBtm<top){
	// In windows drawing-rectangles, the 'top' SHOULD BE < the bottom!
		bottom = top;
		top = newBtm;
	}else{
		bottom=newBtm;
	}
}


LgbRectIntsecnEnum LgbRect::getIntersection( const LgbRect &rect ) const
{

	// Check whether rect is completely within 'this', or whether this and
	// rect overlap partly, or not at all.

	// A. If both corners of rect are within this -> complete overlap.
	// B. If at least one corner of this is within rect -> partial overlap.
	// C. As in B, but with 'this' and 'rect vice-versa.

	LgbRect convRect = rect.makeConventional();
	LgbRect convThis = this->makeConventional();

	//-----------------------------------------------------
	// TOP LEFT

	// Is top left of rect within this?

	bool rectTopLftInThis = convThis.pointIsIn(convRect.TopLeft() );

	//-----------------------------------------------------
	// BOTTOM RIGHT

	bool rectBtmRgtInThis = convThis.pointIsIn(convRect.BottomRight() );

	//-----------------------------------------------------
	// BOTTOM LEFT

	bool rectBtmLftInThis = convThis.pointIsIn( CPoint( convRect.left, convRect.bottom )  );

	//-----------------------------------------------------
	// TOP RIGHT

	bool rectTopRgtInThis = convThis.pointIsIn( CPoint( convRect.right, convRect.top )  );


	if( rectTopLftInThis && rectTopLftInThis && rectBtmLftInThis && rectTopRgtInThis ){

		return k_LgbCompletelyWithin;

	} else if( rectTopLftInThis || rectTopLftInThis || rectBtmLftInThis || rectTopRgtInThis ){

		return k_LgbPartlyWithin;

	}else{

		// Examine whether marquee corners are in rect.
			
		//-----------------------------------------------------
		// TOP LEFT

		// Is top left of rect within this?

		bool thisTopLftInRect = convRect.pointIsIn(convThis.TopLeft() );

		//-----------------------------------------------------
		// BOTTOM RIGHT

		bool thisBtmRgtInRect = convRect.pointIsIn(convThis.BottomRight() );

		//-----------------------------------------------------
		// BOTTOM LEFT

		bool thisBtmLftInRect = convRect.pointIsIn( CPoint( convThis.left, convThis.bottom )  );

		//-----------------------------------------------------
		// TOP RIGHT

		bool thisTopRgtInRect = convRect.pointIsIn( CPoint( convThis.right, convThis.top )  );


		if( thisTopLftInRect || thisBtmRgtInRect || thisBtmLftInRect || thisTopRgtInRect ){

			return k_LgbPartlyWithin;

		}else{

			return k_LgbCompletelyWithout;
		}
	}

}

bool LgbRect::pointIsIn( const CPoint pnt) const
{
	
	return ( left<=pnt.x &&  right>=pnt.x && top>=pnt.y && (bottom<=pnt.y )  );

}



void LgbRect::testIntsn()
{

	LgbRect outer( CPoint( 0,0 ), CPoint(200,200) );
	LgbRect outerRev( CPoint(200,200), CPoint( 0,0 ) );

	LgbRect completelyWithin( CPoint( 10,10 ), CPoint(20,20) );
	LgbRect completelyWithinRev( CPoint(20,20), CPoint( 10,10 )  );

	LgbRect completelyWithout( CPoint( 1000,1000 ), CPoint(1020,1020) );
	LgbRect completelyWithoutRev(  CPoint(1020,1020), CPoint( 1000,1000 ) );

	LgbRect partlyWithin1( CPoint( 100,-20 ), CPoint(102,1020) );
	LgbRect partlyWithin2( CPoint( 100,-20 ), CPoint(102,102) );
	LgbRect partlyWithin3( CPoint( 100,100 ), CPoint(1102,102) );
	LgbRect partlyWithin4( CPoint( -20,100 ), CPoint(102,102) );
	LgbRect partlyWithin5( CPoint( 20,100 ), CPoint(1102,102) );

	LgbRectIntsecnEnum res;

	res = outer.getIntersection(completelyWithin);
	res = outer.getIntersection(completelyWithinRev);

	res = outerRev.getIntersection(completelyWithin);
	res = outerRev.getIntersection(completelyWithinRev);

	res = outer.getIntersection(completelyWithout);
	res = outer.getIntersection(completelyWithoutRev);

	res = outerRev.getIntersection(completelyWithout);
	res = outerRev.getIntersection(completelyWithoutRev);

	res = outer.getIntersection(partlyWithin1);
	res = outer.getIntersection(partlyWithin2);
	res = outer.getIntersection(partlyWithin3);
	res = outer.getIntersection(partlyWithin4);
	res = outer.getIntersection(partlyWithin5);

	res = outerRev.getIntersection(partlyWithin1);
	res = outerRev.getIntersection(partlyWithin2);
	res = outerRev.getIntersection(partlyWithin3);
	res = outerRev.getIntersection(partlyWithin4);
	res = outerRev.getIntersection(partlyWithin5);

}