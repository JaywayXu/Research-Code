#if !defined(AFX_SORT_H__0EFCB6C4_13B4_4B10_A204_04821F7FEA80__INCLUDED_)
#define AFX_SORT_H__0EFCB6C4_13B4_4B10_A204_04821F7FEA80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SORT.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SORT dialog

class SORT : public CDialog
{
// Construction
public:
	SORT(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SORT)
	enum { IDD = IDD_SORT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SORT)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SORT)
	virtual void OnCancel();
	afx_msg void OnX();
	afx_msg void OnNum();
	afx_msg void OnMath();
	afx_msg void OnPhysics();
	afx_msg void OnEnglish();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SORT_H__0EFCB6C4_13B4_4B10_A204_04821F7FEA80__INCLUDED_)
