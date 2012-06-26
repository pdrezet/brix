/** @file DrawGUIView.h
 * Represent the MFC 'View' class for editing layouts in LGB.
 * Represents a re-write performed during June- July 2007.
 * Code is clearer, but doesn't properly (at all!) respect the view/model/controlller paradigm
 * ie there is still too much document data in the view rather than the document.
 * @author: Matthew Rutherford
 * @version: $Revision: 4318 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */

/** Selection Rules.

If user clicks on something
  if ctrl key is down
    toggle selection of clicked item
  else
    de-select everything except clicked item
  endif
else if user clicks on nothing
  if ctrl key is down
    do nothing
  else
    de-select everything
  endif
endif

1. Changes selection display on button up, not button down.


*/
#pragma once

#include "stdafx.h"
#include "DrawGUIDoc.h"
#include "LgbImageIcon.h"
#include "LgbRect.h"
#include "LgbDrawableBag.h"
#include "LgbZOrderDlogBar.h"
#include "LgbColorsDef.h"
#include "../common/LgbIconDataStrucs.h"
#include "LgbUndoTemplateStore.h"
#include "DrawGUIViewStore.h"
#include <list>

using namespace std;


//! The MFC 'view' class for LGB
class CDrawGUIView : public CView
{

friend class CDrawGUIViewStore;

public:
	LgbUndoTemplateStore< CDrawGUIViewStore, CString > m_cLgbUndoStore;
	void resetUndoStore();
	void saveUndoAction( CString &csDesriptionOfAction );
	void saveUndoAction( char *pszDesriptionOfAction );

private:
	void transferToTarget( const bool &bUpdatedOnly );

	bool m_bEnableRedo;
	bool m_bEnableUndo;

	CString m_csUndoPrompt;
	CString m_csRedoPrompt;

	// Record state of initial left-button click
	bool m_bCtrlKeyDown;
	bool m_bClickedOnSomething; // Did user click on an icon
	bool m_bThingWasAlreadySelected; // ie was the icon cclicked-upon already selected.

	enum MouseActionEnum { k_SelectionsCleared, k_SelectionToggled=100, k_SelectionSingle };

	std::vector< MouseActionEnum > m_vMouseActions;

	CString getBestPrompt( const std::vector< MouseActionEnum > vMouseActions );
	bool isFocusEventStarted;
	bool isFocusEventFinished;

protected: // create from serialization only
	CDrawGUIView();
	CRect		InvalidRect;
	DECLARE_DYNCREATE(CDrawGUIView)

// Attributes
public:
	CDrawGUIDoc* GetDocument();
	static CDrawGUIView * GetView();

	enum SelnModeEnum { k_SelModeNull, k_SelModeEdge=100, k_SelModeIcon };

// Operations
public:
    //! The one and only defining store and manager for all the drawables (icons) currently loaded from sodl.
	/*! Provides an interface for the LGB application to process (eg left-align selected icons), manage ( eg setting state of all
	icons to be 'deselected') and 'draw' all the drawables.  There is and must be only 1 of these for all drawables */
	LgbDrawableBag m_cDrawableBag; 

    //! Stores which icons are selected ***in the order in which they are selected*** - hence allows identification of 'master' icon.
	/*! The first item of a selection is pushed into this sclasses list, and becomes the master icon.  That is - the master
	icons 'left edge' would be used to align any other selected icon's left edges.  If the 1st 'master' icon is deselected,
	then the instance allows identification of the 2nd-selected icon as the new master.
	The instance uses only a subset of functionality required for m_cDrawableBag.  Therefore m_cSelectionBag should really
	be an instance of a superclass of LgbDrawableBag ( which hasn't yet been coded... ) */
	LgbDrawableBag m_cSelectionBag;

    //! For convenience, a vector of icons outlines - used when the user is dragging-around a selection of icons, before she releases mouse button
	std::vector<LgbRect> m_vSelRects;

	//! The document pertaining to this view
	CDrawGUIDoc* pDoc;

	//! The point the user lat left-clicked upon
	CPoint m_cInitialClickPt;

