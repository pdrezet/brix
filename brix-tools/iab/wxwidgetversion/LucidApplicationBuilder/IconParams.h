#ifndef _ICONPARAMS
#define _ICONPARAMS

// IconParams.h : header file
//
#include "../common/LucidConstants.h"
#include "Condat.h"
#include "ConDataTempStore.h"
//#include "afxwin.h"
//#include "explorer1.h"
#include "Porting_Classes/INXString.h"
#include "Porting_Classes/INXDialog.h"
//#include "ToolTipEdit.h"

/////////////////////////////////////////////////////////////////////////////
// IconParams dialog

class IconParams : public INXDialog
{
// Construction
public:
	IconParams(ConData* pBlob, Project* _pProject, void* pParent = NULL);   // standard constructor
	///////////IconParams & operator=( const IconParams &rhs );
	
	~IconParams();

	void transferDialogDataToCache();

// Dialog Data
	//{{AFX_DATA(IconParams)
	enum { IDD = IDD_PARAMETERS };
	//}}AFX_DATA

	//attributes
	INXString labels[MAXPARAMS];
	INXString values[MAXPARAMS];
	/* MFC
	CEdit* paramVal[MAXPARAMS];
	CStatic* paramLabel[MAXPARAMS];
	CComboBox* enumVal[MAXPARAMS];
	CStatic* nameLabel;
	CEdit* nameVal;
	CStatic* instLabel;
	CEdit* instVal;
	CStatic* descLabel;
	CEdit* descVal;
	CButton* screenTagButton;
	*/
	ConDataTempStore		mBlobTempStore;
	ConData		*pOrigBlob;
	Project* pProject;
	bool m_bIsWidget;

	// global variable. This is the initial parameter id. It is assigned in OnInitDialog(),
	// and is used in OnOK().
	UINT iInitParamID;

public:
	//methods
	bool isDigit(char c);
	void updateWidgetInProject();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(IconParams)
	protected:
	virtual void DoDataExchange(void* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(IconParams)
	virtual bool OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	void OnScreenTagManager();
	void OnSelChangeWidgetGroup();
	//DECLARE_MESSAGE_MAP()

public:
	//CButton m_ctlOK;

protected:
	bool errorsInData();
	bool IsFileName8Dot3Format(INXString csFileName);
/* Some Scroll state parms */
	int m_nCurHeight;
	int m_nScrollPos;
	INXRect m_rect;

public:
	//CExplorer1 html_control;
private:
void SetHTML();
protected:
// todo	virtual bool OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
//todo	void OnTimer(UINT_PTR nIDEvent);
public:
//todo 	void OnVScroll(UINT nSBCode, UINT nPos, void* pScrollBar);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ICONPARAMS_H__21B0273C_7D8A_47D4_B28E_E196A3896D90__INCLUDED_)
