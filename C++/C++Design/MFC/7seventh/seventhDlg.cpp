// seventhDlg.cpp : implementation file
//

#include "stdafx.h"
#include "seventh.h"
#include "seventhDlg.h"

#define LEN 10000

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeventhDlg dialog

CSeventhDlg::CSeventhDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSeventhDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSeventhDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSeventhDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSeventhDlg)
	DDX_Control(pDX, IDC_LIST2, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSeventhDlg, CDialog)
	//{{AFX_MSG_MAP(CSeventhDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeventhDlg message handlers

BOOL CSeventhDlg::OnInitDialog()
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

void CSeventhDlg::OnPaint() 
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
HCURSOR CSeventhDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CSeventhDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	char ch[10];
	GetDlgItem(IDC_EDIT1)->GetWindowText(ch,10);
	int x = atoi(ch);
	if (!x)
	{
		MessageBox("错误！请输入正整数");
		return FALSE;
	}

	int count, i, j;
	int arry[LEN],n = 1;
	for (i = 0; i<LEN; i++) arry[i] = 0;
	arry[0] = 2;
	for(i = 3; i<x; i++)
	{
		count = 0;
		for(j = 2; j<i; j++)
		{
			if (i%j == 0) count++;
		}
		if (count == 0) arry[n++] = i;
	}

	CString strarry[LEN/5];
	int m = 0;
	for(i = 0; arry[m]!=0; i++)
	{
		if (arry[m])
		{
			strarry[i].Format("%-6d %-6d %-6d %-6d %-6d",
				arry[m],arry[m+1],arry[m+2],arry[m+3],arry[m+4]);
			m_list.AddString(strarry[i]);
		}
		m += 5;
	}
	return TRUE;
}
