// ProjectDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ProjectDialog.h"
#include "PathDialog.h"
#include "FolderDlg.h"
#include "LucidConstants.h"

#include <fstream>
using namespace std;
#include "direct.h"

// CProjectDialog dialog

IMPLEMENT_DYNAMIC(CProjectDialog, CDialog)

CProjectDialog::CProjectDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CProjectDialog::IDD, pParent)
	, m_ProjectName(_T(""))
	//, m_ProjectDir(_T("C:\\Lucid Projects"))
	// Get the project directory from the registry
	, m_ProjectDir(AfxGetApp()->GetProfileString(_T("Project"),_T("ProjectRootDir"),_T(DEFAULTPROJECTROOTDIR)))
	, m_ProjectCommercialName(_T(""))
	, m_ProjectVersion(_T(""))
	, m_ProjectDescription(_T(""))
{
	bIsWindowsEnv = true;
}

CProjectDialog::~CProjectDialog()
{
}

void CProjectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PROJ_NAME_EDIT, m_ProjectName);
	DDX_Text(pDX, IDC_PROJ_DIR_EDIT, m_ProjectDir);
	DDX_Control(pDX, IDC_PROJ_DIR_EDIT, m_ProjectDirEdit);
	DDX_Text(pDX, IDC_PROJECT_COMMERCIALNAME, m_ProjectCommercialName);
	DDX_Text(pDX, IDC_PROJECT_VERSION, m_ProjectVersion);
	DDX_Text(pDX, IDC_PROJECT_DESCRIPTION, m_ProjectDescription);
}


BEGIN_MESSAGE_MAP(CProjectDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CProjectDialog::OnOk)
	ON_BN_CLICKED(IDC_PROJ_DIR_BUTT, &CProjectDialog::OnFindProjDir)
END_MESSAGE_MAP()


// CProjectDialog message handlers

BOOL CProjectDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_PROJ_NAME_EDIT);
	if(pEdit != NULL) {
		pEdit->SetFocus();
		return 0; //since we are explicity setting focus
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CProjectDialog::OnOk()
{
	CPathDialog dlg;
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (m_ProjectName == "") {
		AfxMessageBox("You must enter a project name.");
	}
	else if (m_ProjectDir == "") {
		AfxMessageBox("You must enter a project root directory.");
	}
	else if (dlg.isValidDir(m_ProjectDir)) {
		AfxMessageBox("The project root path is invalid.");
	}
	else if (dlg.isValidDir(m_ProjectDir + "\\" + m_ProjectName)) {
		AfxMessageBox("The project name is invalid.");
	}
	else if (ProjectExists()) {
		if (AfxMessageBox("The project already exists.Do you want to replace it?",MB_YESNO|MB_ICONEXCLAMATION)==IDYES) {
			// write the project dir to the registry
			AfxGetApp()->WriteProfileString(_T("Project"), _T("ProjectRootDir"), m_ProjectDir);
			AfxGetApp()->WriteProfileString(_T("Project"), _T("ProjectDir"), m_ProjectDir + "\\" + m_ProjectName);
			OnOK();
		}
	}
	else {
		// write the project dir to the registry
		AfxGetApp()->WriteProfileString(_T("Project"), _T("ProjectRootDir"), m_ProjectDir);
		AfxGetApp()->WriteProfileString(_T("Project"), _T("ProjectDir"), m_ProjectDir + "\\" + m_ProjectName);
		OnOK();
	}
}

void CProjectDialog::OnFindProjDir()
{
	// TODO: Add your control notification handler code here
	CString projDirPath = "";
	CString projDirCaption(_T("Project Root Directory"));
	CString projDirTitle(_T("Select a new project root directory."));

	UINT uFlags	= BIF_RETURNONLYFSDIRS | BIF_USENEWUI;
	//NOTE - new folder button in CFolderDialog doesn't work in Wine, so have disabled it
	if (!bIsWindowsEnv) {
		uFlags = uFlags | BIF_NONEWFOLDERBUTTON;
	}

	m_ProjectDirEdit.GetWindowText(projDirPath);

	//CPathDialog dlg(projDirCaption, projDirTitle, projDirPath);
	CFolderDialog dlg(projDirTitle, m_ProjectDir, this, uFlags);
	dlg.SetSelectedFolder(projDirPath); //set initial tree selection node
	if(dlg.DoModal()==IDOK) {
		m_ProjectDirEdit.SetWindowText(dlg.GetFolderPath());
	}
}

bool CProjectDialog::IsValidDir()
{
	CPathDialog dlg;

	if (dlg.MakeSurePathExists(m_ProjectDir)) {
		return FALSE;
	}
	else {
		return TRUE;
	}
}

bool CProjectDialog::IsValidName()
{
	int len = m_ProjectName.GetLength();
	if (m_ProjectName.GetAt(len - 1) == ' ') {
		return FALSE;
	}
	else {
		return TRUE;
	}
}

bool CProjectDialog::ProjectExists()
{
	CString projectFilename = m_ProjectDir + "\\" + m_ProjectName + "\\" + m_ProjectName + PROJECTEXT;

	ifstream projectfile(projectFilename);

	if (projectfile.fail()) {
		return FALSE;
	}
	else {
		return TRUE;
	}
}

void CProjectDialog::SetIsWinEnv(bool isWinEnv)
{
	bIsWindowsEnv = isWinEnv;
}
