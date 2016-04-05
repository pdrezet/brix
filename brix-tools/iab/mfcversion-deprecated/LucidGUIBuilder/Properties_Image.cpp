/** @file Properties_Image.cpp
 * Implementation of Properties_Image class
 * @author: Matthew Rutherford
 * @version: $Revision: 577 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */

#include "stdafx.h"
#include "Properties_Image.h"
#include "../common/LucidConstants.h"
#include "../common/ProjectMetaData.h"
#include "../common/ExtBmpFile.h"
#include "../LucidApplicationBuilder/FileOperations.h"
#include "DrawGUI.h"
#include "LgbImageIcon.h"
#include "IconSelection.h"
#include "Resource.h"
#include <math.h>

#include <cassert>

// CProperties_Image dialog

IMPLEMENT_DYNAMIC(CProperties_Image, CDialog)


CProperties_Image::CProperties_Image(ProjectMetaData *pProjMetaData, 
									 const IconSelection< LgbImageIcon >  &iconSeln,
									 CWnd* pParent /*=NULL*/)
									 : CDialog(CProperties_Image::IDD, pParent),
										m_cIconSeln ( iconSeln )
{

	m_pProjectMetaData = pProjMetaData;
}

CProperties_Image::~CProperties_Image()
{
}

void CProperties_Image::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_X1, m_x1);
	DDX_Control(pDX, IDC_X2, m_x2);
	DDX_Control(pDX, IDC_Y1, m_y1);
	DDX_Control(pDX, IDC_Y2, m_y2);
	DDX_Control(pDX, IDC_TAG, m_ctlEditTag);
	DDX_Control(pDX, IDC_TYPE, m_ctlEditType);
	DDX_Control(pDX, IDC_COMBO_BMPFILES, m_ctlImageFileCombo);
	DDX_Control(pDX, IDC_ZORDER, m_ctl_EditZOrder);
	DDX_Control(pDX, IDC_CHECK_LOCKASPECTRATIO, m_ctl_LockAspectRatioToImage);
	DDX_Control(pDX, IDC_WIDTH, m_ctlEditWidth);
	DDX_Control(pDX, IDC_VERTEXTENT, m_ctlEditVertExtent);
	DDX_Control(pDX, IDC_EDIT_PC_TRANSP, m_ctlEditPcTransp);
	DDX_Control(pDX, IDC_SLIDER_TRANSP, m_ctlSliderTransp);
}


BEGIN_MESSAGE_MAP(CProperties_Image, CDialog)
	ON_BN_CLICKED(IDOK, &CProperties_Image::OnBtnClickedOk)
	ON_BN_CLICKED(IDC_IMPORT_BITMAP, &CProperties_Image::OnBnClickedImageLoadImage)
	ON_CBN_SELCHANGE(IDC_COMBO_BMPFILES, &CProperties_Image::OnCbnSelchangeComboBmpfiles)
	ON_EN_CHANGE(IDC_EDIT_Z_ORDER, &CProperties_Image::OnEnChangeEditZOrder)
	ON_STN_CLICKED(IDC_TAG_LABEL, &CProperties_Image::OnStnClickedTagLabel)
	ON_EN_KILLFOCUS(IDC_X1, &CProperties_Image::OnEnKillfocusX1)
	ON_EN_KILLFOCUS(IDC_X2, &CProperties_Image::OnEnKillfocusX2)
	ON_EN_CHANGE(IDC_Y1, &CProperties_Image::OnEnChangeY1)
	ON_EN_KILLFOCUS(IDC_Y1, &CProperties_Image::OnEnKillfocusY1)
	ON_EN_KILLFOCUS(IDC_Y2, &CProperties_Image::OnEnKillfocusY2)
	ON_EN_CHANGE(IDC_EDIT_PC_TRANSP, &CProperties_Image::OnEnChangeEditPcTransp)
	ON_WM_HSCROLL()
	ON_EN_KILLFOCUS(IDC_VERTEXTENT, &CProperties_Image::OnEnKillfocusVertExtent)
	ON_EN_KILLFOCUS(IDC_WIDTH, &CProperties_Image::OnEnKillfocusWidth)
	ON_CBN_KILLFOCUS(IDC_COMBO_BMPFILES, &CProperties_Image::OnCbnKillfocusComboBmpfiles)
	ON_BN_CLICKED(IDC_CHECK_LOCKASPECTRATIO, &CProperties_Image::OnBnClickedCheckLockaspectratio)
