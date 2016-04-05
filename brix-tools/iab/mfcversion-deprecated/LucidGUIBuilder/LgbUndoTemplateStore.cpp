
#include "stdafx.h"
#include "LgbUndoTemplateStore.h"
#include "../common/GlobalFuncs_2.h"
#include "../LucidApplicationBuilder/FileOperations.h"
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;


template < class Store > LgbUndoTemplateStore::LgbUndoTemplateStore( ):
m_iStorageFileKey(-100000)
{  
}

LgbUndoTemplateStore::~LgbUndoTemplateStore( )
{ 
}

void template < class Store > LgbUndoTemplateStore::init( const CString &csFileStem, const int &iMaxUndos )
{  
	// Check not already init'ed
	assert( m_iStorageFileKey < 0);

	m_iMaxSize = iMaxUndos + 1;
	assert( m_iMaxSize > 5);
	m_i_csStore.setMaxSize( m_iMaxSize );

	m_iPresentPos = -1;

}


CString LgbUndoTemplateStore::reset(	
				bool &bEnableUndo,			// Out: flags whether 'undo' menu item should be enabled
				bool &bEnableRedo,			// Out: flags whether 'redo' menu item should be enabled
				CString &csNewUndoPrompt,	// Out: new prompt for the undo menu
				CString &csNewRedoPrompt	// Out: new prompt for the redo menu
				)
{

	// Check IS already init'ed
	assert( m_iStorageFileKey >= 0);

	m_i_csStore.clear();
	m_iPresentPos = 0;

	m_iStorageFileKey++;
	CString csNowt = "";

	std::pair< int, CString > pr( m_iStorageFileKey, csNowt );
	m_i_csStore.push_back( pr );

	bEnableUndo = false;	
	bEnableRedo = false;

	csNewUndoPrompt = "Undo";
	csNewRedoPrompt = "Redo";

	return m_csFileStem + intToString(m_iStorageFileKey);
}

void LgbUndoTemplateStore::addAction(	
				CString &csAction,	
				bool &bEnableUndo,	
				bool &bEnableRedo,		
				CString &csNewUndoPrompt, 
				CString &csNewRedoPrompt 
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

	if( int iNumToPop =  m_i_csStore.size() - m_iPresentPos -1 )
		m_i_csStore.pop_back( iNumToPop  );


	std::pair< int, CString > pr( m_iStorageFileKey, csAction );
	m_i_csStore.push_back( pr );

	// If the store was already full, we cannot be
	// pointing past the top after latest add.
	m_iPresentPos += m_iPresentPos < (m_iMaxSize-1) ? 1 : 0;

	setFlags( bEnableUndo, bEnableRedo, csNewUndoPrompt, csNewRedoPrompt );

}


CString LgbUndoTemplateStore::undo(	
				bool &bEnableUndo,		// Out: flags whether 'undo' menu item should be enabled
				bool &bEnableRedo,		// Out: flags whether 'redo' menu item should be enabled
				CString &csNewUndoPrompt, // Out: new prompt for the undo menu
				CString &csNewRedoPrompt // Out: new prompt for the redo menu
				)
{

	// We should never try to 'undo' down to pos 0, as 
	// the 'save file' is saved AFTER an action,
	// so there is no save file to read for the state at pos 0;
	//assert( m_iPresentPos > 1);

	// For testing purposes, stop it going less than 1, rather than assert / blow-up
	m_iPresentPos -= (m_iPresentPos > 0) ? 1 : 0;

	setFlags( bEnableUndo, bEnableRedo, csNewUndoPrompt, csNewRedoPrompt );

	pair< int, CString > dumPair;
	//Get storage file to do the 'undo'
	dumPair = m_i_csStore.at( m_iPresentPos );
	return m_csFileStem + intToString(dumPair.first);
}


CString LgbUndoTemplateStore::redo(	
				bool &bEnableUndo,		// Out: flags whether 'undo' menu item should be enabled
				bool &bEnableRedo,		// Out: flags whether 'redo' menu item should be enabled
				CString &csNewUndoPrompt, // Out: new prompt for the undo menu
				CString &csNewRedoPrompt // Out: new prompt for the redo menu
				)
{

	m_iPresentPos += hasRedos() ? 1 : 0;

	setFlags( bEnableUndo, bEnableRedo, csNewUndoPrompt, csNewRedoPrompt );

	pair< int, CString > dumPair;
	//Get storage file to do the 'undo'
	dumPair = m_i_csStore.at( m_iPresentPos );
	return m_csFileStem + intToString(dumPair.first);	

}

void LgbUndoTemplateStore::setFlags(
			bool &bEnableUndo,			// Out: flags whether 'undo' menu item should be enabled
			bool &bEnableRedo,			// Out: flags whether 'redo' menu item should be enabled
			CString &csNewUndoPrompt,	// Out: new prompt for the undo menu
			CString &csNewRedoPrompt	// Out: new prompt for the redo menu
			)
{
	pair< int, CString > dumPair;

	// Undo Prompts:
	if( hasUndos() ){
		dumPair = m_i_csStore.at( m_iPresentPos );
		csNewUndoPrompt = "Undo " + dumPair.second;
	} else {
		csNewUndoPrompt = "Undo";
	}

	// Redo Prompts:
	if( hasRedos( )  ){
		dumPair = m_i_csStore.at( m_iPresentPos +1 );
		csNewRedoPrompt = "Redo " + dumPair.second;
	} else {
		// Not at the top.
		csNewRedoPrompt = "Redo";
	}

	bEnableUndo = hasUndos();	
	bEnableRedo = hasRedos();

}

inline bool LgbUndoTemplateStore::hasUndos( )
{
	return m_iPresentPos > 0;
}

inline bool LgbUndoTemplateStore::hasRedos( )
{
	return m_iPresentPos < ( size()-1 ) ;
}

inline int LgbUndoTemplateStore::size()
{
	return m_i_csStore.size();
}

void LgbUndoTemplateStore::test()
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