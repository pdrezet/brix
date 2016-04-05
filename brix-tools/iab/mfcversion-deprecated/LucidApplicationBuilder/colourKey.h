#if !defined(AFX_COLOURKEY_H__9010B458_1EB1_4E0B_8867_A1983D99483C__INCLUDED_)
#define AFX_COLOURKEY_H__9010B458_1EB1_4E0B_8867_A1983D99483C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// colourKey.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ColourKey dialog

class ColourKey : public CDialog
{
// Construction
public:
	ColourKey(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ColourKey)
	enum { IDD = IDD_COLOUR_KEY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ColourKey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ColourKey)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLOURKEY_H__9010B458_1EB1_4E0B_8867_A1983D99483C__INCLUDED_)
