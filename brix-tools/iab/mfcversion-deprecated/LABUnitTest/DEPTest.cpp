#include "StdAfx.h"
#include "DEPTest.h"

// include HelperMacros to use CppUnit macros
#include <cppunit/extensions/HelperMacros.h>

#include "../LucidApplicationBuilder/condat.h"
//#include "../LucidApplicationBuilder/resource.h"
#include "../LucidApplicationBuilder/DEP.h"

// global variable declared in CDrawProgApp
//extern char workDir[4096];

// register the test suite
CPPUNIT_TEST_SUITE_REGISTRATION( DEPTest );

/********************************* Test Suite definition *****************************************************/
/**
 * Constructor for the HandleCommands test suite.
 */
DEPTest::DEPTest(void)
{
	//strcpy(workDir, "..\\..\\..\\dist");
}

/**
 * Destructor for the HandleCommands test suite.
 */
DEPTest::~DEPTest(void)
{
}

/**
 * Called immediately before every test case to perform global setup activities.
 */
void DEPTest::setUp()
{
}

/**
 * Called immediately after every test case to perform global tear-down activities.
 */
void DEPTest::tearDown()
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
void DEPTest::getInitScrollPosT1()
{
	DEP dep;
	ConData *blob1 = new ConData;
	ConData *blob2 = new ConData;
	CPoint point, point2, point3, scrollPos;
	CRect clientRect(0,0,100,100);
	
	// get scroll pos when there are no icons
	scrollPos = dep.getInitScrollPos(clientRect);
	if (scrollPos.x != -1 && scrollPos.y != -1) {
		CPPUNIT_FAIL("The initial scroll position is incorrect!!");
	}
	// get scroll pos when there is one icon
	point.SetPoint(333,444);
	blob1->init("guitextbox_i", "", point, 1);
	dep.condata->AddTail(blob1);
	scrollPos = dep.getInitScrollPos(clientRect);
	if (scrollPos.x != (point.x - INIT_SCROLL_LEFT_MARGIN) && scrollPos.y != (point.y - INIT_SCROLL_TOP_MARGIN)) {
		CPPUNIT_FAIL("The initial scroll position is incorrect!!");
	}
	// get scroll pos when there are 2 icons that fit in the client view and the one is to the right and above the other
	point2.SetPoint(300,460);
	blob2->init("guitextbox_i", "", point2, 1);
	dep.condata->AddTail(blob2);
	scrollPos = dep.getInitScrollPos(clientRect);
	if (scrollPos.x != (point2.x - INIT_SCROLL_LEFT_MARGIN) && scrollPos.y != (point.y - INIT_SCROLL_TOP_MARGIN)) {
		CPPUNIT_FAIL("The initial scroll position is incorrect!!");
	}
	// get scroll pos when there are 2 icons, that don't fit in the client view together
	dep.condata->RemoveTail();
	delete blob2;
	ConData *blob3 = new ConData;
	point3.SetPoint(200,460);
	blob3->init("guitextbox_i", "", point3, 1);
	dep.condata->AddTail(blob3);
	scrollPos = dep.getInitScrollPos(clientRect);
	if (scrollPos.x != (point3.x - INIT_SCROLL_LEFT_MARGIN) && scrollPos.y != (point3.y - INIT_SCROLL_TOP_MARGIN)) {
		CPPUNIT_FAIL("The initial scroll position is incorrect!!");
	}
}

// tests the getPortLabel method
/**
 * @page EssUA0023 EssUA0023 getPortLabelT2
 * @anchor EssUA0023
 * @section purpose Purpose:
 * This test exercises getPortLabel
 * method of the class DEP.
 *
 * @section initial Initial conditions: 
 * - 1 instance of ConData is created and initialised to be a 4 input mux
 * - It is added to the condata list in the dep object
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Execute dep.GetPortLabel(pos,1,INPUTPORT)
 * -# Set the third start port label to "s3"
 * -# Execute dep.GetPortLabel(pos,2,STARTPORT)
 * -# Set the first output port label to "o1"
 * -# Execute dep.GetPortLabel(pos,0,OUTPUTPORT)
 * -# Set the first finish port label to "f1"
 * -# Execute dep.GetPortLabel(pos,0,FINISHPORT)
 *
 * @section results Expected results:
 * - step 1 returns "i2"
 * - step 3 returns "s3"
 * - step 5 returns "o1"
 * - step 7 returns "f1"
 *
 */
