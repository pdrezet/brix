// InterfaceDropTarget.h: Schnittstelle für die Klasse CInterfaceDropTarget.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTERFACEDROPTARGET_H__075272E3_A999_11D2_BE7E_0020187099A1__INCLUDED_)
#define AFX_INTERFACEDROPTARGET_H__075272E3_A999_11D2_BE7E_0020187099A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef LEGACYREMOVE
#include "afxole.h"

class CInterfaceDropTarget : public COleDropTarget  
{

public:
	int InsertRow(CString TabSeparated);
	CInterfaceDropTarget();
	virtual ~CInterfaceDropTarget();

protected:
	virtual BOOL OnDrop( CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, INXPoint point );
	virtual DROPEFFECT OnDragOver( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, INXPoint point );

private:
	CString m_csIconType;
	CString m_csBlockName;
};

#endif // !defined(AFX_INTERFACEDROPTARGET_H__075272E3_A999_11D2_BE7E_0020187099A1__INCLUDED_)
#endif
