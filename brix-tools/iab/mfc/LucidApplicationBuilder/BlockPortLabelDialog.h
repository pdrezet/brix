#pragma once

#include "resource.h"
#include "condat.h"
#include "DEP.h"

// CBlockPortLabelDialog dialog

class CBlockPortLabelDialog : public CDialog
{
	DECLARE_DYNAMIC(CBlockPortLabelDialog)

public:
	CBlockPortLabelDialog(CString csOldLabel, ConData* pBlock, DEP* pDEP, CWnd* pParent = NULL);   // standard constructor
	virtual ~CBlockPortLabelDialog();

// Dialog Data
	enum { IDD = IDD_BLOCK_PORT_LABEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOk();
	virtual BOOL OnInitDialog();

	CString GetPortLabel();
	bool IsUnique();

private:
	CString m_csPortLabel;
	CString m_csOldPortLabel;
	ConData* m_pBlock;
	DEP* m_pDEP;
};
