// colordlg.cpp : implementation file
//

#include "stdafx.h"
#include "eighth.h"
#include "colordlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// colordlg

IMPLEMENT_DYNAMIC(colordlg, CColorDialog)

colordlg::colordlg(COLORREF clrInit, DWORD dwFlags, CWnd* pParentWnd) :
	CColorDialog(clrInit, dwFlags, pParentWnd)
{
}


BEGIN_MESSAGE_MAP(colordlg, CColorDialog)
	//{{AFX_MSG_MAP(colordlg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

