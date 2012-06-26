#include "StdAfx.h"
#include "ConDataTest.h"

// include HelperMacros to use CppUnit macros
#include <cppunit/extensions/HelperMacros.h>

#include "../LucidApplicationBuilder/condat.h"

// global variable declared in CDrawProgApp
extern char workDir[WORK_DIR_SIZE];

// register the test suite
CPPUNIT_TEST_SUITE_REGISTRATION( ConDataTest );

/********************************* Test Suite definition *****************************************************/
/**
 * Constructor for the HandleCommands test suite.
 */
ConDataTest::ConDataTest(void)
{
	strcpy(workDir, "..\\..\\..\\dist");
}

/**
 * Destructor for the HandleCommands test suite.
 */
ConDataTest::~ConDataTest(void)
{
}

/**
 * Called immediately before every test case to perform global setup activities.
 */
void ConDataTest::setUp()
{
}

/**
 * Called immediately after every test case to perform global tear-down activities.
 */
void ConDataTest::tearDown()
{
}

// tests the isGuiWidget function
/**
 * @page EssUA0015 EssUA0015 isGuiWidgetT1
 * @anchor EssUA0015
 * @section purpose Purpose:
 * This test exercises isGuiWidget
 * method of the class ConData.
 *
 * @section initial Initial conditions: 
 * - An instance of ConData is created and initialised to be a gui textbox
 * - A second instance of ConData is created nd initialised to be an accumulator
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Execute blob1->isGuiWidget()
 * -# Execute blob2->isGuiWidget()
 *
 * @section results Expected results:
 * - step 1 returns TRUE
 * - step 2 returns FALSE
 *
 */
void ConDataTest::isGuiWidgetT1()
{
	ConData *blob1 = new ConData;
	CPoint point(0,0);
	
	// create a condata object for a gui widget
	blob1->init("guitextbox_i", "", point, 1);
	if (!blob1->isGuiWidget()) {
		CPPUNIT_FAIL("This should be a Gui widget!!");
	}
	delete blob1;

	// create a condata object for a function that isn't a gui widget
	ConData *blob2 = new ConData;
	blob2->init("operator_addacci", "", point, 1);
	if (blob2->isGuiWidget()) {
		CPPUNIT_FAIL("This is NOT a gui widget!!");
	}
	delete blob2;
}

// tests the getWidgetTag function
/**
 * @page EssUA0016 EssUA0016 getWidgetTagT2
 * @anchor EssUA0016
 * @section purpose Purpose:
 * This test exercises getWidgetTag
 * method of the class ConData.
 *
 * @section initial Initial conditions: 
 * - An instance of ConData is created and initialised to be a gui textbox
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Execute blob->getWidgetTag(csWidgetTag)
 *
 * @section results Expected results:
 * - step 1 csWidgetTag = "widget"
 *
 */
void ConDataTest::getWidgetTagT2()
{
	ConData *blob = new ConData;
	CPoint point(0,0);
	CString csWidgetTag;
	
	// create a condata object for a gui widget
	blob->init("guitextbox_i", "", point, 1);
	blob->getWidgetTag(csWidgetTag);
	if (csWidgetTag != "widget") {
		CPPUNIT_FAIL("The widget tag is incorrect!!");
	}
	delete blob;
}

// tests the getScreenTag function
/**
 * @page EssUA0017 EssUA0017 getScreenTagT3
 * @anchor EssUA0017
 * @section purpose Purpose:
 * This test exercises getScreenTag
 * method of the class ConData.
 *
 * @section initial Initial conditions: 
 * - An instance of ConData is created and initialised to be a gui textbox
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Execute blob->getScreenTag(csScreenTag)
 *
 * @section results Expected results:
 * - step 1 csWidgetTag = "default"
 *
 */
void ConDataTest::getScreenTagT3()
{
	ConData *blob = new ConData;
	CPoint point(0,0);
	CString csScreenTag;
	
	// create a condata object for a gui widget
	blob->init("guitextbox_i", "", point, 1);
	blob->getScreenTag(csScreenTag);
	if (csScreenTag != "default") {
		CPPUNIT_FAIL("The screen tag is incorrect!!");
	}
	delete blob;
}