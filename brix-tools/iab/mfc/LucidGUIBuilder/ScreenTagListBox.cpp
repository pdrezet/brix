#include "stdafx.h"
#include "ScreenTagListBox.h"

CScreenTagListBox::CScreenTagListBox(void)
: m_cKeyLftDelimiter('['), m_cKeyRgtDelimiter(']'), m_csKeyDescriptionDelimiter(".......")
{
}

CScreenTagListBox::~CScreenTagListBox(void)
{
}

void CScreenTagListBox::AddStrings(CString & tag, CString & descrip)
{
	AddString( CString( m_cKeyLftDelimiter + tag + m_cKeyRgtDelimiter + m_csKeyDescriptionDelimiter 
		+ descrip ) );
}

int CScreenTagListBox::getSelectedKey(CString &key)
{
	UpdateData();

	CString dumStr;
	int selPos = LB_ERR; // initialise to value caused by 'none selected' or 'list is multi-selectable'.

	selPos = GetCurSel();

	if(selPos == LB_ERR){
		return LB_ERR;
	}else{

		// 1 line is selected ...

		GetText(selPos, dumStr);

		int dumPos1 = dumStr.Find(m_cKeyLftDelimiter);
		int dumPos2 = dumStr.Find(m_cKeyRgtDelimiter);

		key = dumStr.Mid(dumPos1+1, dumPos2-dumPos1-1);
		return selPos;
	}
}
