// InstanceNameDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DrawProg.h"
#include "InstanceNameDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInstanceNameDialog dialog


CInstanceNameDialog::CInstanceNameDialog(ConData* blob, CWnd* pParent /*=NULL*/)
	: CDialog(CInstanceNameDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInstanceNameDialog)
	m_InstanceName = _T("");
	//}}AFX_DATA_INIT
	m_InstanceName = _T(blob->description);
}


void CInstanceNameDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInstanceNameDialog)
	DDX_Text(pDX, IDC_INSTANCE_EDIT, m_InstanceName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInstanceNameDialog, CDialog)
	//{{AFX_MSG_MAP(CInstanceNameDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInstanceNameDialog message handlers
