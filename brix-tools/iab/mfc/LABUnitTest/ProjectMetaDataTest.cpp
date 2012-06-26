#include "StdAfx.h"
#include "ProjectMetaDataTest.h"
#include <direct.h>

// include HelperMacros to use CppUnit macros
#include <cppunit/extensions/HelperMacros.h>

#include "../common/ProjectMetaData.h"
#include "../common/revision.h"
#include "../LucidApplicationBuilder/FileOperations.h"
#include "../common/LucidConstants.h"
#include "TProjectMetaData.h"
//#include "../LucidTools/ExternalTest/tester.h"

// global variable declared in CDrawProgApp
//extern char workDir[4096];

// register the test suite
CPPUNIT_TEST_SUITE_REGISTRATION( ProjectMetaDataTest );

/********************************* Test Suite definition *****************************************************/
/**
 * Constructor for the HandleCommands test suite.
 */
ProjectMetaDataTest::ProjectMetaDataTest(void)
{
	/* write the revision ID to a file */
	FILE* fVersion = fopen("version.txt","w");
	if (fVersion)
	{
		fprintf(fVersion,"%s",EHS_REVISION_ID);
		fclose(fVersion);
	}
}

/**
 * Destructor for the HandleCommands test suite.
 */
ProjectMetaDataTest::~ProjectMetaDataTest(void)
{
}

/**
 * Called immediately before every test case to perform global setup activities.
 */
void ProjectMetaDataTest::setUp()
{
}

/**
 * Called immediately after every test case to perform global tear-down activities.
 */
void ProjectMetaDataTest::tearDown()
{
}

// Check a valid folder structure
/**
 * @page EssUA0001 EssUA0001 folderStructureNotOkT1
 * @anchor EssUA0001
 * @section purpose Purpose:
 * This test exercises folderStructureNotOk
 * method of the class ProjectMetaData.
 *
 * @section initial Initial conditions: 
 * - An instance of ProjectMetaData is created
 * - The project name is set to T1
 * - The project dir is set to ..\\LABUnitTest\\TestData\\ProjectMetaData\\T1
 * - Create the project folder T1

 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Execute folderStructureNotOk(T1)
 * -# Delete DEP folder
 * -# Execute folderStructureNotOk(T1)
 * -# Delete project folder T1
 * -# Create project folder T1
 * -# Delete GUI folder
 * -# Execute folderStructureNotOk(T1)
 * -# Delete project folder T1
 * -# Create project folder T1
 * -# Delete data folder
 * -# Execute folderStructureNotOk(T1)
 * -# Delete project folder T1
 * -# Create project folder T1
 * -# Delete export folder
 * -# Execute folderStructureNotOk(T1)
 * -# Delete project folder T1
 * -# Create project folder T1
 * -# Delete SODL folder
 * -# Execute folderStructureNotOk(T1)
 *
 * @section results Expected results:
 * - step 1 returns no error
 * - step 3 returns an error
 * - step 7 returns an error
 * - step 11 returns an error
 * - step 15 returns an error
 * - step 19 returns an error
 *
 */
void ProjectMetaDataTest::folderStructureNotOkT1()
{
	TProjectMetaData projMData;
	CString csProjectDir;
	CFileOperation fo;

	projMData.setProjectName("T1");
	csProjectDir = "..\\..\\LABUnitTest\\TestData\\ProjectMetaData\\T1";
	projMData.setProjectDir(csProjectDir);
	fo.Delete(csProjectDir);
	projMData.createFolderStructure();
	if (projMData.folderStructureNotOk()) {
		CPPUNIT_FAIL("Folder structure should be ok in this case!!");
	}
	// Check the function does not return 0 when the folder structure is not ok
	// DEP folder is missing	
	fo.Delete(csProjectDir + DEPDIR);
	if (!projMData.folderStructureNotOk()) {
		CPPUNIT_FAIL("Folder structure should NOT be ok in this case!!");
	}
	// GUI folder is missing
	fo.Delete(csProjectDir);
	projMData.createFolderStructure();
	fo.Delete(csProjectDir + GUIDIR);
	if (!projMData.folderStructureNotOk()) {
		CPPUNIT_FAIL("Folder structure should NOT be ok in this case!!");
	}
	// data folder is missing
	fo.Delete(csProjectDir);
	projMData.createFolderStructure();
	fo.Delete(csProjectDir + DDATADIR);
	if (!projMData.folderStructureNotOk()) {
		CPPUNIT_FAIL("Folder structure should NOT be ok in this case!!");
	}
	// export folder is missing	
	fo.Delete(csProjectDir);
	projMData.createFolderStructure();
	fo.Delete(csProjectDir + EXPORTDIR);
	if (!projMData.folderStructureNotOk()) {
		CPPUNIT_FAIL("Folder structure should NOT be ok in this case!!");
	}
	// SODL folder is missing	
	//fo.Delete(csProjectDir);
	//projMData.createFolderStructure();
	//fo.Delete(csProjectDir + SODLDIR);
	//if (!projMData.folderStructureNotOk(csProjectDir)) {
	//	CPPUNIT_FAIL("Folder structure should NOT be ok in this case!!");
	//}
}

