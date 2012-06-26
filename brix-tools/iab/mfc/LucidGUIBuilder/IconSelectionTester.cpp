#include "stdafx.h"
#include "IconSelectionTester.h"
#include "IconSelection.h"
#include "LgbDrawable.h"
#include "LgbTextIcon.h"
#include "LgbColorsDef.h"
IconSelectionTester::IconSelectionTester(void)
{
}

IconSelectionTester::~IconSelectionTester(void)
{
}

void IconSelectionTester::test1(void)
{
	/*
	IconSelection< LgbDrawable > fred;
	LgbDrawable::Scan scan;

	LgbDrawable drbl1(CRect(10,12,20,22), "Type1", "Tag1", 1 );
	LgbDrawable drbl2(CRect(10,12,20,22), "Type1", "Tag1", 1 );
	LgbDrawable drbl3(CRect(10,12,20,22), "Type1", "Tag1", 1 );

	fred.push_back( &drbl1 );
	fred.push_back( &drbl2 );
	fred.push_back( &drbl3 );
	scan = fred.processEquality();

	LgbDrawable drbl4(CRect(11,12,20,22), "Type1", "Tag1", 1 );
	fred.push_back( &drbl4 );
	scan = fred.processEquality();

	fred.clear();
*/
}

void IconSelectionTester::test2(void)
{
	/*
	IconSelection< LgbTextIcon > fred;
	LgbTextIcon::Scan scan;

	LgbColorsDef colors_1 = { 1,2,3, 6,7,8 };
	LgbColorsDef colors_2 = { 1,2,3, 6,7,10 };

	// All fields the same.

	LgbTextIcon drbl1( CRect(10,12,20,22), "Type1", "Tag1", 1, colors_1 );
	LgbTextIcon drbl2( CRect(10,12,20,22), "Type1", "Tag1", 1, colors_1 );

	fred.push_back( &drbl1 );
	fred.push_back( &drbl2 );

	scan = fred.processEquality();



	// same colors -> false
	LgbTextIcon drbl3( CRect(10,12,20,22), "Type1", "Tag1", 1, colors_2 );
	fred.push_back( &drbl3 );
	scan = fred.processEquality();

	// sameLft -> false
	LgbTextIcon drbl4( CRect(11,12,20,22), "Type1", "Tag1", 1, colors_2 );
	fred.push_back( &drbl4 );
	scan = fred.processEquality();

	fred.clear();

	fred.push_back( &drbl1 );
	fred.push_back( &drbl2 );
	fred.push_back( &drbl3 );
	fred.push_back( &drbl4 );
	scan = fred.processEquality();
*/
}