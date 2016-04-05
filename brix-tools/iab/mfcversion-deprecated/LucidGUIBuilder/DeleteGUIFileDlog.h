#pragma once
#include "afxwin.h"
#include "Resource.h"

// CDeleteGUIFileDlog dialog

class CDeleteGUIFileDlog : public CDialog
{
	DECLARE_DYNAMIC(CDeleteGUIFileDlog)

public:
	CDeleteGUIFileDlog(const CString &hostFilename, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDeleteGUIFileDlog();

// Dialog Data
	enum { IDD = IDD_DELETE_GUI_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedFileDeleteButton();
	afx_msg void OnBnClickedCancel();
	CButton m_ctl_ButtonCancel;
	CButton m_ctl_ButtonConfirm;
	CEdit m_ctl_EditFileName;
	virtual BOOL OnInitDialog();
protected:
	CString m_csHostFileName;
public:
	afx_msg void OnBnClickedConfirm();
};
