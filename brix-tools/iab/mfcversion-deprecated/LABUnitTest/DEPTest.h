#pragma once

#include <cppunit/extensions/HelperMacros.h>

// forward declare classes under test if necessary 
// e.g. class MyClass;

/// cppunit test class, main doc text
class DEPTest : public CppUnit::TestFixture 
{
public:
	DEPTest(void);
	~DEPTest(void);

	CPPUNIT_TEST_SUITE( DEPTest );// note: name is the same as the class
    /// add tests to suite
		CPPUNIT_TEST( getInitScrollPosT1 );
		CPPUNIT_TEST( getPortLabelT2 );
		CPPUNIT_TEST( setPortLabelT3 );
		CPPUNIT_TEST( setPortLabelT4 );
		CPPUNIT_TEST( isOutputPortConnectedT5 );
		CPPUNIT_TEST( isFinishPortConnectedT6 );
		CPPUNIT_TEST( removeConnectedInputTagsT7 );
		CPPUNIT_TEST( removeConnectedStartTagsT8 );
    CPPUNIT_TEST_SUITE_END();

public:
   // executed automatically as each test case starts/ends
    void setUp();
    void tearDown();

protected:
 	// this is our list of test cases - one method per test case.
	// ensure that test cases are registered with CPPUNIT_TEST, above.
	void getInitScrollPosT1();
	void getPortLabelT2();
	void setPortLabelT3();
	void setPortLabelT4();
	void isOutputPortConnectedT5();
	void isFinishPortConnectedT6();
	void removeConnectedInputTagsT7();
	void removeConnectedStartTagsT8();

};