	//! The point the user had moved the mouse to at the last 'mouse move' event, previous to the current event.
	CPoint m_cPreviousPt;

	//! Describes what the user left-clicked upon- ie no icon / icon's centre / icon's leftEdge / etc
	LgbRectSelTypeEnum m_eSelnMode;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawGUIView)

public:
	//! overridden to draw this view
	virtual void OnDraw(CDC* pDC);  

	//irtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	//! overridden to set child titles
	virtual void OnInitialUpdate();

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	//! Records if the view has ever had focus.
	/*! The 1st time a view gets focused, set the z-clip to max, so the user can see
	everything.
	Afterwards, the user will have set the zclip herself, and the view will
	have been updated to whatever this value was.
	*/
	bool m_bZSliderNeverMoved;
/*
	//! The z-lean and z-clipping dialog shared between views.
	/*! 
	 The business req is that there is only one dialog for the user to manage, however many views/documents are open.
	 NB.  This member was tried as non-static, the idea being that the
	 z-order dlog for each view was popped-up / down as the view
	 concerned lost / gained focus.  However, which eveent to use to pop up/down the dialog for a given view.
	 'OnActivateFrame' was called too often, and using View::OnKillFocus / OnSetFocus 
	 failed because the view concerned DID lose focus even when you clicked on its zdlog.  Hence the user was
	 put into a circle where clicking the z dlog woul cause the respective z dlogs to be 'popped up' and hence need to be 
	 re focused upon.
	 */
	 LgbZOrderDlogBar *m_pLgbZOrderDlogBar;

	//}}AFX_VIRTUAL

// Implementation
public:

	//! Sets up z-dialog and initialises various members
	void init();

	void setStatusBarText(CString csText);

	//! reads in icons from a file
	/*!
      \param Info name of file to be read
    */
	void LoadGUIInfFromGuiFile(CString Info);

	//! saves icons to file
	/*!
      \param Info name of file to be (over) written
    */
	void SaveGUIInf(CString filnam);

	void UpdateProjectMetaData();

	//int DrawAll();

	//! finds the highest-z icon under 'point'
	/*!
      \param point point where user clicked
      \param pIcon pointer to icon (may be NULL)
      \return enum describing no icon there, centre/left edge/ right edge etc at point
    */
	LgbRectSelTypeEnum getSelectedIcon( 
		const CPoint &point, 
		LgbDrawable *  &pIcon ) ;

    //! Adds a text box icon of default colours (actually to the the drawable bag )
    /*!
      \param type The type of the new icon (from LAB).
      \param tag  The tag of the new icon (from LAB).
      \param rect The outline border of the new icon.
      \param zpos The z-order of the icon (highest nearest user).
    */

