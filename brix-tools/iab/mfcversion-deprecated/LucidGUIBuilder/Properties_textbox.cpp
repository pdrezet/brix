/** @file Properties_textbox.cpp
 * Implementation of Properties_Textbox class
 * @author: Matthew Rutherford
 * @version: $Revision: 577 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */

#include "stdafx.h"
#include "Properties_textbox.h"
#include "LgbTextIcon.h"
#include "IconSelection.h"
#include "LgbColorsDef.h"
//#include "LgbUndoStore.h"
#include "../common/LucidConstants.h"
#include "../common/GlobalFuncs_2.h"
#include "ReadOnlyEdit.h"
#include "Resource.h"
#include "InlineTextDialog.h"

IMPLEMENT_DYNAMIC(CProperties_textbox, CDialog)

CProperties_textbox::CProperties_textbox(	ProjectMetaData *pProjMetaData, 
											IconSelection< LgbTextIcon >  &iconSeln,
											CWnd* pParent /*=NULL*/)
											: CDialog(CProperties_textbox::IDD, pParent),
											m_cIconSeln ( iconSeln )
{
	m_pProjectMetaData = pProjMetaData;
	//m_pLgbUndoStore = pUndoStore;
	m_Bevel = 0;
}


CProperties_textbox::~CProperties_textbox()
{
}

void CProperties_textbox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_X1, m_x1);
	DDX_Control(pDX, IDC_X2, m_x2);
	DDX_Control(pDX, IDC_Y1, m_y1);
	DDX_Control(pDX, IDC_Y2, m_y2);
	DDX_Control(pDX, IDC_COLOURPICKER_RESULT, m_ctlEditColouredText);
	DDX_Control(pDX, IDC_ZORDER, m_ctlEditZOrder);
	DDX_Control(pDX, IDC_WIDTH, m_ctlEditWidth);
	DDX_Control(pDX, IDC_VERTEXTENT, m_ctlEditVertExtent);
	DDX_Control(pDX, IDC_TAG, m_ctlEditTag);
	DDX_Control(pDX, IDC_TYPE, m_ctlEditType);
	//	DDX_Control(pDX, IDC_EDIT_PC_TRANSP2, m_ctlEditPcTransp);
	DDX_Control(pDX, IDC_EDIT_PC_BG_TRANSP, m_ctlEditBgTransp);
	DDX_Control(pDX, IDC_EDIT_PC_FG_TRANSP, m_ctlEditFgTransp);
	DDX_Control(pDX, IDC_SLIDER_FG_TRANSP, m_ctlSliderFgTransp);
	DDX_Control(pDX, IDC_SLIDER_BG_TRANSP, m_ctlSliderBgTransp);
	DDX_Control(pDX, IDC_COMBO_FONT, m_ctlComboFont);
	DDX_Control(pDX, IDC_EDIT_LEFT_INDENT, m_ctlEditLeftIndent);
	DDX_Control(pDX, IDC_EDIT_RIGHT_INDENT, m_ctlEditRightIndent);
	DDX_Control(pDX, IDC_EDIT_TOP_INDENT, m_ctlEditTopIndent);
	DDX_Control(pDX, IDC_EDIT_BOTTOM_INDENT, m_ctlEditBottomIndent);
	DDX_Control(pDX, IDC_EDIT_LINE_SPACING, m_ctlEditLineSpacing);
	DDX_Control(pDX, IDC_EDIT_NUMBER_OF_LINES, m_ctlEditNumberOfLines);
	DDX_Control(pDX, IDC_BUTTON_PROPTEXT_FG_COLOR, m_ctlFgColorButton);
	DDX_Control(pDX, IDC_BUTTON_PROPTEXT_BG_COLOR, m_ctlBgColorButton);
}


