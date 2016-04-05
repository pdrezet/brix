/** @file LgbSliderCtrl.cpp
 * Implementation of LgbSliderCtrl class
 * @author: Matthew Rutherford
 * @version: $Revision: 577 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */
#include "stdafx.h"
#include <cassert>

#include "LgbZOrderDlogBar.h"

#include "LgbSliderCtrl.h"


LgbSliderCtrl::LgbSliderCtrl(void):
m_pDlogBar(NULL)
{  }

LgbSliderCtrl::~LgbSliderCtrl(void)
{ }

int LgbSliderCtrl::Mfc2Lgb( const int &pos )
{
	return CSliderCtrl::GetRangeMin() + CSliderCtrl::GetRangeMax() - pos;
}

int LgbSliderCtrl::Lgb2Mfc( const int &pos )
{
	return CSliderCtrl::GetRangeMin() + CSliderCtrl::GetRangeMax() - pos;
}

int LgbSliderCtrl::GetPos()
{
	return Mfc2Lgb( CSliderCtrl::GetPos() );
}

void LgbSliderCtrl::SetPos(const int &pos)
{
	CSliderCtrl::SetPos( Lgb2Mfc(pos) );
}


void LgbSliderCtrl::SetTic(const int &pos)
{
	CSliderCtrl::SetTic(  Lgb2Mfc(pos)  );
}

BEGIN_MESSAGE_MAP(LgbSliderCtrl, CSliderCtrl)
ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

void LgbSliderCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	assert( m_pDlogBar != NULL );
	m_pDlogBar->childAdjustmentCompleted( ( CScrollBar * ) this );

	CSliderCtrl::OnLButtonUp(nFlags, point);
}
