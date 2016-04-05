/** @file LgbSliderCtrl.h
 * Represents an MFC slider control where the max is at the top, rather than the botom!
 * @author: Matthew Rutherford
 * @version: $Revision: 577 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */
#pragma once
#include "afxcmn.h"


// Forward decln
class LgbZOrderDlogBar;

//! Represents an MFC slider control where the max is displayed at the top, rather than the botom!
class LgbSliderCtrl : public CSliderCtrl
{

public:
	LgbSliderCtrl(void);
	~LgbSliderCtrl(void);

	int GetPos();					//!< Get current pos of slider
	void SetPos(const int &pos);	//!< Set current pos of slider
	void SetTic(const int &nTic);	//!< Set a tic mark at position 'nTic'.
	LgbZOrderDlogBar *m_pDlogBar;

private:

	int Mfc2Lgb( const int &pos ); //!< Convert from the pos MFC thinks the slider is at to the reversed, LGB intepretation
	int Lgb2Mfc( const int &pos ); //!< Convert from the pos LGB thinks the slider is at to the reversed, MFC intepretation
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
