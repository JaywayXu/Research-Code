// forthDlg.cpp : implementation file
//

#include "stdafx.h"
#include "forth.h"
#include "forthDlg.h"
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CForthDlg dialog

CForthDlg::CForthDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CForthDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CForthDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CForthDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CForthDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CForthDlg, CDialog)
	//{{AFX_MSG_MAP(CForthDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CForthDlg message handlers

BOOL CForthDlg::OnInitDialog()
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

void CForthDlg::OnPaint() 
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
HCURSOR CForthDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CForthDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	char ch1[10],ch2[10],ch3[10];
	double a,b,c;
	GetDlgItem(IDC_EDIT1)->GetWindowText(ch1,10);
	GetDlgItem(IDC_EDIT2)->GetWindowText(ch2,10);
	GetDlgItem(IDC_EDIT3)->GetWindowText(ch3,10);
	a = atof(ch1);
	b = atof(ch2);
	c = atof(ch3);

	if(!a || !b ||!c)
	{
		MessageBox("错误！请输入正确的数据");
		return FALSE;
	}

	if(a+b<=c || a+c<=b || b+c<=a)
	{
		MessageBox("错误！不能构成三角形");
		return FALSE;
	}

	double p = (a+b+c)/2.0;
	double s = sqrt(p*(p-a)*(p-b)*(p-c));

	CString str;
	str.Format("面积为：%.3f",s);
	MessageBox(str);
	return TRUE;
}
