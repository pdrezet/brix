#pragma once

#include "resource.h"
#include "afxwin.h" 
#include "ProjectMetaData.h"

// ProjectDescriptionDialog dialog

class ProjectDescriptionDialog : public CDialog
{
	DECLARE_DYNAMIC(ProjectDescriptionDialog)

public:
	ProjectDescriptionDialog(ProjectMetaData* pProjMData, CWnd* pParent = NULL);   // standard constructor
	virtual ~ProjectDescriptionDialog();
	BOOL ProjectDescriptionDialog::OnInitDialog();

// Dialog Data
	enum { IDD = IDD_PROJECT_DESCRIPTION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	ProjectMetaData* _pProjMData;


public:
	afx_msg void OnBnClickedOk();
};
