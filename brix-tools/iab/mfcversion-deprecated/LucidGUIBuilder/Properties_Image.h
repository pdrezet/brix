/** @file Properties_Image.h
 * Represents the LGB properties dialog for selections including only bitmaps icons
 * @author: Matthew Rutherford
 * @version: $Revision: 577 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */

#pragma once
#include "../common/LucidTypedefs.h"
#include "LgbImageIcon.h"
#include "IconSelection.h"
#include <vector>
#include "Resource.h"
#include "afxwin.h"
#include "afxcmn.h"

class ProjectMetaData;
class LgbImageIcon;

class CProperties_Image : public CDialog
{
	DECLARE_DYNAMIC(CProperties_Image)

public:

	//! Constructor
	/*!
	\param pProjMetaData ptr to project's meta data
	\param iconSeln an IconSelection pre-loaded with ptrs to all the bitmap icons selected by the user
	\param parent window
	*/
	CProperties_Image(	
						ProjectMetaData *  pProjMetaData, 
						const IconSelection< LgbImageIcon >  &iconSeln,
						CWnd* pParent = NULL);   
	
	
	//! standard constructor
	virtual ~CProperties_Image();

// Dialog Data
	enum { IDD = IDD_PROPERTIES_IMAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void CProperties_Image::updateHeightIfAspectLocked();
	void CProperties_Image::updateWidthIfAspectLocked();

	DECLARE_MESSAGE_MAP()

public:

	IconSelection< LgbImageIcon > m_cIconSeln; //!< Local copy of IconSelection

	CEdit m_x1; //!< left border pos
	CEdit m_x2; //!< right border pos
	CEdit m_y1; //!< top border pos
	CEdit m_y2; //!< bottom border pos

	CComboBox	m_ctlImageFileCombo; //!< combo box for image file choice
	CEdit		m_ctl_EditZOrder;	 //!< Field for editing z-pos
	CButton		m_ctl_LockAspectRatioToImage;

	//int m_Bevel;
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnClickedOk();
	afx_msg void OnBnClickedImageLoadImage(); //!< Import a combobox into the project.
	afx_msg void OnBnClickedRadioTextcol();
	afx_msg void OnBnClickedBackcol();

	//COLORREF m_crColour;

	//void setPreferredTopLftCorner(const int & xVal, const int & yVal);

protected:
	//int m_iXpreferred;
	//int m_iYpreferred;
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	ProjectMetaData *m_pProjectMetaData; //!< Local copy of project's meta data.

//	IconSelection< LgbImageIcon >  m_cIconSeln;

public:
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);

	afx_msg void OnCbnSelchangeComboBmpfiles();
	afx_msg void OnEnChangeEditZOrder();
	afx_msg void OnStnClickedTagLabel();
	afx_msg void OnEnKillfocusX1();
	afx_msg void OnEnKillfocusX2();
	afx_msg void OnEnChangeY1();
	afx_msg void OnEnKillfocusY1();
	afx_msg void OnEnKillfocusY2();

	CEdit m_ctlEditWidth;		//!< Read-only field for width (user can't resize bitmaps willy-nilly).
	CEdit m_ctlEditVertExtent;	//!< Read-only field for vert extent (user can't resize bitmaps willy-nilly).
	CEdit m_ctlEditType;		//!< Read-only field for type 
	CEdit m_ctlEditTag;			//!< Read-only field for tag

public:
	CEdit m_ctlEditPcTransp;
	CSliderCtrl m_ctlSliderTransp;
	afx_msg void OnEnChangeEditPcTransp();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnKillfocusVertExtent();
	afx_msg void OnEnKillfocusWidth();
	afx_msg void OnCbnKillfocusComboBmpfiles();
public:
	afx_msg void OnBnClickedCheckLockaspectratio();

private:
	long m_iImageHeight;
	long m_iImageWidth;
	float m_dImageHtoW;

};
