#if !defined(AFX_DEL_H__E799CD6F_20B0_4E8B_89DF_2719AFFE1959__INCLUDED_)
#define AFX_DEL_H__E799CD6F_20B0_4E8B_89DF_2719AFFE1959__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Del.h : header file
//

#include <vector>
#include "SGMS.h"

/////////////////////////////////////////////////////////////////////////////
// Del dialog

class Del : public CDialog
{
// Construction
public:
	Del(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Del)
	enum { IDD = IDD_DEL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Del)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Del)
	virtual void OnCancel();
	afx_msg void OnButtonS();
	afx_msg void OnButtonD();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	std::vector<Student>::iterator iter;
	bool candel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEL_H__E799CD6F_20B0_4E8B_89DF_2719AFFE1959__INCLUDED_)