//	void AddTextboxIcon(
//					const CString	&type,	
//					const CString	&tag,
//					const CRect		&rect,
//					const int		&zPos,
//					const int		&alpha
//				);

    //! Adds a text box icon of given colours to the the drawable bag
    /*!
      \param type The type of the new icon (from LAB).
      \param tag  The tag of the new icon (from LAB).
      \param rect The outline border of the new icon.
      \param zpos The z-order of the icon (highest nearest user).
      \param colors The foreground and background RGB values of the new icon.
    */
	void AddTextboxIcon(
					const CString		&type,						
					const CString		&tag,
					const CRect			&rect,
					const int			&zPos,
					//const int			&alpha,
					const LgbColorsDef	&colors

				);

	void AddTextboxIcon( const LgbTextIconEssentialData_t &textIcon );

	void AddTextboxIcon( const LgbTextIcon &textIcon );

	void AddTextboxIcon(const LgbTextIconEssentialData_t &textIcon, const vector<LgbTextStyleEssentialData_t> vTextStyles);



    //! Adds a text box icon of given colours to the the drawable bag
    /*!
      \param type The type of the new icon (from LAB).
      \param tag  The tag of the new icon (from LAB).
      \param rect The outline border of the new icon.
      \param zpos The z-order of the icon (highest nearest user).
      \param colors The foreground and background RGB values of the new icon.
    */
	void AddPatchIcon(
					const CString		&type,						
					const CString		&tag,
					const CRect			&rect,
					const int			&zPos,
					//const int			&alpha,
					const LgbColorsDef	&colors

				);

	void AddPatchIcon( const LgbPatchIconEssentialData_t &patchIcon );

	void AddPatchIcon( const LgbPatchIcon &patchIcon );




    //! Adds a bitmap icon of given colours to the the drawable bag.
    /*!
      \param type The type of the new icon (from LAB).
      \param tag  The tag of the new icon (from LAB).
	*/
	void AddBitmapIcon(
					const CString		&type,				
					const CString		&tag,
					const CRect			&rect,
					const int			&zPos,
					const int			&alpha,
					const CString		&bitmapFileName,
					const int			&lockAspect
				);

	void AddBitmapIcon( const LgbImageIcon &imageIcon );

	void AddBitmapIcon( const LgbImageIconEssentialData_t &imageIcon );

	virtual ~CDrawGUIView();

    //! Empties the drawable bag and reinitialises the view
	void ResetAll();


    //! Re-loads the drawables against the SODL file.
    /*!
      NB.  LAB may have re-written the sodl file since the last time LGB processed it.
	  Therefore this routine:
	  Adds new icons (if any) in default positions,
	  Removes icons no longer in sodl,
	  Doesn't alter icons that are still there from last load ( so the user doesn't lose all his work!).
    */
	void LoadSODL();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawGUIView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point); 	

	afx_msg void OnLOADAFXSODL();
//	afx_msg void OnFtpOptions();
	afx_msg void OnIconProperties();
	afx_msg void OnFtpGui();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//public:
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnActivateFrame(UINT nState, CFrameWnd* pDeactivateFrame);

protected:
	virtual void PostNcDestroy();

    //! The number of icons currently selected.
	short m_iNumberIconsCurrentlySelected;

	//! Flag that indicates whether mouse left-button is down.
	/*! Useful to tell when the user is dragging the mouse rather
	than just moving it.  NB.  Although Windows supplies flags ( eg on mouseMove events )
	that indicate whether a button is down, these are not as reliable
	as maintaining your own flag, because sometime a few mouseMove events keep
	coming for a bit *after* the user has released the button - even if he 
	hasn't moved mouse after button-up
	*/
	bool m_bMouseIsDown;

	/*! If true, show icons' tags */
	bool m_bShowTags;

	//! Z-lean/clip dialog max/min lean values.
	/*! ( 1-way because they go to the dialog from the view, no back again ) */
	LgbZLeanBounds_t m_cZDatMaxMins;

	/*! Z-lean/clip dialog slider values */
	/*! ( 2-way because they go to the dialog from the view, and back again, so that the view can re-set the z dlog
	next time the view is focused ) */
	Lgb_UserZVals_t m_cZDatVals;

public:
	afx_msg void OnAlignmentLeftEdges(); //!< Align left edges of selections with that of master icon.
	afx_msg void OnAlignmentRightEdges(); //!< Align right edges of selections with that of master icon.
	afx_msg void OnAlignmentLeftRightCentres(); //!< Align horizontally centres of selections with that of master icon.
	afx_msg void OnAlignmentTopEdges(); //!< Align top edges of selections with that of master icon.
	afx_msg void OnAlignmentBottomEdges(); //!< Align bottom edges of selections with that of master icon.
	afx_msg void OnAlignmentTopBottomCentres(); //!< Align vertically centres of selections with that of master icon.
	afx_msg void OnResizeWidth(); //!< set width of selections to that of master icon.
	afx_msg void OnResizeHeight(); //!< set vertical extent of selections to that of master icon.


protected:
	//LgbDrawable *m_pIconLastSelected;

	/*! Draw the outline of selected icons - as they are dragged */
	void drawGhostRectangles(const LgbRect & rect1, const LgbRect & rect2, CClientDC *pDC ) const;
	void CDrawGUIView::maintainAspectRatioOnResize(const LgbRectSelTypeEnum &eSelnMode, const CPoint point, float dHtoW, long &newX, long &newY);

