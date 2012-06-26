// TagDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DrawProg.h"
#include "TagDialog.h"
#include "../common/LucidConstants.h"
#include "condat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTagDialog dialog


CTagDialog::CTagDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTagDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTagDialog)
	//}}AFX_DATA_INIT
}

CTagDialog::CTagDialog(CStringArray* _boolTags, CStringArray* _intTags, CStringArray* _realTags, 
	CStringArray* _stringTags, CStringArray* _eventTags, int _dataType, int _portType, INXObjList* _condata,
	int _tagLine, CWnd* pParent /*=NULL*/)
	: CDialog(CTagDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTagDialog)
	//}}AFX_DATA_INIT
	boolTags = _boolTags;
	intTags = _intTags;
	realTags = _realTags;
	stringTags = _stringTags;
	eventTags = _eventTags;
	dataType = _dataType;
	portType = _portType;
	condata = _condata;
	tagLine = _tagLine;
}


void CTagDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTagDialog)
	DDX_Control(pDX, IDC_TAG_COMBO, m_Tag);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTagDialog, CDialog)
	//{{AFX_MSG_MAP(CTagDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTagDialog message handlers

BOOL CTagDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// if tagging line don't add items to combobox
	if (tagLine) {
		return TRUE;
	}
	// Add items from tag lists to the combobox depending on data type
	switch (dataType) {
	case 0 : 
		{
			for (int i=0; i<boolTags->GetSize(); i++) {
				m_Tag.AddString(boolTags->GetAt(i));
			}
			break;
		}
	case 1 :
		{
			for (int i=0; i<intTags->GetSize(); i++) {
				m_Tag.AddString(intTags->GetAt(i));
			}
			break;
		}
	case 2 :
		{
			for (int i=0; i<realTags->GetSize(); i++) {
				m_Tag.AddString(realTags->GetAt(i));
			}
			break;
		}
	case 3 :
		{
			for (int i=0; i<stringTags->GetSize(); i++) {
				m_Tag.AddString(stringTags->GetAt(i));
			}
			break;
		}
	case 4 :
		{
			for (int i=0; i<eventTags->GetSize(); i++) {
				m_Tag.AddString(eventTags->GetAt(i));
			}
			break;
		}
	}

	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_TAG_COMBO);
	if(pCombo != NULL) {
		pCombo->SetFocus();
		return 0; //since we are explicity setting focus
	}		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTagDialog::OnOK() 
{
	// TODO: Add extra validation here

	m_Tag.GetWindowText(tag);
	
	// check tag is not used by another data type
	if (!IsTagUnique()) {
		AfxMessageBox("This tag is used by a different data type.");
	}
	// if output check tag is not used by another output
	else if (!IsUniqueOutTag()) {
		if (portType == OUTPUTPORT) {
			AfxMessageBox("The tag is already used by an output port.");
		}
		else if (portType == FINISHPORT) {
			AfxMessageBox("The tag is already used by a finish port.");
		}
	}
	// check tag is not empty string
	else if (tag == "") {
		AfxMessageBox("You must enter a tag.");
	}
	else {
		if (IsTagNew()) {
			AddTag2List();
		}
		CDialog::OnOK();
	}
}

void CTagDialog::AddTag2List() {
	switch (dataType) {
	case 0 : boolTags->Add(tag); break;
	case 1 : intTags->Add(tag); break;
	case 2 : realTags->Add(tag); break;
	case 3 : stringTags->Add(tag); break;
	case 4 : eventTags->Add(tag); break;
	}
}

bool CTagDialog::IsTagUnique() {
	CStringArray tmp;

	// if tagging an existing line then check every data type, as don't want to 
	// connect to an existing tag
	// if adding tags to ports then check it is not used by another data type.
	if (dataType != BOOLEAN || tagLine) {
		for (int i=0; i<boolTags->GetSize(); i++) {
			if (tag == boolTags->GetAt(i)) {
				return FALSE;
			}
		}
	}
	if (dataType != INTEGER || tagLine) {
		for (int i=0; i<intTags->GetSize(); i++) {
			if (tag == intTags->GetAt(i)) {
				return FALSE;
			}
		}
	}
	if (dataType != FLOAT || tagLine) {
		for (int i=0; i<realTags->GetSize(); i++) {
			if (tag == realTags->GetAt(i)) {
				return FALSE;
			}
		}
	}
	if (dataType != STRING || tagLine) {
		for (int i=0; i<stringTags->GetSize(); i++) {
			if (tag == stringTags->GetAt(i)) {
				return FALSE;
			}
		}
	}
	if (dataType != EVENT || tagLine) {
		for (int i=0; i<eventTags->GetSize(); i++) {
			if (tag == eventTags->GetAt(i)) {
				return FALSE;
			}
		}
	}

	return TRUE;
}


bool CTagDialog::IsTagNew() {
	CStringArray tmp;
	
	if (dataType == BOOLEAN) {
		for (int i=0; i<boolTags->GetSize(); i++) {
			if (tag == boolTags->GetAt(i)) {
				return FALSE;
			}
		}
	}
	if (dataType == INTEGER) {
		for (int i=0; i<intTags->GetSize(); i++) {
			if (tag == intTags->GetAt(i)) {
				return FALSE;
			}
		}
	}
	if (dataType == FLOAT) {
		for (int i=0; i<realTags->GetSize(); i++) {
			if (tag == realTags->GetAt(i)) {
				return FALSE;
			}
		}
	}
	if (dataType == STRING) {
		for (int i=0; i<stringTags->GetSize(); i++) {
			if (tag == stringTags->GetAt(i)) {
				return FALSE;
			}
		}
	}
	if (dataType == EVENT) {
		for (int i=0; i<eventTags->GetSize(); i++) {
			if (tag == eventTags->GetAt(i)) {
				return FALSE;
			}
		}
	}

	return TRUE;
}

bool CTagDialog::IsUniqueOutTag() {
	INXPOSITION pos;
	ConData* blob;

	// Make sure no other output ports have same tag
	if (portType == OUTPUTPORT) {
		pos = condata->GetHeadPosition();
		while (pos) {
			blob = (ConData*) condata->GetNext(pos);
			for (UINT i=0; i<blob->outputport_num; i++) {
				if (tag == blob->outputport[i]->tag) {
					return FALSE;
				}
			}
		}
	}
	else if (portType == FINISHPORT) {
		pos = condata->GetHeadPosition();
		while (pos) {
			blob = (ConData*) condata->GetNext(pos);
			for (UINT i=0; i<blob->finishport_num; i++) {
				if (tag == blob->finishport[i]->tag) {
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}