#include "StdAfx.h"
#include "EncapsulationTest.h"

// include HelperMacros to use CppUnit macros
#include <cppunit/extensions/HelperMacros.h>

#include "../LucidApplicationBuilder/condat.h"
#include "../LucidApplicationBuilder/resource.h"
#include "../LucidApplicationBuilder/Encapsulation.h"

// global variable declared in CDrawProgApp
//extern char workDir[4096];

// register the test suite
CPPUNIT_TEST_SUITE_REGISTRATION( EncapsulationTest );

/********************************* Test Suite definition *****************************************************/
/**
 * Constructor for the HandleCommands test suite.
 */
EncapsulationTest::EncapsulationTest(void)
{
	//strcpy(workDir, "..\\..\\..\\dist");
}

/**
 * Destructor for the HandleCommands test suite.
 */
EncapsulationTest::~EncapsulationTest(void)
{
}

/**
 * Called immediately before every test case to perform global setup activities.
 */
void EncapsulationTest::setUp()
{
}

/**
 * Called immediately after every test case to perform global tear-down activities.
 */
void EncapsulationTest::tearDown()
{
}

// tests the repositionEncapsulated method
/**
 * @page EssUA0019 EssUA0019 repositionEncapsulatedT1
 * @anchor EssUA0019
 * @section purpose Purpose:
 * This test exercises repositionEncapsulated
 * method of the class Encapsulation.
 *
 * @section initial Initial conditions: 
 * - An instance of ConData is created and initialised to be a gui textbox with coords (333,444)
 * - An instance of CObList is created, and the ConData object is added
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Execute encap.repositionEncapsulated()
 * -# blob1->GetIconPos()
 *
 * @section results Expected results:
 * - returns (150, 25)
 *
 */
void EncapsulationTest::repositionEncapsulatedT1()
{
	Encapsulation encap;
	CObList* encapsulated = new CObList;
	ConData *blob1 = new ConData;
	CPoint point(333,444), newpoint;
	
	// create a condata object and add it to the encapsulated list
	blob1->init("guitextbox_i", "", point, 1);
	encap.encapsulated = encapsulated;
	encap.encapsulated->AddTail(blob1);
	encap.repositionEncapsulated();
	newpoint = blob1->GetIconPos();
	if (newpoint.x != ENCAPS_XPOS && newpoint.y != ENCAPS_YPOS) {
		CPPUNIT_FAIL("This encapsulated icon has not been repositioned correctly!!");
	}
	delete blob1;
	delete encapsulated;
}

// tests the GetFirstPortYCoord method
/**
 * @page EssUA0021 EssUA0021 repositionEncapsulatedT1
 * @anchor EssUA0021
 * @section purpose Purpose:
 * This test exercises GetFirstPortYCoord
 * method of the class Encapsulation.
 *
 * @section initial Initial conditions: 
 * - An instance of CObList is created
 * - 3 instances of ConData are created
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Execute encap.GetFirstPortYCoord()
 * -# An instance of ConData is initialised to be a xstart port
 * -# This instance is added to the CObList instance
 * -# Execute encap.GetFirstPortYCoord()
 * -# 2 instances of ConData are initialised to be xfinish ports
 * -# Both instances are added to the CObList instance
 * -# Execute encap.GetFirstPortYCoord()
 *
 * @section results Expected results:
 * - step 1 returns 15
 * - step 2 returns 30
 * - step 3 returns 45
 *
 */
void EncapsulationTest::getFirstPortYCoordT2()
{
	Encapsulation encap;
	CObList* encapsulated = new CObList;
	ConData *blob1 = new ConData;
	ConData *blob2 = new ConData;
	ConData *blob3 = new ConData;
	CPoint point(0,0);

	encap.encapsulated = encapsulated;
	// check ycoord if there are no start or finish xports
	if (encap.GetFirstPortYCoord() != 15) {
		CPPUNIT_FAIL("The first port y coordinate is incorrect!!");
	}

	// check ycoord when there is 1 Xstart port
	blob1->init("XSTART", "", point, 1);
	encap.encapsulated->AddTail(blob1);
	if (encap.GetFirstPortYCoord() != 30) {
		CPPUNIT_FAIL("The first port y coordinate is incorrect!!");
	}

	// check ycoord when there are 1 Xstart port and 2 Xfinish ports
	blob2->init("XFINISH", "", point, 1);
	encap.encapsulated->AddTail(blob2);
	blob3->init("XFINISH", "", point, 1);
	encap.encapsulated->AddTail(blob3);
	if (encap.GetFirstPortYCoord() != 45) {
		CPPUNIT_FAIL("The first port y coordinate is incorrect!!");
	}

	delete blob1;
	delete blob2;
	delete blob3;
	delete encapsulated;
}