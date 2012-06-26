/** @file Properties_Patch.h
 * Represents the LGB properties dialog for selections including only textbox icons
 * @author: Matthew Rutherford
 * @version: $Revision: 1480 $
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
#include "LgbPatchIcon.h"
#include "IconSelection.h"
#include "ReadOnlyEdit.h"
#include "LgbColorsDef.h"
#include "afxcmn.h"

class CProperties_Patch : public CDialog
{
	DECLARE_DYNAMIC(CProperties_Patch)

public:

	//! Constructor
	/*!
	\param pProjMetaData ptr to project's meta data
	\param iconSeln an IconSelection pre-loaded with ptrs to all the textbox icons selected by the user
	\param parent window
	*/	CProperties_Patch(
						ProjectMetaData *  pProjMetaData, 
						IconSelection< LgbPatchIcon >  &iconSeln,
						CWnd* pParent = NULL
						); 
		
	virtual ~CProperties_Patch();


	enum { IDD = IDD_PROPERTIES_PATCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	LgbColorsDef m_cColors;

	DECLARE_MESSAGE_MAP()

private:
	bool m_bColorsDiffer;

public:
	ProjectMetaData *m_pProjectMetaData;
	IconSelection< LgbPatchIcon > m_cIconSeln;

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

	int m_Bevel;
	afx_msg void OnBnClickedTextboxOk();
	afx_msg void OnBnClickedButtonBgColor();

	void setColors( const LgbColorsDef &colors); //!< Set icons foreground (text) and background (fill) colors

public:
	CReadOnlyEdit m_ctlEditColouredBlankText; //!< read-only edit field that 'demos' the fore- and background colors on the dlog
	afx_msg void OnEnChangeDescription();

	afx_msg void OnEnKillfocusY1();
	afx_msg void OnEnKillfocusVertextent();
	afx_msg void OnEnKillfocusY2();
	afx_msg void OnEnKillfocusWidth();
	afx_msg void OnEnKillfocusX2();
	afx_msg void OnEnKillfocusX1();

public:
	afx_msg void OnEnKillfocusEditPcBgTransp();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CEdit m_ctlEditBgTransp;
	CSliderCtrl m_ctlSliderBgTransp;
	afx_msg void OnEnChangeEditOpacity2();
	CEdit xEditOpacityBg;
	afx_msg void OnEnChangeEditOpacity3();
	CButton m_ctlBgColorButton;
};
