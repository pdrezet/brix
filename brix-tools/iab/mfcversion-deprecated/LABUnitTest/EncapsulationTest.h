#pragma once

#include <cppunit/extensions/HelperMacros.h>

// forward declare classes under test if necessary 
// e.g. class MyClass;

/// cppunit test class, main doc text
class EncapsulationTest : public CppUnit::TestFixture 
{
public:
	EncapsulationTest(void);
	~EncapsulationTest(void);

	CPPUNIT_TEST_SUITE( EncapsulationTest );// note: name is the same as the class
    /// add tests to suite
		CPPUNIT_TEST( repositionEncapsulatedT1 );
		CPPUNIT_TEST( getFirstPortYCoordT2 );
    CPPUNIT_TEST_SUITE_END();

public:
   // executed automatically as each test case starts/ends
    void setUp();
    void tearDown();

protected:
 	// this is our list of test cases - one method per test case.
	// ensure that test cases are registered with CPPUNIT_TEST, above.
	void repositionEncapsulatedT1();
	void getFirstPortYCoordT2();

};