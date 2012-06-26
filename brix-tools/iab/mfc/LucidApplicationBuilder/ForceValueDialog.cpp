// ForceValueDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DrawProg.h"
#include "ForceValueDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CForceValueDialog dialog


CForceValueDialog::CForceValueDialog(int _dataType, CWnd* pParent /*=NULL*/)
	: CDialog(CForceValueDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CForceValueDialog)
	m_ForceValue = _T("");
	//}}AFX_DATA_INIT
	dataType = _dataType;
}

bool CForceValueDialog::isDigit(char c) {
	if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' ||
		c == '6' || c == '7' || c == '8' || c == '9') {
		return TRUE;
	}
	return FALSE;
}


void CForceValueDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CForceValueDialog)
	DDX_Text(pDX, IDC_EDIT_VALUE, m_ForceValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CForceValueDialog, CDialog)
	//{{AFX_MSG_MAP(CForceValueDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CForceValueDialog message handlers

void CForceValueDialog::OnOK() 
{
	bool errorFlag = FALSE;
	int dotCnt;
	
	UpdateData(TRUE);
	// Check textbox text is valid
	// check for empty string
	if (dataType != 3 && m_ForceValue == "") {
		AfxMessageBox("ERROR: must assign a value.");
		errorFlag = TRUE;
	}
	// if the line datatype is bool then check it is a 0 or 1
	else if (dataType == 0) {
		if (m_ForceValue != "0" && m_ForceValue != "1") {
			AfxMessageBox("ERROR: Line is of type bool and must be a 0 or 1");
			errorFlag = TRUE;
		}
	}
	// if the line datatype is integer then check it
	else if (dataType == 1) {
		// check it is an integer
		for (int j=0; j < m_ForceValue.GetLength(); j++) {
			if (j==0 && m_ForceValue.GetAt(0) == '-') {
				if (m_ForceValue.GetLength() < 2) {
					AfxMessageBox("ERROR: Value must be of type integer.");
					errorFlag = TRUE;
				}
			}
			else if (!isDigit(m_ForceValue.GetAt(j))) {
				AfxMessageBox("ERROR: Value must be of type integer.");
				errorFlag = TRUE;
				break;
			}
		}
	}
	// if the line datatype is real then check it
	else if (dataType == 2) {
		// check it is a real
		dotCnt = 0;
		for (int j=0; j < m_ForceValue.GetLength(); j++) {
			if (m_ForceValue.GetAt(j) == '.') {
				dotCnt++;
			}
			if (j==0 && m_ForceValue.GetAt(0) == '-') {
				if (m_ForceValue.GetLength() < 2) {
					AfxMessageBox("ERROR: Value must be of type real.");
					errorFlag = TRUE;
				}
			}
			else if ((!isDigit(m_ForceValue.GetAt(j)) && m_ForceValue.GetAt(j) != '.') || dotCnt > 1) {
				AfxMessageBox("ERROR: Value must be of type real.");
				errorFlag = TRUE;
				break;
			}
		}
	}

	// if the textboxes contain valid text then store this updated text in the icon
	if (!errorFlag) {
		CDialog::OnOK();
	}
}
