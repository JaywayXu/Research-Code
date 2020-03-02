// sixthDlg.cpp : implementation file
//

#include "stdafx.h"
#include "sixth.h"
#include "sixthDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSixthDlg dialog

CSixthDlg::CSixthDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSixthDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSixthDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSixthDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSixthDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSixthDlg, CDialog)
	//{{AFX_MSG_MAP(CSixthDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSixthDlg message handlers

BOOL CSixthDlg::OnInitDialog()
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

void CSixthDlg::OnPaint() 
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
HCURSOR CSixthDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CSixthDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	char ch1[10], ch2[10];
	int a,b;
	GetDlgItem(IDC_EDIT1)->GetWindowText(ch1,10);
	GetDlgItem(IDC_EDIT2)->GetWindowText(ch2,10);
	a = atoi(ch1);
	b = atoi(ch2);

	if(!a || !b)
	{
		MessageBox("输入错误！请输入正确的正整数");
		return FALSE;
	}
	int m = a, n = b, c = 1;
	while(c != 0)
	{
		c = a%b;
		a = b;
		b = c;
	}

	CString str;
	str.Format("最大公约数为：%d\n最小公倍数为：%d",a,m*n/a);
	MessageBox(str);
	return TRUE;
}
