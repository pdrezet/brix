// SomeTests.h: interface for the CSomeTests class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOMETESTS_H__A96C341D_3047_4AB5_B38F_738D65F47795__INCLUDED_)
#define AFX_SOMETESTS_H__A96C341D_3047_4AB5_B38F_738D65F47795__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <cppunit/extensions/HelperMacros.h>

// forward declare classes under test if necessary // e.g. class MyClass;
/// cppunit test class, main doc text
class CSomeTests : public CppUnit::TestFixture 
{
public:
	CSomeTests(void);
	virtual ~CSomeTests(void);

	CPPUNIT_TEST_SUITE( CSomeTests );// note: name is the same as the class
    /// add tests to suite
        CPPUNIT_TEST( test1 );
        CPPUNIT_TEST( test2 );
    CPPUNIT_TEST_SUITE_END();

public:
   // executed automatically as each test case starts/ends
    void setUp();
    void tearDown();

protected:
 	// this is our list of test cases - one method per test case.
	// ensure that test cases are registered with CPPUNIT_TEST, above.
	void test2();
	void test1();



};

#endif // !defined(AFX_SOMETESTS_H__A96C341D_3047_4AB5_B38F_738D65F47795__INCLUDED_)