void DEPTest::getPortLabelT2()
{
	DEP dep;
	ConData *blob1 = new ConData;
	CPoint point(0,0);
	POSITION pos;
	CString csPortLabel;

	blob1->init("mux_4i", "", point, 1);
	dep.condata->AddTail(blob1);
	pos = dep.condata->GetHeadPosition();
	
	// check that the second input port is "i2"
	csPortLabel = dep.GetPortLabel(pos,1,INPUTPORT);
	if (csPortLabel != "i2") {
		CPPUNIT_FAIL("The input port label is incorrect!!");
	}

	//check that the third start port is "s3"
	dep.SetPortLabel(pos,2,STARTPORT,"s3");
	csPortLabel = dep.GetPortLabel(pos,2,STARTPORT);
	if (csPortLabel != "s3") {
		CPPUNIT_FAIL("The start port label is incorrect!!");
	}

	//check that the first output port is "o1"
	dep.SetPortLabel(pos,0,OUTPUTPORT,"o1");
	csPortLabel = dep.GetPortLabel(pos,0,OUTPUTPORT);
	if (csPortLabel != "o1") {
		CPPUNIT_FAIL("The output port label is incorrect!!");
	}

	//check that the first finish port is "f1"
	dep.SetPortLabel(pos,0,FINISHPORT,"f1");
	csPortLabel = dep.GetPortLabel(pos,0,FINISHPORT);
	if (csPortLabel != "f1") {
		CPPUNIT_FAIL("The finish port label is incorrect!!");
	}

	dep.condata->RemoveTail();
	delete blob1;
}

// tests the SetPortLabel method
/**
 * @page EssUA0024 EssUA0024 setPortLabelT3
 * @anchor EssUA0024
 * @section purpose Purpose:
 * This test exercises SetPortLabel
 * method of the class DEP.
 *
 * @section initial Initial conditions: 
 * - 1 instance of ConData is created and initialised to be a 4 input mux
 * - It is added to the condata list in the dep object
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Execute dep.SetPortLabel(pos,2,INPUTPORT,"in2")
 * -# Get the second input port label
 * -# Execute dep.SetPortLabel(pos,2,STARTPORT,"s3")
 * -# Get the third start port label
 * -# Execute dep.SetPortLabel(pos,0,OUTPUTPORT,"o1")
 * -# Get the first output port label
 * -# Execute dep.SetPortLabel(pos,0,FINISHPORT,"f1")
 * -# Get the first finish port label
 *
 * @section results Expected results:
 * - step 2 returns "in2"
 * - step 4 returns "s3"
 * - step 6 returns "o1"
 * - step 8 returns "f1"
 *
 */

void DEPTest::setPortLabelT3()
{
	DEP dep;
	ConData *blob1 = new ConData;
	CPoint point(0,0);
	POSITION pos;
	CString csPortLabel;

	blob1->init("mux_4i", "", point, 1);
	dep.condata->AddTail(blob1);
	pos = dep.condata->GetHeadPosition();
	
	// set the second input port to "in2"
	dep.SetPortLabel(pos,1,INPUTPORT,"in2");
	csPortLabel = dep.GetPortLabel(pos,1,INPUTPORT);
	if (csPortLabel != "in2") {
		CPPUNIT_FAIL("The input port label is incorrect!!");
	}

	//set the third start port to "s3"
	dep.SetPortLabel(pos,2,STARTPORT,"s3");
	csPortLabel = dep.GetPortLabel(pos,2,STARTPORT);
	if (csPortLabel != "s3") {
		CPPUNIT_FAIL("The start port label is incorrect!!");
	}

	//set the first output port to "o1"
	dep.SetPortLabel(pos,0,OUTPUTPORT,"o1");
	csPortLabel = dep.GetPortLabel(pos,0,OUTPUTPORT);
	if (csPortLabel != "o1") {
		CPPUNIT_FAIL("The output port label is incorrect!!");
	}

	//set the first finish port to "f1"
	dep.SetPortLabel(pos,0,FINISHPORT,"f1");
	csPortLabel = dep.GetPortLabel(pos,0,FINISHPORT);
	if (csPortLabel != "f1") {
		CPPUNIT_FAIL("The finish port label is incorrect!!");
	}

	dep.condata->RemoveTail();
	delete blob1;
}

