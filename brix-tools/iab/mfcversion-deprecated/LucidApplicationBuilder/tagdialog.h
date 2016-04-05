#if !defined(AFX_TAGDIALOG_H__695AD5F2_CC23_47B0_B368_1D0AEC7ECD43__INCLUDED_)
#define AFX_TAGDIALOG_H__695AD5F2_CC23_47B0_B368_1D0AEC7ECD43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TagDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTagDialog dialog
#include "Porting_Classes/INXObjList.h"
#include "Porting_Classes/INXString.h"
class CTagDialog : public CDialog
{
// Construction
public:
	CTagDialog(CWnd* pParent = NULL);   // standard constructor
	CTagDialog(INXObjArray<INXString>* _boolTags, INXObjArray<INXString>* _intTags, INXObjArray<INXString>* _realTags, INXObjArray<INXString>* _stringTags, 
		INXObjArray<INXString>* _eventTags, int _dataType, int _portType, INXObjList* _condata, int _tagLine, CWnd* pParent = NULL); 

// Dialog Data
	//{{AFX_DATA(CTagDialog)
	enum { IDD = IDD_TAG_LINE };
	CComboBox	m_Tag;
	//}}AFX_DATA

	// Attributes
	INXString tag;
	INXObjArray<INXString>* boolTags;
	INXObjArray<INXString>* intTags;
	INXObjArray<INXString>* realTags;
	INXObjArray<INXString>* stringTags;
	INXObjArray<INXString>* eventTags;
	int dataType;
	int portType;
	INXObjList* condata;
	int tagLine;

	// Methods
	void AddTag2List();
	bool IsTagUnique();
	bool IsTagNew();
	bool IsUniqueOutTag();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTagDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTagDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAGDIALOG_H__695AD5F2_CC23_47B0_B368_1D0AEC7ECD43__INCLUDED_)