END_MESSAGE_MAP()


BOOL CProperties_Image::OnInitDialog()
{

	CDialog::OnInitDialog();

	m_ctlSliderTransp.SetRange( 0, 255, false );

	// The icons of type bitmap were loaded into an IconSelection instance by the view 
	// just before this dialog was
	// created, and a local copy made of this in the construtor.
	// We now scan the collection to see whether all the (eg) top borders have the same position.
	// If they do, we load this value into the field in the dialog.  If hopwever the
	// icons differ in value for this
	// field, the filed is set to blank.
	LgbImageIcon::Scan scan;

	if( m_cIconSeln.size() == 1)
	{
		scan.init();

	}else{

		scan =  m_cIconSeln.processEquality();

	}

	// Pick any icon as an example from which to extract any 'common' values.
	LgbImageIcon *pIcon = NULL;
	pIcon = m_cIconSeln.m_vContents.front();

	//store the size and aspect ratio of the original image
	m_iImageHeight = 	pIcon->getImageHeight();
	m_iImageWidth = 	pIcon->getImageWidth();
	m_dImageHtoW = float(m_iImageHeight) / float(m_iImageWidth);


	char buffer[16];

	// Tag
	if(scan.m_cDrblScan.m_bSameTag){
		//_itoa_s(pIcon->m_cRect.left,buffer,16,10);
		m_ctlEditTag.SetWindowText(pIcon->m_csTag);
	}else{
		m_ctlEditTag.SetWindowText(FLAG_DIFF_VALUE_FIELD);
	}

	// Type
	if(scan.m_cDrblScan.m_bSameType){
		//_itoa_s(pIcon->m_cRect.left,buffer,16,10);
		m_ctlEditType.SetWindowText(pIcon->m_csType);
	}else{
		m_ctlEditType.SetWindowText(FLAG_DIFF_VALUE_FIELD);
	}


	// Left border
	if(scan.m_cDrblScan.m_bSameLft){
		_itoa_s(pIcon->m_cRect.left,buffer,16,10);
		m_x1.SetWindowText(buffer);
	}else{
		m_x1.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_x1.EnableWindow(0);
	}

	// Right border
	if(scan.m_cDrblScan.m_bSameRgt){
		_itoa_s(pIcon->m_cRect.right,buffer,16,10);
		m_x2.SetWindowText(buffer);
	}else{
		m_x2.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_x2.EnableWindow(0);
	}

	// Top border
	if(scan.m_cDrblScan.m_bSameTop){
		_itoa_s(pIcon->m_cRect.top,buffer,16,10);
		m_y1.SetWindowText(buffer);
	}else{
		m_y1.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_y1.EnableWindow(0);
	}

	// Bottom border
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


	// zpos
	if(scan.m_cDrblScan.m_bSameZPos){
		_itoa_s(pIcon->m_iZPosUser,buffer,16,10);
		m_ctl_EditZOrder.SetWindowText(buffer);
	}else{
		m_ctl_EditZOrder.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_ctl_EditZOrder.EnableWindow(0);
	}

	// opacity
	if(scan.m_bSameAlpha){

		float dum = float( (255 - pIcon->getAlpha() ))/ float( 2.55 );
		sprintf_s( buffer, 16, "%3.1f", dum );
		m_ctlEditPcTransp.SetWindowText(buffer);

		m_ctlSliderTransp.SetPos( 255 - pIcon->getAlpha() );

	}else{
		m_ctlEditPcTransp.SetWindowText(FLAG_DIFF_VALUE_FIELD);
		m_ctlEditPcTransp.EnableWindow(0);
		m_ctlSliderTransp.SetPos( 0 );
		m_ctlSliderTransp.EnableWindow(0);
	}


	// 1st Clear contents of combobox, in case this method is
	// being called for the 2nd time around.
	m_ctlImageFileCombo.ResetContent();

	// PNG file names

	// 1st get the project's png files so far
	std::vector< ExtPngFile > pngFileVec;
	m_pProjectMetaData->getPngFiles(pngFileVec);

	// Now load these into the combobox
	CString dumStr;
	for(size_t i=0;i<pngFileVec.size();i++){
		pngFileVec[i].getHostFileName(dumStr);
		m_ctlImageFileCombo.AddString(dumStr);
	}


	// Now get the project' bitmap files so far
	std::vector< ExtBmpFile > bmpFileVec;
	m_pProjectMetaData->getBmpFiles(bmpFileVec);

	// Now load these into the combobox
	for(size_t i=0;i<bmpFileVec.size();i++){
		bmpFileVec[i].getHostFileName(dumStr);
		m_ctlImageFileCombo.AddString(dumStr);
	}

	if(scan.m_bSameFileName){
		// If the icons have the same bitmap file, set the combobox to this value
		int pos = m_ctlImageFileCombo.FindStringExact(0, pIcon->getFileName() );
		m_ctlImageFileCombo.SetCurSel(pos);

	}else{
		// Otherwise, we need to add a 'blank' to the combobox, and select it
		m_ctlImageFileCombo.AddString(LGB_NULL_COMBO_CHOICE);
		int pos = m_ctlImageFileCombo.FindStringExact(0, LGB_NULL_COMBO_CHOICE );
		m_ctlImageFileCombo.SetCurSel(pos);
		m_ctlImageFileCombo.EnableWindow(0);
	}

	// aspect ratio
	if(scan.m_bSameLockAspect){
		m_ctl_LockAspectRatioToImage.SetCheck(pIcon->getLockAspect());
	}else{
		m_ctl_LockAspectRatioToImage.SetCheck(0);
		m_ctl_LockAspectRatioToImage.EnableWindow(0);
	}

	UpdateData(false);


	return TRUE;  // return TRUE unless you set the focus to a control
}


