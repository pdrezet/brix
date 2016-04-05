/** @file graphics.h
 * Declarations for the general-purpose graphics functions and types.
 * 
 * @author: Andrew Coombes
 * @version: $Revision: 1120 $
 * @date: $Date: 2006-10-30 05:05:44 +0000 (Mon, 30 Oct 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_GRAPHICS_H
#define EHS_GRAPHICS_H
#include "ehs_types.h"
/**
 * EHS default representation of colour
 */
/*lint  -e960 acceptable use for a union - packing and unpacking data */
typedef union
	{
	struct {
#ifdef EHS_TARGET_BIGENDIAN
		ehs_uint8 nAlpha;
		ehs_uint8 nRed;
		ehs_uint8 nGreen;
		ehs_uint8 nBlue;
#else
		ehs_uint8 nBlue;
		ehs_uint8 nGreen;
		ehs_uint8 nRed;
		ehs_uint8 nAlpha;
#endif /* EHS_TARGET_BIGENDIAN */
	} sComp;	/**< Component view of the alpha RGB value of colour */
	ehs_uint32 nUint32;
} EhsGraphicsColourClass;
/*lint +e960*/

/**
 * Create a colour structure from individual red, green, blue components
 */
EHS_GLOBAL EhsGraphicsColourClass EhsGraphicsColour_rgb(ehs_uint8 r, ehs_uint8 g, ehs_uint8 b);

/**
 * Create a colour structure from individual red, green, blue, alpha components
 */
EHS_GLOBAL EhsGraphicsColourClass EhsGraphicsColour_argb(ehs_uint8 r, ehs_uint8 g, ehs_uint8 b, ehs_uint8 alpha);

/**
 * Permitted representations of colour
 */
typedef enum {
	EHS_GRAPHICS_COLOUR_ARGB8888,
	EHS_GRAPHICS_COLOUR_A8,
	EHS_GRAPHICS_COLOUR_A1
} EhsGraphicsColourFormatEnum;


/**
 * Representation of a simple rectangle
 */
typedef struct {
	ehs_uint16 nLeft;		/**< Pixels from left of screen to this rect. */
	ehs_uint16 nWidth;		/**< number of pixels across this rect */
	ehs_uint16 nTop;		/**< Number of pixels from top of this screen to top of this rect */
	ehs_uint16 nHeight;		/**< Number of pixels vertically for this rect */
} EhsGraphicsRectangleClass;

/**
 * True if two rectangles overlap
 */
EHS_GLOBAL ehs_bool EhsGraphicsRectangle_overlap(const EhsGraphicsRectangleClass* r1, const EhsGraphicsRectangleClass* r2);

/**
 * Returns the intersection of two rectangles
 * 
 * @param[out] ret Contains the intersection of the two rectangles
 * @param[in] r1 First rectangle
 * @param[in] r2 Second rectangle
 * @return false if no intersection exists
 */
EHS_GLOBAL ehs_bool EhsGraphicsRectangle_intersect(EhsGraphicsRectangleClass* ret, const EhsGraphicsRectangleClass* r1, const EhsGraphicsRectangleClass* r2);

/**
 * Returns the union of two rectangles
 * 
 * @param[out] ret Contains the union of the two rectangles
 * @param[in] r1 First rectangle
 * @param[in] r2 Second rectangle
 */
EHS_GLOBAL void EhsGraphicsRectangle_union(EhsGraphicsRectangleClass* ret, const EhsGraphicsRectangleClass* r1, const EhsGraphicsRectangleClass* r2);

#endif /* EHS_GRAPHICS_H */

