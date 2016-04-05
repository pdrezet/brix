/** @file LgbUndoTemplateStore.h
 * @author: Matthew Rutherford
 * @version: $Revision: 1480 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */

#pragma once

#include "../common/LucidTypedefs.h"
#include "LgbDeque.h"
#include <algorithm>
#include <deque>

//! Class to store and manage undo / redo options for applications
/*! 
Assume that the undo/redo 'stores' of data (changes) are stored in a file, 1 file for
each user action.

To Use This Class:

For each document/view which is to have an undo/redo capability, provide an instance of
this class.


Initalising the instance.

'.init' the instance with the stem of thestorage-file name  (eg C:\Fred\Projects\TempstoreFolder\StorageFile", or "..\Temp\storeFile, 
and the max number of undos yo wish to provide.

(Re-) setting the instance.

WHEN you just opened a document, but before you made any changes to it, call '.reset'.
this will return a filename, eg C:\Fred\Projects\TempstoreFolder\StorageFile0, (note the '0' appended)
to which you then save a copy of the
unchanged file.


User actions thereafter.

Thereafter, everytime the user performs an action which is 'undo'able, make a call to addAction(...).
This call will return a filename ( C:\Fred\Projects\TempstoreFolder\StorageFile1, ...2, ...3, etc, 
You should immediately save the document that has just had the change performed on it.

Undo-ing
If you wish to undo an action, call undo(...).  This will return the name of the file that must be read-in
to the document to set it to the undo'ne condition.

Redo-ing

Similarly with redo.

Note that the call have arguments for setting menus, logical ones for whether undo / redo should be grayed or enabled,
and prompts o which to set the menu (eg for 'Undo move( 23, 12)' as opposed to just 'undo'

Design Notes.

Because 'undo' storage-file saves are made AFTER each undo-able action, we need a 'reset' function to cause
the initial, unchanged state to be saved.  
Initially, this original state is stored at the front of the buffer.  Its presence means that the number of
undo's is 1 less than the size of the buffer.
If subsequently (as is likely) more actions are pushed onto the stack than it's size allows for,
the 'initial' state of the document will be lost, but nonethless, the 'backstop' state - provivding
something to undo-to, but to which the stack position pointer can't point to, will still be present.
IN Other Words, the minimum value of m_iPresentPos is 1, NOT 0, once the instance i in use.
*/

template < class Store, class Label > class LgbUndoTemplateStore
{

private:

	int m_iPresentPos;		//! The position in the stack which describes the current undo/redo state
	int m_iMaxSize;			//! The max size of the 

	LgbDeque< std::pair< Store, Label > > m_Store;

	void setFlags(
				bool &bEnableUndo,			// Out: flags whether 'undo' menu item should be enabled
				bool &bEnableRedo,			// Out: flags whether 'redo' menu item should be enabled
				Label &csNewUndoPrompt,	// Out: new prompt for the undo menu
				Label &csNewRedoPrompt	// Out: new prompt for the redo menu
				);

	bool hasUndos( );

	bool hasRedos( );

	int size();

public:

	LgbUndoTemplateStore( );

	~LgbUndoTemplateStore(void);

	void test();

	void init( const int &iMaxUndos = 20  );

	void addAction(	
				Label &csAction,		//! In: prompt for what was done in this action
				bool &bEnableUndo,		//! Out: flags whether 'undo' menu item should be enabled
				bool &bEnableRedo,		//! Out: flags whether 'redo' menu item should be enabled
				Label &csNewUndoPrompt, //! Out: new prompt for the undo menu
				Label &csNewRedoPrompt, //! Out: new prompt for the redo menu
				const Store &stateData //! In: data describing state off model
				);

	void  undo(	
				bool &bEnableUndo,		//! Out: flags whether 'undo' menu item should be enabled
				bool &bEnableRedo,		//! Out: flags whether 'redo' menu item should be enabled
				Label &csNewUndoPrompt, //! Out: new prompt for the undo menu
				Label &csNewRedoPrompt, //! Out: new prompt for the redo menu
				Store &stateData
				);

	void redo(	
				bool &bEnableUndo,		//! Out: flags whether 'undo' menu item should be enabled
				bool &bEnableRedo,		//! Out: flags whether 'redo' menu item should be enabled
				Label &csNewUndoPrompt, //! Out: new prompt for the undo menu
				Label &csNewRedoPrompt, //! Out: new prompt for the redo menu
				Store &stateData
				);

	void reset(
				bool &bEnableUndo,			//! Out: flags whether 'undo' menu item should be enabled
				bool &bEnableRedo,			//! Out: flags whether 'redo' menu item should be enabled
				Label &csNewUndoPrompt,	//! Out: new prompt for the undo menu
				Label &csNewRedoPrompt,	//! Out: new prompt for the redo menu
				const Store &stateData
				);

};


