#pragma once


#include "stdafx.h"
//#include "LgbProjFileMgrTabCtrl.h"
#include "ProjectFileManagerDialog.h"

LgbProjFileMgrTabCtrl::LgbProjFileMgrTabCtrl(void):m_pProjectFileManagerDialog(NULL)
{
}

LgbProjFileMgrTabCtrl::~LgbProjFileMgrTabCtrl(void)
{
}
BEGIN_MESSAGE_MAP(LgbProjFileMgrTabCtrl, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &LgbProjFileMgrTabCtrl::OnTcnSelchange)
END_MESSAGE_MAP()

void LgbProjFileMgrTabCtrl::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	int selTabIndx = GetCurSel();
	m_pProjectFileManagerDialog->processTabChange( selTabIndx );
	*pResult = 0;
}
