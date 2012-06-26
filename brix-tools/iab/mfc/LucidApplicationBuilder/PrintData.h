// PrintData.h: interface for the CPrintData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINTDATA_H__F031C21D_FF3E_4697_8B20_E521D3053F0C__INCLUDED_)
#define AFX_PRINTDATA_H__F031C21D_FF3E_4697_8B20_E521D3053F0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPrintData  
{
public:
	CPrintData();
	virtual ~CPrintData();

	// Attributes
	UINT m_nWidths; // No. of pages for the width of the view
	UINT m_nLengths; // No. of pages for the length of the view
	CPoint m_ViewRefPoint; // Top left corner of the view contents
	CString m_ViewTitle; // Name of the view

};

#endif // !defined(AFX_PRINTDATA_H__F031C21D_FF3E_4697_8B20_E521D3053F0C__INCLUDED_)