public:

	afx_msg void OnIconBringTofront(); //!< move selections so that rearmost seln is in front of frontmost non-selected

	afx_msg void OnIconSendToRear(); //!< move selections so that frontmost seln is behind rearmost non-selected

	afx_msg void OnIconMoveForward(); //!< Move selections forward by 1

	afx_msg void OnIconMoveBackward(); //!< Move selections rearward by 1

	afx_msg void OnIconEqualiseToFrontmost(); //!< move selections to be equal in Z to global frontmost

	afx_msg void OnIconEqualiseToRearmost(); //!<  move selections to be equal in Z to global rearmost

	afx_msg void OnOptionsSelectAllWidgets(); //!< Select all icons

	afx_msg void OnOptionsDisplayWidgetLabels(); //!< turn on dissplay of icon labels


	void setUpperZActiveLevel(const int & val, const bool bSave = false ); //!< set highest z-level to 'vaal'

	void setZLeanLevel(const int & val, const bool bSave = false ); //!< set amount of pseudo 3D lean.

	void refreshZDialog(const bool &setClipZToMax = false); //!< Update the z lean/clip dialog


protected:
//	void setZDlogShowing(bool shown);
//	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);

public:
	afx_msg void OnZRenumberConsectively(); //!< renumber icons consecutively from 0
	//! compress gaps in z-numbering that are more than 2 to equal 2
	/*! Eg 1,2,3, 5,5, 11,11,11, 18, 101, 102,102,102 -> 1,2,3, 5,5, 7,7,7, 9, 11, 12,12,12 */
	afx_msg void OnZRenumberKeepGaps(); 
	afx_msg void OnSelectionSelectAllBitmaps();
	afx_msg void OnSelectionSelectAllTextBoxes();
	afx_msg void OnUpdateOptionsDisplayWidgetLabels(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAlignment(CCmdUI *pCmdUI);
	afx_msg void OnViewZdialog();
	afx_msg void OnUpdateViewZdialog(CCmdUI *pCmdUI);
	static int c_iInstanceCount;
	afx_msg void OnOptionsNativeviewbground();
	afx_msg void OnUpdateOptionsNativeviewbground(CCmdUI *pCmdUI);
	bool m_bNativeBackgroundColors;
	bool m_bWarningBackgroundColors; // flag to show warning colour for background
	bool m_bIsDirtySODL; // flag to warn of dirty SODL
	COLORREF m_cStdNativeBackgroundColors;
	COLORREF m_cStdWarningBackgroundColors;
	COLORREF m_cStdEditingBackgroundColors;
	void BlitCompo(void);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnIconSetfullyopaque();
	afx_msg void OnIconDecrementOpacity();
	afx_msg void OnLgbShowTransferManager();
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);
	afx_msg void OnLgbTransferAll();
	afx_msg void OnLgbSendDataChanged();
	afx_msg void OnUpdateLgbTransferAll(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLgbTransferChanged(CCmdUI *pCmdUI);
	void copyDrawables( std::vector< LgbDrawable *> &rCopiedDrawablePtrs,
						std::vector< LgbDrawable *> &rCopiedMasters ) const;

	void loadDrawables( const std::vector< LgbDrawable *> &rCopiedDrawablePtrs,
						const std::vector< LgbDrawable *> &rCopiedMasters );
	afx_msg void OnSelectionSelectAllPatches();

	afx_msg void OnEHSStartRestart();
	afx_msg void OnEHSStop();
//	afx_msg void OnEHSUpdate();
	afx_msg void OnEHSTopmost();
	afx_msg void OnEHSBottommost();
	afx_msg void OnEHSNormalZOrder();
	afx_msg void OnEHSInitParams();
	afx_msg void OnEHSManageLocally();
	afx_msg void OnEHSManageRemotely();
	afx_msg void OnSelChangeEHSHostCombo();
	afx_msg void OnUpdateEHSManageLocally(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEHSManageRemotely(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEHSStartRestart(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEHSStop(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEHSInitParams(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in DrawGUIView.cpp
inline CDrawGUIDoc* CDrawGUIView::GetDocument()
   { return (CDrawGUIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

