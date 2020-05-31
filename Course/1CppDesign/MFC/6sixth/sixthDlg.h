// sixthDlg.h : header file
//

#if !defined(AFX_SIXTHDLG_H__1D67C24B_F72B_45AC_B516_FAF1B334E0F0__INCLUDED_)
#define AFX_SIXTHDLG_H__1D67C24B_F72B_45AC_B516_FAF1B334E0F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSixthDlg dialog

class CSixthDlg : public CDialog
{
// Construction
public:
	CSixthDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSixthDlg)
	enum { IDD = IDD_SIXTH_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSixthDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSixthDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIXTHDLG_H__1D67C24B_F72B_45AC_B516_FAF1B334E0F0__INCLUDED_)
