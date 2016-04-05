// GotoTimeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DrawProg.h"
#include "GotoTimeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGotoTimeDialog dialog


CGotoTimeDialog::CGotoTimeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGotoTimeDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGotoTimeDialog)
	m_DbgHistTime = 0;
	//}}AFX_DATA_INIT
}


void CGotoTimeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGotoTimeDialog)
	DDX_Text(pDX, IDC_TIME_EDIT, m_DbgHistTime);
	DDV_MinMaxLong(pDX, m_DbgHistTime, 0, 2147483647);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGotoTimeDialog, CDialog)
	//{{AFX_MSG_MAP(CGotoTimeDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGotoTimeDialog message handlers
