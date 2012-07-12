#pragma once
#include <wx/string.h>
#include <algorithm>
using namespace std;

class INXString: public wxString{

public:
	// constructors
	INXString(): wxString(){}
	INXString(const wxString &str): wxString(str){}
	INXString(const char *s): wxString(s){}
	INXString(const char c, unsigned int n = 1): wxString(c, n){}
	// The String as an Array 
	int GetLength(){
		return Len();	
	};
//	bool IsEmpty(){} // is inherited
//	void Empty(){} // is inherited
	char GetAt(unsigned int index){
		GetChar(index);
	};
	void SetAt(unsigned int index, char c){
		SetChar(index, c);
	};
	// Comparision
	int CompareNoCase(const char *s){ // case insensetive
		return  CmpNoCase(s);
	};
	// Extraction 

	INXString SpanExcluding(const wxString &str){ /*@todo SpanExcluding uncompleted */
		//return Prepend(str);
	};
	// Other Conversions 
//	void MakeUpper(){} inherits from parent
//	void MakeLower(){} inherits from parent
	void MakeReverse(){
		reverse(begin(), end());
	};
/*	void Format(char *s, ... ){} use Printf(char *s, ...) instead 
	that is inherited from parent */
	void TrimLeft(){
		 Trim(false);
	};
	void TrimRight(){
		 Trim(true);
	};
	// Searching 
//	int Find(char c){}; inherited from parent class
//	int Find(char *s){}; inherited from parent
	int Find(char c, int nStart){
		return (int) find(c, nStart);
	};
	int Find(char *s, int nStart){
		return (int) find(s, nStart);
	};
	int ReverseFind(char c){
		return (int) find_last_of(c, size() - 1);		
	};
	int FindOneOf(char *s){
		return (int) find_first_of(s); 
	};
	//	Buffer Access 
	char* GetBuffer(const int nMinBufLength){
		return GetWriteBuf(nMinBufLength);
	};
	void ReleaseBuffer( int nNewLength = -1 ){
		UngetWriteBuf(nNewLength);
	};
};
