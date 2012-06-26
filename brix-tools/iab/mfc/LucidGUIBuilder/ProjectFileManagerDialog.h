#pragma once

#define PROJFILEMGRDLOG_FRAME_STUB_CAPTION "File manager For Project "
#define PROJFILEMGRDLOG_NULL_PROJ_STR "<NO PROJECT SET>"
#define PROJFILEMGRDLOG_FRAME_SCREEN_CLASH_WARNING " - WARNING - SCREENTAG CLASH!!!"

#include "Resource.h"

#include <vector>
#include <set>
#include "../common/LucidTypedefs.h"
//#include "ProjectFileListBox.h"
#include "../common/ProjectMetaData.h"
#include "afxwin.h"
#include "LgbListCtrl.h"
#include "LgbProjFileMgrTabCtrl.h"

using namespace std;

// ProjectFileManagerDialog dialog

class ProjectFileManagerDialog : public CDialog
{
	DECLARE_DYNAMIC(ProjectFileManagerDialog)

public:
	ProjectFileManagerDialog(
		ProjectMetaData *pPMD,
		CWnd* pParent = NULL);   // standard constructor

	virtual ~ProjectFileManagerDialog();

// Dialog Data
	enum { IDD = IDD_PROJ_FILE_MGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void updateDisplayWithUnderlyingData( const int &tabIndex = -1 );
	//vector<GuiFileMonty_t> m_vContents;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenprojBtn();
	afx_msg void OnBnClickedCloseprojBtn();
	afx_msg void OnBnClickedNewfileBtn();
	afx_msg void OnBnClickedTagdlogBtn();
	afx_msg void OnBnClickedDeletefileBtn();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLbnDblclkFileList();
	afx_msg void OnBnClickedDismiss();
	afx_msg void OnBnClickedOpenThenDismiss();

	virtual BOOL OnInitDialog();
	ProjectMetaData		*m_pProjectMetaData;

protected:


	//CButton m_ctlCloseProjBtn;
	//CButton m_ctlOpenProjBtn;
	CButton m_ctlDeleteFileBtn;
	CButton m_ctlNewFileBtn;
	CButton m_ctlScreenTagDlogBtn;
	CButton m_ctlOpenFileBtn;

public:
	//afx_msg void OnBnClickedOpenBtn();
	afx_msg void OnBnClickedCopyBtn();
	//void setFrameCaption();
protected:
	//CListBox m_ctlScreenList;
	//CListBox m_ctlFileList;
	//CListBox m_ctlScreenDesrcripList;
	//CListBox m_ctlFileDescripList;
	CButton m_ctlCopyBtn;

public:
	afx_msg void OnLbnSelchangeFileList();

protected:
	vector<GuiFileEssentialData_t> m_vCurrentSelections;
	//CString m_csCurrentlySelectedFile;
	//CString m_csCurrentlySelectedFileDescrip;
	//CString m_csCurrentlySelectedFileScreenTag;

public:

	int loadCurrentSelections(void);
	bool somethingIsSelected(void);
protected:
	CButton m_ctlOpenThenDismissBtn;
public:
	LgbProjFileMgrTabCtrl m_ctlTab_WidgetGroups;
public:
	LgbListCtrl m_ctlListC_Layouts;
	CString getCurrentTabLabel();
	void processTabChange( const int &tabIndex );
	void processListChange();

private:

	void setupListColumns();
	void setupTabs( const int &tabIndex );
	void loadLayoutData();//const CString &widgetGroup);

	afx_msg void OnNMClickListctrlLayouts(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedOpenAllActive();
	afx_msg void OnTcnSelchangeTabWidgetgrpTab(NMHDR *pNMHDR, LRESULT *pResult);
};
