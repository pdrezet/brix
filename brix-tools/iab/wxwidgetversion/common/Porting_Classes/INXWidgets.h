#ifndef __INXWIDGETS_H
#define __INXWIDGETS_H

//#include "condat.h"

#include "Porting_Classes/INXString.h"
#include "Porting_Classes/INXTree.h"
#include "Porting_Classes/INXObjList.h"
/* 
     Porting file to map onto platform widget library
*/


// todo just to get through the day!
#define INX_STUBBED
#ifdef INX_STUBBED

class INX_Edit {
public:
	void SetFocus() {}

};

class INX_Static {
public:
	void SetFocus() {}
};

class INX_ProjectTree {
public :
	INXString GetDEPPath(INXTREEITEM hItem) {
		return "./";
	}
	INXString GetItemText(INXTREEITEM hItem) {
		return "./";
	}

	INXTREEITEM GetUserDefChildItem(void* pBlob, INXTREEITEM hItem) {
		return NULL;
	}

	INXTREEITEM hSelItem;
};

class INX_ProjectBar {
public:
	INX_ProjectTree m_cProjTree;
};

class INX_MainFrame {
public:
	INX_ProjectBar m_wndProjectBar;
	static INX_MainFrame* INX_GetAppMainWindow() {
		return NULL;
	}
};

class INX_Document {
public:
	
	static INX_Document* OpenDocumentFile(INXString FILE) {
		return NULL;
	}
	INXPOSITION GetFirstViewPosition() {
		return NULL;
	}
	INXPOSITION GetNextView(INXPOSITION pos) {
		return NULL;
	}
};


void INX_MessageBox(void * parent, INXString dummy, INXString  message);
void INX_MessageBox(INXString  message);

#endif

#endif