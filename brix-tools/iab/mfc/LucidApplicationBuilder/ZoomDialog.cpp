// ZoomDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DrawProg.h"
#include "ZoomDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoomDialog dialog


CZoomDialog::CZoomDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CZoomDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZoomDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CZoomDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZoomDialog)
	DDX_Control(pDX, IDC_ZOOM_COMBO, m_scale);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZoomDialog, CDialog)
	//{{AFX_MSG_MAP(CZoomDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoomDialog message handlers

BOOL CZoomDialog::OnInitDialog() 
{
	char tmp[MAX_ZOOM_CHAR] = {'\0'};

	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	_itoa_s(iScale, tmp, RADIX);
	m_scale.SetWindowText((CString)tmp);
	for (int i=MAX_ZOOM; i>=MIN_ZOOM; i=i-ZOOM_DELTA) {
		_itoa_s(i, tmp, RADIX);
		m_scale.AddString((CString)tmp);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CZoomDialog::OnOK() 
{
	// TODO: Add extra validation here
	m_scale.GetWindowText(szScale);
	iScale = atoi(szScale);
	
	CDialog::OnOK();
}
