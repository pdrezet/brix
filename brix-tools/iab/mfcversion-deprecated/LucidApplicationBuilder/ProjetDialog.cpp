// ProjetDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ProjetDialog.h"


// CProjetDialog dialog

IMPLEMENT_DYNAMIC(CProjetDialog, CDialog)

CProjetDialog::CProjetDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CProjetDialog::IDD, pParent)
{

}

CProjetDialog::~CProjetDialog()
{
}

void CProjetDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProjetDialog, CDialog)
END_MESSAGE_MAP()


// CProjetDialog message handlers
