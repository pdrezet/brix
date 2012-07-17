#pragma once

#include "resource.h"
#include "afxwin.h" 
#include "Porting_Classes/INXString.h"
// CProjectDialog dialog

class CProjectDialog : public CDialog
{
	DECLARE_DYNAMIC(CProjectDialog)

public:
	CProjectDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProjectDialog();

// Dialog Data
	enum { IDD = IDD_PROJECTDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOk();
	afx_msg void OnFindProjDir();

	virtual BOOL OnInitDialog();

	bool IsValidDir();
	bool IsValidName();
	bool ProjectExists();
	void SetIsWinEnv(bool isWinEnv);


	INXString m_ProjectName;
	INXString m_ProjectDir;
	CEdit m_ProjectDirEdit;
	INXString m_ProjectCommercialName;
	INXString m_ProjectVersion;
	INXString m_ProjectDescription;

private:
	bool bIsWindowsEnv;

};