// Checks that an error is reported when the project dir is invalid
/**
 * @page EssUA0002 readProjectFileT2
 * @anchor EssUA0002
 * @section purpose Purpose:
 * This test exercises readProjectFile
 * method of the class ProjectMetaData.
 *
 * @section initial Initial conditions: 
 * - 2 instances of TProjectMetaData are created
 * - Project name is set to T2
 * - Project dir is set to ..\\LABUnitTest\\TestData\\ProjectMetaData\\T2
 * - Project folder T2 is created
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Execute setProjectRootDir("C:\\Lucid Projects")
 * -# Execute writeProjectFileAs(csProjectPathName)
 * -# Execute readProjectFile(T2)
 *
 * @section results Expected results:
 * - returns kErr_InvalidProjectDir
 *
 */
void ProjectMetaDataTest::readProjectFileT2()
{
	TProjectMetaData wrProjMData;
	TProjectMetaData rdProjMData;
	CString csProjectDir, csProjectPathName;
	CFileOperation fo;

	wrProjMData.setProjectName("T2");
	csProjectDir = "..\\..\\LABUnitTest\\TestData\\ProjectMetaData\\T2";
	wrProjMData.setProjectDir(csProjectDir);
	fo.Delete(csProjectDir);
	wrProjMData.createFolderStructure();
	// Set incorrect project dir
	wrProjMData.setProjectDir("C:\\Lucid Projects");
	csProjectPathName = csProjectDir + "\\T2.lpj";
	wrProjMData.writeProjectFileAs(csProjectPathName);

	if (rdProjMData.readProjectFile("..\\LABUnitTest\\TestData\\ProjectMetaData\\T2\\T2.lpj") != kErr_InvalidProjectDir) {
		CPPUNIT_FAIL("An invalid project dir error should have been reported!!");
	}
}

// Check a project file is written ok
/**
 * @page EssUA0003 writeProjectFileT3
 * @anchor EssUA0003
 * @section purpose Purpose:
 * This test exercises writeProjectFile and readProjectFile
 * methods of the class ProjectMetaData.
 *
 * @section initial Initial conditions: 
 * - An instance of ProjectMetaData is created
 * - Project name is set to T3
 * - Project dir is set to ..\\LABUnitTest\\TestData\\ProjectMetaData\\T3
 * - Project folder T3 is created
 * - default group is created
 * - data file T3.txt is added
 * - gui file T3.gui is added
 * - bmp file T3.bmp is added
 * - widget("T3 widget", "T3 screen") is added
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Execute writeProjectFile()
 * -# Execute readProjectFile(T3.lpj)
 *
 * @section results Expected results:
 * - project name is T3
 * - project root dir is ..\\LABUnitTest\\TestData\\ProjectMetaData
 * - group name is Default
 * - group period is 100000
 * - group allocation is 90000
 * - group id is 1
 * - GUI host filename is T3.gui
 * - GUI target filename is g0000000.gui
 * - BMP host filename is T3.bmp
 * - BMP target filename is b0000000.bmp
 * - Data host filename is T3.txt
 * - Data target filename is d0000000.txt
 * - widget is widget("T3 widget", "T3 screen")
 *
 */
