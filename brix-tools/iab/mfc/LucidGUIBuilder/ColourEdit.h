#if !defined(AFX_COLOUREDIT_H__CB2FD7EA_8697_452F_891C_519854528B0E__INCLUDED_)
#define AFX_COLOUREDIT_H__CB2FD7EA_8697_452F_891C_519854528B0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColourEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ColourEdit window

class ColourEdit : public CEdit
{
// Construction
public:
	ColourEdit();

// Attributes
public:
protected:
	static CBrush m_brush;
	CBrush m_brBkgnd; // Holds Brush Color for the Edit Box
	COLORREF m_crBkColor; // Holds the Background Color for the Text
	COLORREF m_crTextColor; // Holds the Color for the Text

// Operations
public:
	//BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM Param, LRESULT* pLResult);
	void SetBkColor(COLORREF crColor); // This Function is to set the BackGround Color for the Text and the Edit Box.
	void SetTextColor(COLORREF crColor); // This Function is to set the Color for the Text.
	BOOL SetReadOnly(BOOL flag = TRUE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ColourEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ColourEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(ColourEdit)
	//kwhite afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HBRUSH ColourEdit::CtlColor(CDC* pDC, UINT nCtlColor) ;
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLOUREDIT_H__CB2FD7EA_8697_452F_891C_519854528B0E__INCLUDED_)
