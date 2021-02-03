#if !defined(AFX_ADD_H__EA761C76_5830_4B35_94BE_8F78374EEB32__INCLUDED_)
#define AFX_ADD_H__EA761C76_5830_4B35_94BE_8F78374EEB32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ADD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ADD dialog

class ADD : public CDialog
{
// Construction
public:
	ADD(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ADD)
	enum { IDD = IDD_ADD_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ADD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ADD)
	virtual void OnCancel();
	afx_msg void OnADD();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADD_H__EA761C76_5830_4B35_94BE_8F78374EEB32__INCLUDED_)
