/** @file LgbResizedDrawable.h
 * Extends LgbDrawable to represent an icon that can also be resized by dragging its
 * sides.  NB.  This doesn't make sense for bitmaps, but does for text icons.
 * @author: Matthew Rutherford
 * @version: $Revision: 577 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */
#pragma once
#include "lgbdrawable.h"
#include "atltypes.h"

class LgbResizedDrawable :
	public LgbDrawable
{
public:

	LgbResizedDrawable(void); //!< Std constructor

	//! Constructor
	/*!
	\param rect icon's outline border
	\param type ie textbox, bitmap etc
	\param tag id string from LAB
	\param zPos the z-level of the icon
	*/
	LgbResizedDrawable(	
					const CRect			&rect,
					const CString		&type,
					const CString		&tag,
					const int			&zPos
					);

	LgbResizedDrawable(	const LgbResizedDrawable &icon );

	~LgbResizedDrawable(void);

	//! Message for icon to draw itslef
	void Draw( const int &bobbleSize, CDC *pMemDC, const CRect &clientRect, const int &zLower, const int &zUpper, const int &leanPerUnitZ);

	//! tests whethet 'pt' is inside border, and if so, whether it is left, bottom-left, bottom etc
	LgbRectSelTypeEnum getSelectionMode( const CPoint &pt , const int &tol );

	//! Return enum indicating class 
	LgbClassIDEnum getClassId();


	void offsetRgt(const int &mov ); //!< Move border's right side
	void offsetLft(const int &mov ); //!< Move border's left side
	void offsetTop(const int &mov ); //!< Move border's top side
	void offsetBtm(const int &mov ); //!< Move border's bottom side

	void offsetTopRgt(const CPoint &mov ); //!< Move border's top-right corner
	void offsetTopLft(const CPoint &mov ); //!< Move border's top-left corner
	void offsetBtmLft(const CPoint &mov ); //!< Move border's bottom-left corner
	void offsetBtmRgt(const CPoint &mov ); //!< Move border's bottom-right corner
};