// tests the seond SetPortLabel method
/**
 * @page EssUA0025 EssUA0025 setPortLabelT4
 * @anchor EssUA0025
 * @section purpose Purpose:
 * This test exercises the seond SetPortLabel
 * method of the class DEP.
 *
 * @section initial Initial conditions: 
 * - 1 instance of ConData is created and initialised to be a 4 input mux
 * - It is added to the condata list in the dep object
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Execute dep.SetPortLabel("mux_4i","i2","in2")
 * -# Get the second input port label
 * -# Execute dep.SetPortLabel("mux_4i","s3","start3")
 * -# Get the third start port label
 * -# Execute dep.SetPortLabel("mux_4i","o1","out1")
 * -# Get the first output port label
 * -# Execute dep.SetPortLabel("mux_4i","f1","finish1")
 * -# Get the first finish port label
 *
 * @section results Expected results:
 * - step 2 returns "in2"
 * - step 4 returns "start3"
 * - step 6 returns "out1"
 * - step 8 returns "finish1"
 *
 */
void DEPTest::setPortLabelT4()
{
	DEP dep;
	ConData *blob1 = new ConData;
	CPoint point(0,0);
	CString csPortLabel;
	POSITION pos;

	blob1->init("mux_4i", "", point, 1);
	blob1->description = "mux_4i";
	dep.condata->AddTail(blob1);
	pos = dep.condata->GetHeadPosition();
	
	// set the second input port to "in2"
	dep.SetPortLabel("mux_4i","i2","in2");
	csPortLabel = dep.GetPortLabel(pos,1,INPUTPORT);
	if (csPortLabel != "in2") {
		CPPUNIT_FAIL("The input port label is incorrect!!");
	}

	//set the third start port is "start3"
	dep.SetPortLabel(pos,2,STARTPORT,"s3");
	dep.SetPortLabel("mux_4i","s3","start3");
	csPortLabel = dep.GetPortLabel(pos,2,STARTPORT);
	if (csPortLabel != "start3") {
		CPPUNIT_FAIL("The start port label is incorrect!!");
	}

	//set the first output port to "out1"
	dep.SetPortLabel(pos,0,OUTPUTPORT,"o1");
	dep.SetPortLabel("mux_4i","o1","out1");
	csPortLabel = dep.GetPortLabel(pos,0,OUTPUTPORT);
	if (csPortLabel != "out1") {
		CPPUNIT_FAIL("The output port label is incorrect!!");
	}

	//set the first finish port is "finish1"
	dep.SetPortLabel(pos,0,FINISHPORT,"f1");
	dep.SetPortLabel("mux_4i","f1","finish1");
	csPortLabel = dep.GetPortLabel(pos,0,FINISHPORT);
	if (csPortLabel != "finish1") {
		CPPUNIT_FAIL("The finish port label is incorrect!!");
	}

	dep.condata->RemoveTail();
	delete blob1;
}


// tests the IsOutputPortConnected method
/**
 * @page EssUA0027 EssUA0027 IsOutputPortConnectedT5
 * @anchor EssUA0027
 * @section purpose Purpose:
 * This test exercises the IsOutputPortConnected
 * method of the class DEP.
 *
 * @section initial Initial conditions: 
 * - 2 instances of ConData are created and initialised to be a 2 input demux and a 2 input mux
 * - They are added to the condata list in the dep object
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Connect the second output of blob1 to the second input of blob2
 * -# Execute dep.IsOutputPortConnected(blob1, 0)
 * -# Disconnect the second output of blob1 from the second input of blob2
 * -# Connect the first output of blob1 to the first input of blob2
 * -# Execute dep.IsOutputPortConnected(blob1, 0)
 *
 * @section results Expected results:
 * - step 2 returns FALSE
 * - step 5 returns TRUE
 *
 */
void DEPTest::isOutputPortConnectedT5()
{
	DEP dep;
	ConData *blob1 = new ConData;
	ConData *blob2 = new ConData;
	CPoint point(0,0);

	blob1->init("demux_2i", "", point, 1);
	dep.condata->AddTail(blob1);
	blob2->init("mux_2i", "", point, 1);
	dep.condata->AddTail(blob2);
	
	// connect the second output of blob1 to the second input of blob2
	blob1->identnum = 0;
	blob2->identnum = 1;
	blob2->inputport[1]->line.othericonid = 0;
	blob2->inputport[1]->line.exist = 1;
	blob2->inputport[1]->line.otherportno = 1;
	// check if the first output of blob1 is connected
	if (dep.IsOutputPortConnected(blob1, 0)) {
		CPPUNIT_FAIL("The output port should not be connected!!");
	}

	// disconnect the second output of blob1 from the second input of blob2
	blob2->inputport[1]->line.othericonid = 2;
	blob2->inputport[1]->line.exist = 0;
	blob2->inputport[1]->line.otherportno = 3;
	// connect the first output of blob1 to the first input of blob2
	blob2->inputport[0]->line.othericonid = 0;
	blob2->inputport[0]->line.exist = 1;
	blob2->inputport[0]->line.otherportno = 0;
	// check if the first output of blob1 is connected
	if (!dep.IsOutputPortConnected(blob1, 0)) {
		CPPUNIT_FAIL("The output port should be connected!!");
	}

	dep.condata->RemoveAll();
	delete blob1;
	delete blob2;
}

