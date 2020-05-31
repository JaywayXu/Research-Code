// eighthDlg.h : header file
//

#if !defined(AFX_EIGHTHDLG_H__3EB81AF0_1C59_4DDE_B2A2_743BA85B8C62__INCLUDED_)
#define AFX_EIGHTHDLG_H__3EB81AF0_1C59_4DDE_B2A2_743BA85B8C62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEighthDlg dialog

class CEighthDlg : public CDialog
{
// Construction
public:
	CEighthDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEighthDlg)
	enum { IDD = IDD_EIGHTH_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEighthDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEighthDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonColor1();
	afx_msg void OnButtonColor2();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EIGHTHDLG_H__3EB81AF0_1C59_4DDE_B2A2_743BA85B8C62__INCLUDED_)
