/** @file Properties_textbox.h
 * Represents the LGB properties dialog for selections including only textbox icons
 * @author: Matthew Rutherford
 * @version: $Revision: 577 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */
#pragma once

#include "resource.h"
#include "Resource.h"
#include "afxwin.h"
#include "LgbColorsDef.h"
#include "LucidTypedefs.h"
#include "ProjectMetaData.h"
#include "LgbTextIcon.h"
#include "IconSelection.h"
#include "ReadOnlyEdit.h"
#include "LgbColorsDef.h"
#include "afxcmn.h"

class CProperties_textbox : public CDialog
{
	DECLARE_DYNAMIC(CProperties_textbox)

public:

	//! Constructor
	/*!
	\param pProjMetaData ptr to project's meta data
	\param iconSeln an IconSelection pre-loaded with ptrs to all the textbox icons selected by the user
	\param parent window
	*/	CProperties_textbox(
						ProjectMetaData *  pProjMetaData, 
						//LgbUndoStore  *pUndoStore,
						IconSelection< LgbTextIcon >  &iconSeln,
						CWnd* pParent = NULL); 
		
	virtual ~CProperties_textbox();


	enum { IDD = IDD_PROPERTIES_TEXTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	LgbColorsDef m_cColors;

	DECLARE_MESSAGE_MAP()

private:
	bool m_bColorsDiffer;
	int m_iPrevLeftIndent;
	int m_iPrevRightIndent;
	int m_iPrevTopIndent;
	int m_iPrevBottomIndent;
	int m_iPrevVertExtent;
	int m_iPrevWidth;
	vector<InlineText> m_vInlineTextVec;

public:
	ProjectMetaData *m_pProjectMetaData;
	IconSelection< LgbTextIcon > m_cIconSeln;

	virtual BOOL OnInitDialog();

	CEdit m_x1; //!< left border pos
	CEdit m_x2; //!< right border pos
	CEdit m_y1; //!< top border pos
	CEdit m_y2; //!< bottom border pos

	CEdit m_ctlEditWidth;		//!< Editable field for width (user can resize bitmaps willy-nilly).
	CEdit m_ctlEditVertExtent;	//!< Editable field for vert extent (user can resize bitmaps willy-nilly).
	CEdit m_ctlEditType;		//!< Read-only field for type 
	CEdit m_ctlEditTag;			//!< Read-only field for tag

	CEdit m_ctlEditZOrder;
	//CEdit m_ctlEditWidth;
	//CEdit m_ctlEditVertExtent;

	int m_Bevel;
	afx_msg void OnBnClickedTextboxOk();
	afx_msg void OnBnClickedFgColourpicker();
	afx_msg void OnBnClickedTextColor();
	afx_msg void OnBnClickedButtonBgColor();
	//CString m_csDecsrip;

	void setColors( const LgbColorsDef &colors); //!< Set icons foreground (text) and background (fill) colors

public:
	CReadOnlyEdit m_ctlEditColouredText; //!< read-only edit field that 'demos' the fore- and background colors on the dlog
	afx_msg void OnEnChangeDescription();

	afx_msg void OnEnKillfocusY1();
	afx_msg void OnEnKillfocusVertextent();
	afx_msg void OnEnKillfocusY2();
	afx_msg void OnEnKillfocusWidth();
	afx_msg void OnEnKillfocusX2();
	afx_msg void OnEnKillfocusX1();


public:
	afx_msg void OnEnKillfocusEditPcBgTransp();
	afx_msg void OnEnKillfocusEditPcFgTransp();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CEdit m_ctlEditBgTransp;
	CEdit m_ctlEditFgTransp;
	CSliderCtrl m_ctlSliderFgTransp;
	CSliderCtrl m_ctlSliderBgTransp;
	afx_msg void OnEnChangeEditOpacity2();
	CEdit xEditOpacityBg;
	afx_msg void OnEnChangeEditOpacity3();
	afx_msg void OnNMCustomdrawSliderFgTransp(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_ctlComboFont;
	CEdit m_ctlEditLeftIndent;
	CEdit m_ctlEditRightIndent;
	CEdit m_ctlEditTopIndent;
	CEdit m_ctlEditBottomIndent;
	CEdit m_ctlEditLineSpacing;
	afx_msg void OnEnKillfocusEditLeftIndent();
	afx_msg void OnEnKillfocusEditRightIndent();
	afx_msg void OnEnKillfocusEditTopIndent();
	afx_msg void OnEnKillfocusEditBottomIndent();
	CEdit m_ctlEditNumberOfLines;
	afx_msg void OnEnKillfocusEditLineSpacing();
	afx_msg void OnBnClickedButtonInlineText();
	CButton m_ctlFgColorButton;
	CButton m_ctlBgColorButton;
};