// tests the IsFinishPortConnected method
/**
 * @page EssUA0028 EssUA0028 IsFinishPortConnectedT6
 * @anchor EssUA0028
 * @section purpose Purpose:
 * This test exercises the IsFinishPortConnected
 * method of the class DEP.
 *
 * @section initial Initial conditions: 
 * - 2 instances of ConData are created and initialised to be a 2 input demux and a 2 input mux
 * - They are added to the condata list in the dep object
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Connect the second finish port of blob1 to the second start port of blob2
 * -# Execute dep.IsFinishPortConnected(blob1, 0)
 * -# Disconnect the second finish port of blob1 from the second start port of blob2
 * -# Connect the first finish port of blob1 to the first start port of blob2
 * -# Execute dep.IsFinishPortConnected(blob1, 0)
 *
 * @section results Expected results:
 * - step 2 returns FALSE
 * - step 5 returns TRUE
 *
 */

void DEPTest::isFinishPortConnectedT6()
{
	DEP dep;
	ConData *blob1 = new ConData;
	ConData *blob2 = new ConData;
	CPoint point(0,0);

	blob1->init("demux_2i", "", point, 1);
	dep.condata->AddTail(blob1);
	blob2->init("mux_2i", "", point, 1);
	dep.condata->AddTail(blob2);
	
	// connect the second finish port of blob1 to the second start port of blob2
	blob1->identnum = 0;
	blob2->identnum = 1;
	blob2->startport[1]->line.othericonid = 0;
	blob2->startport[1]->line.exist = 1;
	blob2->startport[1]->line.otherportno = 1;
	// check if the first finish port of blob1 is connected
	if (dep.IsFinishPortConnected(blob1, 0)) {
		CPPUNIT_FAIL("The finish port should not be connected!!");
	}

	// disconnect the second finish port of blob1 from the second start port of blob2
	blob2->inputport[1]->line.othericonid = 2;
	blob2->inputport[1]->line.exist = 0;
	blob2->inputport[1]->line.otherportno = 3;
	// connect the first finish port of blob1 to the first start port of blob2
	blob2->startport[0]->line.othericonid = 0;
	blob2->startport[0]->line.exist = 1;
	blob2->startport[0]->line.otherportno = 0;
	// check if the first finish port of blob1 is connected
	if (!dep.IsFinishPortConnected(blob1, 0)) {
		CPPUNIT_FAIL("The finish port should be connected!!");
	}

	dep.condata->RemoveAll();
	delete blob1;
	delete blob2;
}

// tests the RemoveConnectedInputTags method
/**
 * @page EssUA0029 EssUA0029 removeConnectedInputTagsT7
 * @anchor EssUA0029
 * @section purpose Purpose:
 * This test exercises the RemoveConnectedInputTags
 * method of the class DEP.
 *
 * @section initial Initial conditions: 
 * - 2 instances of ConData are created and initialised to be a 2 input demux and a 2 input mux
 * - They are added to the condata list in the dep object
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Connect the second output of blob1 to the second input of blob2 using the tag "xyz"
 * -# Execute dep.RemoveConnectedInputTags(blob1, 0)
 * -# Disconnect the second output of blob1 from the second input of blob2
 * -# Connect the first output of blob1 to the first input of blob2 using the tag "abc"
 * -# Execute dep.RemoveConnectedInputTags(blob1, 0)
 *
 * @section results Expected results:
 * - step 2 blob2->inputport[1]->tag = "xyz"
 * - step 5 blob2->inputport[0]->tag = ""
 *
 */
