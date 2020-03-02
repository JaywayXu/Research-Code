// fifthDlg.cpp : implementation file
//

#include "stdafx.h"
#include "fifth.h"
#include "fifthDlg.h"
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFifthDlg dialog

CFifthDlg::CFifthDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFifthDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFifthDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFifthDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFifthDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFifthDlg, CDialog)
	//{{AFX_MSG_MAP(CFifthDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFifthDlg message handlers

BOOL CFifthDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFifthDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFifthDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CFifthDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	char ch1[10],ch2[10],ch3[10];
	double a,b,c;
	GetDlgItem(IDC_EDIT1)->GetWindowText(ch1,10);
	GetDlgItem(IDC_EDIT2)->GetWindowText(ch2,10);
	GetDlgItem(IDC_EDIT3)->GetWindowText(ch3,10);
	if (ch1[0] == '-')
	{
		char ch[9];
		for(int i = 0; i<9; i++) ch[i] = ch1[i+1];
		a = -(atof(ch));
	}
	else a = atof(ch1);
	if (ch2[0] == '-')
	{
		char ch[9];
		for(int i = 0; i<9; i++) ch[i] = ch2[i+1];
		b = -(atof(ch));
	}
	else b = atof(ch2);
	if (ch3[0] == '-')
	{
		char ch[9];
		for(int i = 0; i<9; i++) ch[i] = ch3[i+1];
		c = -(atof(ch));
	}
	else c = atof(ch3);

	if ((b*b - 4.0*a*c) < 0)
	{
		MessageBox("无解");
		return FALSE;
	}

	double a1 = (-b + sqrt(b*b - 4.0*a*c))/(2.0*a);
	double a2 = (-b - sqrt(b*b - 4.0*a*c))/(2.0*a);

	CString str;
	str.Format("两个根分别为：%.3f、%.3f",a1,a2);
	MessageBox(str);
	return TRUE;
}
