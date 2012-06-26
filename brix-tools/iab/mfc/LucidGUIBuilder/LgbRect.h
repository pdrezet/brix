/** @file LgbRect.h
 * Extends an MFC CRect to provide support for representation of LGB icon borders
 * @author: Matthew Rutherford
 * @version: $Revision: 577 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */
#pragma once
#include "stdafx.h"
#include "atltypes.h"
#include "../common/LucidEnums.h"


//! Extends the MFC CRect class to provide support for representation of LGB icon borders.
/*! Ensures that the top of the rect is always at the same or a lower value than the bottom,
	and that the right is always a higher value than the left.  This is for consistentcy - for
	working out intersections etc - and also to reflect the way that the screen pixel coords have
	y increase from top to bottom.
	*/
class LgbRect :	public CRect
{

private:
	LgbRect makeConventional() const;

public:

	LgbRect(void);
	LgbRect(const CRect &rect);

	LgbRect( const CPoint &pt1, const CPoint &pt2 ); //!< Construct from top-left & bottom-right corners

	~LgbRect(void);

	//! Draw the borders of the rectangle.
	/*!
	\param inflateOffset how much to inflate the drawn size by
	\param dc the derawing context (with  a pen selected, etc)
	*/
	void Draw(const int &inflateOffset, CDC *dc) const;

	//! Find the intersection between this and he argument rectangle
	/*!
	\param rect The 2nd rectangle against which to test
	\return enum indicating type (if any) of intersection
	*/
	LgbRectIntsecnEnum getIntersection( const LgbRect &rect ) const;

	void offsetRgt(const int &mov ); //!< Move right border by 'mov'
	void offsetLft(const int &mov ); //!< Move left border by 'mov'
	void offsetTop(const int &mov ); //!< Move top border by 'mov'
	void offsetBtm(const int &mov ); //!< Move bottom border by 'mov'

	bool pointIsIn( const CPoint pnt) const; //!< Returns true if point is within, or on, rectangle's border.

	void testIntsn();

};
