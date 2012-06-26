/** @file graphics.c
 * Definitions for the general-purpose graphics functions and types.
 * 
 * @author: Andrew Coombes
 * @version: $Revision: 1120 $
 * @date: $Date: 2006-10-30 05:05:44 +0000 (Mon, 30 Oct 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 *
 */

#include "graphics.h"

/**
 * Create a colour structure from individual red, green, blue components
 */
EhsGraphicsColourClass EhsGraphicsColour_rgb(ehs_uint8 r, ehs_uint8 g, ehs_uint8 b)
{
	EhsGraphicsColourClass c;
	c.sComp.nAlpha = (ehs_uint8)0xff; 
	c.sComp.nRed = r;
	c.sComp.nGreen = g;
	c.sComp.nBlue = b;

	return c;
}

/**
 * Create a colour structure from individual red, green, blue, alpha components
 */
EhsGraphicsColourClass EhsGraphicsColour_argb(ehs_uint8 r, ehs_uint8 g, ehs_uint8 b,ehs_uint8 alpha)
{
	EhsGraphicsColourClass c;
	c.sComp.nAlpha = alpha; 
	c.sComp.nRed = r;
	c.sComp.nGreen = g;
	c.sComp.nBlue = b;

	return c;
}

/**
 * True if two rectangles overlap
 */
ehs_bool EhsGraphicsRectangle_overlap(const EhsGraphicsRectangleClass* r1, const EhsGraphicsRectangleClass* r2)
{
	ehs_bool bRet;

	if (((r1->nLeft + r1->nWidth) < r2->nLeft) ||	/* r1 is completely to the left of r2 */
		((r2->nLeft + r2->nWidth) < r1->nLeft) ||	/* r2 is completely to the left of r1 */
		((r1->nTop + r1->nHeight) < r2->nTop) ||	/* r1 is completely above r2 */
		((r2->nTop + r2->nHeight) < r1->nTop))		/* r2 is completely above r1 */
	{
		bRet = EHS_FALSE;
	}
	else
	{
		bRet = EHS_TRUE;
	}

	return bRet;
}

/**
 * Returns the intersection of two rectangles
 * 
 * @param[out] ret Contains the intersection of the two rectangles
 * @param[in] r1 First rectangle
 * @param[in] r2 Second rectangle
 * @return false if rectangles don't intersect
 */
 ehs_bool EhsGraphicsRectangle_intersect(EhsGraphicsRectangleClass* ret, const EhsGraphicsRectangleClass* r1, const EhsGraphicsRectangleClass* r2)
 {
 	ehs_uint16 r1Rt, r2Rt, r1Btm, r2Btm; /* calculated RHS and bottom edges of rectangle r1, r2 */
 	ehs_uint16 maxLeft, maxTop; /* calculated edge of intersected rectangle */
 	ehs_bool bRet = EHS_FALSE;
 	
 	if (EhsGraphicsRectangle_overlap(r1,r2))
 	{
 		/* you could save 4 bytes and a few cycles using ret->nLeft and ret->nTop instead of maxLeft, maxTop,
 		 * but in the case where r1 == ret or r2 == ret, this has side effects
 		 */
	 	maxLeft = (r1->nLeft > r2->nLeft)?r1->nLeft:r2->nLeft;
	 	maxTop  = (r1->nTop  > r2->nTop )?r1->nTop :r2->nTop ;
	 	r1Rt = (r1->nLeft + r1->nWidth) - maxLeft;
	 	r2Rt = (r2->nLeft + r2->nWidth) - maxLeft;
	 	r1Btm  = (r1->nTop  + r1->nHeight) - maxTop;
	 	r2Btm  = (r2->nTop  + r2->nHeight) - maxTop;
	 	
	 	ret->nWidth = (r1Rt < r2Rt)?r1Rt:r2Rt;
	 	ret->nHeight = (r1Btm < r2Btm)?r1Btm:r2Btm;
	 	ret->nLeft = maxLeft;
	 	ret->nTop = maxTop;
	 	bRet = EHS_TRUE;
 	}
 	
 	return bRet;
 }

 /**
  * Returns the union of two rectangles
  * 
  * @param[out] ret Contains the union of the two rectangles
  * @param[in] r1 First rectangle
  * @param[in] r2 Second rectangle
  */
void EhsGraphicsRectangle_union(EhsGraphicsRectangleClass* ret, const EhsGraphicsRectangleClass* r1, const EhsGraphicsRectangleClass* r2)
{
	ehs_uint16 r1Rt, r2Rt, r1Btm, r2Btm; /* calculated RHS and bottom edges of rectangle r1, r2 */
	ehs_uint16 minLeft, minTop; /* minimum values for top and left */
	
	/* you could use ret->nLeft and ret->nTop instead of minLeft, minTop, but in the
	 * case where r1 == ret or r2 == ret, this has side effects
	 */
	minLeft = (r1->nLeft < r2->nLeft)?r1->nLeft:r2->nLeft;
 	minTop  = (r1->nTop  < r2->nTop )?r1->nTop :r2->nTop ;
 	r1Rt = (r1->nLeft + r1->nWidth) - minLeft;
 	r2Rt = (r2->nLeft + r2->nWidth) - minLeft;
 	r1Btm  = (r1->nTop  + r1->nHeight) - minTop;
 	r2Btm  = (r2->nTop  + r2->nHeight) - minTop;
 	
 	ret->nWidth = (r1Rt > r2Rt)?r1Rt:r2Rt;
 	ret->nHeight = (r1Btm > r2Btm)?r1Btm:r2Btm;
 	ret->nLeft = minLeft;
 	ret->nTop = minTop;
}
