/** @file Properties_Drawable.h
 * Represents the LGB properties dialog for selections including both bitmaps and textboxes
 * @author: Matthew Rutherford
 * @version: $Revision: 577 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */
#pragma once

#include "Resource.h"

#include "LucidTypedefs.h"
#include "ProjectMetaData.h"
#include "LgbTextIcon.h"
#include "LgbPatchIcon.h"
#include "LgbImageIcon.h"
#include "IconSelection.h"
#include "afxwin.h"


//! LGB properties dialog for selections including both bitmaps and textboxes
class CProperties_Drawable : public CDialog
{
	DECLARE_DYNAMIC(CProperties_Drawable)

public:
	//! Constructor
	CProperties_Drawable(	ProjectMetaData *pProjMetaData, 
							IconSelection< LgbTextIcon >	&txtIconSeln,
							IconSelection< LgbPatchIcon >	&ptchIconSeln,
							IconSelection< LgbImageIcon >  &bmpIconSeln,
							CWnd* pParent = NULL );

	virtual ~CProperties_Drawable();

// Dialog Data
	enum { IDD = IDD_PROPERTIES_DRAWABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()


public:

	ProjectMetaData *m_pProjectMetaData;
	IconSelection< LgbTextIcon > m_cTxtIconSeln;
	IconSelection< LgbPatchIcon > m_cPatchIconSeln;
	IconSelection< LgbImageIcon > m_cBmpIconSeln;

	virtual BOOL OnInitDialog();

	CEdit m_x1;					//!< border's LH edge
	CEdit m_x2;					//!< border's RH edge
	CEdit m_y1;					//!< border's top edge
	CEdit m_y2;					//!< border's bottom edge

	CEdit m_ctlEditZOrder;		//!< field for zpos
	CEdit m_ctlEditWidth;		//!< filed for icons' width
	CEdit m_ctlEditVertExtent;	//!< field for icons' vert extent

	afx_msg void OnBtnClickedOk();
	//afx_msg void OnEnKillfocusY1();			//!< Fired when focus leaves 'border top' field
	//afx_msg void OnEnKillfocusVertextent();	//!< Fired when focus leaves 'border top' field
	//afx_msg void OnEnKillfocusY2();		//!< Fired when focus leaves 'border bottom' field
	//afx_msg void OnEnKillfocusWidth();	//!< Fired when focus leaves 'width' field
	//afx_msg void OnEnKillfocusX2();		//!< Fired when focus leaves 'right' field
//	afx_msg void OnEnKillfocusX1();		//!< Fired when focus leaves 'left' field

public:
	//CEdit m_ctlEditPcTransp;
};

