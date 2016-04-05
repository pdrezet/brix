/** @file LgbZOrderDlog.cpp
 * Implementation of LgbZOrderDlog class
 * @author: Matthew Rutherford
 * @version: $Revision: 577 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */

#include "stdafx.h"
#include "LgbZOrderDlog.h"
#include "LucidTypedefs.h"
#include "DrawGUIView.h"
#include "../common/intToString.h"
#include "LgbSliderCtrl.h"

IMPLEMENT_DYNAMIC(LgbZOrderDlog, CDialog)

LgbZOrderDlog *LgbZOrderDlog::c_pDlog = NULL;

LgbZOrderDlog::LgbZOrderDlog(	CWnd* pParent /*=NULL*/)
: CDialog(LgbZOrderDlog::IDD, pParent), m_pCDrawGuiView( NULL )
{ }

LgbZOrderDlog::~LgbZOrderDlog()
{}

LgbZOrderDlog *LgbZOrderDlog::getLgbZOrderDlog( CWnd* pParent /*=NULL*/ )
{
	if(c_pDlog == NULL){
		// Create an instance once only
		c_pDlog = new LgbZOrderDlog(pParent);
		c_pDlog->Create( LgbZOrderDlog::IDD );
	}
	return c_pDlog;
}

void LgbZOrderDlog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ZCLIP_VAL, m_ctlEdit_ZClip);
	DDX_Control(pDX, IDC_EDIT_ZLEAN_VAL, m_ctlEdit_ZLeanVal);
	DDX_Control(pDX, IDC_SLIDER_ZCLIP, m_ctlSlider_ZClip);
	DDX_Control(pDX, IDC_SLIDER_ZLEAN, m_ctlSlider_ZLean);
}


BEGIN_MESSAGE_MAP(LgbZOrderDlog, CDialog)
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// LgbZOrderDlog message handlers

BOOL LgbZOrderDlog::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_pCDrawGuiView = NULL;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

Lgb_UserZVals_t LgbZOrderDlog::getSliderPositions()
{
	Lgb_UserZVals_t dummy;

	UpdateData();
	dummy.zClipVal = m_ctlSlider_ZClip.GetPos();
	dummy.zLeanVal = m_ctlSlider_ZLean.GetPos();

	return dummy;
}


void LgbZOrderDlog::uploadData(
								CDrawGUIView	*pView,
								const CString &fileName,
								const std::vector<int> &zClipTics,
								const bool &setZClipToMax,
								LgbZLeanBounds_t limits,
								Lgb_UserZVals_t  userVals )
{

	char buff[100];

#ifdef DEBUG
	sprintf_s( buff, 100, "%s %d, %d, %d, %d\n", "LgbZOrderDlog ZLean, ZClip, ZClipMin, ZClipMax vals set to: ",
		userVals.zLeanVal, userVals.zClipVal, zClipTics.front(), zClipTics.back() );
	OutputDebugString(buff);


	for(size_t i=0;i<zClipTics.size();i++){
		sprintf_s( buff, 100, "%s %d %s %d\n", "Tic[", i, "]=: ", zClipTics[i] );
		OutputDebugString(buff);
	}
#endif

	this->SetWindowTextA( fileName );

	m_pCDrawGuiView = pView;

	m_cZLimits = limits;
	m_cZUserVals = userVals;

	m_ctlSlider_ZLean.SetRangeMin(	m_cZLimits.zLeanMin );
	m_ctlSlider_ZLean.SetRangeMax(	m_cZLimits.zLeanMax );
	m_ctlSlider_ZLean.SetPos	(	m_cZUserVals.zLeanVal );

	m_ctlSlider_ZClip.SetRangeMin(	zClipTics.front() -1 ); 
	m_ctlSlider_ZClip.SetRangeMax(	zClipTics.back() );

	if(setZClipToMax) 
		m_ctlSlider_ZClip.SetPos( zClipTics.back() );

	m_ctlEdit_ZClip.SetWindowTextA( intToString( m_ctlSlider_ZClip.GetPos() ));
	m_ctlEdit_ZLeanVal.SetWindowTextA( intToString( m_ctlSlider_ZLean.GetPos() ));

	m_ctlSlider_ZLean.SetTic( 1 );
	m_ctlSlider_ZLean.SetTic( 2 );
	m_ctlSlider_ZLean.SetTic( 3 );
	m_ctlSlider_ZLean.SetTicFreq( 1 );

	m_ctlSlider_ZClip.ClearTics(0);
	m_ctlSlider_ZClip.SetTicFreq( 1 );

	if(zClipTics.size() > 2){
		for(size_t i=0;i<zClipTics.size();i++){
			m_ctlSlider_ZClip.SetTic( zClipTics[i] );
		}
	}

	m_ctlSlider_ZClip.RedrawWindow();

	UpdateData(false);
}

void LgbZOrderDlog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);

	if(m_pCDrawGuiView==NULL) return; // No GUI got focused yet!
	CString csDum;

	UpdateData();

	if(  (LgbSliderCtrl *) pScrollBar ==  &m_ctlSlider_ZClip ){

		int pos = m_ctlSlider_ZClip.GetPos(); 
		m_cZUserVals.zClipVal = pos;
		m_pCDrawGuiView->setUpperZActiveLevel( pos );
		m_ctlEdit_ZClip.SetWindowTextA( intToString( pos ) );

	}else if( (LgbSliderCtrl *) pScrollBar == &m_ctlSlider_ZLean){

		int pos = m_ctlSlider_ZLean.GetPos();
		m_cZUserVals.zLeanVal = pos;
		m_pCDrawGuiView->setZLeanLevel( pos );
		m_ctlEdit_ZLeanVal.SetWindowTextA( intToString(pos) );

	}

	UpdateData(false);

}
