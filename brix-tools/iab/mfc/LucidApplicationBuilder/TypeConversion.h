// TypeConversion.h: interface for the TypeConversion class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TYPECONVERSION_H__B717973E_2FDE_4762_9D78_A6D204137E24__INCLUDED_)
#define AFX_TYPECONVERSION_H__B717973E_2FDE_4762_9D78_A6D204137E24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TypeConversion  
{
public:
	TypeConversion();
	virtual ~TypeConversion();

	// Methods
	char DataType2Char(int dataType);
	int DataType2Int(char dataType);
	int DataType2Int(CString dataType);

};

#endif // !defined(AFX_TYPECONVERSION_H__B717973E_2FDE_4762_9D78_A6D204137E24__INCLUDED_)
