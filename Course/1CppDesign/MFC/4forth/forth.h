// forth.h : main header file for the FORTH application
//

#if !defined(AFX_FORTH_H__D96AF140_71B7_42BE_A0CA_0A639D0E65FD__INCLUDED_)
#define AFX_FORTH_H__D96AF140_71B7_42BE_A0CA_0A639D0E65FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CForthApp:
// See forth.cpp for the implementation of this class
//

class CForthApp : public CWinApp
{
public:
	CForthApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CForthApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CForthApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORTH_H__D96AF140_71B7_42BE_A0CA_0A639D0E65FD__INCLUDED_)
