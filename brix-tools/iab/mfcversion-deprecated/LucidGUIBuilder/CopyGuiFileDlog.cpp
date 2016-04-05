// CopyGuiFileDlog.cpp : implementation file
//

#include "stdafx.h"
#include "CopyGuiFileDlog.h"


// CCopyGuiFileDlog dialog

IMPLEMENT_DYNAMIC(CCopyGuiFileDlog, CDialog)

CCopyGuiFileDlog::CCopyGuiFileDlog(ProjectMetaData *pPMD, 
								   const CString &origFileName,
								   const CString &origFileDescrip,
								   CWnd* pParent /*=NULL*/)
	: CDialog(CCopyGuiFileDlog::IDD, pParent),
	m_csOrigFileName(_T(origFileName)),
	m_csOrigFileDescription(_T(origFileDescrip)),
	m_csNewFileName(_T("")),
	m_csNewFileDescription(_T(""))
{
}

CCopyGuiFileDlog::~CCopyGuiFileDlog()
{
}

void CCopyGuiFileDlog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ORIGFILE_NAME, m_ctlOrigFileName);
	DDX_Control(pDX, IDC_EDIT_ORIGFILE_DESCRIP, m_ctlOrigFileDescrip);
	DDX_Control(pDX, IDC_EDIT_NEWFILE_NAME, m_ctlNewFileName);
	DDX_Control(pDX, IDC_EDIT_NEWFILE_DESCRIP, m_ctlNewFileDescrip);
}


BEGIN_MESSAGE_MAP(CCopyGuiFileDlog, CDialog)
	ON_EN_CHANGE(IDC_EDIT_NEWFILE_NAME, &CCopyGuiFileDlog::OnEnChangeEditNewfileName)
	ON_STN_CLICKED(IDC_STATIC_FILENAME, &CCopyGuiFileDlog::OnStnClickedStaticFilename)
	ON_BN_CLICKED(IDOK, &CCopyGuiFileDlog::OnBnClickedOk)
END_MESSAGE_MAP()


// CCopyGuiFileDlog message handlers

void CCopyGuiFileDlog::OnOK()
{
	UpdateData();

	int curSel = CB_ERR;

//	if( (curSel = m_ctlScreenTagCombo.GetCurSel()) == CB_ERR){
//
//		m_csNewFileName = "";
//		m_csNewFileDescription = "";
//		m_csScreenTag = "";

//	}else{

	m_ctlNewFileDescrip.GetWindowText(m_csNewFileDescription);
	m_ctlNewFileName.GetWindowText(m_csNewFileName);
	//m_csNewFileName += ".gui";

//		m_ctlScreenTagCombo.GetLBText( curSel, m_csScreenTag );

//	}

	CDialog::OnOK();
}

BOOL CCopyGuiFileDlog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctlOrigFileName.SetWindowText( m_csOrigFileName);
	m_ctlOrigFileDescrip.SetWindowText( m_csOrigFileDescription );

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CCopyGuiFileDlog::OnEnChangeEditNewfileName()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CCopyGuiFileDlog::OnStnClickedStaticFilename()
{
	// TODO: Add your control notification handler code here
}

void CCopyGuiFileDlog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
