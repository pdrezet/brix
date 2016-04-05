#include "StdAfx.h"
#include "BlockPortLabelDialogTest.h"

// include HelperMacros to use CppUnit macros
#include <cppunit/extensions/HelperMacros.h>

#include "../LucidApplicationBuilder/BlockPortLabelDialog.h"

// global variable declared in CDrawProgApp
//extern char workDir[4096];

// register the test suite
CPPUNIT_TEST_SUITE_REGISTRATION( BlockPortLabelDialogTest );

/********************************* Test Suite definition *****************************************************/
/**
 * Constructor for the HandleCommands test suite.
 */
BlockPortLabelDialogTest::BlockPortLabelDialogTest(void)
{
	//strcpy(workDir, "..\\..\\..\\dist");
}

/**
 * Destructor for the HandleCommands test suite.
 */
BlockPortLabelDialogTest::~BlockPortLabelDialogTest(void)
{
}

/**
 * Called immediately before every test case to perform global setup activities.
 */
void BlockPortLabelDialogTest::setUp()
{
}

/**
 * Called immediately after every test case to perform global tear-down activities.
 */
void BlockPortLabelDialogTest::tearDown()
{
}

// tests the IsUnique method
/**
 * @page EssUA0026 EssUA0026 IsUniqueT1
 * @anchor EssUA0026
 * @section purpose Purpose:
 * This test exercises IsUnique
 * method of the class CBlockPortLabelDialog.
 *
 * @section initial Initial conditions: 
 * - 1 instance of ConData is created and initialised to be a 4 input mux
 * - 4 instances of ConData are created and initialised to be Xports
 * - Initialise the xport labels
 * - All ConData instances are added to the condata list in the dep object
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Set port label to "sam"
 * -# Execute dlg1.IsUnique()
 * -# Set port label to "i2"
 * -# Execute dlg1.IsUnique()
 * -# Set port label to "s3"
 * -# Execute dlg1.IsUnique()
 * -# Set port label to "o1"
 * -# Execute dlg1.IsUnique()
 * -# Set port label to "f1"
 * -# Execute dlg1.IsUnique()
 * -# Set XInput label to "sam"
 * -# Execute dlg1.IsUnique()
 * -# Set XInput label to "xs1"
 * -# Execute dlg1.IsUnique()
 * -# Set XStart label to "xo1"
 * -# Execute dlg1.IsUnique()
 * -# Set XOutput label to "xf1"
 * -# Execute dlg1.IsUnique()
 * -# Set XFinish label to "xi1"
 * -# Execute dlg1.IsUnique()
 *
 * @section results Expected results:
 * - step 2 returns TRUE
 * - step 4 returns FALSE
 * - step 6 returns FALSE
 * - step 8 returns FALSE
 * - step 10 returns FALSE
 * - step 12 returns TRUE
 * - step 14 returns FALSE
 * - step 16 returns FALSE
 * - step 18 returns FALSE
 * - step 20 returns FALSE
 *
 */
void BlockPortLabelDialogTest::IsUniqueT1()
{
	DEP *pDep = new DEP;
	ConData *blob = new ConData;
	CPoint point(0,0);
	CString csPortLabel;
	POSITION pos;

	blob->init("mux_4i", "", point, 1);
	blob->userDefined = 1;
	pDep->condata->AddTail(blob);
	pos = pDep->condata->GetHeadPosition();

	// check block ports are unique
	// "sam" is a unique port label
	CBlockPortLabelDialog dlg1("sam",blob,pDep);
	if (!dlg1.IsUnique()) {
		CPPUNIT_FAIL("The port label should be unique!!");
	}	
	// "i2" is not a unique input port label
	CBlockPortLabelDialog dlg2("i2",blob,pDep);
	if (dlg2.IsUnique()) {
		CPPUNIT_FAIL("The port label should not be unique!!");
	}
	// "s3" is not a unique start port label
	pDep->SetPortLabel(pos,2,STARTPORT,"s3");
	CBlockPortLabelDialog dlg3("s3",blob,pDep);
	if (dlg3.IsUnique()) {
		CPPUNIT_FAIL("The port label should not be unique!!");
	}
	// "o1" is not a unique output port label
	pDep->SetPortLabel(pos,0,OUTPUTPORT,"o1");
	CBlockPortLabelDialog dlg4("o1",blob,pDep);
	if (dlg4.IsUnique()) {
		CPPUNIT_FAIL("The port label should not be unique!!");
	}
	// "f1" is not a unique output port label
	pDep->SetPortLabel(pos,0,FINISHPORT,"f1");
	CBlockPortLabelDialog dlg5("f1",blob,pDep);
	if (dlg5.IsUnique()) {
		CPPUNIT_FAIL("The port label should not be unique!!");
	}

	// check Xports are unique
	ConData *xport1 = new ConData;
	ConData *xport2 = new ConData;
	ConData *xport3 = new ConData;
	ConData *xport4 = new ConData;

	xport1->init("XINPUTI", "", point, 1);
	xport2->init("XSTART", "", point, 1);
	xport3->init("XOUTPUTI", "", point, 1);
	xport4->init("XFINISH", "", point, 1);
	xport1->description = "xi1";
	xport2->description = "xs1";
	xport3->description = "xo1";
	xport4->description = "xf1";
	pDep->condata->AddTail(xport1);
	pDep->condata->AddTail(xport2);
	pDep->condata->AddTail(xport3);
	pDep->condata->AddTail(xport4);

	// "sam" is a unique port label
	CBlockPortLabelDialog dlg6("sam",xport1,pDep);
	if (!dlg6.IsUnique()) {
		CPPUNIT_FAIL("The port label should be unique!!");
	}	
	// xs1 is not a unique xinput port label
	CBlockPortLabelDialog dlg7("xs1",xport1,pDep);
	if (dlg7.IsUnique()) {
		CPPUNIT_FAIL("The port label should not be unique!!");
	}
	// xo1 is not a unique xstart port label
	CBlockPortLabelDialog dlg8("xo1",xport2,pDep);
	if (dlg8.IsUnique()) {
		CPPUNIT_FAIL("The port label should not be unique!!");
	}
	// xf1 is not a unique xoutput port label
	CBlockPortLabelDialog dlg9("xf1",xport3,pDep);
	if (dlg9.IsUnique()) {
		CPPUNIT_FAIL("The port label should not be unique!!");
	}
	// xi1 is not a unique xfinish port label
	CBlockPortLabelDialog dlg10("xi1",xport4,pDep);
	if (dlg10.IsUnique()) {
		CPPUNIT_FAIL("The port label should not be unique!!");
	}

	delete pDep;
}
