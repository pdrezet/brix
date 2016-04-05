#pragma once
#include "afxcmn.h"

class ProjectFileManagerDialog;

class LgbProjFileMgrTabCtrl :
	public CTabCtrl
{
public:
	LgbProjFileMgrTabCtrl(void);
public:
	~LgbProjFileMgrTabCtrl(void);

	ProjectFileManagerDialog *m_pProjectFileManagerDialog;
public:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
};
