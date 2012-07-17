// Tags.cpp : implementation file
//
/*

  Tag dialog box shows IO ports 


  */

#include "stdafx.h"
#include "DrawProg.h"
#include "Tags.h"
#include "GetInput.h"
#include "config.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Tags dialog


Tags::Tags(CWnd* pParent /*=NULL*/)
	: CDialog(Tags::IDD, pParent)
{
	//{{AFX_DATA_INIT(Tags)
	//}}AFX_DATA_INIT
	//CDialog::CDialog(Tags::IDD, pParent);
	deleteme=0;
	momentary=1;
	constant=0;
	negedge=0;
	plusedge=1;
	recorddelim="\\n";
	fielddelim=',';
	option2="";
	option1="";
	description="";
	fixedinfo="";
	TagList=NULL;
	//m_tags.CCombo
	assigned=-1;
}


void Tags::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Tags)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Tags, CDialog)
	//{{AFX_MSG_MAP(Tags)
	ON_BN_CLICKED(ID_DELETE, OnDelete)
	ON_LBN_DBLCLK(IDC_LIST, OnDblclkList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Tags message handlers

BOOL Tags::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	INXString entry;
	int tagsize=TagList->GetSize();
	if (TagList) {
		for (int i=0;i<255;i++) {
			entry.Format("% 3.3d |",i+1);
			if (i<tagsize) m_list.AddString(entry+ (INXString)TagList->GetAt(i));
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
	else m_list.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Tags::OnDelete() 
{
	// TODO: Add your control notification handler code here
	if (AfxMessageBox("Are you sure you want to delete this block?",MB_YESNO)==IDYES) {
		deleteme=1;
		CDialog::OnOK();
	}
}

void Tags::OnOK() 
{
	// TODO: Add extra validation here
	selected=m_list.GetCurSel( )+1 ;
	if (selected==CB_ERR ) {
		AfxMessageBox("Must Select a TAG");
			return;
	}
	/*if (((assigned!=selected)&&(TagList->GetAt(selected-1)!=UNUSEDTAGSTRING)) ||
	((assigned==-1)&&(TagList->GetAt(selected-1)!=UNUSEDTAGSTRING))){
		//don't allow to nick already assigned tags
		AfxMessageBox("Cannot assign previously assigned channels to this device");
		return;
	}*/
	option1.Format("%d",selected);//set the option to the selected tag
	INXString stuff;
	m_list.GetText(selected-1,(LPTSTR)stuff);
	if (stuff.Mid(6)==UNUSEDTAGSTRING) {
		description=UNNAMEDTAGSTRING;
		//update seperate tag list
		//stuff.Format("% 3.3d |%s",selected-1,UNNAMEDTAGSTRING);
		TagList->RemoveAt(selected-1);
		TagList->InsertAt(selected-1,UNNAMEDTAGSTRING);
	}
	else {
		m_list.GetText(selected-1,(LPTSTR)stuff);
		description=stuff.Mid(6);
	}
	CDialog::OnOK();
}



void Tags::OnDblclkList() 
{
	int i;
	// TODO: Add your control notification handler code here
	selected=m_list.GetCurSel( ) ;
	if (selected==CB_ERR ) {
		AfxMessageBox("Must Select a TAG");
		return;
	}
	
	INXString num;
	INXString entry;
	GetInput box;
	int tagsize=TagList->GetSize();
	if (selected<tagsize) box.m_string=TagList->GetAt(selected);
	num.Format("%d",selected);
	if (box.DoModal()==IDOK) {
		TagList->SetAtGrow(selected,box.m_string);
	}
	tagsize=TagList->GetSize();
	for (i=0;i<256;i++)m_list.DeleteString(0);
	for (i=0;i<255;i++) {
		entry.Format("% 3.3d |  ",i+1);
		if (i<tagsize) m_list.AddString(entry+TagList->GetAt(i));
		else m_list.AddString(entry);
	}
	m_list.SetCurSel(selected);
}
