#pragma once
#include "scbarg.h"
#include "afxcmn.h"
#include "FunctionBlockTree.h"


class FunctionBlockBar : public CSizingControlBarG
{
public:
	FunctionBlockBar(void);
public:
	~FunctionBlockBar(void);
public:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMButtonDown(UINT nFlags, CPoint _point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint _point);
	bool crp;
	afx_msg void OnRButtonDown(UINT nFlags, CPoint _point);
public:
	//CTreeCtrl m_cTreeCtrl1, m_cTreeCtrl2;


	FunctionBlockTree m_cFuncBlckTree;

public:
	int init(void);
	int loadContents(void);
};
