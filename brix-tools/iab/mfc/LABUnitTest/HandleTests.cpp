#include "StdAfx.h"
#include "HandleTests.h"

// include HelperMacros to use CppUnit macros
#include <cppunit/extensions/HelperMacros.h>

//#include "../LucidApplicationBuilder/condat.h"
//#include "../LucidTools/ExternalTest/tester.h"

// register the test suite
CPPUNIT_TEST_SUITE_REGISTRATION( HandleTests);

/********************************* Test Suite definition *****************************************************/
/**
 * Constructor for the HandleCommands test suite.
 */
HandleTests::HandleTests(void)
{
}

/**
 * Destructor for the HandleCommands test suite.
 */
HandleTests::~HandleTests(void)
{
}

/**
 * Called immediately before every test case to perform global setup activities.
 */
void HandleTests::setUp()
{
}

/**
 * Called immediately after every test case to perform global tear-down activities.
 */
void HandleTests::tearDown()
{
}


void HandleTests::Test1()
{
	int var1 = 66;
	int var2 = 66;

	CPPUNIT_ASSERT_EQUAL(var1, var2);
}

void HandleTests::Test2()
{
	int var1 = 99;
	int var2 = 99;

	if (var1 == var2) {
        CPPUNIT_FAIL("var1 and var2 matched - should not be equal in this case!!");
    }
}

void HandleTests::T21_CreateCondataObjects()
{
	int var1 = 12345;
	int var2 = 66;

	//Tester tester;
	//CPPUNIT_ASSERT_EQUAL(var1, tester.testit());
}