void CProperties_Image::OnBtnClickedOk()
{

	UpdateData();

	// These are necessary for when 'enter' is pressed to dismiss the dialog.
	// Otherwise, the loss of focus event is not received to work out widths.
	// eg if you change the left-edge, then hit return, the icon should move, but
	// instead it resizes.

	OnEnKillfocusX1();
	OnEnKillfocusY1();

	LgbImageIcon *pIcon = NULL;

	CString dumCs;

	int lft, rgt, top, btm, wdth, ht;
	int newLft, newRgt, newTop, newBtm;
	bool gdLft, gdRgt, gdTop, gdBtm, gdWdth, gdHt;

	// for each selected bitmap icon, if a given field has a valid value,
	// set the icon's field to this.
	// otherwise, leave the icon's filed value as-was.
	for(size_t i=0;i<m_cIconSeln.size();i++){

		pIcon = m_cIconSeln.getItem(i);

/*
		m_x1.GetWindowTextA(dumCs);
		if(dumCs.GetLength() > 0){
			pIcon->m_cRect.left = ( atoi(dumCs) );
		}

		m_y1.GetWindowTextA(dumCs);
		if(dumCs.GetLength() > 0){
			pIcon->m_cRect.top = ( atoi(dumCs) );
		}

		m_x2.GetWindowTextA(dumCs);
		if(dumCs.GetLength() > 0){
			pIcon->m_cRect.right = ( atoi(dumCs) );
		}

		m_y2.GetWindowTextA(dumCs);
		if(dumCs.GetLength() > 0){
			pIcon->m_cRect.bottom = ( atoi(dumCs) );
		}
*/

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




		m_ctl_EditZOrder.GetWindowTextA(dumCs);
		if(dumCs != FLAG_DIFF_VALUE_FIELD && dumCs.GetLength() > 0){
			pIcon->m_iZPosUser = atoi(dumCs);
		}

		// aspect ratio
		//note - FLAG_DIFF_VALUE_FIELD can't be set on a check box
		pIcon->setLockAspect(m_ctl_LockAspectRatioToImage.GetCheck());

		// Alpha
		m_ctlEditPcTransp.GetWindowTextA(dumCs);
		if(dumCs != FLAG_DIFF_VALUE_FIELD){
			int pos = m_ctlSliderTransp.GetPos();
			pIcon->setAlpha( 255 - pos );
		}

		int iDlogBmpPos = m_ctlImageFileCombo.GetCurSel();

		// This is thecase if the user typed-in his own file name.
		// The index of the thing she typed in should be got by the following!
		if( iDlogBmpPos == -1)
			iDlogBmpPos = m_ctlImageFileCombo.GetTopIndex();
		
		CString csDlogFileName;
		//m_ctlImageFileCombo.GetLBText( iDlogBmpPos, csDlogFileName );
		m_ctlImageFileCombo.GetWindowText( csDlogFileName );

		if( (csDlogFileName.Right(4) != ".png") && (csDlogFileName.Right(4) != ".PNG") ){

			CString dum = "Only .png ( or .PNG ) file types are\npresently supported.\n\nPlease select a file of this type";
			AfxMessageBox(dum);

			csDlogFileName = LGB_NULL_COMBO_CHOICE;

		}

		if(csDlogFileName != LGB_NULL_COMBO_CHOICE ){
			pIcon->changeImageFile( csDlogFileName );
		}

	} // for(int i=0;i<m_vpIcon.size();i++)

	CDialog::OnOK();
}

