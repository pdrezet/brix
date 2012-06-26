#pragma once

#include <cppunit/extensions/HelperMacros.h>

// forward declare classes under test if necessary 
// e.g. class MyClass;

/// cppunit test class, main doc text
class ProjectMetaDataTest : public CPPUNIT_NS::TestFixture 
{
public:
	ProjectMetaDataTest(void);
	~ProjectMetaDataTest(void);

	CPPUNIT_TEST_SUITE( ProjectMetaDataTest );// note: name is the same as the class
    /// add tests to suite
		CPPUNIT_TEST( folderStructureNotOkT1 );
		//CPPUNIT_TEST( readProjectFileT2 );
		CPPUNIT_TEST( writeProjectFileT3 );
		CPPUNIT_TEST( fileInVecT4 );
		CPPUNIT_TEST( createDefaultGroupT5 );
		CPPUNIT_TEST( createFolderStructureT6 );
		CPPUNIT_TEST( copyFolderToT7 );
		CPPUNIT_TEST( addGuiWidgetT8 );
		CPPUNIT_TEST( removeGuiWidgetT9 );
		CPPUNIT_TEST( updateWidgetT10 );
    CPPUNIT_TEST_SUITE_END();

public:
   // executed automatically as each test case starts/ends
    void setUp();
    void tearDown();

protected:
 	// this is our list of test cases - one method per test case.
	// ensure that test cases are registered with CPPUNIT_TEST, above.
	void folderStructureNotOkT1();
	void readProjectFileT2();
	void writeProjectFileT3();
	void fileInVecT4();
	void createDefaultGroupT5();
	void createFolderStructureT6();
	void copyFolderToT7();
	void addGuiWidgetT8();
	void removeGuiWidgetT9();
	void updateWidgetT10();

};