template < class Store, class Label >  LgbUndoTemplateStore< Store, Label >::LgbUndoTemplateStore( )
{  
}

template < class Store, class Label >  LgbUndoTemplateStore< Store, Label >::~LgbUndoTemplateStore( )
{ 
}

template < class Store, class Label > void LgbUndoTemplateStore< Store, Label >::init( const int &iMaxUndos )
{  

	m_iMaxSize = iMaxUndos + 1;
	assert( m_iMaxSize > 5);
	m_Store.setMaxSize( m_iMaxSize );

	m_iPresentPos = -1;

}


template < class Store, class Label > void LgbUndoTemplateStore< Store, Label >::reset(
				bool &bEnableUndo,			// Out: flags whether 'undo' menu item should be enabled
				bool &bEnableRedo,			// Out: flags whether 'redo' menu item should be enabled
				Label &csNewUndoPrompt,		// Out: new prompt for the undo menu
				Label &csNewRedoPrompt,		// Out: new prompt for the redo menu
				const Store &stateData		// In: data describing state off model
				)
{

	m_Store.clear();
	m_iPresentPos = 0;

	Label csNowt = "";
	std::pair< Store, CString > pr( stateData, csNowt );
	m_Store.push_back( pr );

	bEnableUndo = false;	
	bEnableRedo = false;

	csNewUndoPrompt = "Undo";
	csNewRedoPrompt = "Redo";

}

template < class Store, class Label > void LgbUndoTemplateStore< Store, Label >::addAction(	
				Label &csAction,	
				bool &bEnableUndo,	
				bool &bEnableRedo,		
				Label &csNewUndoPrompt, 
				Label &csNewRedoPrompt,
				const Store &stateData
				)
{	
	// Check the thing has been init'ed
	assert( m_iPresentPos > -1);

	// 0-length action is allowed/appropriate only for the 1st action stored (in 'init'), 
	// and will cause incorrect graying of menus if used elsewhere, as well
	// as failing to inform the user of what is undo/redo-able in the menus, later.
	assert( csAction.GetLength() > 0 );

	// Pop-off any 'redo's that were later than current pos.
	// There are any to pop only if present pos wasn't at the top.

	if( int iNumToPop =  m_Store.size() - m_iPresentPos -1 )
		m_Store.pop_back( iNumToPop  );

	std::pair< Store, Label > pr( stateData, csAction );
	m_Store.push_back( pr );

	// If the store was already full, we cannot be
	// pointing past the top after latest add.
	m_iPresentPos += m_iPresentPos < (m_iMaxSize-1) ? 1 : 0;

	setFlags( bEnableUndo, bEnableRedo, csNewUndoPrompt, csNewRedoPrompt );

}


template < class Store, class Label > void LgbUndoTemplateStore< Store, Label >::undo(	
				bool &bEnableUndo,		// Out: flags whether 'undo' menu item should be enabled
				bool &bEnableRedo,		// Out: flags whether 'redo' menu item should be enabled
				Label &csNewUndoPrompt, // Out: new prompt for the undo menu
				Label &csNewRedoPrompt, // Out: new prompt for the redo menu
				Store &stateData
				)
{

	// We should never try to 'undo' down to pos 0, as 
	// the 'save file' is saved AFTER an action,
	// so there is no save file to read for the state at pos 0;
	// assert( m_iPresentPos > 1);

	// For testing purposes, stop it going less than 1, rather than assert / blow-up.

	m_iPresentPos -= (m_iPresentPos > 0) ? 1 : 0;

	setFlags( bEnableUndo, bEnableRedo, csNewUndoPrompt, csNewRedoPrompt );

	std::pair< Store, Label > dumPair;
	//Get storage file to do the 'undo'
	dumPair = m_Store.at( m_iPresentPos );

	stateData = dumPair.first;

	return;

}


