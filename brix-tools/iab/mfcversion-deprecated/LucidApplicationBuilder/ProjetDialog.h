#pragma once

#include "resource.h"
// CProjetDialog dialog


class CProjetDialog : public CDialog
{
	DECLARE_DYNAMIC(CProjetDialog)

public:
	CProjetDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProjetDialog();

// Dialog Data
	enum { IDD = IDD_PROJETDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
