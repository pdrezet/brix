// ExportDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DrawProg.h"
#include "ExportDialog.h"
#include "FileOperations.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// global variable declared in CDrawProgApp
extern char workDir[WORK_DIR_SIZE];

/////////////////////////////////////////////////////////////////////////////
// CExportDialog dialog


CExportDialog::CExportDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CExportDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExportDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CExportDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExportDialog)
	DDX_Control(pDX, IDC_LIB_LIST, m_Library);
	DDX_Control(pDX, IDC_EXPORT_LIST, m_Export);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExportDialog, CDialog)
	//{{AFX_MSG_MAP(CExportDialog)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExportDialog message handlers

BOOL CExportDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CFileFind finder;
	CString fileName;
	int bWorking = finder.FindFile(workDir + USERDEFDIR + "*.prg");
	
	// read in ini files and construct menu tree
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		fileName = finder.GetFileName();
		// Remove .prg
		fileName.MakeReverse();
		fileName.Delete(0,4);
		fileName.MakeReverse();
		m_Library.AddString(fileName);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CExportDialog::OnOK() 
{
	CString lib, exDir;
	CFileOperation fo;

	// TODO: Add extra validation here
	// Copy selected libraries from userdefined to export
	exDir = (CString)workDir + EXPORTDIR;
	fo.SetOverwriteMode(true); // set OverwriteMode flag
	fo.Delete(exDir);
	CreateDirectory(exDir, NULL);
	for (int i=0; i<m_Export.GetCount(); i++) {
		m_Export.GetText(i, lib);
		fo.Copy(workDir + USERDEFDIR + lib + ".prg", exDir);
		fo.Copy(workDir + USERDEFDIR + lib, exDir);
		fo.Copy(workDir + USERDEFDIR + lib + ".idf.ini", exDir);
	}
	
	CDialog::OnOK();
}

// Add a library component to the export list
void CExportDialog::OnAdd() 
{
	CString lib;

	int index = m_Library.GetCurSel();
	if (index == LB_ERR) {
		AfxMessageBox("Select a library component to add.");
	}
	else if (ExportExist(index)) {
		AfxMessageBox("The library component selected is already in the export list.");
	}
	else {
		m_Library.GetText(index, lib);	
		m_Export.AddString(lib);
	}
}	

// Delete a library component from the export list
void CExportDialog::OnDelete() 
{
	int index = m_Export.GetCurSel();
	if (index == LB_ERR) {
		AfxMessageBox("Select an export component to delete.");
		return;
	}
	m_Export.DeleteString(index);
}

// returns true if the selected library component is already in the export list
bool CExportDialog::ExportExist(int index) {
	CString lib, exportLib;

	m_Library.GetText(index, lib);
	for (int i=0; i<m_Export.GetCount(); i++) {
		m_Export.GetText(i, exportLib);
		if (lib == exportLib) {
			return TRUE;
		}
	}

	return FALSE;
}