void CProperties_Image::OnBnClickedImageLoadImage()
{

	CFileDialog box(
		1,
		"",
		"",
		OFN_FILEMUSTEXIST,
		"PNG Files (*.png)|*.png|"
		);


	if (box.DoModal()==IDOK) {

		CString bmpPath = box.GetPathName();
		CString fileName = box.GetFileName();
		LucidErrEnum err;

		CDrawGUIApp *pApp = ( CDrawGUIApp * ) AfxGetApp();
		ProjectMetaData *pPMD = &(pApp->m_ProjectMetaData);

		if( (fileName.Right(4) != ".png") && (fileName.Right(4) != ".PNG") ){

			CString dum = "Only .png ( or .PNG ) file types are\npresently supported.\n\nPlease select a file of this type";
			AfxMessageBox(dum);

		} else {

			ExtPngFile pngFile;
			pngFile.setHostFileName( fileName );

			CDrawGUIApp *pApp = ( CDrawGUIApp * ) AfxGetApp();
			ProjectMetaData *pPMD = &(pApp->m_ProjectMetaData);

			// Load the bitmap file into the project's meta data
			err = pPMD->addPngFile( pngFile );

			if(err == kErr_NoErr){

				// Update the combobox contents with the new file
				OnInitDialog();

				// Select in the combobox the newly-imported file
				int pos = m_ctlImageFileCombo.FindStringExact(0, fileName );
				m_ctlImageFileCombo.SetCurSel(pos);

				pPMD->writeProjectFile();

				// Now actually do the file system copy of file into project folder.
				// 1st test if the file is already present...
				CString projDir;
				pPMD->getProjectDir(projDir);
				CFileOperation fileOp;

				int dum = bmpPath.GetLength() - fileName.GetLength();
				CString sourceFolder = bmpPath.Left(dum);

				if( PATH_IS_FILE != fileOp.CheckPath( projDir + GUIDIR + fileName ) )
				{
					fileOp.CopyFileGood( sourceFolder, fileName, projDir + GUIDIR, fileName );
				}

				pPMD->writeProjectFile();

				if (fileName != "placeholder.png") {
					m_ctlEditWidth.EnableWindow(0);
					m_ctlEditVertExtent.EnableWindow(0);
				}

			}else if (err == kErr_ProjectMetaData_PngFileAlreadyPresent){

				AfxMessageBox("A file of this name is already present in the project");

			}else{

				// Unfnown error.
				assert(1==0);
			}

		} // fileName.Right(4) == ".png") || (fileName.Right(4) == ".PNG") )

	} // if (box.DoModal()==IDOK)

}

