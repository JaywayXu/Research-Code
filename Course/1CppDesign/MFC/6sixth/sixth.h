// sixth.h : main header file for the SIXTH application
//

#if !defined(AFX_SIXTH_H__43F11A1E_5322_4DA9_A2B0_FDAEDC9D1E89__INCLUDED_)
#define AFX_SIXTH_H__43F11A1E_5322_4DA9_A2B0_FDAEDC9D1E89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSixthApp:
// See sixth.cpp for the implementation of this class
//

class CSixthApp : public CWinApp
{
public:
	CSixthApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSixthApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSixthApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIXTH_H__43F11A1E_5322_4DA9_A2B0_FDAEDC9D1E89__INCLUDED_)
