// ConDataTempStore.h: interface for the Coninfo class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "ParameterStore.h"

#include "../common/LucidEnums.h"
#include "../common/LucidConstants.h"

#include "condat.h"

class ConDataTempStore  
{

public:
	ConDataTempStore();
	~ConDataTempStore();

	int m_iParamNum;
	int m_iUserDefined;

	CString	m_csType; //graphic filename
	CString m_csBlock; // block name for encapsulated blocks. graphic filename is encapsulate
	CString m_csDescription;
	CString m_csLongDesc;
	CString m_csClassName;
	CString m_csOptionstring;
	CSize m_cSize;

	int m_iInstNum;
	CString m_csHierarchyName;
	bool m_bSaveSelectedFlag;
	CRect m_cRectangle; /// body part of icon

	ParameterStore* m_pParamStoreArr[MAXPARAMS];

	void loadFromProject( const ConData &source );
	void commitToProject( ConData *dest );

};