BOOL CProperties_Image::PreCreateWindow(CREATESTRUCT& cs)
{
	return CDialog::PreCreateWindow(cs);
}

BOOL CProperties_Image::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	return CDialog::Create(lpszTemplateName, pParentWnd);
}

void CProperties_Image::OnCbnSelchangeComboBmpfiles()
{ 
}

void CProperties_Image::OnEnChangeEditZOrder()
{ }

void CProperties_Image::OnStnClickedTagLabel()
{ }

void CProperties_Image::OnEnKillfocusX1()
{

	// Because width is not editable, if left is moved, move right by same amount
	UpdateData();

	char buffer[20];
	CString csWidth;
	m_ctlEditWidth.GetWindowTextA(csWidth);
	int iWidth = atoi(csWidth);

	CString csLeft;
	m_x1.GetWindowTextA(csLeft);
	int iLeft = atoi(csLeft);

	if( (csLeft!= FLAG_DIFF_VALUE_FIELD) && (csWidth!= FLAG_DIFF_VALUE_FIELD) ){
		int iRight = iLeft + iWidth;

		_itoa_s( iRight, buffer,16,10);
		m_x2.SetWindowText(buffer);

		UpdateData(false);
	}
}

void CProperties_Image::OnEnKillfocusX2()
{
	// Because width is not editable, if right is moved, move left by same amount
	UpdateData();

	char buffer[20];
	CString csWidth;
	m_ctlEditWidth.GetWindowTextA(csWidth);
	int iWidth = atoi(csWidth);

	CString csRight;
	m_x2.GetWindowTextA(csRight);
	int iRight = atoi(csRight);

	if( (csRight != FLAG_DIFF_VALUE_FIELD) && (csWidth!= FLAG_DIFF_VALUE_FIELD) ){
		int iLeft = iRight - iWidth;

		_itoa_s( iLeft, buffer,16,10);
		m_x1.SetWindowText(buffer);

		UpdateData(false);
	}
}

void CProperties_Image::OnEnChangeY1()
{ }

void CProperties_Image::OnEnKillfocusY1()
{
	// Because vert extent is not editable, if top is moved, move bottom by same amount
	UpdateData();

	char buffer[20];

	CString csHeight;
	m_ctlEditVertExtent.GetWindowTextA(csHeight);
	int iVrtExt = atoi(csHeight);

	CString csTop;
	m_y1.GetWindowTextA(csTop);
	int iTop = atoi(csTop);

	if( (csTop!= FLAG_DIFF_VALUE_FIELD) && (csHeight!= FLAG_DIFF_VALUE_FIELD) ){
		int iCalc = iTop + iVrtExt;

		_itoa_s( iCalc, buffer,16,10);
		m_y2.SetWindowText(buffer);

		UpdateData(false);
	}
}

void CProperties_Image::OnEnKillfocusY2()
{
	// Because vert extent is not editable, if bottom is moved, move top by same amount
	UpdateData();

	char buffer[20];

	CString csHeight;
	m_ctlEditVertExtent.GetWindowTextA(csHeight);
	int iVrtExt = atoi(csHeight);

	CString csBottom;
	m_y2.GetWindowTextA(csBottom);
	int iBtm = atoi(csBottom);

	if( (csBottom!= FLAG_DIFF_VALUE_FIELD) && (csHeight!= FLAG_DIFF_VALUE_FIELD) ){
		int iCalc = iBtm - iVrtExt;

		_itoa_s( iCalc, buffer,16,10);
		m_y1.SetWindowText(buffer);

		UpdateData(false);
	}
}