template < class Store, class Label > void LgbUndoTemplateStore< Store, Label >::redo(	
				bool &bEnableUndo,		// Out: flags whether 'undo' menu item should be enabled
				bool &bEnableRedo,		// Out: flags whether 'redo' menu item should be enabled
				Label &csNewUndoPrompt, // Out: new prompt for the undo menu
				Label &csNewRedoPrompt, // Out: new prompt for the redo menu
				Store &stateData
				)
{

	m_iPresentPos += hasRedos() ? 1 : 0;

	setFlags( bEnableUndo, bEnableRedo, csNewUndoPrompt, csNewRedoPrompt );

	pair< Store, Label > dumPair;

	//Get storage file to do the 'undo'
	dumPair = m_Store.at( m_iPresentPos );
	stateData = dumPair.first;

	return;	

}


template < class Store, class Label > void LgbUndoTemplateStore< Store, Label >::setFlags(
			bool &bEnableUndo,			// Out: flags whether 'undo' menu item should be enabled
			bool &bEnableRedo,			// Out: flags whether 'redo' menu item should be enabled
			Label &csNewUndoPrompt,	// Out: new prompt for the undo menu
			Label &csNewRedoPrompt	// Out: new prompt for the redo menu
			)
{
	pair< Store, Label > dumPair;

	// Undo Prompts:
	if( hasUndos() ){
		dumPair = m_Store.at( m_iPresentPos );
		csNewUndoPrompt = "Undo " + dumPair.second;
	} else {
		csNewUndoPrompt = "Undo";
	}

	// Redo Prompts:
	if( hasRedos( )  ){
		dumPair = m_Store.at( m_iPresentPos +1 );
		csNewRedoPrompt = "Redo " + dumPair.second;
	} else {
		// Not at the top.
		csNewRedoPrompt = "Redo";
	}

	bEnableUndo = hasUndos();	
	bEnableRedo = hasRedos();

}

template < class Store, class Label > bool LgbUndoTemplateStore< Store, Label >::hasUndos( )
{
	return m_iPresentPos > 0;
}

template < class Store, class Label > bool LgbUndoTemplateStore< Store, Label >::hasRedos( )
{
	return m_iPresentPos < ( size()-1 ) ;
}

template < class Store, class Label > int LgbUndoTemplateStore< Store, Label >::size()
{
	return m_Store.size();
}

template < class Store, class Label > void LgbUndoTemplateStore< Store, Label >::test()
{
	CString fileKey;
	bool bUndo, bRedo;
	CString action, undoPrompt, redoPrompt;

	init( "Storage", 5 );
	reset(  bUndo, bRedo, undoPrompt, redoPrompt );

	action = "move 1";
	fileKey = addAction( action, bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	action = "move 2";
	fileKey = addAction( action, bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	action = "move 3";
	fileKey = addAction( action, bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	fileKey = undo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	fileKey = undo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	fileKey = undo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	fileKey = undo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	fileKey = undo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	
	fileKey = redo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	fileKey = redo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	fileKey = redo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	fileKey = redo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	fileKey = redo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	action = "move 4";
	fileKey = addAction( action, bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	action = "move 5";
	fileKey = addAction( action, bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	action = "move 6";
	fileKey = addAction( action, bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	fileKey = undo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	fileKey = undo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	fileKey = undo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	fileKey = undo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	fileKey = undo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	fileKey = undo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	fileKey = undo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	
	fileKey = redo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	fileKey = redo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	fileKey = redo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	fileKey = redo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	fileKey = redo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;
		
	fileKey = redo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

	fileKey = redo( bUndo, bRedo, undoPrompt, redoPrompt );
	cout << "undo/redo: " << bUndo << "/" << bRedo << ",  Undo/Redo Prompts: " << undoPrompt << ", " << redoPrompt;

}

