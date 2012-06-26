#pragma once

#include <cppunit/extensions/HelperMacros.h>

// forward declare classes under test if necessary 
// e.g. class MyClass;

/// cppunit test class, main doc text
class ProjectTest : public CppUnit::TestFixture 
{
public:
	ProjectTest(void);
	~ProjectTest(void);

	CPPUNIT_TEST_SUITE( ProjectTest );// note: name is the same as the class
    /// add tests to suite
		CPPUNIT_TEST( addGuiWidgetT1 );
		CPPUNIT_TEST( removeGuiWidgetT2 );
		CPPUNIT_TEST( depIsLoadedT3 );
    CPPUNIT_TEST_SUITE_END();

public:
   // executed automatically as each test case starts/ends
    void setUp();
    void tearDown();

protected:
 	// this is our list of test cases - one method per test case.
	// ensure that test cases are registered with CPPUNIT_TEST, above.
	void addGuiWidgetT1();
	void removeGuiWidgetT2();
	void depIsLoadedT3();

};

