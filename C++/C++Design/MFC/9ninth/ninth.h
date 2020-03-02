// ninth.h : main header file for the NINTH application
//

#if !defined(AFX_NINTH_H__969DB755_12BF_481E_AAAA_8333ADD9AA3C__INCLUDED_)
#define AFX_NINTH_H__969DB755_12BF_481E_AAAA_8333ADD9AA3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CNinthApp:
// See ninth.cpp for the implementation of this class
//

class CNinthApp : public CWinApp
{
public:
	CNinthApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNinthApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CNinthApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NINTH_H__969DB755_12BF_481E_AAAA_8333ADD9AA3C__INCLUDED_)
