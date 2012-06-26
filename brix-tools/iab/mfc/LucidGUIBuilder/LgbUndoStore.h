/** @file LgbUndoStore.h
 * @author: Matthew Rutherford
 * @version: $Revision: 776 $
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
class LgbUndoStore
{

private:

	int m_iPresentPos;		//! The position in the stack which describes the current undo/redo state
	CString m_csFileStem;	//! The path to a storage file, once a unique integer has been appended
	int m_iMaxSize;			//! The max size of the 
	int m_iStorageFileKey;


	LgbDeque<IntCStringPair_t> m_i_csStore;

	void setFlags(
				bool &bEnableUndo,			// Out: flags whether 'undo' menu item should be enabled
				bool &bEnableRedo,			// Out: flags whether 'redo' menu item should be enabled
				CString &csNewUndoPrompt,	// Out: new prompt for the undo menu
				CString &csNewRedoPrompt	// Out: new prompt for the redo menu
				);

	bool hasUndos( );

	bool hasRedos( );

	int size();

public:

	LgbUndoStore( );

	~LgbUndoStore(void);

	void test();

	void init( const CString &csFileStem, const int &iMaxUndos = 20  );

	CString addAction(	
				CString &csAction,		//! In: prompt for what was done in this action
				bool &bEnableUndo,		//! Out: flags whether 'undo' menu item should be enabled
				bool &bEnableRedo,		//! Out: flags whether 'redo' menu item should be enabled
				CString &csNewUndoPrompt, //! Out: new prompt for the undo menu
				CString &csNewRedoPrompt //! Out: new prompt for the redo menu
				);

	CString undo(	
				bool &bEnableUndo,		//! Out: flags whether 'undo' menu item should be enabled
				bool &bEnableRedo,		//! Out: flags whether 'redo' menu item should be enabled
				CString &csNewUndoPrompt, //! Out: new prompt for the undo menu
				CString &csNewRedoPrompt //! Out: new prompt for the redo menu
				);

	CString redo(	
				bool &bEnableUndo,		//! Out: flags whether 'undo' menu item should be enabled
				bool &bEnableRedo,		//! Out: flags whether 'redo' menu item should be enabled
				CString &csNewUndoPrompt, //! Out: new prompt for the undo menu
				CString &csNewRedoPrompt //! Out: new prompt for the redo menu
				);

	CString reset(					
				bool &bEnableUndo,			//! Out: flags whether 'undo' menu item should be enabled
				bool &bEnableRedo,			//! Out: flags whether 'redo' menu item should be enabled
				CString &csNewUndoPrompt,	//! Out: new prompt for the undo menu
				CString &csNewRedoPrompt	//! Out: new prompt for the redo menu
				);
};

