/** @file IconSelection.h
 * A template class into which icons of a given type can be loaded, which also provides that
 * field values can be scanned to determine if all selections have common value for a given
 * field.
 * @author: Matthew Rutherford
 * @version: $Revision: 577 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */
#pragma once
#include <cassert>
#include <vector>

using namespace std;

//!<  A template class into which icons of a given type can be loaded prior to scanning for properties dlog initialisation.
/*!
The class provides a holder for ptrs of type T, as well as a method, 'procesEquality'.
procesEquality relies on the type T having a method 'scanFieldEquality(..), and also that T has an inner class
'Scan'.
The 'Scan' inner class provides boolean fields for the values of the outer class, such as whether
top, left, right border positions etc for icons
assessed so far have all had the same values for their respective top, left, right border positions etc.
'scanFieldEquality' has arguments of 'scan' for the cumulative comparisons made so far, as well as the next icon in the holder, so that 
the whole contets can be scanned/ compared to see whether any fileds have values common to all icons.
The classes that LGB provides, that meet these criteria and for which IconSelection is designed to be instantiated for,
derive from LgbDrawable.
*/
template <class T> class IconSelection
{

public:

	IconSelection(void){ };	//!< Std constructor
	~IconSelection(void){ };	//!< Std destructor	

	void push_back( T *item ); //!< Loads ptr to a selected icon

	T * getItem(const size_t &i); //!< returns ptr to the i'th item

	size_t size(); //!< Returns number of ptrs currently held

	void clear(); //!< Clears all ptrs

	std::vector< T * > m_vContents; //!< Holder for the contents

	//! Method which scans contents, assessing whether each field of a given type share a common value 
	typename T::Scan processEquality()
	{

		
		T::Scan scan; //!< The summary of field analysis to be returned.

		scan.init(); // Set all commonalities to 'true'

		if(m_vContents.size()<2){

			// If only one ptr contained, there can be no difference between fields
			return scan;

		}else{

			bool keepGoing = true;
			size_t i=0;

			while(keepGoing)
			{
				// Have we worked through the vector?
				// We work through comparing prsent ptr to next, so last call is to penultimate 
				if( i==m_vContents.size()-2) keepGoing = false;

				// Keep sending the old scan as aa param, and getting back the updated scan. 
				scan = m_vContents[i]->scanFieldEquality( m_vContents[i+1], scan );

				// If we know that ALL the fields have different values 
				// between member of the
				// vector, we needn't continue
				if(scan.allScanFieldsFalse()) keepGoing = false;
				i++;
				
			} // for(int i=0;i<m_vContents.size();i++)

		}

		return scan;
	}
};



template <class T> void IconSelection<T>::push_back( T *item)
{
	m_vContents.push_back(item);
}

template <class T> void IconSelection<T>::clear()
{
	m_vContents.clear();
}

template <class T> size_t IconSelection<T>::size()
{
	return m_vContents.size();
}

template <class T> T * IconSelection<T>::getItem(const size_t &i)
{
	assert( i < size() );
	return m_vContents[i];
}
