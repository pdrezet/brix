// LucidStateMachineDialog1.cpp : implementation file
//

#include "stdafx.h"
#include "DrawProg.h"
#include "LucidStateMachineDialog1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLucidStateMachineDialog dialog


CLucidStateMachineDialog::CLucidStateMachineDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CLucidStateMachineDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLucidStateMachineDialog)
	m_csState = _T("");
	m_csNumTransitionsTo = _T("");
	//}}AFX_DATA_INIT
}


void CLucidStateMachineDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLucidStateMachineDialog)
	DDX_Text(pDX, IDC_EDIT3, m_csState);
	DDX_Text(pDX, IDC_EDIT1, m_csNumTransitionsTo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLucidStateMachineDialog, CDialog)
	//{{AFX_MSG_MAP(CLucidStateMachineDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLucidStateMachineDialog message handlers