void DEPTest::removeConnectedInputTagsT7()
{
	DEP dep;
	ConData *blob1 = new ConData;
	ConData *blob2 = new ConData;
	CPoint point(0,0);

	blob1->init("demux_2i", "", point, 1);
	dep.condata->AddTail(blob1);
	blob2->init("mux_2i", "", point, 1);
	dep.condata->AddTail(blob2);
	
	// connect the second output of blob1 to the second input of blob2 using the tag "xyz"
	blob1->identnum = 0;
	blob2->identnum = 1;
	blob2->inputport[1]->line.othericonid = 0;
	blob2->inputport[1]->line.exist = 1;
	blob2->inputport[1]->line.otherportno = 1;
	blob2->inputport[1]->tag = "xyz";
	dep.RemoveConnectedInputTags(blob1, 0);
	// check if the second input tag of blob2 is removed
	if (blob2->inputport[1]->tag != "xyz") {
		CPPUNIT_FAIL("The second input port tag should not be removed!!");
	}
	
	// disconnect the second output of blob1 from the second input of blob2
	blob2->inputport[1]->line.othericonid = 2;
	blob2->inputport[1]->line.exist = 0;
	blob2->inputport[1]->line.otherportno = 3;
	// connect the first output of blob1 to the first input of blob2 using the tag "abc"
	blob2->inputport[0]->line.othericonid = 0;
	blob2->inputport[0]->line.exist = 1;
	blob2->inputport[0]->line.otherportno = 0;
	blob2->inputport[0]->tag = "abc";
	// check if the first input tag of blob2 is removed
	dep.RemoveConnectedInputTags(blob1, 0);
	if (blob2->inputport[0]->tag != "") {
		CPPUNIT_FAIL("The first input port tag should be removed!!");
	}
	
	dep.condata->RemoveAll();
	delete blob1;
	delete blob2;
}

// tests the RemoveConnectedStartTags method
/**
 * @page EssUA0030 EssUA0030 removeConnectedStartTagsT8
 * @anchor EssUA0030
 * @section purpose Purpose:
 * This test exercises the RemoveConnectedStartTags
 * method of the class DEP.
 *
 * @section initial Initial conditions: 
 * - 2 instances of ConData are created and initialised to be a 2 input demux and a 2 input mux
 * - They are added to the condata list in the dep object
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Connect the second finish port of blob1 to the second start port of blob2 using the tag "xyz"
 * -# Execute dep.RemoveConnectedStartTags(blob1, 0)
 * -# Disconnect the second finish port of blob1 from the second start port of blob2
 * -# Connect the first finish port of blob1 to the first start port of blob2 using the tag "abc"
 * -# Execute dep.RemoveConnectedStartTags(blob1, 0)
 *
 * @section results Expected results:
 * - step 2 blob2->startport[1]->tag = "xyz"
 * - step 5 blob2->startport[0]->tag = ""
 *
 */
void DEPTest::removeConnectedStartTagsT8()
{
	DEP dep;
	ConData *blob1 = new ConData;
	ConData *blob2 = new ConData;
	CPoint point(0,0);

	blob1->init("demux_2i", "", point, 1);
	dep.condata->AddTail(blob1);
	blob2->init("mux_2i", "", point, 1);
	dep.condata->AddTail(blob2);
	
	// connect the second output of blob1 to the second input of blob2 using the tag "xyz"
	blob1->identnum = 0;
	blob2->identnum = 1;
	blob2->startport[1]->line.othericonid = 0;
	blob2->startport[1]->line.exist = 1;
	blob2->startport[1]->line.otherportno = 1;
	blob2->startport[1]->tag = "xyz";
	dep.RemoveConnectedStartTags(blob1, 0);
	// check if the second start port tag of blob2 is removed
	if (blob2->startport[1]->tag != "xyz") {
		CPPUNIT_FAIL("The second start port tag should not be removed!!");
	}
	
	// disconnect the second finish port of blob1 from the second start port of blob2
	blob2->startport[1]->line.othericonid = 2;
	blob2->startport[1]->line.exist = 0;
	blob2->startport[1]->line.otherportno = 3;
	// connect the first finish port of blob1 to the first start port of blob2 using the tag "abc"
	blob2->startport[0]->line.othericonid = 0;
	blob2->startport[0]->line.exist = 1;
	blob2->startport[0]->line.otherportno = 0;
	blob2->startport[0]->tag = "abc";
	// check if the first start port tag of blob2 is removed
	dep.RemoveConnectedStartTags(blob1, 0);
	if (blob2->startport[0]->tag != "") {
		CPPUNIT_FAIL("The first satrt port tag should be removed!!");
	}
	
	dep.condata->RemoveAll();
	delete blob1;
	delete blob2;
}
