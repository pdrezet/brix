#include "StdAfx.h"
#include "PathDialogTest.h"

// include HelperMacros to use CppUnit macros
#include <cppunit/extensions/HelperMacros.h>

#include "../LucidApplicationBuilder/PathDialog.h"

// global variable declared in CDrawProgApp
//extern char workDir[4096];

// register the test suite
CPPUNIT_TEST_SUITE_REGISTRATION( PathDialogTest );

/********************************* Test Suite definition *****************************************************/
/**
 * Constructor for the HandleCommands test suite.
 */
PathDialogTest::PathDialogTest(void)
{
	//strcpy(workDir, "..\\..\\..\\dist");
}

/**
 * Destructor for the HandleCommands test suite.
 */
PathDialogTest::~PathDialogTest(void)
{
}

/**
 * Called immediately before every test case to perform global setup activities.
 */
void PathDialogTest::setUp()
{
}

/**
 * Called immediately after every test case to perform global tear-down activities.
 */
void PathDialogTest::tearDown()
{
}

// tests the getInitScrollPos method
/**
 * @page EssUA0020 EssUA0020 getInitScrollPosT1
 * @anchor EssUA0020
 * @section purpose Purpose:
 * This test exercises getInitScrollPos
 * method of the class DEP.
 *
 * @section initial Initial conditions: 
 * - 3 instances of ConData are created and initialised to be gui textboxes with coords (333,444), (300,460), (200,460)
 * - set client rect to be (0,0,100,100)
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Execute dep.getInitScrollPos(clientRect)
 * -# Add first instance of condata to condata list in dep object
 * -# Execute dep.getInitScrollPos(clientRect)
 * -# Add second instance of condata to condata list in dep object
 * -# Execute dep.getInitScrollPos(clientRect)
 * -# Remove second instance of condata from condata list in dep object
 * -# Add third instance of condata to condata list in dep object
 * -# Execute dep.getInitScrollPos(clientRect)
 *
 * @section results Expected results:
 * - step 1 returns (-1, -1)
 * - step 3 returns (308, 419)
 * - step 5 returns (275, 419)
 * - step 8 returns (175, 435)
 *
 */
void PathDialogTest::getInitScrollPosT1()
{
	CPathDialog dlg;

	if (!dlg.isValidDir("C:\\xxx ")) {
		CPPUNIT_FAIL("This should not be a valid directory!!");
	}

	if (dlg.isValidDir("C:\\xxx")) {
		CPPUNIT_FAIL("This should be a valid directory!!");
	}
}
