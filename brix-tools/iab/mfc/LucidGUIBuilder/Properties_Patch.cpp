/** @file Properties_Patch.cpp
 * Implementation of Properties_Textbox class
 * @author: Matthew Rutherford
 * @version: $Revision: 577 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */

#include "stdafx.h"
#include "Properties_Patch.h"
#include "LgbPatchIcon.h"
#include "IconSelection.h"
#include "LgbColorsDef.h"
#include "LgbUndoStore.h"
#include "../common/LucidConstants.h"
#include "../common/GlobalFuncs_2.h"
#include "ReadOnlyEdit.h"
#include "Resource.h"

IMPLEMENT_DYNAMIC(CProperties_Patch, CDialog)

CProperties_Patch::CProperties_Patch(	ProjectMetaData *pProjMetaData, 
											IconSelection< LgbPatchIcon >  &iconSeln,
											CWnd* pParent /*=NULL*/)
											: CDialog(CProperties_Patch::IDD, pParent),
											m_cIconSeln ( iconSeln )
{
	m_pProjectMetaData = pProjMetaData;
	m_Bevel = 0;
}


CProperties_Patch::~CProperties_Patch()
{
}

void CProperties_Patch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_X1, m_x1);
	DDX_Control(pDX, IDC_X2, m_x2);
	DDX_Control(pDX, IDC_Y1, m_y1);
	DDX_Control(pDX, IDC_Y2, m_y2);
	DDX_Control(pDX, IDC_COLOURPICKER_RESULT, m_ctlEditColouredBlankText);
	DDX_Control(pDX, IDC_ZORDER, m_ctlEditZOrder);
	DDX_Control(pDX, IDC_WIDTH, m_ctlEditWidth);
	DDX_Control(pDX, IDC_VERTEXTENT, m_ctlEditVertExtent);
	DDX_Control(pDX, IDC_TAG, m_ctlEditTag);
	DDX_Control(pDX, IDC_TYPE, m_ctlEditType);
	DDX_Control(pDX, IDC_EDIT_PC_BG_TRANSP, m_ctlEditBgTransp);
	DDX_Control(pDX, IDC_SLIDER_BG_TRANSP, m_ctlSliderBgTransp);
	DDX_Control(pDX, IDC_BUTTON_PROPTEXT_BG_COLOR, m_ctlBgColorButton);
}


BEGIN_MESSAGE_MAP(CProperties_Patch, CDialog)
	ON_BN_CLICKED(ID_TEXTBOX_OK, &CProperties_Patch::OnBnClickedTextboxOk)
	ON_BN_CLICKED(IDC_BUTTON_PROPTEXT_BG_COLOR, &CProperties_Patch::OnBnClickedButtonBgColor)
	ON_EN_KILLFOCUS(IDC_Y1, &CProperties_Patch::OnEnKillfocusY1)
	ON_EN_KILLFOCUS(IDC_VERTEXTENT, &CProperties_Patch::OnEnKillfocusVertextent)
	ON_EN_KILLFOCUS(IDC_Y2, &CProperties_Patch::OnEnKillfocusY2)
	ON_EN_KILLFOCUS(IDC_WIDTH, &CProperties_Patch::OnEnKillfocusWidth)
	ON_EN_KILLFOCUS(IDC_X2, &CProperties_Patch::OnEnKillfocusX2)
	ON_EN_KILLFOCUS(IDC_X1, &CProperties_Patch::OnEnKillfocusX1)
	ON_EN_KILLFOCUS(IDC_EDIT_PC_BG_TRANSP, &CProperties_Patch::OnEnKillfocusEditPcBgTransp)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


