// InlineTextDialog.cpp : implementation file
//

#include "stdafx.h"
#include "InlineTextDialog.h"


// CInlineTextDialog dialog

IMPLEMENT_DYNAMIC(CInlineTextDialog, CDialog)

CInlineTextDialog::CInlineTextDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CInlineTextDialog::IDD, pParent)
{
	// ***REVISIT*** SDG: This was my attempt to load a bitmap of the text into the listbox
	//m_ctlListClass.SetDrawC(&m_picDrawc);
}

CInlineTextDialog::~CInlineTextDialog()
{
}

void CInlineTextDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CLASS, m_ctlEditClass);
	DDX_Control(pDX, IDC_COMBO_FONT, m_ctlComboFont);
	DDX_Control(pDX, IDC_LIST_CLASS, m_ctlListClass);
	DDX_Control(pDX, IDC_EDIT_INLINE_PC_TRANSP3, m_ctlEditTransp);
	DDX_Control(pDX, IDC_SLIDER_TRANSP, m_ctlSliderTransp);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_ctlButtonDelete);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_ctlUpdateButton);
}


BEGIN_MESSAGE_MAP(CInlineTextDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_COLOUR, &CInlineTextDialog::OnBnClickedButtonColour)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CInlineTextDialog::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CInlineTextDialog::OnBnClickedButtonDelete)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_TRANSP, &CInlineTextDialog::OnNMCustomdrawSliderTransp)
	ON_WM_HSCROLL()
	ON_EN_KILLFOCUS(IDC_EDIT_INLINE_PC_TRANSP3, &CInlineTextDialog::OnEnKillfocusEditInlinePcTransp3)
	ON_LBN_SELCHANGE(IDC_LIST_CLASS, &CInlineTextDialog::OnLbnSelchangeListClass)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CInlineTextDialog::OnBnClickedButtonUpdate)
END_MESSAGE_MAP()


