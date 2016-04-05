#pragma once

#include "resource.h"
#include "afxwin.h"
#include "LgbColorsDef.h"
#include "InlineText.h"
#include "afxcmn.h"
#include "LgbFont.h"
#include "TextStyleListBox.h"

#include "odrawlbox.h"
#include "picdrawc.h"

// CInlineTextDialog dialog

class CInlineTextDialog : public CDialog
{
	DECLARE_DYNAMIC(CInlineTextDialog)

public:
	CInlineTextDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInlineTextDialog();

	virtual BOOL OnInitDialog();

// Dialog Data
	enum { IDD = IDD_INLINE_TEXT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	LgbColorsDef m_cColors;

	DECLARE_MESSAGE_MAP()

	// attributes
private:
	vector<InlineText> m_vInlineTextVec;
	vector<LgbFont> m_vFontVec;

	// methods
public:
	void RemoveInlineTextFromVec(CString csClass);
	void GetInlineTextVec(vector<InlineText> &vInlineTextVec);
	void SetInlineTextVec(vector<InlineText> vInlineTextVec);
	bool IsClassInVec(CString csClass);
	void SetColor(LgbColorsDef cColors);
	void SetAlpha(int iAlpha);
	void GetInlineTextFromVec(CString csClass, InlineText &xInlineText);
	void UpdateInlineTextInVec(CString csClass, InlineText xInlineText);
	void UpdateListbox();
	void SetFontVec(vector<LgbFont> vFontVec);

protected:
	void SetTextStyleBgColor();

public:
	CEdit m_ctlEditClass;
	CComboBox m_ctlComboFont;
	afx_msg void OnBnClickedButtonColour();
	afx_msg void OnBnClickedButtonAdd();
	CPicDrawC m_picDrawc;
	// ***REVISIT*** SDG: This was my attempt to load a bitmap of the text into the listbox
	//CODrawLBox m_ctlListClass;
	TextStyleListBox m_ctlListClass;
	afx_msg void OnBnClickedButtonDelete();
	CEdit m_ctlEditTransp;
	CSliderCtrl m_ctlSliderTransp;
	afx_msg void OnNMCustomdrawSliderTransp(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnKillfocusEditInlinePcTransp3();
	afx_msg void OnLbnSelchangeListClass();
	afx_msg void OnBnClickedButtonUpdate();
	CButton m_ctlButtonDelete;
	CButton m_ctlUpdateButton;
};