BEGIN_MESSAGE_MAP(CProperties_textbox, CDialog)
	ON_BN_CLICKED(ID_TEXTBOX_OK, &CProperties_textbox::OnBnClickedTextboxOk)
	ON_BN_CLICKED(IDC_BUTTON_PROPTEXT_FG_COLOR, &CProperties_textbox::OnBnClickedTextColor)
	ON_BN_CLICKED(IDC_BUTTON_PROPTEXT_BG_COLOR, &CProperties_textbox::OnBnClickedButtonBgColor)
//	ON_EN_CHANGE(IDC_DESCRIPTION, &CProperties_textbox::OnEnChangeDescription)
	ON_EN_KILLFOCUS(IDC_Y1, &CProperties_textbox::OnEnKillfocusY1)
	ON_EN_KILLFOCUS(IDC_VERTEXTENT, &CProperties_textbox::OnEnKillfocusVertextent)
	ON_EN_KILLFOCUS(IDC_Y2, &CProperties_textbox::OnEnKillfocusY2)
	ON_EN_KILLFOCUS(IDC_WIDTH, &CProperties_textbox::OnEnKillfocusWidth)
	ON_EN_KILLFOCUS(IDC_X2, &CProperties_textbox::OnEnKillfocusX2)
	ON_EN_KILLFOCUS(IDC_X1, &CProperties_textbox::OnEnKillfocusX1)
	ON_EN_KILLFOCUS(IDC_EDIT_PC_BG_TRANSP, &CProperties_textbox::OnEnKillfocusEditPcBgTransp)
	ON_EN_KILLFOCUS(IDC_EDIT_PC_FG_TRANSP, &CProperties_textbox::OnEnKillfocusEditPcFgTransp)
	ON_WM_HSCROLL()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_FG_TRANSP, &CProperties_textbox::OnNMCustomdrawSliderFgTransp)
	ON_EN_KILLFOCUS(IDC_EDIT_LEFT_INDENT, &CProperties_textbox::OnEnKillfocusEditLeftIndent)
	ON_EN_KILLFOCUS(IDC_EDIT_RIGHT_INDENT, &CProperties_textbox::OnEnKillfocusEditRightIndent)
	ON_EN_KILLFOCUS(IDC_EDIT_TOP_INDENT, &CProperties_textbox::OnEnKillfocusEditTopIndent)
	ON_EN_KILLFOCUS(IDC_EDIT_BOTTOM_INDENT, &CProperties_textbox::OnEnKillfocusEditBottomIndent)
	ON_EN_KILLFOCUS(IDC_EDIT_LINE_SPACING, &CProperties_textbox::OnEnKillfocusEditLineSpacing)
	ON_BN_CLICKED(IDC_BUTTON_INLINE_TEXT, &CProperties_textbox::OnBnClickedButtonInlineText)
END_MESSAGE_MAP()


