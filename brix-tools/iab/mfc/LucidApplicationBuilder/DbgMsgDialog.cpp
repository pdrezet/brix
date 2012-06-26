// DbgMsgDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DrawProg.h"
#include "DbgMsgDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDbgMsgDialog dialog


CDbgMsgDialog::CDbgMsgDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDbgMsgDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDbgMsgDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDbgMsgDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDbgMsgDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDbgMsgDialog, CDialog)
	//{{AFX_MSG_MAP(CDbgMsgDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDbgMsgDialog message handlers
