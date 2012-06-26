#include "stdafx.h"
#include "ProjectTest.h"

// include HelperMacros to use CppUnit macros
#include <cppunit/extensions/HelperMacros.h>

#include "../LucidApplicationBuilder/resource.h"
#include "DrawProgApp.h"
#include "../LucidApplicationBuilder/Project.h"
#include "../common/LucidConstants.h"
#include "TProjectMetaData.h"
//#include "../common/GuiWidget.h"

// register the test suite
CPPUNIT_TEST_SUITE_REGISTRATION( ProjectTest );

/********************************* Test Suite definition *****************************************************/
/**
 * Constructor for the HandleCommands test suite.
 */
ProjectTest::ProjectTest(void)
{
}

/**
 * Destructor for the HandleCommands test suite.
 */
ProjectTest::~ProjectTest(void)
{
}

/**
 * Called immediately before every test case to perform global setup activities.
 */
void ProjectTest::setUp()
{
}

/**
 * Called immediately after every test case to perform global tear-down activities.
 */
void ProjectTest::tearDown()
{
}

// tests the addGuiWidget function
/**
 * @page EssUA0011 EssUA0011 addGuiWidgetT1
 * @anchor EssUA0011
 * @section purpose Purpose:
 * This test exercises addGuiWidget
 * method of the class Project.
 *
 * @section initial Initial conditions: 
 * - An instance of TProjectMetaData is created
 * - An instance of Project is created
 * - The ProjectMetaData member in the Project instance is initialised 
 * - A ConData instance is created and initialised to a gui textbox widget
 * - A scond ConData instance is created and initialised to a gui textbox widget
 * - A third ConData instance is created and initialised to an accumulator
 * - A GuiWidget instance is created with a widget tag, "widget0", and a screen tag, "default"
 * - A second GuiWidget instance is created with a widget tag, "widget1", and a screen tag, "default"
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Execute addGuiWidget(blob1)
 * -# Execute guiWidgetInVec(widget1)
 * -# Execute addGuiWidget(blob2)
 * -# Execute guiWidgetInVec(widget1)
 * -# Execute addGuiWidget(blob3)
 * -# Execute getGuiWidgetVecSize(size)
 *
 * @section results Expected results:
 * - step 2 returns kErr_ProjectMetaData_WidgetScreenPairAlreadyPresent
 * - step 4 returns kErr_ProjectMetaData_WidgetScreenPairAlreadyPresent
 * - step 6 returns 0
 *
 */
void ProjectTest::addGuiWidgetT1()
{
	TProjectMetaData* pProjMData1 = new TProjectMetaData;
	ConData* blob1 = new ConData;
	ConData* blob2 = new ConData;
	Project proj;
	CPoint point(0,0);
	UINT size;

	proj.pProjMData = pProjMData1;	
	// create a condata object for a gui widget and check it gets added to project meta data
	blob1->init("guitextbox_i", "", point, 1);
	proj.addGuiWidget(blob1);
	GuiWidget widget1("widget0", "default");
	if (!proj.pProjMData->guiWidgetInVec(widget1)) {
		CPPUNIT_FAIL("Gui widget has not been added!!");
	}
	// check that a second gui widget is added with a unique widget tag
	blob2->init("guitextbox_i", "", point, 1);
	proj.addGuiWidget(blob2);
	GuiWidget widget2("widget1", "default");
	if (!proj.pProjMData->guiWidgetInVec(widget2)) {
		CPPUNIT_FAIL("Gui widget has not been added!!");
	}
	delete blob1;
	delete blob2;
	delete pProjMData1;

	// create a condata object that isnt a gui widget and check it doesn't get added to project meta data
	TProjectMetaData* pProjMData2 = new TProjectMetaData;
	ConData *blob3 = new ConData;

	proj.pProjMData = pProjMData2;
	blob3->init("operator_addacci", "", point, 1);
	proj.addGuiWidget(blob3);
	proj.pProjMData->getGuiWidgetVecSize(size);
	if (size != 0) {
		CPPUNIT_FAIL("Icon should not have been added to Project Meta Data!!");
	}
	delete blob3;
	//delete pProjMData2;
}

// tests the removeGuiWidget function
/**
 * @page EssUA0012 EssUA0012 removeGuiWidgetT2
 * @anchor EssUA0012
 * @section purpose Purpose:
 * This test exercises removeGuiWidget
 * method of the class Project.
 *
 * @section initial Initial conditions: 
 * - An instance of TProjectMetaData is created
 * - An instance of Project is created
 * - The ProjectMetaData member in the Project instance is initialised 
 * - A ConData instance is created and initialised to a gui textbox widget
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Execute addGuiWidget(blob1)
 * -# Execute removeGuiWidget(blob1)
 * -# Execute getGuiWidgetVecSize(size)
 *
 * @section results Expected results:
 * - step 3 returns 0
 *
 */
void ProjectTest::removeGuiWidgetT2()
{
	TProjectMetaData* pProjMData1 = new TProjectMetaData;
	ConData *blob1 = new ConData;
	Project proj;
	CPoint point(0,0);
	UINT size;

	proj.pProjMData = pProjMData1;	
	// create a condata object for a gui widget and check it gets added to project meta data
	blob1->init("guitextbox_i", "", point, 1);
	proj.addGuiWidget(blob1);
	proj.removeGuiWidget(blob1);
	proj.pProjMData->getGuiWidgetVecSize(size);
	if (size != 0) {
		CPPUNIT_FAIL("Gui widget has not been removed!!");
	}
	delete blob1;
}

// The following methods related to gui widgets cannot be tested because they use the CTreeCtrl class
// addPastedGuiWidgets
// uniquifyWidgetsInUserDefBlock
// removeWidgetsInUserDefBlock

// tests the depIsLoaded function
/**
 * @page EssUA0013 EssUA0013 depIsLoadedT3
 * @anchor EssUA0013
 * @section purpose Purpose:
 * This test exercises depIsLoaded
 * method of the class Project.
 *
 * @section initial Initial conditions: 
 * - An instance of Project is created
 * - An instance of DEP is created and assigned to the Project instance
 * - An instance of HTREEITEM is created, initialised and assigned to the DEP instance
 * - A second instance of HTREEITEM is created and initialised
 * - DEPNum is initialised to 1
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Execute depIsLoaded(hItem1)
 * -# Execute depIsLoaded(hItem2)
 *
 * @section results Expected results:
 * - step 1 returns a pointer to the DEP instance
 * - step 2 returns NULL
 *
 */
void ProjectTest::depIsLoadedT3()
{
	Project proj;
	ProjectMetaData* pProjMData = new ProjectMetaData;
	proj.pProjMData = pProjMData;
	HTREEITEM hItem1, hItem2;
	DEP* pDep = new DEP;

	// simulate hItem1 being loaded and hItem2 not loaded
	hItem1 = (HTREEITEM)1;
	proj.pDEP[0] = pDep;
	proj.pDEP[0]->hItem = hItem1;
	proj.DEPNum = 0;
	if (!proj.depIsLoaded(hItem1)) {
		CPPUNIT_FAIL("DEP should be loaded!!");
	}
	hItem2 = (HTREEITEM)2;
	if (proj.depIsLoaded(hItem2)) {
		CPPUNIT_FAIL("DEP should not be loaded!!");
	}
	delete pDep;
}
