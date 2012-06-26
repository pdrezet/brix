// Parameter.h: interface for the Parameter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARAMETER_H__184F839C_89B7_45D7_AEE9_9102F8EE2472__INCLUDED_)
#define AFX_PARAMETER_H__184F839C_89B7_45D7_AEE9_9102F8EE2472__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParameterStore.h"

#include <fstream>
using namespace std;


class ParameterStore;

class Parameter : public CObject  
{
public:
	// constructors
	Parameter();

	Parameter(	CString _name, 
				int _dataType, 
				CString _minRange, 
				CString _maxRange, 
				CString defaultVal, 
				CString _description, 
				CStringArray* _enumValArr, 
				CStringArray* _enumLabelArr);

	virtual ~Parameter();

	Parameter & operator=( const Parameter &rhs );	
	void copy( const ParameterStore *rhs );

	// methods
	void Save(ostream *);
	void Load(istream *);
	bool IsTextbox();

	CString GetEnumLabel(CString enumVal);
	CString GetEnumVal(CString enumLabel);
	
	// attributes
	CString name;
	CString description;
	int dataType;
	CString minRange;
	CString maxRange;
	CString value;

	CStringArray* enumValArr;
	CStringArray* enumLabelArr;

};

#endif // !defined(AFX_PARAMETER_H__184F839C_89B7_45D7_AEE9_9102F8EE2472__INCLUDED_)