BOOL CProperties_textbox::OnInitDialog()
{
	// The icons of type bitmap were loaded into an IconSelection instance by the view just before this dialog was
	// created, and a local copy made of this in the construtor.
	// We now scan the collection to see whether all the (eg) top borders have the same position.
	// If they do, we load this value into the field in the dialog.  If however the icons differ in value for this
	// field, the field is set to blank.
	CDialog::OnInitDialog();

	m_ctlSliderFgTransp.SetRange(0, 255);
	m_ctlSliderBgTransp.SetRange(0, 255);
	m_bColorsDiffer = false;

	LgbTextIcon::Scan scan;

	if(m_cIconSeln.size() == 1){

		scan.init();

	} else {

		scan =  m_cIconSeln.processEquality();

	}

	LgbTextIcon *pIcon = NULL;
	pIcon = m_cIconSeln.m_vContents.front();
	m_vInlineTextVec = pIcon->c_vInlineTextVec;

	char buffer[16];
	int iNumberOfLines;

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
		m_iPrevWidth = pIcon->m_cRect.Width();
	}else{
		m_ctlEditWidth.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_ctlEditWidth.EnableWindow(0);
	}

	if(scan.m_cDrblScan.m_bSameVrtExtnt){
		_itoa_s(pIcon->m_cRect.Height(),buffer,16,10);
		m_ctlEditVertExtent.SetWindowText(buffer);
		m_iPrevVertExtent = pIcon->m_cRect.Height();
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

	if(scan.m_bSameFont){
		m_ctlComboFont.SetWindowText(pIcon->getFont());
	}else{
		m_ctlComboFont.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_ctlComboFont.EnableWindow(0);
	}

	if(scan.m_bSameLeftIndent){
		_itoa_s(pIcon->getLeftIndent(),buffer,16,10);
		m_ctlEditLeftIndent.SetWindowText(buffer);
		m_iPrevLeftIndent = pIcon->getLeftIndent();
	}else{
		m_ctlEditLeftIndent.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_ctlEditLeftIndent.EnableWindow(0);
	}

	if(scan.m_bSameRightIndent){
		_itoa_s(pIcon->getRightIndent(),buffer,16,10);
		m_ctlEditRightIndent.SetWindowText(buffer);
		m_iPrevRightIndent = pIcon->getRightIndent();
	}else{
		m_ctlEditRightIndent.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_ctlEditRightIndent.EnableWindow(0);
	}

	if(scan.m_bSameTopIndent){
		_itoa_s(pIcon->getTopIndent(),buffer,16,10);
		m_ctlEditTopIndent.SetWindowText(buffer);
		m_iPrevTopIndent = pIcon->getTopIndent();
	}else{
		m_ctlEditTopIndent.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_ctlEditTopIndent.EnableWindow(0);
	}

	if(scan.m_bSameBottomIndent){
		_itoa_s(pIcon->getBottomIndent(),buffer,16,10);
		m_ctlEditBottomIndent.SetWindowText(buffer);
		m_iPrevBottomIndent = pIcon->getBottomIndent();
	}else{
		m_ctlEditBottomIndent.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_ctlEditBottomIndent.EnableWindow(0);
	}

	if (scan.m_bSameLineSpacing) {
		_itoa_s(pIcon->getLineSpacing(),buffer,16,10);
		m_ctlEditLineSpacing.SetWindowText(buffer);
	} else {
		m_ctlEditLineSpacing.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_ctlEditLineSpacing.EnableWindow(0);
	}

	if (scan.m_bSameNumberOfLines) {
		iNumberOfLines = (pIcon->m_cRect.Height() - pIcon->getTopIndent() - pIcon->getBottomIndent())/pIcon->getLineSpacing();
		_itoa_s(iNumberOfLines, buffer,16,10);
		m_ctlEditNumberOfLines.SetWindowText(buffer);
	} else {
		m_ctlEditNumberOfLines.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_ctlEditNumberOfLines.EnableWindow(0);
	}

	if(scan.m_bSameFgAlpha){
		//int opacity = 100 * pIcon->m_iAlpha / 255;

		int alpha = pIcon->m_cColors.m_iFgAlpha;

		m_ctlSliderFgTransp.SetPos(255 - alpha);

		float dum = float( (255 - alpha ))/ float( 2.55 );
		sprintf_s( buffer, 16, "%3.1f", dum );
		m_ctlEditFgTransp.SetWindowText(buffer);

	}else{
		m_ctlSliderFgTransp.SetPos(0);
		m_ctlSliderFgTransp.EnableWindow(0);
		m_ctlEditFgTransp.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_ctlEditFgTransp.EnableWindow(0);
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

	}else{
		// signal to user that text colors are NOT same between icons.
		m_bColorsDiffer = true;
	}


	// Get the font vector
	std::vector<LgbFont> vFontVec;
	vFontVec = pIcon->c_vFontVec;

	// Now load these into the combobox
	for(size_t i=0; i<vFontVec.size(); i++){
		m_ctlComboFont.AddString(vFontVec[i].GetFontName());
	}


	if(scan.m_bSameFont) {
		// If the icons have the same font, set the combobox to this value
		int pos = m_ctlComboFont.FindStringExact(0, pIcon->getFont() );
		m_ctlComboFont.SetCurSel(pos);

	} else {
		// Otherwise, we need to add a 'blank' to the combobox, and select it
		m_ctlComboFont.AddString(LGB_NULL_COMBO_CHOICE);
		int pos = m_ctlComboFont.FindStringExact(0, LGB_NULL_COMBO_CHOICE );
		m_ctlComboFont.SetCurSel(pos);
	}

	// if the colours differ between multiple selected textboxes set both colours to white in the dialog
	if (m_bColorsDiffer) {
		m_ctlEditColouredText.SetTextColor( RGB(255, 255, 255) );
		m_ctlEditColouredText.SetBackColor( RGB(255, 255, 255) );
		m_ctlFgColorButton.EnableWindow(0);
		m_ctlBgColorButton.EnableWindow(0);
	}
	else {
		m_ctlEditColouredText.SetTextColor( RGB(m_cColors.m_iFgRed, m_cColors.m_iFgGreen, m_cColors.m_iFgBlue) );
		m_ctlEditColouredText.SetBackColor( RGB(m_cColors.m_iBgRed, m_cColors.m_iBgGreen, m_cColors.m_iBgBlue) );
	}

	SetDlgItemTextA( IDC_COLOURPICKER_RESULT, "Text sample" );

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control

}