void ProjectMetaDataTest::writeProjectFileT3()
{
	TProjectMetaData wrProjMData;
	TProjectMetaData rdProjMData;
	CString csProjectDir;
	CFileOperation fo;
	ExtDataFile dataFile;
	GuiFileEssentialData_t guiWFile;
	ExtGuiFile guiFile;
	ExtBmpFile bmpFile;
	TagProjMetaSupportData_t screenTag;

	// populate project meta data
	wrProjMData.setProjectName("T3");
	csProjectDir = "..\\..\\LABUnitTest\\TestData\\ProjectMetaData\\T3";
	wrProjMData.setProjectDir(csProjectDir);
	fo.Delete(csProjectDir);
	wrProjMData.createFolderStructure();
	wrProjMData.createDefaultGroup();
	dataFile.setHostFileName("T3.txt");
	wrProjMData.addDataFile(dataFile);
	//guiFile.setHostFileName("T3.gui");
	wrProjMData.addScreenTag("default", screenTag);
	guiWFile.fileHostNameStub = "T3";
	guiWFile.screenTag = "default";
	wrProjMData.addGuiFile(guiWFile, FALSE);
	bmpFile.setHostFileName("T3.bmp");
	wrProjMData.addBmpFile(bmpFile);
	GuiWidget widget("T3 widget", "T3 screen");
	wrProjMData.addGuiWidget(widget);

	wrProjMData.writeProjectFile();
	rdProjMData.readProjectFile(csProjectDir + "\\T3.lpj");
	// Check project name is correct
	CString csProjectName;
	rdProjMData.getProjectName(csProjectName);
	if (csProjectName != "T3") {
		CPPUNIT_FAIL("Project name is incorrect!!");
	}
	// Check group data is correct
	vector<Group> groupVec;
	Group grp;
	rdProjMData.getGroupVec(groupVec);
	grp = groupVec.at(0);
	if (grp.Name != "Default") {
		CPPUNIT_FAIL("Group name is incorrect!!");
	}
	if (grp.Period != DEFAULT_PERIOD) {
		CPPUNIT_FAIL("Group period is incorrect!!");
	}
	if (grp.Alloc != DEFAULT_ALLOC) {
		CPPUNIT_FAIL("Group allocation is incorrect!!");
	}
	if (grp.ID != 1) {
		CPPUNIT_FAIL("Group ID is incorrect!!");
	}
	// Check external files are correct
	// Check GUI host filename is correct	
	vector<ExtGuiFile> guiFileVec;
	CString csHostFileName, csTargetFileName;
	rdProjMData.getGuiFiles(guiFileVec);
	// get file at position 1, because position 0 has default file
	guiFileVec.at(1).getHostFileName(csHostFileName);
	if (csHostFileName != "T3") {
		CPPUNIT_FAIL("GUI host filename is incorrect!!");
	}	
	rdProjMData.getTargetFileNameForGuiHostFileName(csHostFileName, csTargetFileName);
	if (csTargetFileName != "g0000000.gui") {
		CPPUNIT_FAIL("GUI target filename is incorrect!!");
	}
	// Check BMP host and target filenames are correct
	vector<ExtBmpFile> bmpFileVec;
	rdProjMData.getBmpFiles(bmpFileVec);
	bmpFile = bmpFileVec.at(0);
	bmpFile.getHostFileName(csHostFileName);
	if (csHostFileName != "T3.bmp") {
		CPPUNIT_FAIL("BMP host filename is incorrect!!");
	}
	bmpFile.getTargetFileName(csTargetFileName);
	if (csTargetFileName != "b0000000.bmp") {
		CPPUNIT_FAIL("BMP target filename is incorrect!!");
	}
	// Check data host and target filenames are correct
	vector<ExtDataFile> dataFileVec;
	rdProjMData.getDataFiles(dataFileVec);
	dataFile = dataFileVec.at(0);
	dataFile.getHostFileName(csHostFileName);
	if (csHostFileName != "T3.txt") {
		CPPUNIT_FAIL("data host filename is incorrect!!");
	}
	dataFile.getTargetFileName(csTargetFileName);
	if (csTargetFileName != "d0000000.txt") {
		CPPUNIT_FAIL("data target filename is incorrect!!");
	}
	// Check widget is correct
	vector<GuiWidget> guiWidgetVec;
	rdProjMData.getGuiWidgets(guiWidgetVec);
	GuiWidget widget1;
	widget1 = guiWidgetVec.at(0);
	if (widget1 == widget) {
	}
	else {
		CPPUNIT_FAIL("widget is incorrect!!");
	}
}

