// SGMS_MFC.h : main header file for the SGMS_MFC application
//

#if !defined(AFX_SGMS_MFC_H__95A3F15A_BFC2_41FF_A240_7814435D24E0__INCLUDED_)
#define AFX_SGMS_MFC_H__95A3F15A_BFC2_41FF_A240_7814435D24E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSGMS_MFCApp:
// See SGMS_MFC.cpp for the implementation of this class
//

class CSGMS_MFCApp : public CWinApp
{
public:
	CSGMS_MFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSGMS_MFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSGMS_MFCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SGMS_MFC_H__95A3F15A_BFC2_41FF_A240_7814435D24E0__INCLUDED_)
