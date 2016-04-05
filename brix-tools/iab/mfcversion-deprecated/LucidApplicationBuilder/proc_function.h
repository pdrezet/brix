// proc_function.h: interface for the proc_function class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROC_FUNCTION_H__55451EA2_F88D_11D8_A9B1_00055DD37FD7__INCLUDED_)
#define AFX_PROC_FUNCTION_H__55451EA2_F88D_11D8_A9B1_00055DD37FD7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <fstream>
using namespace std;
#include <afxtempl.h>

/*
This is the information for a function:
NOTE: IT may be better to make all the ports a member of this class, rather than 
mapping the function arguments to ports using the inputs and outputs variables.???

  */
class Proc_function  
{
public:
	Proc_function();
	Proc_function(istream *);
	virtual ~Proc_function();
//data	
	char func_name[256];
	int start_trig;
	CArray<int,int> complete; //index
	CArray<int,int> outputs;
	CArray<int,int> inputs;
};

#endif // !defined(AFX_PROC_FUNCTION_H__55451EA2_F88D_11D8_A9B1_00055DD37FD7__INCLUDED_)