void CProperties_textbox::OnBnClickedTextboxOk()
{

	UpdateData();

	// These are necessary for when 'enter' is pressed to dismiss the dialog.
	// Otherwise, the loss of focus event is not received to work out widths.
	// eg if you change the left-edge, then hit return, the icon should move, but
	// instead it resizes.

	OnEnKillfocusX1();
	OnEnKillfocusY1();

	LgbTextIcon *pIcon = NULL;

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


		// Condition to ensure no negative width or height - this causes graphics to blow-up

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

		m_ctlEditLeftIndent.GetWindowTextA(dumCs);
		if(dumCs != FLAG_DIFF_VALUE_FIELD && dumCs.GetLength() > 0){
			pIcon->setLeftIndent(atoi(dumCs));
		}

		m_ctlEditRightIndent.GetWindowTextA(dumCs);
		if(dumCs != FLAG_DIFF_VALUE_FIELD && dumCs.GetLength() > 0){
			pIcon->setRightIndent(atoi(dumCs));
		}

		m_ctlEditTopIndent.GetWindowTextA(dumCs);
		if(dumCs != FLAG_DIFF_VALUE_FIELD && dumCs.GetLength() > 0){
			pIcon->setTopIndent(atoi(dumCs));
		}

		m_ctlEditBottomIndent.GetWindowTextA(dumCs);
		if(dumCs != FLAG_DIFF_VALUE_FIELD && dumCs.GetLength() > 0){
			pIcon->setBottomIndent(atoi(dumCs));
		}

		m_ctlEditLineSpacing.GetWindowTextA(dumCs);
		if(dumCs != FLAG_DIFF_VALUE_FIELD && dumCs.GetLength() > 0){
			pIcon->setLineSpacing(atoi(dumCs));
		}

		m_ctlEditFgTransp.GetWindowTextA(dumCs);
		if(dumCs != FLAG_DIFF_VALUE_FIELD){
			int pos = m_ctlSliderFgTransp.GetPos();
			pIcon->setAlpha( 255 - pos, LgbTextIcon::LgbTextIcon_FlagText );
		}

		m_ctlEditBgTransp.GetWindowTextA(dumCs);
		if(dumCs != FLAG_DIFF_VALUE_FIELD){
			int pos = m_ctlSliderBgTransp.GetPos();
			pIcon->setAlpha( 255 - pos, LgbTextIcon::LgbTextIcon_FlagBackground );
		}


		// Font Name
		int iPos = m_ctlComboFont.GetCurSel();
		CString csDlogFontName;
		m_ctlComboFont.GetLBText( iPos, csDlogFontName );

		if(csDlogFontName != LGB_NULL_COMBO_CHOICE ){
			pIcon->setFont( csDlogFontName );
		}

		/*
		// SDG: Commented out the following code because it doesn't allow a white foreground and background
		// Not sure why this would be. It may be a signal.
		if( !(  (m_cColors.m_iBgRed==255) && (m_cColors.m_iBgGreen==255) && (m_cColors.m_iBgBlue==255) &&
				(m_cColors.m_iFgRed==255) && (m_cColors.m_iFgGreen==255) && (m_cColors.m_iFgBlue==255) ))
		{
			pIcon->setColors(m_cColors);
		}
		*/
		if (!m_bColorsDiffer) {
			pIcon->setColors(m_cColors);
		}
		pIcon->c_vInlineTextVec = m_vInlineTextVec;

	} // for(int i=0;i<m_vpIcon.size();i++)

	CDialog::OnOK();

}