BOOL CProperties_Patch::OnInitDialog()
{
	// The icons of type bitmap were loaded into an IconSelection instance by the view just before this dialog was
	// created, and a local copy made of this in the construtor.
	// We now scan the collection to see whether all the (eg) top borders have the same position.
	// If they do, we load this value into the field in the dialog.  If however the icons differ in value for this
	// field, the field is set to blank.
	CDialog::OnInitDialog();

	m_ctlSliderBgTransp.SetRange(0, 255);
	m_bColorsDiffer = false;

	LgbPatchIcon::Scan scan;

	if(m_cIconSeln.size() == 1){

		scan.init();

	} else {

		scan =  m_cIconSeln.processEquality();

	}

	LgbPatchIcon *pIcon = NULL;
	pIcon = m_cIconSeln.m_vContents.front();

	char buffer[16];

	if(scan.m_cDrblScan.m_bSameTag){
		m_ctlEditTag.SetWindowText(pIcon->m_csTag);
	}else{
		m_ctlEditTag.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_ctlEditTag.EnableWindow(0);
	}

	if(scan.m_cDrblScan.m_bSameType){
		m_ctlEditType.SetWindowText(pIcon->m_csType);
	}else{
		m_ctlEditType.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_ctlEditType.EnableWindow(0);
	}



	if(scan.m_cDrblScan.m_bSameLft){
		_itoa_s(pIcon->m_cRect.left,buffer,16,10);
		m_x1.SetWindowText(buffer);
	}else{
		m_x1.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_x1.EnableWindow(0);
	}


	if(scan.m_cDrblScan.m_bSameRgt){
		_itoa_s(pIcon->m_cRect.right,buffer,16,10);
		m_x2.SetWindowText(buffer);
	}else{
		m_x2.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_x2.EnableWindow(0);
	}


	if(scan.m_cDrblScan.m_bSameTop){
		_itoa_s(pIcon->m_cRect.top,buffer,16,10);
		m_y1.SetWindowText(buffer);
	}else{
		m_y1.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_y1.EnableWindow(0);
	}


	if(scan.m_cDrblScan.m_bSameBtm){
		_itoa_s(pIcon->m_cRect.bottom,buffer,16,10);
		m_y2.SetWindowText(buffer);
	}else{
		m_y2.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_y2.EnableWindow(0);
	}


	if(scan.m_cDrblScan.m_bSameWidth){
		_itoa_s(pIcon->m_cRect.Width(),buffer,16,10);
		m_ctlEditWidth.SetWindowText(buffer);
	}else{
		m_ctlEditWidth.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_ctlEditWidth.EnableWindow(0);
	}


	if(scan.m_cDrblScan.m_bSameVrtExtnt){
		_itoa_s(pIcon->m_cRect.Height(),buffer,16,10);
		m_ctlEditVertExtent.SetWindowText(buffer);
	}else{
		m_ctlEditVertExtent.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_ctlEditVertExtent.EnableWindow(0);
	}


	if(scan.m_cDrblScan.m_bSameZPos){
		_itoa_s(pIcon->m_iZPosUser,buffer,16,10);
		m_ctlEditZOrder.SetWindowText(buffer);
	}else{
		m_ctlEditZOrder.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_ctlEditZOrder.EnableWindow(0);
	}

	if(scan.m_bSameBgAlpha){
		//int opacity = 100 * pIcon->m_iAlpha / 255;

		int alpha = pIcon->m_cColors.m_iBgAlpha;

		m_ctlSliderBgTransp.SetPos(255 - alpha);

		float dum = float( (255 - alpha ))/ float( 2.55 );
		sprintf_s( buffer, 16, "%3.1f", dum );
		m_ctlEditBgTransp.SetWindowText(buffer);
	}else{
		m_ctlSliderBgTransp.SetPos(0);
		m_ctlSliderBgTransp.EnableWindow(0);
		m_ctlEditBgTransp.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_ctlEditBgTransp.EnableWindow(0);
	}

	if(scan.m_bSameColors){
		m_cColors = pIcon->getColors();
		m_ctlEditColouredBlankText.SetBackColor( RGB(m_cColors.m_iBgRed, m_cColors.m_iBgGreen, m_cColors.m_iBgBlue) );
	}else{
		// signal to user that text colors are NOT same between icons.
		m_ctlEditColouredBlankText.SetBackColor( RGB(255, 255, 255) );
		m_bColorsDiffer = true;
		m_ctlBgColorButton.EnableWindow(0);
	}

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control

}


