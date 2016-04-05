// SomeTests.cpp: implementation of the CSomeTests class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LABUnitTest.h"
#include "SomeTests.h"

// include HelperMacros to use CppUnit macros
#include <cppunit/extensions/HelperMacros.h>

// register the test suite
CPPUNIT_TEST_SUITE_REGISTRATION( CSomeTests );

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/********************************* Test Suite definition *****************************************************/
/**
 * Constructor for the HandleCommands test suite.
 */
CSomeTests::CSomeTests(void)
{
	CPPUNIT_ASSERT( 1 );
}

/**
 * Destructor for the HandleCommands test suite.
 */
CSomeTests::~CSomeTests(void)
{

}

/**
 * Called immediately before every test case to perform global setup activities.
 */
void CSomeTests::setUp()
{
}

/**
 * Called immediately after every test case to perform global tear-down activities.
 */
void CSomeTests::tearDown()
{
}


void CSomeTests::test1()
{
	int var1 = 66;
	int var2 = 66;

	CPPUNIT_ASSERT_EQUAL(var1, var2);
}

void CSomeTests::test2()
{
	int var1 = 99;
	int var2 = 99;

	if (var1 == var2) {
        CPPUNIT_FAIL("var1 and var2 matched - should not be equal in this case!!");
    }
}
