// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "afxext.h"
#if !defined(AFX_MAINFRM_H__C30D302A_8FCF_11D3_A9AC_00001C21326E__INCLUDED_)
#define AFX_MAINFRM_H__C30D302A_8FCF_11D3_A9AC_00001C21326E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "LgbZOrderDlogBar.h"

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

	void SetZctrltoolBarVisible( const bool &visible );

// Operations
public:


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

//void SetWindowText(
//   LPCTSTR lpszString 
//);

// Implementation

public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CComboBox	m_combo;


	LgbZOrderDlogBar m_cZOrderDlogBar;
	//LgbZOrderDlogBar m_cZOrderDlogBar2;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void resetChildTitles(void);
protected:
	CToolBar m_wndToolBarAlign;
	CToolBar m_wndToolBarOptions;

	//LgbToolBar m_wndToolBarZControl;
public:

	afx_msg LRESULT OnUWMOpenLayout(WPARAM, LPARAM);

	afx_msg void OnToolbarAlignment();
	afx_msg void OnUpdateToolbarAlignment(CCmdUI *pCmdUI);

	afx_msg void OnToolbarOptions();
	afx_msg void OnUpdateToolbarOptions(CCmdUI *pCmdUI);

	afx_msg void OnToggleToolbarStandard();
	afx_msg void OnUpdateToolbarStandard(CCmdUI *pCmdUI);

	BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct); 

	void uwmOpenLayout(const CString & fileName);
	void DockControlLeftOf(CToolBar * bar1, CToolBar * bar2);

public:
	afx_msg void OnViewZctrltoolBarViz();
	afx_msg void OnUpdateViewZctrlToolbarViz(CCmdUI *pCmdUI);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);//!< Called whenever slider pos moved
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
public:
	LgbZOrderDlogBar * getZOrderDlogBarPtr(void);
		void setFrameCaption();
public:
	afx_msg void OnToolbarsOptions();
public:
	afx_msg void OnUpdateToolbarsOptions(CCmdUI *pCmdUI);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__C30D302A_8FCF_11D3_A9AC_00001C21326E__INCLUDED_)
