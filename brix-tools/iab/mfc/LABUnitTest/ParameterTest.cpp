#include "StdAfx.h"
#include "ParameterTest.h"

// include HelperMacros to use CppUnit macros
#include <cppunit/extensions/HelperMacros.h>

#include "../LucidApplicationBuilder/Parameter.h"
#include "../common/LucidConstants.h"

// register the test suite
CPPUNIT_TEST_SUITE_REGISTRATION( ParameterTest );

/********************************* Test Suite definition *****************************************************/
/**
 * Constructor for the HandleCommands test suite.
 */
ParameterTest::ParameterTest(void)
{
}

/**
 * Destructor for the HandleCommands test suite.
 */
ParameterTest::~ParameterTest(void)
{
}

/**
 * Called immediately before every test case to perform global setup activities.
 */
void ParameterTest::setUp()
{
}

/**
 * Called immediately after every test case to perform global tear-down activities.
 */
void ParameterTest::tearDown()
{
}

// tests the isTextBox function
/**
 * @page EssUA0014 EssUA0014 isTextBoxT1
 * @anchor EssUA0014
 * @section purpose Purpose:
 * This test exercises isTextBox
 * method of the class Parameter.
 *
 * @section initial Initial conditions: 
 * - An instance of Parameter is created and initialised to be of type widget tag
 * - An second instance of Parameter is created and initialised to be of type screen tag
 * - A third instance of Parameter is created and initialised to be an enuerated type
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Execute IsTextbox()
 * -# Execute IsTextbox()
 * -# Execute IsTextbox()
 *
 * @section results Expected results:
 * - step 1 returns TRUE
 * - step 2 returns FALSE
 * - step 3 returns FALSE
 *
 */
void ParameterTest::isTextBoxT1()
{
	CStringArray* enumValArr1 = new CStringArray;
	CStringArray* enumLabelArr1 = new CStringArray;
	//Parameter(CString _name, int _dataType, CString _minRange, CString _maxRange, CString defaultVal, CString _description, CStringArray* _enumValArr, CStringArray* _enumLabelArr);
	// Check a parameter that is not enumerated is a text box.
	Parameter p1("Widget Tag", 5, "", "", "widget", "", enumValArr1, enumLabelArr1);
	if (!p1.IsTextbox()) {
		CPPUNIT_FAIL("This parameter should be a text box in the property dialog!!");
	}
	// Check a screen tag parameter is NOT a text box
	CStringArray* enumValArr2 = new CStringArray;
	CStringArray* enumLabelArr2 = new CStringArray;
	Parameter p2("Screen Tag", 4, "", "", "default", "", enumValArr2, enumLabelArr2);
	if (p2.IsTextbox()) {
		CPPUNIT_FAIL("This parameter is not a text box in the property dialog!!");
	}
	// Check an enumerated parameter is NOT a text box
	CStringArray* enumValArr3 = new CStringArray;
	CStringArray* enumLabelArr3 = new CStringArray;
	enumValArr3->Add("64");
	enumLabelArr3->Add("red");
	Parameter p3("Colour", 1, "", "", "default", "64", enumValArr3, enumLabelArr3);
	if (p3.IsTextbox()) {
		CPPUNIT_FAIL("This parameter is not a text box in the property dialog!!");
	}
}