#if !defined(_ENCAPSULATE_H_INCLUDED_)
#define _ENCAPSULATE_H_INCLUDED_


#include "Resource.h"
#include "LucidConstants.h"
#include "Porting_Classes/INXString.h"
#include "Porting_Classes/INXObjList.h"
#include "Porting_Classes/INXWidgets.h"
#include <wx/dialog.h>
#include <wx/event.h>
#include <wx/combobox.h>

/////////////////////////////////////////////////////////////////////////////
// Encapsulate dialog

class Encapsulate : public wxDialog
{
// Construction
public:
	Encapsulate(INXObjList* _encapsulated, wxWindow* pParent = NULL);   // standard constructor
	~Encapsulate();

	INXString inLabels[MAXXPORTS];
	INXString inNames[MAXXPORTS];
	INXString outLabels[MAXXPORTS];
	INXString outNames[MAXXPORTS];
	INXString startLabels[MAXXPORTS];
	INXString startNames[MAXXPORTS];
	INXString finishLabels[MAXXPORTS];
	INXString finishNames[MAXXPORTS];
/* MFCism */
	INX_Edit* inEdit[MAXXPORTS];
	INX_Static* inStatic[MAXXPORTS];
	INX_Edit* outEdit[MAXXPORTS];
	INX_Static* outStatic[MAXXPORTS];
	INX_Edit* startEdit[MAXXPORTS];
	INX_Static* startStatic[MAXXPORTS];
	INX_Edit* finishEdit[MAXXPORTS];
	INX_Static* finishStatic[MAXXPORTS];
	INXObjList* encapsulated;
	unsigned int inNum, outNum, startNum, finishNum;


// Dialog Data
	//{{AFX_DATA(Encapsulate)
	enum { IDD = IDD_ENCAPSULATE };
	INXString	m_BlockName;
	INXString	m_LongDescription;
	//}}AFX_DATA

private:
	INXString m_csMenuName;
	wxComboBox m_ctlMenuName;

public:
// Methods
	INXString getMenuName();	
protected:
	//void setMenuNamesDropList(set<INXString> sMenuNames);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Encapsulate)
	protected:
	//virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Encapsulate)
	virtual bool OnInitDialog();
	void OnOK(wxCommandEvent & event);
	//DECLARE_EVENT_TABLE()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENCAPSULATE_H__3D40BBF3_7822_4FED_A433_819E6CAFAD08__INCLUDED_)
