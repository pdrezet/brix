// ParameterStore.cpp: implementation of the ParameterStore class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "DrawProg.h"

#include "ParameterStore.h"
#include "Parameter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ParameterStore::ParameterStore()
{
}
/*
ParameterStore::ParameterStore(
					 CString _name, 
					 int _dataType, 
					 CString _minRange, 
					 CString _maxRange, 
					 CString _defaultVal, 
					 CString _description, 
					 CStringArray* _enumValArr, 
					 CStringArray* _enumLabelArr
					 )
{
	name = _name;
	dataType = _dataType;
	minRange = _minRange;
	maxRange = _maxRange;
	value = _defaultVal;
	description = _description;

	for(size_t i=0;i<_enumValArr->GetCount(); i++)
		enumValArr.SetAtGrow(i,  (CString)_enumValArr->GetAt(i) );

	for(size_t i=0;i<_enumLabelArr->GetCount(); i++)
		enumLabelArr.SetAtGrow(i,  (CString)_enumLabelArr->GetAt(i) );

}
*/

void ParameterStore::copy( const Parameter *rhs )
{
	m_csName			= rhs->name;
	m_iDataType			= rhs->dataType;
	m_csMinRange		= rhs->minRange;
	m_csMaxRange		= rhs->maxRange;
	m_csValue			= rhs->value;
	m_csDescription		= rhs->description;

	m_csaEnumValArr.RemoveAll();
	m_csaEnumLabelArr.RemoveAll();

	for(size_t i=0;i<rhs->enumValArr->GetCount(); i++)
		m_csaEnumValArr.SetAtGrow(i,  (CString)rhs->enumValArr->GetAt(i) );

	for(size_t i=0;i<rhs->enumLabelArr->GetCount(); i++)
		m_csaEnumLabelArr.SetAtGrow(i,  (CString)rhs->enumLabelArr->GetAt(i) );

}

ParameterStore::~ParameterStore()
{
}

// Function that determines whether a parameter is displayed in a textbox or a drop-down
bool ParameterStore::IsTextbox() {
	// screen tag
	if (m_iDataType == 4) {
		return FALSE;
	}
	else if (m_csaEnumValArr.GetSize() == 0) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

// Function that returns an enumerated Label for a given enumerated value
CString ParameterStore::GetEnumLabel(CString enumVal) {
	CString ret = "";

	for (int i=0; i<m_csaEnumValArr.GetSize(); i++) {
		if (m_csaEnumValArr.GetAt(i) == enumVal) {
			// avoid overflow error
			if (m_csaEnumValArr.GetSize() >= i+1) {
				ret = m_csaEnumValArr.GetAt(i);
			}
		}
	}
	return ret;
}

// Function that returns an enumerated value for a given enumerated label
CString ParameterStore::GetEnumVal(CString enumLabel) {
	CString ret = "";

	for (int i=0; i<m_csaEnumLabelArr.GetSize(); i++) {
		if (m_csaEnumLabelArr.GetAt(i) == enumLabel) {
			// avoid overflow error
			if (m_csaEnumLabelArr.GetSize() >= i+1) {
				ret = m_csaEnumLabelArr.GetAt(i);
			}
		}
	}
	return ret;
}