void CProperties_Patch::OnBnClickedTextboxOk()
{

	UpdateData();

	// These are necessary for when 'enter' is pressed to dismiss the dialog.
	// Otherwise, the loss of focus event is not received to work out widths.
	// eg if you change the left-edge, then hit return, the icon should move, but
	// instead it resizes.

	OnEnKillfocusX1();
	OnEnKillfocusY1();

	LgbPatchIcon *pIcon = NULL;

	CString dumCs;

	int lft, rgt, top, btm, wdth, ht;
	int newLft, newRgt, newTop, newBtm;
	bool gdLft, gdRgt, gdTop, gdBtm, gdWdth, gdHt;

	for(size_t i=0;i<m_cIconSeln.size();i++){

		pIcon = m_cIconSeln.getItem(i);

		m_x1.GetWindowTextA(dumCs);
		if( dumCs != FLAG_DIFF_VALUE_FIELD ){
			lft = atoi(dumCs);
			gdLft = true;
			//pIcon->m_cRect.left = ( atoi(dumCs) );
		}else{
			gdLft = false;
		}

		m_x2.GetWindowTextA(dumCs);
		if( dumCs != FLAG_DIFF_VALUE_FIELD ){
			rgt = atoi(dumCs);
			gdRgt = true;
			//pIcon->m_cRect.left = ( atoi(dumCs) );
		}else{
			gdRgt = false;
		}

		m_ctlEditWidth.GetWindowTextA(dumCs);
		if( dumCs != FLAG_DIFF_VALUE_FIELD ){
			wdth = atoi(dumCs);
			gdWdth = true;
			//pIcon->m_cRect.left = ( atoi(dumCs) );
		}else{
			gdWdth = false;
		}

		// Process LH edge position.
		if( gdLft ){

			newLft = lft;  // If the position is explicitly set, this value must be adopted

		}else{

			if(gdRgt && gdWdth){
				// If width and rhs edge set, calculate lh edge from these
				newLft = rgt - wdth;
			}else{
				//Leave the edge where it is
				newLft = pIcon->m_cRect.left;
			}
		}


		// Process RH edge position.
		// This differs from the LHS process, because if the user changes the width, the
		// LHS is considered the 'anchor' side, and the right moves if the width but not
		// LHS or RHS are set explicitly.

		if( gdRgt ){ 

			newRgt = rgt;
		}else{

			if( gdWdth ){

				if( gdLft ){
					newRgt = lft + wdth;
				}else{
					//int oldWidth = pIcon->m_cRect.right - pIcon->m_cRect.left;
					newRgt = pIcon->m_cRect.left + wdth;
				}

			}else{
				// Move right as much as left has moved
				newRgt = pIcon->m_cRect.right + newLft - pIcon->m_cRect.left;
			}
		}




		// Top
		m_y1.GetWindowTextA(dumCs);
		if( dumCs != FLAG_DIFF_VALUE_FIELD ){
			top = atoi(dumCs);
			gdTop = true;
			//pIcon->m_cRect.left = ( atoi(dumCs) );
		}else{
			gdTop = false;
		}


		// Bottom
		m_y2.GetWindowTextA(dumCs);
		if( dumCs != FLAG_DIFF_VALUE_FIELD ){
			btm = atoi(dumCs);
			gdBtm = true;
			//pIcon->m_cRect.left = ( atoi(dumCs) );
		}else{
			gdBtm = false;
		}


		m_ctlEditVertExtent.GetWindowTextA(dumCs);
		if( dumCs != FLAG_DIFF_VALUE_FIELD ){
			ht = atoi(dumCs);
			gdHt = true;
			//pIcon->m_cRect.left = ( atoi(dumCs) );
		}else{
			gdHt = false;
		}


		// Process Top edge position.
		if( gdTop ){
			newTop = top;
		}else{
			if(gdBtm && gdHt){
				newTop = btm - ht;
			} else{
				newTop = pIcon->m_cRect.top;
			}
		}


		// Process Bottom edge position.
		// This differs from the Top edge process, because if the user changes the height, the
		// Top is considered the 'anchor' side, and the bottom moves if the height but not
		// top or bottom are set explicitly.

		if( gdBtm ){ 
			newBtm = btm;
		}else{
			if( gdHt ){
				if( gdTop ){
					newBtm = top + ht;
				}else{
					//int oldWidth = pIcon->m_cRect.right - pIcon->m_cRect.left;
					newBtm = pIcon->m_cRect.top + ht;
				}
			}else{
				// Move bottom as much as top has moved
				newBtm = pIcon->m_cRect.bottom + newTop - pIcon->m_cRect.top;
			}
		}


		// Condition to ensure no negative width or height - his causes graphics to blow-up

		newRgt = newRgt < newLft ? newLft+1 : newRgt;
		newBtm = newBtm < newTop ? newTop+1 : newBtm;

		pIcon->m_cRect.left = newLft;
		pIcon->m_cRect.right = newRgt;
		pIcon->m_cRect.top = newTop;
		pIcon->m_cRect.bottom = newBtm;

		m_ctlEditZOrder.GetWindowTextA(dumCs);
		if(dumCs != FLAG_DIFF_VALUE_FIELD && dumCs.GetLength() > 0){
			pIcon->m_iZPosUser = atoi(dumCs);
		}

		m_ctlEditBgTransp.GetWindowTextA(dumCs);
		if(dumCs != FLAG_DIFF_VALUE_FIELD){
		int pos = m_ctlSliderBgTransp.GetPos();
			pIcon->setAlpha( 255 - pos, LgbPatchIcon::LgbPatchIcon_FlagBackground );
		}

		if (!m_bColorsDiffer) {
			pIcon->setColors(m_cColors);
		}

	} // for(int i=0;i<m_vpIcon.size();i++)

	CDialog::OnOK();

}

