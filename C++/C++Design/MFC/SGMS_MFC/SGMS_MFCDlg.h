// SGMS_MFCDlg.h : header file
//
#include <string>
#include <vector>
#include <sstream>

#include "ADD.h"
#include "Del.h"
#include "hange.h"
#include "Search.h"
#include "SORT.h"

#if !defined(AFX_SGMS_MFCDLG_H__49705CC7_F677_43D3_8E3E_D563B03DF6A2__INCLUDED_)
#define AFX_SGMS_MFCDLG_H__49705CC7_F677_43D3_8E3E_D563B03DF6A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSGMS_MFCDlg dialog

class CSGMS_MFCDlg : public CDialog
{
// Construction
public:
	CSGMS_MFCDlg(CWnd* pParent = NULL);	// standard constructor
	~CSGMS_MFCDlg();

// Dialog Data
	//{{AFX_DATA(CSGMS_MFCDlg)
	enum { IDD = IDD_SGMS_MFC_DIALOG };
		// NOTE: the ClassWizard will add data members here
	CListBox	m_list;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSGMS_MFCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSGMS_MFCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRead();
	afx_msg void OnWrite();
	afx_msg void OnAdd();
	afx_msg void OnDel();
	afx_msg void OnChange();
	afx_msg void OnSearch();
	afx_msg void OnAnalyse();
	afx_msg void OnSort();
	afx_msg LRESULT OnStrUpdate(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void printstrlist();
	void all_average(double &,double &,double &,double &);
    void standard_deviation(
        double &,double &,double &,double &,
        double,double,double,double);
    void qualified_rate(double &,double &,double &,double &); 

private:
	ADD *adddlg;
	Del *deldlg;
	Change *changedlg;
	Search *searchdlg;
	SORT *sortdlg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SGMS_MFCDLG_H__49705CC7_F677_43D3_8E3E_D563B03DF6A2__INCLUDED_)
