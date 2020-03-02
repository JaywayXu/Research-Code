// seventhDlg.h : header file
//

#if !defined(AFX_SEVENTHDLG_H__A97BC62F_638D_44C0_9340_C632E45A082C__INCLUDED_)
#define AFX_SEVENTHDLG_H__A97BC62F_638D_44C0_9340_C632E45A082C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSeventhDlg dialog

class CSeventhDlg : public CDialog
{
// Construction
public:
	CSeventhDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSeventhDlg)
	enum { IDD = IDD_SEVENTH_DIALOG };
	CListBox	m_list;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeventhDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSeventhDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEVENTHDLG_H__A97BC62F_638D_44C0_9340_C632E45A082C__INCLUDED_)