void CProperties_Patch::OnBnClickedButtonBgColor()
{
	CHOOSECOLOR cc;                 // common dialog box structure 
	static COLORREF acrCustClr[16]; // array of custom colors 
	//HWND hwnd;                      // owner window
	//HBRUSH hbrush;                  // brush handle
	//static DWORD rgbCurrent;        // initial color selection

	// Initialize CHOOSECOLOR 
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = *(AfxGetApp()->m_pMainWnd);
	cc.lpCustColors = (LPDWORD) acrCustClr;
	cc.lpCustColors[0] = RGB(m_cColors.m_iBgRed, m_cColors.m_iBgGreen, m_cColors.m_iBgBlue );
	cc.rgbResult = RGB(m_cColors.m_iBgRed, m_cColors.m_iBgGreen, m_cColors.m_iBgBlue );
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
 
	if (ChooseColor(&cc)==TRUE) {
		m_cColors.m_iBgRed = GetRValue(cc.rgbResult);
		m_cColors.m_iBgGreen = GetGValue(cc.rgbResult);
		m_cColors.m_iBgBlue = GetBValue(cc.rgbResult);

		m_ctlEditColouredBlankText.SetBackColor( cc.rgbResult );

		UpdateData(false);
	}
}

void CProperties_Patch::OnEnChangeDescription()
{

}

void CProperties_Patch::OnEnKillfocusY1()
{
// if user changes value of 'top' edge of widget, AND if the 'height' field has a non-null
// value, assume height is to stay same, and move bottom.

	UpdateData();

	char buffer[20];

	CString csHeight;
	m_ctlEditVertExtent.GetWindowTextA(csHeight);

	CString csTop;
	m_y1.GetWindowTextA(csTop);

	if( (csTop!= FLAG_DIFF_VALUE_FIELD) && (csHeight!= FLAG_DIFF_VALUE_FIELD) ){

		int iVrtExt = atoi(csHeight);
		int iTop = atoi(csTop);
		int iCalc = iTop + iVrtExt;

		_itoa_s( iCalc, buffer,16,10);
		m_y2.SetWindowText(buffer);

		UpdateData(false);
	}

}

