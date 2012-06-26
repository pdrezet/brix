// CreateGuiFileDlog.cpp : implementation file
//

#include "stdafx.h"
#include "CreateGuiFileDlog.h"
#include "../common/ProjectMetaData.h"
#include "../common/LucidTypedefs.h"
#include "Resource.h"
#include <vector>


// CCreateGuiFileDlog dialog

IMPLEMENT_DYNAMIC(CCreateGuiFileDlog, CDialog)

CCreateGuiFileDlog::CCreateGuiFileDlog(ProjectMetaData *pPMD, CString currentWidgetGroup, CWnd* pParent /*=NULL*/)
	: CDialog(CCreateGuiFileDlog::IDD, pParent)
	, m_pProjectMetaData(pPMD)
	, m_csWidgetGroup(_T(""))
	, m_csFileDescrip(_T(""))
	, m_csNewFileName(_T(""))
	, m_csInitialWidgetGroup( _T(currentWidgetGroup) )
{
	//m_cFileData.fileDescr = "";
	//m_cFileData.fileHostNameStub = "";
	//m_cFileData.screenTag = "";
}

CCreateGuiFileDlog::~CCreateGuiFileDlog()
{
}

void CCreateGuiFileDlog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILENAME, m_ctl_EditFileName);
	DDX_Control(pDX, IDC_SCRNTAG_COMBO, m_ctlScreenTagCombo);
	DDX_Control(pDX, IDC_EDIT_DESCRIP, m_ctlEditDescrip);
}


BEGIN_MESSAGE_MAP(CCreateGuiFileDlog, CDialog)
	ON_BN_CLICKED(IDOK, &CCreateGuiFileDlog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCreateGuiFileDlog::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT_FILENAME, &CCreateGuiFileDlog::OnEnChangeEditFilename)
	ON_CBN_CLOSEUP(IDC_SCRNTAG_COMBO, &CCreateGuiFileDlog::OnCbnCloseupScrntagCombo)
	ON_EN_CHANGE(IDC_EDIT_DESCRIP, &CCreateGuiFileDlog::OnEnChangeEditDescrip)
	ON_STN_CLICKED(IDC_STATIC_DESCRIP, &CCreateGuiFileDlog::OnStnClickedStaticDescrip)
END_MESSAGE_MAP()


// CCreateGuiFileDlog message handlers

void CCreateGuiFileDlog::OnBnClickedOk()
{

	UpdateData();

	int curSel = CB_ERR;

	if( (curSel = m_ctlScreenTagCombo.GetCurSel()) == CB_ERR){

		m_csFileDescrip = "";
		m_csNewFileName = "";
		m_csWidgetGroup = "";
		return;

	} else {

		m_ctlScreenTagCombo.GetLBText( curSel, m_csWidgetGroup );
		m_ctl_EditFileName.GetWindowTextA( m_csNewFileName );
		m_ctlEditDescrip.GetWindowTextA( m_csFileDescrip );
	}

	OnOK();
}

void CCreateGuiFileDlog::OnBnClickedCancel()
{
	OnCancel();
}

void CCreateGuiFileDlog::AddComboTag(const CString &tag)
{
	m_ctlScreenTagCombo.AddString(tag);
}

void CCreateGuiFileDlog::setScreenTags(const ScreenMgrDlogMap_t &tagMap )
{

	m_ctlScreenTagCombo.ResetContent(); // clear it out whatever the size of new list

	ScreenMgrDlogMapPair_t *pPr;

	if(tagMap.size() == 0){

		return;

	}else{

		ScreenMgrDlogMapConstIt_t it = tagMap.begin();
		while(it != tagMap.end()){

			pPr = ( ScreenMgrDlogMapPair_t * )&(*it);
			m_ctlScreenTagCombo.AddString(pPr->first);
			it++;

		} // for(int i=0;i<tags.size();i++)
	}

	int pos = m_ctlScreenTagCombo.FindStringExact( 0, m_csInitialWidgetGroup );
	if(pos != CB_ERR)
		m_ctlScreenTagCombo.SetCurSel(pos);
}


BOOL CCreateGuiFileDlog::OnInitDialog()
{
	CDialog::OnInitDialog();

	ScreenMgrDlogMap_t screenTagMap;
	m_pProjectMetaData->getScreenTagMgrData( screenTagMap );

	UpdateData();

	setScreenTags( screenTagMap );

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

LucidErrEnum CCreateGuiFileDlog::getGuiFileEssentials(GuiFileEssentialData_t &fileData)
{
	fileData.fileHostNameStub = m_csNewFileName;
	fileData.fileDescr = m_csFileDescrip;
	fileData.screenTag = m_csWidgetGroup;

	return kErr_NoErr;
}

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


	return kErr_NoErr;
	
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
void CCreateGuiFileDlog::OnCbnCloseupScrntagCombo()
{
	/*
	int curSel = CB_ERR;

	if( (curSel = m_ctlScreenTagCombo.GetCurSel()) == CB_ERR){

		m_csTagSelection = "";

	}else{

		m_ctlScreenTagCombo.GetLBText( curSel, m_csTagSelection );
	}*/
}

void CCreateGuiFileDlog::OnEnChangeEditDescrip()
{
	UpdateData();
	m_ctlEditDescrip.GetWindowText(m_csFileDescrip);

}

void CCreateGuiFileDlog::OnEnChangeEditFilename()
{
//	m_ctl_EditFileName.GetWindowText(m_csNewFileName);
}

void CCreateGuiFileDlog::OnStnClickedStaticDescrip()
{
	// TODO: Add your control notification handler code here
}