// tests the addFile and fileInVec functions
/**
 * @page EssUA0004 fileInVecT4
 * @anchor EssUA0004
 * @section purpose Purpose:
 * This test exercises fileInVec and addFile
 * methods of the class ProjectMetaData.
 *
 * @section initial Initial conditions: 
 * - An instance of ProjectMetaData is created
 * - Project name is set to T4
 * - Project root dir is set to ..\\LABUnitTest\\TestData\\ProjectMetaData\\T4
 * - Project folder T4 is created
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Set filename T4.gui
 * -# Execute addFile(kGui, file)
 * -# Execute fileInVec(kGui, file)
 * -# Set filename T4.bmp
 * -# Execute addFile(kBmp, file)
 * -# Execute fileInVec(kBmp, file)
 * -# Set filename T4.txt
 * -# Execute addFile(kData, file)
 * -# Execute fileInVec(kData,file)
 *
 * @section results Expected results:
 * - step 3 returns kErr_FileInVec
 * - step 6 returns kErr_FileInVec
 * - step 9 returns kErr_FileInVec
 *
 */
void ProjectMetaDataTest::fileInVecT4()
{
	TProjectMetaData projMData;
	CString csProjectDir;
	CFileOperation fo;
	GuiFileEssentialData_t guiWFile;
	ExtGuiFile guiFile;
	ExtBmpFile bmpFile;
	ExtDataFile dataFile;
	TagProjMetaSupportData_t screenTag;

	projMData.setProjectName("T4");
	csProjectDir = "..\\..\\LABUnitTest\\TestData\\ProjectMetaData\\T4";
	projMData.setProjectDir(csProjectDir);
	fo.Delete(csProjectDir);
	projMData.createFolderStructure();	
	// Check a gui file added to the GUI file vector is there
	projMData.addScreenTag("default", screenTag);
	guiWFile.fileHostNameStub = "T4.gui";
	guiWFile.screenTag = "default";
	LucidErrEnum err = projMData.addGuiFile(guiWFile, FALSE);
	guiFile.setHostFileName("T4.gui");
	guiFile.setScreenTag("default");
	if (!projMData.fileInProject(guiFile)) {
		CPPUNIT_FAIL("GUI file is not in GUI file vector!!");
	}
	// Check a bmp file added to the bmp file vector is there
	bmpFile.setHostFileName("T4.bmp");
	projMData.addBmpFile(bmpFile);
	if (!projMData.fileInProject(bmpFile)) {
		CPPUNIT_FAIL("BMP file is not in BMP file vector!!");
	}
	// Check a data file added to the data file vector is there
	dataFile.setHostFileName("T4.txt");
	projMData.addDataFile(dataFile);
	if (!projMData.fileInProject(dataFile)) {
		CPPUNIT_FAIL("Data file is not in data file vector!!");
	}
}

// Tests the createDefaultGroup function
// calls the function and then checks the values in the group are correct
/**
 * @page EssUA0005 createDefaultGroupT5
 * @anchor EssUA0005
 * @section purpose Purpose:
 * This test exercises createDefaultGroup
 * method of the class ProjectMetaData.
 *
 * @section initial Initial conditions: 
 * - An instance of ProjectMetaData is created
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Execute createDefaultGroup()
 * -# Execute getGroupVec(groupVec)
 *
 * @section results Expected results:
 * - Group name is Default
 * - Group period is 100000
 * - Group allocation is 90000
 * - Group ID is 1
 *
 */
void ProjectMetaDataTest::createDefaultGroupT5()
{
	TProjectMetaData projMData;
	vector<Group> groupVec;
	Group grp;

	projMData.createDefaultGroup();
	projMData.getGroupVec(groupVec);
	grp = groupVec.at(0);
	if (grp.Name != "Default") {
		CPPUNIT_FAIL("Group name is incorrect!!");
	}
	if (grp.Period != DEFAULT_PERIOD) {
		CPPUNIT_FAIL("Group period is incorrect!!");
	}
	if (grp.Alloc != DEFAULT_ALLOC) {
		CPPUNIT_FAIL("Group allocation is incorrect!!");
	}
	if (grp.ID != 1) {
		CPPUNIT_FAIL("Group ID is incorrect!!");
	}
}

