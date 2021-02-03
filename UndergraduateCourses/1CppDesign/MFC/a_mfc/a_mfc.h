// a_mfc.h : main header file for the A_MFC application
//

#if !defined(AFX_A_MFC_H__9A34760E_CB7D_4E27_8C7A_D26248212869__INCLUDED_)
#define AFX_A_MFC_H__9A34760E_CB7D_4E27_8C7A_D26248212869__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CA_mfcApp:
// See a_mfc.cpp for the implementation of this class
//

class CA_mfcApp : public CWinApp
{
public:
	CA_mfcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CA_mfcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CA_mfcApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_A_MFC_H__9A34760E_CB7D_4E27_8C7A_D26248212869__INCLUDED_)
