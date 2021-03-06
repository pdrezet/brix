#ifndef _INXSTRING_H
#define _INXSTRING_H



#include <wx/string.h>
#include <algorithm>
using namespace std;

// some temporary porting for gcc
#define strcpy_s(dst, len, src ) strncpy(dst, src, len )
#define strtok_s(str, token, a) strtok(str, token) // todo not so safe - use C11 version !!

class INXString: public wxString{

public:
	operator char*(){
#ifdef __INX_WXWIDGETS2
		return (char *)c_str();
#else
		return (char *)c_str().AsChar();
#endif

	} 
	/*
	operator char(){
		char * chars = (char *)c_str();
		return (char)chars[0];
	}*/
public:
	// constructors
	INXString(): wxString(){
	};
	INXString(const wxString &str):wxString(str){
	};

	INXString(const char *s): wxString((const unsigned char *)s){
	};
	//copy constructor
	INXString(const char &c){
		append(c);
	};

	void AppendChar(char c){
		Append((wxChar)c);
	};
	void Delete(unsigned int _start, unsigned int _end){
		erase(_start,_end);
	};
	int GetLength() const{
		return (int)Len();	
	};
//	bool IsEmpty(){} // is inherited
//	void Empty(){} // is inherited
	char GetAt(unsigned int index) const{
		return GetChar(index);
	};
	void SetAt(unsigned int index, char c){
		SetChar(index, c);
	};
	// Comparision
	int CompareNoCase(const char *s){ // case insensetive
		return  CmpNoCase(s);
	};
	// Other Conversions 
//	void MakeUpper(){} inherits from parent
//	void MakeLower(){} inherits from parent
	void MakeReverse(){
		reverse(begin(), end());
	};
/*	void Format(char *s, ... ){} use Printf(char *s, ...) instead 
	that is inherited from parent */

	INXString TrimLeft(){
		 Trim(false);
#ifdef __INX_WXWIDGETS2
		return (INXString)c_str();
#else
		return (INXString)c_str().AsChar();
#endif
	};
	INXString TrimRight(){
		Trim(true);
#ifdef __INX_WXWIDGETS2
		return (INXString)c_str();
#else
		return (INXString)c_str().AsChar();
#endif
	};
	// Searching 
	int Find(const unsigned char c){
		return (int)wxString::Find((wxChar)c);
	}; 
	int Find(const char c){
		return (int)wxString::Find((wxChar)c); 
	}; 
	int Find(const char *s){
		return (int)wxString::Find((wxChar *)(char *)s);
	};
	int Finds( const char* s, int nStart)const {
#ifdef __INX_WXWIDGETS2
		return (int)wxStringBase::find((wxChar *)s, nStart);	
#else
		return (int)find((wxChar *)s, nStart);	
#endif
	};
/*	int Find(INXString str){
		return (int)wxString::Find((wxChar *)(char *)str);
	};
	int Find(INXString str, int nStart){
		return (int)find((wxChar *)(char *)str, nStart);
	};*/
	int Find(char c, int nStart){
		return (int)find(c, nStart);
	};
	int ReverseFind(char c){
		return (int) find_last_of(c, size() - 1);		
	};
	int FindOneOf(char *s){
		return (int) find_first_of(s); 
	};
	//	Buffer Access 
	char* GetBuffer(const int nMinBufLength){
#ifdef __INX_WXWIDGETS2
		return wxString::GetWriteBuf(nMinBufLength);
#else
		return wxStringBuffer((wxString&)(*this),nMinBufLength);
#endif
	};
	void ReleaseBuffer(int nNewLength){
#ifdef __INX_WXWIDGETS2
		UngetWriteBuf(nNewLength);
#else 
// do nothing - the wxStringBuffer function doesn't need an unget
#endif 	
	};
	void SetLength(int _length){
		resize(_length);
	};
	int StringLength(const char *s){
		if(s == NULL){
			 return(0);
		}return(int(strlen(s)));
	};
	/* @todo using mfc CString to creatre the method 
	 see http://docs.wxwidgets.org/3.1.0/classwx_string_tokenizer.html */
	INXString Tokenize(char* str, int pos){
		//CString _str;
		//_str = _str.Tokenize(str, pos);
		return "";
	};
	// Extraction 

	INXString SpanExcluding(const char* str){
		//CString _str = c_str();
		//_str = _str.SpanExcluding(str);
		return "";
	};
};
#endif
