// ProjectChooser.cpp : implementation file
//

#include "stdafx.h"
#include "DrawProg.h"
#include "ProjectChooser.h"
#include "PathDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProjectChooser dialog


CProjectChooser::CProjectChooser(CWnd* pParent /*=NULL*/)
	: CDialog(CProjectChooser::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProjectChooser)
	m_strPathName = _T("");
	m_strProjectName = _T("");
	//}}AFX_DATA_INIT
}


void CProjectChooser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProjectChooser)
	DDX_Control(pDX, IDC_NAME_EDIT, m_ctrlProjectName);
	DDX_Control(pDX, IDC_DIR_EDIT, m_ctrlPathName);
	DDX_Text(pDX, IDC_DIR_EDIT, m_strPathName);
	DDX_Text(pDX, IDC_NAME_EDIT, m_strProjectName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProjectChooser, CDialog)
	//{{AFX_MSG_MAP(CProjectChooser)
	ON_BN_CLICKED(IDC_BROWSER, OnBrowser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProjectChooser message handlers

void CProjectChooser::OnBrowser() 
{
	INXString strPath;
	INXString strYourCaption(_T("Project Chooser"));
	INXString strYourTitle(_T("Select a project directory."));

	m_ctrlPathName.GetWindowText(strPath);

	CPathDialog dlg(strYourCaption, strYourTitle, strPath);

	if(dlg.DoModal()==IDOK)
	{
		m_ctrlPathName.SetWindowText(dlg.GetPathName());
	}
}

void CProjectChooser::OnOK() 
{
	INXString strPath;
	INXString strProject;

	m_ctrlPathName.GetWindowText(strPath);
	m_ctrlProjectName.GetWindowText(strProject);

	if(CPathDialog::MakeSurePathExists(strPath)==0 && CPathDialog::ValidProject(strProject)==0)
	{
		CDialog::OnOK();
	}
}
