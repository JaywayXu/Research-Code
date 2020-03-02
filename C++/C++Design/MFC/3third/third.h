// third.h : main header file for the THIRD application
//

#if !defined(AFX_THIRD_H__D2776191_F000_42DD_A564_FF1438C55078__INCLUDED_)
#define AFX_THIRD_H__D2776191_F000_42DD_A564_FF1438C55078__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CThirdApp:
// See third.cpp for the implementation of this class
//

class CThirdApp : public CWinApp
{
public:
	CThirdApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThirdApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CThirdApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THIRD_H__D2776191_F000_42DD_A564_FF1438C55078__INCLUDED_)