// Tests the createFolderStructure function
// call the function to create a project folder
// then call the folderStructureNotOk function to verify the folder has been created correctly
/**
 * @page EssUA0006 createFolderStructureT6
 * @anchor EssUA0006
 * @section purpose Purpose:
 * This test exercises createFolderStructure
 * method of the class ProjectMetaData.
 *
 * @section initial Initial conditions: 
 * - An instance of ProjectMetaData is created
 * - Project name is set to T6
 * - Project dir is set to ..\\LABUnitTest\\TestData\\ProjectMetaData\\T6
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Execute createFolderStructure()
 * -# Execute folderStructureNotOk(projectDir)
 * -# Execute CheckPath(projectDEPDir + "T6")
 * -# Execute CheckPath(projectDEPDir + "T6.prg")
 *
 * @section results Expected results:
 * - step 2 returns no error
 * - step 3 returns ok
 * - step 4 returns ok
 *
 */
void ProjectMetaDataTest::createFolderStructureT6()
{
	TProjectMetaData projMData;
	CString csProjectDir;
	CFileOperation fo;

	projMData.setProjectName("T6");
	csProjectDir = "..\\..\\LABUnitTest\\TestData\\ProjectMetaData\\T6";
	projMData.setProjectDir(csProjectDir);
	fo.Delete(csProjectDir);
	projMData.createFolderStructure();
	if (projMData.folderStructureNotOk()) {
		CPPUNIT_FAIL("Project folder structure has not been created correctly!!");
	}
	// Check that the DEP encapsulated block sub-directory is created
	if (!fo.CheckPath(csProjectDir + DEPDIR + "T6")) {
		CPPUNIT_FAIL("DEP sub-function directory not created!!");
	}
	// Check that the DEP directory has a .prg file
	if (!fo.CheckPath(csProjectDir + DEPDIR + "T6.prg")) {
		CPPUNIT_FAIL("DEP directory does not have the correct .prg file!!");
	}
}

// Tests the copyFolderTo function
// call the function to copy a project folder
// then verify the project folder has been copied correctly
/**
 * @page EssUA0007 copyFolderToT7
 * @anchor EssUA0007
 * @section purpose Purpose:
 * This test exercises copyFolderTo
 * method of the class ProjectMetaData.
 *
 * @section initial Initial conditions: 
 * - An instance of ProjectMetaData is created
 * - Project name is set to T7
 * - Project dir is set to ..\\LABUnitTest\\TestData\\ProjectMetaData\\T7
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Execute createFolderStructure()
 * -# Execute copyFolderTo(projectDir, "NewT7")
 * -# Execute folderStructureNotOk(projectDir)
 * -# Execute CheckPath(projectDEPDir + "NewT7")
 * -# Execute CheckPath(projectDEPDir + "NewT7.prg")
 *
 * @section results Expected results:
 * - step 3 returns no error
 * - step 4 returns ok
 * - step 5 returns ok
 *
 */
void ProjectMetaDataTest::copyFolderToT7()
{
	TProjectMetaData projMData;
	CString csProjectDir, csNewProjectDir;
	CFileOperation fo;

	projMData.setProjectName("T7");
	csProjectDir = "..\\..\\LABUnitTest\\TestData\\ProjectMetaData";
	projMData.setProjectDir(csProjectDir + "\\T7");
	fo.Delete(csProjectDir + "\\T7");
	fo.Delete(csProjectDir + "\\NewT7");
	projMData.createFolderStructure();
	projMData.copyFolderTo(csProjectDir, "NewT7");
	csProjectDir = csProjectDir + "\\NewT7";
	if (projMData.folderStructureNotOk()) {
		CPPUNIT_FAIL("Project folder structure has not been created correctly!!");
	}
	// Check that the DEP encapsulated block sub-directory is created
	if (!fo.CheckPath(csProjectDir + DEPDIR + "NewT7")) {
		CPPUNIT_FAIL("DEP sub-function directory not created!!");
	}
	// Check that the DEP directory has a .prg file
	if (!fo.CheckPath(csProjectDir + DEPDIR + "NewT7.prg")) {
		CPPUNIT_FAIL("DEP directory does not have the correct .prg file!!");
	}
}