void CProperties_textbox::OnBnClickedTextColor()
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
	cc.lpCustColors[0] = RGB(m_cColors.m_iFgRed, m_cColors.m_iFgGreen, m_cColors.m_iFgBlue );
	cc.rgbResult = RGB(m_cColors.m_iFgRed, m_cColors.m_iFgGreen, m_cColors.m_iFgBlue );
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
 
	if (ChooseColor(&cc)==TRUE) {
		m_cColors.m_iFgRed = GetRValue(cc.rgbResult);
		m_cColors.m_iFgGreen = GetGValue(cc.rgbResult);
		m_cColors.m_iFgBlue = GetBValue(cc.rgbResult);

		m_ctlEditColouredText.SetTextColor( cc.rgbResult );

		UpdateData(false);
	}
}

void CProperties_textbox::OnBnClickedButtonBgColor()
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

		m_ctlEditColouredText.SetBackColor( cc.rgbResult );

		UpdateData(false);
	}
}

void CProperties_textbox::OnEnChangeDescription()
{

}

void CProperties_textbox::OnEnKillfocusY1()
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

void CProperties_textbox::OnEnKillfocusVertextent()
{
	char buffer[20];
	CString csHeight, csTopIndent, csBottomIndent, csLineSpacing;
	int iHeight, iTopIndent, iBottomIndent, iLineSpacing, iNumberOfLines;

	UpdateData();

	m_ctlEditVertExtent.GetWindowTextA(csHeight);
	m_ctlEditTopIndent.GetWindowTextA(csTopIndent);
	m_ctlEditBottomIndent.GetWindowTextA(csBottomIndent);
	m_ctlEditLineSpacing.GetWindowTextA(csLineSpacing);

	if ((csTopIndent != FLAG_DIFF_VALUE_FIELD) && (csHeight != FLAG_DIFF_VALUE_FIELD) &&
		(csBottomIndent != FLAG_DIFF_VALUE_FIELD) && csLineSpacing != FLAG_DIFF_VALUE_FIELD) {

		iHeight = atoi(csHeight);
		iTopIndent = atoi(csTopIndent);
		iBottomIndent = atoi(csBottomIndent);
		iLineSpacing = atoi(csLineSpacing);

		// REVISIT - Remove height restrictions for the time being
		/*if (iTopIndent + iBottomIndent + iLineSpacing > iHeight) {
			// if height is less than top + bottom indent + line spacing load previous height
			_itoa_s(m_iPrevVertExtent, buffer,16,10);
			m_ctlEditVertExtent.SetWindowText(buffer);
		}
		else {*/
			// if user changes vert extent, assume top is to stay same, and move bottom.
			OnEnKillfocusY1();

			// calculate number of lines
			iNumberOfLines = (iHeight - iTopIndent - iBottomIndent)/iLineSpacing;
			if (iNumberOfLines < 0) {
				iNumberOfLines = 0;
			}
			_itoa_s(iNumberOfLines, buffer,16,10);
			m_ctlEditNumberOfLines.SetWindowText(buffer);
		/*}
		m_ctlEditVertExtent.GetWindowTextA(csHeight);
		m_iPrevVertExtent = atoi(csHeight);*/

		UpdateData(false);
	}
}

