#pragma once

#include "resource.h"
#include "condat.h"
#include "DEP.h"
#include "Porting_Classes/INXString.h"

// CBlockPortLabelDialog dialog

class CBlockPortLabelDialog : public CDialog
{
	DECLARE_DYNAMIC(CBlockPortLabelDialog)

public:
	CBlockPortLabelDialog(INXString csOldLabel, ConData* pBlock, DEP* pDEP, CWnd* pParent = NULL);   // standard constructor
	virtual ~CBlockPortLabelDialog();

// Dialog Data
	enum { IDD = IDD_BLOCK_PORT_LABEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOk();
	virtual BOOL OnInitDialog();

	INXString GetPortLabel();
	bool IsUnique();

private:
	INXString m_csPortLabel;
	INXString m_csOldPortLabel;
	ConData* m_pBlock;
	DEP* m_pDEP;
};
