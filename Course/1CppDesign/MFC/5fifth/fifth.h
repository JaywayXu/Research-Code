// fifth.h : main header file for the FIFTH application
//

#if !defined(AFX_FIFTH_H__5F7E3233_B752_455D_825B_ED5098EF71B8__INCLUDED_)
#define AFX_FIFTH_H__5F7E3233_B752_455D_825B_ED5098EF71B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFifthApp:
// See fifth.cpp for the implementation of this class
//

class CFifthApp : public CWinApp
{
public:
	CFifthApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFifthApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFifthApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIFTH_H__5F7E3233_B752_455D_825B_ED5098EF71B8__INCLUDED_)