// CInlineTextDialog message handlers
BOOL CInlineTextDialog::OnInitDialog()
{
	char buffer[16];

	CDialog::OnInitDialog();

	m_ctlSliderTransp.SetRange(0, 255);
	m_ctlButtonDelete.EnableWindow(false);
	m_ctlUpdateButton.EnableWindow(false);

	// load the class list box
	for (size_t i=0; i<m_vInlineTextVec.size(); i++) {
		m_ctlListClass.AddString(m_vInlineTextVec[i].GetClass());
	}
	SetTextStyleBgColor();
	m_ctlListClass.SetTextStylesVec(m_vInlineTextVec);
	// ***REVISIT*** SDG: This was my attempt to load a bitmap of the text into the listbox
	/*
	m_ctlListClass.Init();
    //m_ctlListClass.AddItem(IDB_BLACK);
    m_ctlListClass.AddItem();
	*/

	// Initialise the transparency textbox and slider
	int iAlpha = m_cColors.m_iFgAlpha;

	m_ctlSliderTransp.SetPos(255 - iAlpha);

	float fTmp = float( (255 - iAlpha ))/ float( 2.55 );
	sprintf_s( buffer, 16, "%3.1f", fTmp );
	m_ctlEditTransp.SetWindowText(buffer);

	// Load the fonts into the combobox
	for(size_t i=0; i<m_vFontVec.size(); i++){
		m_ctlComboFont.AddString(m_vFontVec[i].GetFontName());
	}
	m_ctlComboFont.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CInlineTextDialog::OnBnClickedButtonColour()
{
	CHOOSECOLOR cc;                 // common dialog box structure 
	static COLORREF acrCustClr[16]; // array of custom colors 

	// Initialize CHOOSECOLOR 
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = *(AfxGetApp()->m_pMainWnd);
	cc.lpCustColors = (LPDWORD) acrCustClr;
	cc.lpCustColors[0] = RGB(m_cColors.m_iFgRed, m_cColors.m_iFgGreen, m_cColors.m_iFgBlue );
	cc.rgbResult = RGB(m_cColors.m_iFgRed, m_cColors.m_iFgGreen, m_cColors.m_iFgBlue );
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
 
	if (ChooseColor(&cc)==TRUE) {
		m_cColors.m_iFgRed = GetRValue(cc.rgbResult);
		m_cColors.m_iFgGreen = GetGValue(cc.rgbResult);
		m_cColors.m_iFgBlue = GetBValue(cc.rgbResult);

		//m_ctlEditColouredText.SetTextColor( cc.rgbResult );

		UpdateData(false);
	}
}

void CInlineTextDialog::OnBnClickedButtonAdd()
{
	CString csClass, csFont;

	m_ctlEditClass.GetWindowTextA(csClass);
	if (csClass == "") {
		AfxMessageBox("You must enter a class to add.");
		return;
	}
	else if (IsClassInVec(csClass)) {
		AfxMessageBox("This class already exists.");
		return;
	}

	m_ctlComboFont.GetWindowTextA(csFont);
	m_cColors.m_iFgAlpha = 255 - m_ctlSliderTransp.GetPos();
	InlineText xInlineClass(csClass, m_cColors, csFont);
	m_vInlineTextVec.push_back(xInlineClass);
	m_ctlListClass.SetTextStylesVec(m_vInlineTextVec);

	m_ctlListClass.AddString(csClass);
}

void CInlineTextDialog::OnBnClickedButtonDelete()
{
	CString csClass;

	// Load dialog varbls into support ones
	UpdateData();

	// get selected row pos
	int iSelPos = LB_ERR;
	iSelPos = m_ctlListClass.GetCurSel();

	if(iSelPos != LB_ERR){ // something is selected
		m_ctlListClass.GetText(iSelPos, csClass);
		RemoveInlineTextFromVec(csClass);
		UpdateListbox();
		m_ctlButtonDelete.EnableWindow(false);
		m_ctlUpdateButton.EnableWindow(false);
	}
}

// Removes the InlineText object from the vector specified by csClass
void CInlineTextDialog::RemoveInlineTextFromVec(CString csClass)
{
	UINT index;
	bool remove = false;

	for (UINT i=0; i<m_vInlineTextVec.size(); i++) {
		if (m_vInlineTextVec[i].GetClass() == csClass) {
			remove = TRUE;
			index = i;
		}
	}

	if (remove) {
		m_vInlineTextVec.erase(m_vInlineTextVec.begin()+index, m_vInlineTextVec.begin()+index+1);
	}
}

void CInlineTextDialog::GetInlineTextVec(std::vector<InlineText> &vInlineTextVec)
{
	vInlineTextVec = m_vInlineTextVec;
}

void CInlineTextDialog::SetInlineTextVec(std::vector<InlineText> vInlineTextVec)
{
	m_vInlineTextVec = vInlineTextVec;
}

// Returns TRUE if the class is in the InlineText Vector
bool CInlineTextDialog::IsClassInVec(CString csClass)
{
	bool bRet = false;

	for (size_t i=0; i<m_vInlineTextVec.size(); i++) {
		if (m_vInlineTextVec[i].GetClass() == csClass) {
			bRet = true;
		}
	}

	return bRet;
}

void CInlineTextDialog::SetColor(LgbColorsDef cColors)
{
	m_cColors = cColors;
}

void CInlineTextDialog::SetAlpha(int iAlpha)
{
	m_cColors.m_iFgAlpha = iAlpha;
}

void CInlineTextDialog::OnNMCustomdrawSliderTransp(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CInlineTextDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	char buffer[16];

	float fDum = float( (m_ctlSliderTransp.GetPos() ))/ float( 2.55 );
	sprintf_s( buffer, 16, "%3.1f", fDum );

	m_ctlEditTransp.SetWindowText(buffer);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CInlineTextDialog::OnEnKillfocusEditInlinePcTransp3()
{
	CString csDum;
	m_ctlEditTransp.GetWindowTextA(csDum);
	double dDum = atof(csDum);

	if(dDum>100.0)dDum = 100.0;
	int iDum = (int) ( (dDum/100.0) * 255);

	m_ctlSliderTransp.SetPos( iDum );
}

void CInlineTextDialog::OnLbnSelchangeListClass()
{
	UpdateData();

	CString csClass;
	InlineText xInlineText;
	int iAlpha;
	char buffer[16];

	// get selected row pos
	int iSelPos = LB_ERR;
	iSelPos = m_ctlListClass.GetCurSel();

	// Display the selected Inline Text values
	if (iSelPos != LB_ERR) { // something is selected
		m_ctlButtonDelete.EnableWindow(true);
		m_ctlUpdateButton.EnableWindow(true);
		m_ctlListClass.GetText(iSelPos, csClass);
		m_ctlEditClass.SetWindowTextA(csClass);
		GetInlineTextFromVec(csClass, xInlineText);
		xInlineText.GetColors(m_cColors);

		iAlpha = m_cColors.m_iFgAlpha;
		m_ctlSliderTransp.SetPos(255 - iAlpha);
		float fTmp = float((255 - iAlpha ))/ float(2.55);
		sprintf_s( buffer, 16, "%3.1f", fTmp );
		m_ctlEditTransp.SetWindowTextA(buffer);

		m_ctlComboFont.SetWindowTextA(xInlineText.GetFont());
	}

	UpdateData(false);
}

// Returns the InlineText object in the vector specified by csClass
void CInlineTextDialog::GetInlineTextFromVec(CString csClass, InlineText &xInlineText)
{
	for (size_t i=0; i<m_vInlineTextVec.size(); i++) {
		if (m_vInlineTextVec[i].GetClass() == csClass) {
			xInlineText = m_vInlineTextVec[i];
		}
	}
}

void CInlineTextDialog::OnBnClickedButtonUpdate()
{
	CString csClass, csUpdatedClass, csFont;

	// get selected row pos
	int iSelPos = LB_ERR;
	iSelPos = m_ctlListClass.GetCurSel();

	// Update selected Inline Text
	if (iSelPos != LB_ERR) { // something is selected
		m_ctlListClass.GetText(iSelPos, csClass);
		m_ctlEditClass.GetWindowTextA(csUpdatedClass);
		m_cColors.m_iFgAlpha = 255 - m_ctlSliderTransp.GetPos();
		m_ctlComboFont.GetWindowTextA(csFont);
		InlineText xInlineText(csUpdatedClass, m_cColors, csFont);
		UpdateInlineTextInVec(csClass, xInlineText);
		UpdateListbox();
		m_ctlButtonDelete.EnableWindow(false);
		m_ctlUpdateButton.EnableWindow(false);
	}
}

// Updates the InlineText object in the vector specified by csClass
void CInlineTextDialog::UpdateInlineTextInVec(CString csClass, InlineText xInlineText)
{
	for (size_t i=0; i<m_vInlineTextVec.size(); i++) {
		if (m_vInlineTextVec[i].GetClass() == csClass) {
			m_vInlineTextVec[i] = xInlineText;
		}
	}
}

void CInlineTextDialog::UpdateListbox()
{
	m_ctlListClass.ResetContent();
	for(size_t i=0; i<m_vInlineTextVec.size(); i++){
		m_ctlListClass.AddString(m_vInlineTextVec[i].GetClass());
	}
	m_ctlListClass.SetTextStylesVec(m_vInlineTextVec);
}

void CInlineTextDialog::SetFontVec(std::vector<LgbFont> vFontVec)
{
	m_vFontVec = vFontVec;
}

// Sets the background colour for each text style to be the same as the textbox background colour
void CInlineTextDialog::SetTextStyleBgColor()
{
	for (size_t i=0; i<m_vInlineTextVec.size(); i++) {
		m_vInlineTextVec[i].SetBgColor(m_cColors.m_iBgAlpha, m_cColors.m_iBgRed, m_cColors.m_iBgGreen, m_cColors.m_iBgBlue);
	}
}