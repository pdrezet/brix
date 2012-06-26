#pragma once
#include "afxwin.h"

class CScreenTagListBox :
	public CListBox
{
public:
	CScreenTagListBox(void);
	~CScreenTagListBox(void);
	void AddStrings(CString & tag, CString & descrip);
	int getSelectedKey(CString &key);

protected:
	const char		m_cKeyLftDelimiter;
	const char		m_cKeyRgtDelimiter;
	const CString	m_csKeyDescriptionDelimiter;


};
