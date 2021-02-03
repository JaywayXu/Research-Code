// fifthDlg.h : header file
//

#if !defined(AFX_FIFTHDLG_H__1C390BD5_33F2_4156_82D4_8ACCA8E974B4__INCLUDED_)
#define AFX_FIFTHDLG_H__1C390BD5_33F2_4156_82D4_8ACCA8E974B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFifthDlg dialog

class CFifthDlg : public CDialog
{
// Construction
public:
	CFifthDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFifthDlg)
	enum { IDD = IDD_FIFTH_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFifthDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFifthDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIFTHDLG_H__1C390BD5_33F2_4156_82D4_8ACCA8E974B4__INCLUDED_)