void CProperties_Image::OnEnChangeEditPcTransp()
{
	CString dum;
	m_ctlEditPcTransp.GetWindowTextA(dum);
	double ddum = atof(dum);

	if(ddum>100.0)ddum=100.0;

	if(ddum<0.0)ddum=0.0;

	int idum = (ddum/100.0) * 255;

	//_itoa_s( idum   , buffer, 16, 10 );
	m_ctlSliderTransp.SetPos( idum );

}

void CProperties_Image::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	char buffer[16];
	float dum = float( (m_ctlSliderTransp.GetPos() ))/ float( 2.55 );
	sprintf_s( buffer, 16, "%3.1f", dum );
	m_ctlEditPcTransp.SetWindowText(buffer);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CProperties_Image::OnEnKillfocusVertExtent()
{
	// if user changes vert extent, assume top is to stay same, and move bottom.
	OnEnKillfocusY1();
	updateWidthIfAspectLocked();
}

void CProperties_Image::OnEnKillfocusWidth()
{
	// if user changes width, assume left is to stay same, and move right.
	OnEnKillfocusX1();
	updateHeightIfAspectLocked();
}

void CProperties_Image::OnCbnKillfocusComboBmpfiles()
{
	CString csFileName;
	// Pick any icon as an example from which to extract any 'common' values.
	LgbImageIcon *pIcon = NULL;
	pIcon = m_cIconSeln.m_vContents.front();

	//if we've changed the file, lock the width and height control until we exit the dialog
	//it is after we OK this dialog, that IGB loads the new image and resizes the control to the image
	m_ctlImageFileCombo.GetWindowTextA(csFileName);
	if (csFileName != pIcon->getFileName()) {
		m_ctlEditWidth.EnableWindow(0);
		m_ctlEditVertExtent.EnableWindow(0);
	} else {
		m_ctlEditWidth.EnableWindow(1);
		m_ctlEditVertExtent.EnableWindow(1);
	}
}

void CProperties_Image::OnBnClickedCheckLockaspectratio()
{
	// when user checks the box, reset the height to respect aspect ratio
	updateHeightIfAspectLocked();
}

void CProperties_Image::updateHeightIfAspectLocked() {
	int checked = m_ctl_LockAspectRatioToImage.GetCheck();
	if (checked) {
		// when this is checked, reset image to correct aspect ratio
		UpdateData();
		CString csWidth;
		m_ctlEditWidth.GetWindowTextA(csWidth);
		int iWidth = atoi(csWidth);
		int iHeight = ceil(float(iWidth) * m_dImageHtoW);
		char buffer[16];
		_itoa_s(iHeight,buffer,16,10);
		m_ctlEditVertExtent.SetWindowText(buffer);
		UpdateData(false);
		// changed vert extent, assume top is to stay same, and move bottom.
		OnEnKillfocusY1();
	}
}

void CProperties_Image::updateWidthIfAspectLocked() {
	int checked = m_ctl_LockAspectRatioToImage.GetCheck();
	if (checked) {
		// when this is checked, reset image to correct aspect ratio
		UpdateData();
		CString csHeight;
		m_ctlEditVertExtent.GetWindowTextA(csHeight);
		int iHeight = atoi(csHeight);
		int iWidth = floor(float(iHeight) / m_dImageHtoW);
		char buffer[16];
		_itoa_s(iWidth,buffer,16,10);
		m_ctlEditWidth.SetWindowText(buffer);
		UpdateData(false);
		// changed width, assume top is to stay same, and move bottom.
		OnEnKillfocusX1();
	}
}
