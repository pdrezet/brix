/** @file Properties_Drawable.cpp
 * implementaation of Properties_Drawable class
 * @author: Matthew Rutherford
 * @version: $Revision: 577 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */

#include "stdafx.h"
#include "Properties_Drawable.h"


// CProperties_Drawable dialog

IMPLEMENT_DYNAMIC(CProperties_Drawable, CDialog)

//! Constructor
/*!
	\param pProjMetaData		Ptr to Projeect meta data
				txtIconSeln		set of text icons, selected prior to invocation of this dlog
				bmpIconSeln		set of bitmap icons, selected prior to invocation of this dlog
				pParent			dlog's parent window								
*/
CProperties_Drawable::CProperties_Drawable(	ProjectMetaData *pProjMetaData, 
											IconSelection< LgbTextIcon >	&txtIconSeln,
											IconSelection< LgbPatchIcon >	&ptchIconSeln,
											IconSelection< LgbImageIcon >  &bmpIconSeln,
											CWnd* pParent /*=NULL*/)
											: CDialog(CProperties_Drawable::IDD, pParent),
											m_cTxtIconSeln ( txtIconSeln ),
											m_cPatchIconSeln ( ptchIconSeln ),
											m_cBmpIconSeln ( bmpIconSeln )
{
	m_pProjectMetaData = pProjMetaData;
}


CProperties_Drawable::~CProperties_Drawable()
{ }

void CProperties_Drawable::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_X1, m_x1);
	//DDX_Control(pDX, IDC_X2, m_x2);
	//DDX_Control(pDX, IDC_Y1, m_y1);
//	DDX_Control(pDX, IDC_Y2, m_y2);
	DDX_Control(pDX, IDC_ZORDER, m_ctlEditZOrder);
//	DDX_Control(pDX, IDC_WIDTH, m_ctlEditWidth);
//	DDX_Control(pDX, IDC_VERTEXTENT, m_ctlEditVertExtent);
	//DDX_Control(pDX, IDC_EDIT_PC_TRANSP, m_ctlEditPcTransp);
}


BEGIN_MESSAGE_MAP(CProperties_Drawable, CDialog)
	ON_BN_CLICKED(IDOK, &CProperties_Drawable::OnBtnClickedOk)
//	ON_EN_KILLFOCUS(IDC_Y1, &CProperties_Drawable::OnEnKillfocusY1)
//	ON_EN_KILLFOCUS(IDC_Y2, &CProperties_Drawable::OnEnKillfocusY2)
//	ON_EN_KILLFOCUS(IDC_X2, &CProperties_Drawable::OnEnKillfocusX2)
//	ON_EN_KILLFOCUS(IDC_X1, &CProperties_Drawable::OnEnKillfocusX1)
END_MESSAGE_MAP()


// CProperties_Drawable message handlers

