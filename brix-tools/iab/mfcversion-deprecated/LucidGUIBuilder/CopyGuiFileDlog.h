#pragma once
#include "afxwin.h"
#include "Resource.h"
#include "../common/ProjectMetaData.h"

// CCopyGuiFileDlog dialog

class CCopyGuiFileDlog : public CDialog
{
	DECLARE_DYNAMIC(CCopyGuiFileDlog)

public:

	CCopyGuiFileDlog(	ProjectMetaData *pPMD, 
					   const CString &origFileName,
					   const CString &origFileDescrip,
					   CWnd* pParent =NULL );

	virtual ~CCopyGuiFileDlog();

// Dialog Data
	enum { IDD = IDD_COPY_GUIFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

protected:

public:
	CString m_csOrigFileName;
	CString m_csOrigFileDescription;

	CString m_csNewFileName;
	CString m_csNewFileDescription;

protected:
	virtual void OnOK();

	CEdit m_ctlOrigFileName;
	CEdit m_ctlOrigFileDescrip;

	CEdit m_ctlNewFileName;
	CEdit m_ctlNewFileDescrip;

public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnEnChangeEditNewfileName();
public:
	afx_msg void OnStnClickedStaticFilename();
public:
	afx_msg void OnBnClickedOk();
};
