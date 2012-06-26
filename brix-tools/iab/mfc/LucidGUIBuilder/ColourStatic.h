
#pragma once

// ColourStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ColourStatic window

class ColourStatic : public CStatic
{
// Construction
public:
	ColourStatic();

// Attributes
public:
	CBrush m_brBkgnd; // Holds Brush Color for the Static Text
	COLORREF m_crBkColor; // Holds the Background Color for the Text
	COLORREF m_crTextColor; // Holds the Color for the Text

// Operations
public:
	void SetTextColor(COLORREF crColor); // This Function is to set the Color for the Text.
	void SetBkColor(COLORREF crColor); // This Function is to set the BackGround Color for the Text.

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ColourStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ColourStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(ColourStatic)
	//afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

