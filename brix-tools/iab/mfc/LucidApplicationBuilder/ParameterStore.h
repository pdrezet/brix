// ParameterStore.h: interface for the ParameterStore class.
//
//////////////////////////////////////////////////////////////////////

#pragma once
//#include "Parameter.h"
using namespace std;

class Parameter;

class ParameterStore : public CObject  
{
public:
	// constructors
	ParameterStore();

	bool IsTextbox();

	ParameterStore(	CString _name, 
				int _dataType, 
				CString _minRange, 
				CString _maxRange, 
				CString defaultVal, 
				CString _description, 
				CStringArray* _enumValArr, 
				CStringArray* _enumLabelArr);

	virtual ~ParameterStore();
	
	void copy( const Parameter *rhs );

	// attributes
	CString m_csName;
	CString m_csDescription;
	int m_iDataType; //parameter data type @tod the types here need to be enumerated type 5 is for tags info
	CString m_csMinRange;
	CString m_csMaxRange;
	CString m_csValue;
	CStringArray m_csaEnumValArr;
	CStringArray m_csaEnumLabelArr;

	CString GetEnumLabel(CString enumVal);
	CString GetEnumVal(CString enumLabel);

};