void CProperties_textbox::OnEnKillfocusY2()
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

void CProperties_textbox::OnEnKillfocusWidth()
{
	// left indent + right indent must be less than width
	CString csWidth, csLeftIndent, csRightIndent;
	int iWidth, iLeftIndent, iRightIndent;

	UpdateData();

	m_ctlEditWidth.GetWindowTextA(csWidth);
	m_ctlEditLeftIndent.GetWindowTextA(csLeftIndent);
	m_ctlEditRightIndent.GetWindowTextA(csRightIndent);

	if ((csLeftIndent != FLAG_DIFF_VALUE_FIELD) && (csWidth != FLAG_DIFF_VALUE_FIELD) &&
		(csRightIndent != FLAG_DIFF_VALUE_FIELD)){

		iWidth = atoi(csWidth);
		iRightIndent = atoi(csRightIndent);
		iLeftIndent = atoi(csLeftIndent);

		// REVISIT - Remove restrictions on width
		/*if (iLeftIndent + iRightIndent > iWidth) {
			_itoa_s(m_iPrevWidth, buffer,16,10);
			m_ctlEditWidth.SetWindowText(buffer);
		}
		else { */
			// if user changes width, assume left is to stay same, and move right.
			OnEnKillfocusX1();
		/*}
		m_ctlEditWidth.GetWindowTextA(csWidth);
		m_iPrevWidth = atoi(csWidth);*/

		UpdateData(false);
	}
}


void CProperties_textbox::OnEnKillfocusX1()
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


void CProperties_textbox::OnEnKillfocusX2()
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

void CProperties_textbox::OnEnKillfocusEditPcBgTransp()
{
	CString dum;
	m_ctlEditBgTransp.GetWindowTextA(dum);
	double ddum = atof(dum);

	if(ddum>100.0)ddum=100.0;
	int idum = (int) ( (ddum/100.0) * 255);

	m_ctlSliderBgTransp.SetPos( idum );
}

void CProperties_textbox::OnEnKillfocusEditPcFgTransp()
{
	CString dum;
	m_ctlEditFgTransp.GetWindowTextA(dum);
	double ddum = atof(dum);

	if(ddum>100.0)ddum=100.0;
	int idum = (int) ( (ddum/100.0) * 255);

	m_ctlSliderFgTransp.SetPos( idum );
}

void CProperties_textbox::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	char buffer[16];
	//float dum;

	if(( CSliderCtrl *) pScrollBar == &m_ctlSliderFgTransp)
	{
		int idum = m_ctlSliderFgTransp.GetPos();

		if(idum>=0){
			float dum = float( (m_ctlSliderFgTransp.GetPos() ))/ float( 2.55 );
			sprintf_s( buffer, 16, "%3.1f", dum );
		}else{
			strcpy_s(buffer, 16, FLAG_DIFF_VALUE_FIELD );
		}
		m_ctlEditFgTransp.SetWindowText(buffer);

	}else if(( CSliderCtrl *) pScrollBar == &m_ctlSliderBgTransp)
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

