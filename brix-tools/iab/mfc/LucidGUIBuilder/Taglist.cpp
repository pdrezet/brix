// Taglist.cpp : implementation file
//

#include "stdafx.h"
#include "DrawGUI.h"
#include "Taglist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Taglist dialog


Taglist::Taglist(CWnd* pParent /*=NULL*/)
	: CDialog(Taglist::IDD, pParent)
{
	//{{AFX_DATA_INIT(Taglist)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Taglist::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Taglist)
	DDX_Control(pDX, IDCLGB_LIST1, m_taglist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Taglist, CDialog)
	//{{AFX_MSG_MAP(Taglist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Taglist message handlers

BOOL Taglist::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	/*
	CString entry;
	int tagsize=TagList->GetSize();
	if (TagListbuf) {
		for (int i=0;i<255;i++) {
			entry.Format("% 3.3d |",i+1);
			if (i<tagsize) m_list.AddString(entry+TagListbuf->GetAt(i));
			else m_list.AddString(entry);
		}
	}
	else  {
		for (int i=0;i<255;i++) {
			entry.Format("% 3.3d |",i+1);
			m_list.AddString(entry);
		}
		//readonly here
	}
	if (assigned>-1) m_list.SetCurSel(assigned-1);
	*/
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Taglist::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
