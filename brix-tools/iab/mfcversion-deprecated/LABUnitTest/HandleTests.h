#pragma once

#include <cppunit/extensions/HelperMacros.h>

// forward declare classes under test if necessary 
// e.g. class MyClass;

/// cppunit test class, main doc text
class HandleTests : public CppUnit::TestFixture 
{
public:
	HandleTests(void);
	~HandleTests(void);

	CPPUNIT_TEST_SUITE( HandleTests );// note: name is the same as the class
    /// add tests to suite
    //    CPPUNIT_TEST( Test1 );
    //    CPPUNIT_TEST( Test2 );
	    CPPUNIT_TEST( T21_CreateCondataObjects );
    CPPUNIT_TEST_SUITE_END();

public:
   // executed automatically as each test case starts/ends
    void setUp();
    void tearDown();

protected:
 	// this is our list of test cases - one method per test case.
	// ensure that test cases are registered with CPPUNIT_TEST, above.
	void Test1();
	void Test2();
	void T21_CreateCondataObjects();

};
