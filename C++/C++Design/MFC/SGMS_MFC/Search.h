#if !defined(AFX_SEARCH_H__B30F53BB_34E0_45DB_8436_A5FF6CF772A2__INCLUDED_)
#define AFX_SEARCH_H__B30F53BB_34E0_45DB_8436_A5FF6CF772A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Search.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Search dialog

class Search : public CDialog
{
// Construction
public:
	Search(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Search)
	enum { IDD = IDD_SEARCH_DIALOG };
	CComboBox	m_combo_data;
	CListBox	m_list;
	CComboBox	m_combo_menu;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Search)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Search)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBUTTONYes();
	afx_msg void OnButtonS();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCH_H__B30F53BB_34E0_45DB_8436_A5FF6CF772A2__INCLUDED_)
