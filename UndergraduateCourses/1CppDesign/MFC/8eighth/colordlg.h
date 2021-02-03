#if !defined(AFX_COLORDLG_H__9BB5BFA4_2860_46B6_8C0E_116B661693CE__INCLUDED_)
#define AFX_COLORDLG_H__9BB5BFA4_2860_46B6_8C0E_116B661693CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// colordlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// colordlg dialog

class colordlg : public CColorDialog
{
	DECLARE_DYNAMIC(colordlg)

public:
	colordlg(COLORREF clrInit = 0, DWORD dwFlags = 0,
			CWnd* pParentWnd = NULL);

protected:
	//{{AFX_MSG(colordlg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORDLG_H__9BB5BFA4_2860_46B6_8C0E_116B661693CE__INCLUDED_)
