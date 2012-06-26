/** @file LgbZOrderDlog.h
 * Represents the dialog that LGB uses to control z-display clipping & pseudo-3D lean
 * @author: Matthew Rutherford
 * @version: $Revision: 577 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */
#pragma once
#include "stdafx.h"

#include "LucidTypedefs.h"
#include "Resource.h"
#include "LgbSliderCtrl.h"

#include "afxwin.h"
#include "afxcmn.h"
#include <vector>

// LgbZOrderDlog dialog

class CDrawGUIView;

//! The dialog that LGB uses to control z-display clipping & pseudo-3D lean
/*! 
	There is only 1 instance of this dialog, shared between all LGB views.
	Each time a view gets the focus, it loads its own z-pos paramaters into the dlog,
	which repaints itself to show these.  So that the view 'knows' what its own zclip
	settings are - both for its own purposes and so that the view can reset the dialog
	when it regains focus - the dialog constantly updates the view's z-pos display
	data as the dlog is maanipulated by the user.
	The reason for not doing a std 'singleton' implem was because of MFC dialog initialisation
	funnies that I didn't have time to sort out.
*/
class LgbZOrderDlog : public CDialog
{
	
	DECLARE_DYNAMIC(LgbZOrderDlog)

public:	
	LgbZOrderDlog(	CWnd* pParent = NULL);  //!< standard constructor
	virtual ~LgbZOrderDlog();				//!< standard destructor
	static LgbZOrderDlog *c_pDlog;			//!< Ptr to the 1 and only instance

	static LgbZOrderDlog *getLgbZOrderDlog( CWnd* pParent = NULL );

	Lgb_UserZVals_t getSliderPositions();

	//! Called by a view as its get the focus, to set this dlog to reflect the view's data.
	/*!
	\param pView ptr to view that just gained focus (which is making the call)
	\param fileName Name of view's layout file (useful reminder to user when sets as dlog title)
	\param tics		Array of tick marks for z-scale ( tick present at whatever z-level an icon exists at)
	\param setZClipToMax If true, set the z-clip plane to max z-pos.
	\param limits 
	\param userVals The values of the user-settable sliders
	*/
	void uploadData(
		CDrawGUIView	*pView,
		const CString &fileName,
		const std::vector<int> &tics,
		const bool &setZClipToMax,
		LgbZLeanBounds_t limits,
		Lgb_UserZVals_t  userVals);

// Dialog Data
	enum { IDD = IDD_LGB_ZORDER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:

	CEdit m_ctlEdit_ZClip;			//!< RO field for echo of current z-clip slider pos
	CEdit m_ctlEdit_ZLeanVal;		//!< RO filed for echo of current z-lean slider pos
	LgbSliderCtrl m_ctlSlider_ZClip; //!< z-clip Slider control
	LgbSliderCtrl m_ctlSlider_ZLean; //!< z-lean Slider control

	Lgb_UserZVals_t m_cZUserVals; //!< z-lean & z-clip Slider control settings
	LgbZLeanBounds_t m_cZLimits; //!<

	CDrawGUIView *m_pCDrawGuiView; //!< currently-focused view

	virtual BOOL OnInitDialog();

	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);//!< Called whenever slider pos moved

	};