void CProperties_Patch::OnEnKillfocusVertextent()
{
	// if user changes vert extent, assume top is to stay same, and move bottom.
	OnEnKillfocusY1();
}

void CProperties_Patch::OnEnKillfocusY2()
{
	// if user changes bottom, assume width is to stay same, and move top.
	UpdateData();

	char buffer[20];

	CString csHeight;
	m_ctlEditVertExtent.GetWindowTextA(csHeight);

	CString csBottom;
	m_y2.GetWindowTextA(csBottom);

	if( (csBottom!= FLAG_DIFF_VALUE_FIELD) && (csHeight!= FLAG_DIFF_VALUE_FIELD) ){

		int iVrtExt = atoi(csHeight);
		int iBtm = atoi(csBottom);
		int iCalc = iBtm - iVrtExt;

		_itoa_s( iCalc, buffer,16,10);
		m_y1.SetWindowText(buffer);

		UpdateData(false);
	}
}

void CProperties_Patch::OnEnKillfocusWidth()
{
// if user changes width, assume left is to stay same, and move right.
	OnEnKillfocusX1();
}


void CProperties_Patch::OnEnKillfocusX1()
{
// if user changes left, assume width is to stay same, and move right.
	UpdateData();

	char buffer[20];
	CString csWidth;
	m_ctlEditWidth.GetWindowTextA(csWidth);

	CString csLeft;
	m_x1.GetWindowTextA(csLeft);


	if( (csLeft!= FLAG_DIFF_VALUE_FIELD) && (csWidth!= FLAG_DIFF_VALUE_FIELD) ){

		int iWidth = atoi(csWidth);
		int iLeft = atoi(csLeft);
		int iRight = iLeft + iWidth;

		_itoa_s( iRight, buffer,16,10);
		m_x2.SetWindowText(buffer);

		UpdateData(false);
	}
}


void CProperties_Patch::OnEnKillfocusX2()
{
// if user changes right, assume width is to stay same, and move left.
	UpdateData();

	char buffer[20];
	CString csWidth;
	m_ctlEditWidth.GetWindowTextA(csWidth);

	CString csRight;
	m_x2.GetWindowTextA(csRight);


	if( (csRight != FLAG_DIFF_VALUE_FIELD) && (csWidth!= FLAG_DIFF_VALUE_FIELD) ){

		int iWidth = atoi(csWidth);
		int iRight = atoi(csRight);
		int iLeft = iRight - iWidth;

		_itoa_s( iLeft, buffer,16,10);
		m_x1.SetWindowText(buffer);

		UpdateData(false);
	}
}

void CProperties_Patch::OnEnKillfocusEditPcBgTransp()
{
	CString dum;
	m_ctlEditBgTransp.GetWindowTextA(dum);
	double ddum = atof(dum);

	if(ddum>100.0)ddum=100.0;
	int idum = (int) ( (ddum/100.0) * 255);

	m_ctlSliderBgTransp.SetPos( idum );
}

void CProperties_Patch::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	char buffer[16];

	if(( CSliderCtrl *) pScrollBar == &m_ctlSliderBgTransp)
	{
		int idum = m_ctlSliderBgTransp.GetPos();

		if(idum>=0){
			float dum = float( (m_ctlSliderBgTransp.GetPos() ))/ float( 2.55 );
			sprintf_s( buffer, 16, "%3.1f", dum );
		}else{
			strcpy_s(buffer, 16, FLAG_DIFF_VALUE_FIELD );
		}
		m_ctlEditBgTransp.SetWindowText(buffer);
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
