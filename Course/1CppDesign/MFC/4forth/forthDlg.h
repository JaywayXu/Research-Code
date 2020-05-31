// forthDlg.h : header file
//

#if !defined(AFX_FORTHDLG_H__B737830D_AEE7_446A_BE58_0FFEBDC5EA89__INCLUDED_)
#define AFX_FORTHDLG_H__B737830D_AEE7_446A_BE58_0FFEBDC5EA89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CForthDlg dialog

class CForthDlg : public CDialog
{
// Construction
public:
	CForthDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CForthDlg)
	enum { IDD = IDD_FORTH_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CForthDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CForthDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORTHDLG_H__B737830D_AEE7_446A_BE58_0FFEBDC5EA89__INCLUDED_)
