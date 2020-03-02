#if !defined(AFX_HANGE_H__7D88EE9C_5742_4B04_BED0_F0213156B2C0__INCLUDED_)
#define AFX_HANGE_H__7D88EE9C_5742_4B04_BED0_F0213156B2C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// hange.h : header file
//

#include <vector>
#include "SGMS.h"

/////////////////////////////////////////////////////////////////////////////
// Change dialog

class Change : public CDialog
{
// Construction
public:
	Change(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Change)
	enum { IDD = IDD_HANGE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Change)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Change)
	afx_msg void OnButtonS();
	afx_msg void OnButtonC();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	std::vector<Student>::iterator iter;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HANGE_H__7D88EE9C_5742_4B04_BED0_F0213156B2C0__INCLUDED_)