// Tests the addGuiWidget and guiWidgetInVec functions
/**
 * @page EssUA0008 EssUA0008 addGuiWidgetT8
 * @anchor EssUA0008
 * @section purpose Purpose:
 * This test exercises addGuiWidget and guiWidgetInVec
 * methods of the class ProjectMetaData.
 *
 * @section initial Initial conditions: 
 * - An instance of ProjectMetaData is created
 * - Create a GuiWidget instance with a widget tag, "T8 widget", and screen tag, "T8 screen"
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Execute addGuiWidget(widget)
 * -# Execute guiWidgetInVec(widget)
 * -# Execute addGuiWidget(widget)
 * -# Execute getGuiWidgetVecSize(size)
 *
 * @section results Expected results:
 * - step 2 returns kErr_ProjectMetaData_WidgetScreenPairAlreadyPresent
 * - step 4 returns 1
 *
 */
void ProjectMetaDataTest::addGuiWidgetT8()
{
	TProjectMetaData projMData;
	GuiWidget widget("T8 widget", "T8 screen");
	UINT size;

	projMData.addGuiWidget(widget);
	// check the widget has been added to the vector
	if (!projMData.guiWidgetInVec(widget)) {
		CPPUNIT_FAIL("Gui widget has not been added!!");
	}
	//check the same widget cannot be added twice
	projMData.addGuiWidget(widget);
	projMData.getGuiWidgetVecSize(size);
	if (size != 1) {
		CPPUNIT_FAIL("The same widget has been added twice!!");
	}
}

// Tests the removeGuiWidget function
/**
 * @page EssUA0009 EssUA0009 removeGuiWidgetT9
 * @anchor EssUA0009
 * @section purpose Purpose:
 * This test exercises removeGuiWidget
 * method of the class ProjectMetaData.
 *
 * @section initial Initial conditions: 
 * - An instance of ProjectMetaData is created
 * - Create a GuiWidget instance with a widget tag, "T9 widget", and screen tag, "T9 screen"
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Execute addGuiWidget(widget)
 * -# Execute removeGuiWidget(widget)
 * -# Execute guiWidgetInVec(widget)
 *
 * @section results Expected results:
 * - step 2 returns no error
 * - step 3 returns no error
 *
 */
void ProjectMetaDataTest::removeGuiWidgetT9()
{
	TProjectMetaData projMData;
	GuiWidget widget("T9 widget", "T9 screen");

	projMData.addGuiWidget(widget);
	if (projMData.removeGuiWidget(widget)) {
		CPPUNIT_FAIL("Widget to remove is not in the project!!");
	}
	if (projMData.guiWidgetInVec(widget)) {
		CPPUNIT_FAIL("Widget was not removed!!");
	}
}

// Tests the updateWidget function
/**
 * @page EssUA0010 EssUA0010 updateWidgetT10
 * @anchor EssUA0010
 * @section purpose Purpose:
 * This test exercises updateWidget
 * method of the class ProjectMetaData.
 *
 * @section initial Initial conditions: 
 * - An instance of ProjectMetaData is created
 * - Create a GuiWidget instance with a widget tag, "T10 widget", and screen tag, "T10 screen"
 * - Create a GuiWidget instance with a widget tag, "T10 new widget", and screen tag, "T10 new screen"
 *
 * @section data Test data:
 *
 * @section steps Test steps:
 * -# Execute addGuiWidget(widget)
 * -# Execute updateWidget(widget, newWidget)
 * -# Execute guiWidgetInVec(newWidget)
 * -# Execute guiWidgetInVec(widget)
 *
 * @section results Expected results:
 * - step 3 returns kErr_ProjectMetaData_WidgetScreenPairAlreadyPresent
 * - step 4 returns no error
 *
 */
void ProjectMetaDataTest::updateWidgetT10()
{
	TProjectMetaData projMData;
	GuiWidget widget("T10 widget", "T10 screen");
	GuiWidget newWidget("T10 new widget", "T10 new screen");

	projMData.addGuiWidget(widget);
	projMData.updateWidget(widget, newWidget);
	if (!projMData.guiWidgetInVec(newWidget)) {
		CPPUNIT_FAIL("Widget has not been updated correctly!!");
	}
	if (projMData.guiWidgetInVec(widget)) {
		CPPUNIT_FAIL("This widget should not be in the project!!");
	}
}