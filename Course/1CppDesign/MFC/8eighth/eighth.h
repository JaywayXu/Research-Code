// eighth.h : main header file for the EIGHTH application
//

#if !defined(AFX_EIGHTH_H__99BBEDD1_2EF1_4FBB_A5AB_B7CCDBEE0A10__INCLUDED_)
#define AFX_EIGHTH_H__99BBEDD1_2EF1_4FBB_A5AB_B7CCDBEE0A10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEighthApp:
// See eighth.cpp for the implementation of this class
//

class CEighthApp : public CWinApp
{
public:
	CEighthApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEighthApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEighthApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EIGHTH_H__99BBEDD1_2EF1_4FBB_A5AB_B7CCDBEE0A10__INCLUDED_)
