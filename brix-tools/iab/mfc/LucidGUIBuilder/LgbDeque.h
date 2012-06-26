/** @file LgbDeque.h
 * @author: Matthew Rutherford
 * @version: $Revision: 871 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */

#pragma once

#include <deque>

//! A stack of settable max size.  Items are popped before anything is pushed, if size has been reached
/*! 
A utility class, based on the STL 'deque' (double-ended queue).
If the store is filled to capacity, then, an item will be popped off the back
before anything is pushed onto the front, and vice-versa.
*/
template < class T > class LgbDeque: public std::deque< T >
{
public:
	LgbDeque(void) //! Constructor
	{  };

	~LgbDeque(void)//! Destructor
	{   };

	void push_back( const T &val )
	{
		if( size() == m_iMaxContents){
			pop_front() ;
		}
		deque::push_back(val );
	}

	void push_front( const T &val )
	{
		if( size() == m_iMaxContents){
			pop_back();
		}
		deque::push_front(val );
	}

	void pop_front()
	{
		std::deque<T>::pop_front( );
	}

	void pop_front( const int &nToPop )
	{
		for( size_t i=0; i< (size_t) nToPop;i++ )
			pop_front( );
	}

	void pop_back()
	{
		std::deque<T>::pop_back( );
	}

	void pop_back( const int &nToPop )
	{
		for( size_t i=0; i< (size_t) nToPop;i++ )
			pop_back( );
	}

	inline void setMaxSize( const int &val )
	{ m_iMaxContents = val; }


private:
	size_t m_iMaxContents; //! The maximum size of the container

};