void CProperties_textbox::OnNMCustomdrawSliderFgTransp(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CProperties_textbox::OnEnKillfocusEditLeftIndent()
{
	// left indent + right indent must be less than width
	CString csWidth, csLeftIndent, csRightIndent;
	int iWidth, iLeftIndent, iRightIndent;

	UpdateData();

	m_ctlEditWidth.GetWindowTextA(csWidth);
	m_ctlEditLeftIndent.GetWindowTextA(csLeftIndent);
	m_ctlEditRightIndent.GetWindowTextA(csRightIndent);

	if ((csLeftIndent != FLAG_DIFF_VALUE_FIELD) && (csWidth != FLAG_DIFF_VALUE_FIELD) &&
		(csRightIndent != FLAG_DIFF_VALUE_FIELD)){

		iWidth = atoi(csWidth);
		iRightIndent = atoi(csRightIndent);
		iLeftIndent = atoi(csLeftIndent);

		// REVISIT - Remove restrictions on left indent
		/*
		if (iLeftIndent + iRightIndent > iWidth) {
			_itoa_s(m_iPrevLeftIndent, buffer,16,10);
			m_ctlEditLeftIndent.SetWindowText(buffer);
		}
		m_ctlEditLeftIndent.GetWindowTextA(csLeftIndent);
		m_iPrevLeftIndent = atoi(csLeftIndent);
		*/

		UpdateData(false);
	}
}

void CProperties_textbox::OnEnKillfocusEditRightIndent()
{
	// left indent + right indent must be less than width
	CString csWidth, csLeftIndent, csRightIndent;
	int iWidth, iLeftIndent, iRightIndent;

	UpdateData();

	m_ctlEditWidth.GetWindowTextA(csWidth);
	m_ctlEditLeftIndent.GetWindowTextA(csLeftIndent);
	m_ctlEditRightIndent.GetWindowTextA(csRightIndent);

	if ((csLeftIndent != FLAG_DIFF_VALUE_FIELD) && (csWidth != FLAG_DIFF_VALUE_FIELD) &&
		(csRightIndent != FLAG_DIFF_VALUE_FIELD)){

		iWidth = atoi(csWidth);
		iRightIndent = atoi(csRightIndent);
		iLeftIndent = atoi(csLeftIndent);

		// REVISIT - Remove restrictions on right indent
		/*
		if (iLeftIndent + iRightIndent > iWidth) {
			_itoa_s(m_iPrevRightIndent, buffer,16,10);
			m_ctlEditRightIndent.SetWindowText(buffer);
		}
		m_ctlEditRightIndent.GetWindowTextA(csRightIndent);
		m_iPrevRightIndent = atoi(csRightIndent);
		*/

		UpdateData(false);
	}
}

void CProperties_textbox::OnEnKillfocusEditTopIndent()
{
	// top indent + bottom indent + line spacing must be less than height
	CString csHeight, csTopIndent, csBottomIndent, csLineSpacing;
	int iHeight, iTopIndent, iBottomIndent, iLineSpacing;

	UpdateData();

	m_ctlEditVertExtent.GetWindowTextA(csHeight);
	m_ctlEditTopIndent.GetWindowTextA(csTopIndent);
	m_ctlEditBottomIndent.GetWindowTextA(csBottomIndent);
	m_ctlEditLineSpacing.GetWindowTextA(csLineSpacing);

	if ((csTopIndent != FLAG_DIFF_VALUE_FIELD) && (csHeight != FLAG_DIFF_VALUE_FIELD) &&
		(csBottomIndent != FLAG_DIFF_VALUE_FIELD)){

		iHeight = atoi(csHeight);
		iTopIndent = atoi(csTopIndent);
		iBottomIndent = atoi(csBottomIndent);
		iLineSpacing = atoi(csLineSpacing);

		// REVISIT - Remove restrictions on top indent
		/*
		if (iTopIndent + iBottomIndent + iLineSpacing > iHeight) {
			_itoa_s(m_iPrevTopIndent, buffer,16,10);
			m_ctlEditTopIndent.SetWindowText(buffer);
		}
		m_ctlEditTopIndent.GetWindowTextA(csTopIndent);
		m_iPrevTopIndent = atoi(csTopIndent);
		*/

		UpdateData(false);
	}
}

void CProperties_textbox::OnEnKillfocusEditBottomIndent()
{
	// top indent + bottom indent + line spacing must be less than height
	CString csHeight, csTopIndent, csBottomIndent, csLineSpacing;
	int iHeight, iTopIndent, iBottomIndent, iLineSpacing;

	UpdateData();

	m_ctlEditVertExtent.GetWindowTextA(csHeight);
	m_ctlEditTopIndent.GetWindowTextA(csTopIndent);
	m_ctlEditBottomIndent.GetWindowTextA(csBottomIndent);
	m_ctlEditLineSpacing.GetWindowTextA(csLineSpacing);

	if ((csTopIndent != FLAG_DIFF_VALUE_FIELD) && (csHeight != FLAG_DIFF_VALUE_FIELD) &&
		(csBottomIndent != FLAG_DIFF_VALUE_FIELD)){

		iHeight = atoi(csHeight);
		iTopIndent = atoi(csTopIndent);
		iBottomIndent = atoi(csBottomIndent);
		iLineSpacing = atoi(csLineSpacing);

		// REVISIT - Remove restrictions on bottom indent
		/*
		if (iTopIndent + iBottomIndent + iLineSpacing > iHeight) {
			_itoa_s(m_iPrevBottomIndent, buffer,16,10);
			m_ctlEditBottomIndent.SetWindowText(buffer);
		}
		m_ctlEditBottomIndent.GetWindowTextA(csBottomIndent);
		m_iPrevBottomIndent = atoi(csBottomIndent);
		*/

		UpdateData(false);
	}
}

void CProperties_textbox::OnEnKillfocusEditLineSpacing()
{
	// Change number of lines
	char buffer[20];
	CString csHeight, csTopIndent, csBottomIndent, csLineSpacing;
	int iHeight, iTopIndent, iBottomIndent, iLineSpacing, iNumberOfLines;
	double dNumberOfLines;

	UpdateData();

	m_ctlEditVertExtent.GetWindowTextA(csHeight);
	m_ctlEditTopIndent.GetWindowTextA(csTopIndent);
	m_ctlEditBottomIndent.GetWindowTextA(csBottomIndent);
	m_ctlEditLineSpacing.GetWindowTextA(csLineSpacing);

	if ((csTopIndent != FLAG_DIFF_VALUE_FIELD) && (csHeight != FLAG_DIFF_VALUE_FIELD) &&
		(csBottomIndent != FLAG_DIFF_VALUE_FIELD) && (csLineSpacing != FLAG_DIFF_VALUE_FIELD)) {

		iHeight = atoi(csHeight);
		iTopIndent = atoi(csTopIndent);
		iBottomIndent = atoi(csBottomIndent);
		iLineSpacing = atoi(csLineSpacing);

		dNumberOfLines = (double)(iHeight - iTopIndent - iBottomIndent)/(double)iLineSpacing;
		if (dNumberOfLines < 1.0 && dNumberOfLines > 0.0) {
			iNumberOfLines = 1;
		}
		else {
			iNumberOfLines = (int)dNumberOfLines;
		}
		_itoa_s(iNumberOfLines, buffer,16,10);
		m_ctlEditNumberOfLines.SetWindowText(buffer);

		UpdateData(false);
	}
}

void CProperties_textbox::OnBnClickedButtonInlineText()
{
	CInlineTextDialog dialog;

	// Initialise the InlineText dialog
	dialog.SetInlineTextVec(m_vInlineTextVec);
	dialog.SetColor(m_cColors);
	int iPos = m_ctlSliderFgTransp.GetPos();
	dialog.SetAlpha(255 - iPos);

	LgbTextIcon *pIcon = NULL;
	pIcon = m_cIconSeln.m_vContents.front();
	dialog.SetFontVec(pIcon->c_vFontVec);

	if (dialog.DoModal() == IDOK) {
		dialog.GetInlineTextVec(m_vInlineTextVec);
	}
}
