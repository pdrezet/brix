#pragma once
#include "afxwin.h"
#include "Resource.h"
#include "../common/LucidEnums.h"
#include "../common/LucidTypedefs.h"

#include <vector>

using namespace std;

class ProjectMetaData;

// CCreateGuiFileDlog dialog

class CCreateGuiFileDlog : public CDialog
{
	DECLARE_DYNAMIC(CCreateGuiFileDlog)

public:
	CCreateGuiFileDlog(ProjectMetaData *pPMD, CString currentWidgetGroup, CWnd* pParent = NULL);   // standard constructor
	virtual ~CCreateGuiFileDlog();

// Dialog Data
	enum { IDD = IDD_CREATE_GUIFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	void setScreenTags(const ScreenMgrDlogMap_t &tags);
	CEdit m_ctl_EditFileName;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	void AddComboTag(const CString &tag);
	void GetNewFileName( CString &name) const;
	int GetTagForNewFile(CString &tag);

	afx_msg void OnEnChangeEditFilename();

private:
	//GuiFileEssentialData_t &m_cFileData;

protected:
	CComboBox m_ctlScreenTagCombo;
	ProjectMetaData *m_pProjectMetaData;
public:
	virtual BOOL OnInitDialog();
	LucidErrEnum getGuiFileEssentials(GuiFileEssentialData_t &fileData);

protected:
	CString m_csWidgetGroup;
	CString m_csNewFileName;

	CString m_csInitialWidgetGroup;
public:
	afx_msg void OnCbnCloseupScrntagCombo();
protected:
	CEdit m_ctlEditDescrip;
	CString m_csFileDescrip;
public:
	afx_msg void OnEnChangeEditDescrip();
public:
	afx_msg void OnStnClickedStaticDescrip();
};
