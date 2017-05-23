
#pragma once

#include "Porting_Classes/INXString.h"

typedef struct  {

	INXString type;
	INXString tag;
	int xTopLft;
	int yTopLft;
	int width;
	int height;
	int location;
	int zPos;

} LgbIconEssentialData_t;

typedef struct  {

	INXString csClass;
	INXString csFont;
	short alpha;
	short red;
	short green;
	short blue;

} LgbTextStyleEssentialData_t;

typedef struct  {

	LgbIconEssentialData_t basics;

	short fgAlpha;
	short bgAlpha;

	short	bgRed;
	short 	bgGreen;
	short 	bgBlue;
	short 	fgRed;
	short 	fgGreen;
	short 	fgBlue;

	INXString csFont;
	int leftIndent;
	int rightIndent;
	int topIndent;
	int bottomIndent;
	int lineSpacing;

} LgbTextIconEssentialData_t;

typedef struct  {

	LgbIconEssentialData_t basics;

	short bgAlpha;

	short	bgRed;
	short 	bgGreen;
	short 	bgBlue;

} LgbPatchIconEssentialData_t;

typedef struct  {

	LgbIconEssentialData_t basics;

	short alpha;

	INXString bitmapFileName;

	short lockAspect;

} LgbImageIconEssentialData_t;
