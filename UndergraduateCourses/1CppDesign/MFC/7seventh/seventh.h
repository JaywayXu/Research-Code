// seventh.h : main header file for the SEVENTH application
//

#if !defined(AFX_SEVENTH_H__1932C6B0_6230_437D_A553_14A80016341F__INCLUDED_)
#define AFX_SEVENTH_H__1932C6B0_6230_437D_A553_14A80016341F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSeventhApp:
// See seventh.cpp for the implementation of this class
//

class CSeventhApp : public CWinApp
{
public:
	CSeventhApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeventhApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSeventhApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEVENTH_H__1932C6B0_6230_437D_A553_14A80016341F__INCLUDED_)