BOOL CProperties_Drawable::OnInitDialog()
{

	CDialog::OnInitDialog();

	// Scan the selected text icons for field equalities
	LgbTextIcon::Scan txtScan;
	txtScan =  m_cTxtIconSeln.processEquality();

	// Scan the selected patch icons for field equalities
	LgbPatchIcon::Scan ptchScan;
	ptchScan =  m_cPatchIconSeln.processEquality();

	// Scan the selected bitmap icons for field equalities
	LgbImageIcon::Scan bmpScan;
	bmpScan =  m_cBmpIconSeln.processEquality();

	// Get an example text and bmp icon - any will do - so that if a given field is
	// common to all icons, we can use the 'eg icon' to get the actual value.
	//LgbDrawable *pIcon = NULL;

	LgbTextIcon *egTxtIcon = NULL;
	LgbPatchIcon *egPtchIcon = NULL;
	LgbImageIcon *egBmpIcon = NULL;



	int iMinZPos;
	int iMaxZPos;

	bool bGotGoodIcon = false;

	if(m_cTxtIconSeln.size() > 0){

		if(!bGotGoodIcon){
			iMinZPos = m_cTxtIconSeln.m_vContents.front()->m_iZPosUser;
			iMaxZPos = iMinZPos;
			bGotGoodIcon = true;
		}else{
			iMinZPos = min(iMinZPos, m_cTxtIconSeln.m_vContents.front()->m_iZPosUser );
			iMaxZPos = max(iMaxZPos, m_cTxtIconSeln.m_vContents.front()->m_iZPosUser );;
		}

	}
	
	if(m_cPatchIconSeln.size() > 0) {

		if(!bGotGoodIcon){
			iMinZPos = m_cPatchIconSeln.m_vContents.front()->m_iZPosUser;
			iMaxZPos = iMinZPos;
			bGotGoodIcon = true;
		}else{
			iMinZPos = min(iMinZPos, m_cPatchIconSeln.m_vContents.front()->m_iZPosUser );
			iMaxZPos = max(iMaxZPos, m_cPatchIconSeln.m_vContents.front()->m_iZPosUser );;
		}
	}

	if(m_cBmpIconSeln.size() > 0) {

		if(!bGotGoodIcon){
			iMinZPos = m_cBmpIconSeln.m_vContents.front()->m_iZPosUser;
			iMaxZPos = iMinZPos;
			bGotGoodIcon = true;
		}else{
			iMinZPos = min(iMinZPos, m_cBmpIconSeln.m_vContents.front()->m_iZPosUser );
			iMaxZPos = max(iMaxZPos, m_cBmpIconSeln.m_vContents.front()->m_iZPosUser );;
		}

	}

	int iExampleZPos = -999; // any silly initial value.
	bool bInterGroupZPosIsConsistent = ( iMinZPos == iMaxZPos );

	if ( bInterGroupZPosIsConsistent )
		iExampleZPos = iMinZPos;

	char buffer[16];

	bool bSetValue = false;

	// If the value IS common, initialise the dlog's field to that value.
	// Otherwise leave the field blank.

	bool bEachGroupZPosIsSelfConsistent = false;

	if (bInterGroupZPosIsConsistent){

		// OK! We know that the 1st icon of each non-zero size group has the same z-value.
		// Determine now if each group of icons have the same z-pos values within itself.
		// If so, then this proves that all the icons have the same z-value.

		 bEachGroupZPosIsSelfConsistent =	txtScan.m_cDrblScan.m_bSameZPos && 
												ptchScan.m_cDrblScan.m_bSameZPos &&
												bmpScan.m_cDrblScan.m_bSameZPos;
	}


	if( bEachGroupZPosIsSelfConsistent && bInterGroupZPosIsConsistent ){
		_itoa_s( iExampleZPos, buffer, 16, 10 );
		m_ctlEditZOrder.SetWindowText( buffer );
	}else{
		m_ctlEditZOrder.SetWindowText("");
	}


	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control

}

void CProperties_Drawable::OnBtnClickedOk()
{

	UpdateData();

	CString dumCs;

	//Set the values of all icons to the non-blank values of the dialog

	// Text Icons
	for(size_t i=0;i<m_cTxtIconSeln.size();i++){

		LgbTextIcon *pIcon = NULL;
		pIcon = m_cTxtIconSeln.getItem(i);

		m_ctlEditZOrder.GetWindowTextA(dumCs);
		if(dumCs.GetLength() > 0){
			pIcon->m_iZPosUser = atoi(dumCs);
		}

	} // for(int i=0;i<m_vpIcon.size();i++)


	// Patch Icons
	for(size_t i=0;i<m_cPatchIconSeln.size();i++){

		LgbPatchIcon *pIcon = NULL;
		pIcon = m_cPatchIconSeln.getItem(i);

		m_ctlEditZOrder.GetWindowTextA(dumCs);
		if(dumCs.GetLength() > 0){
			pIcon->m_iZPosUser = atoi(dumCs);
		}

	} // for(int i=0;i<m_vpIcon.size();i++)


	// Bitmap Icons
	for(size_t i=0;i<m_cBmpIconSeln.size();i++){

		LgbImageIcon *pIcon = NULL;
		pIcon = m_cBmpIconSeln.getItem(i);

		m_ctlEditZOrder.GetWindowTextA(dumCs);
		if(dumCs.GetLength() > 0){
			pIcon->m_iZPosUser = atoi(dumCs);
		}


	} // for(int i=0;i<m_vpIcon.size();i++)
	CDialog::OnOK();

}
