// eighthDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eighth.h"
#include "eighthDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEighthDlg dialog

CEighthDlg::CEighthDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEighthDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEighthDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEighthDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEighthDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEighthDlg, CDialog)
	//{{AFX_MSG_MAP(CEighthDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_COLOR1, OnButtonColor1)
	ON_BN_CLICKED(IDC_BUTTON_COLOR2, OnButtonColor2)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEighthDlg message handlers

BOOL CEighthDlg::OnInitDialog()
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

void CEighthDlg::OnPaint() 
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
HCURSOR CEighthDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEighthDlg::OnButtonColor1() 
{
	// TODO: Add your control notification handler code here
	COLORREF color = RGB(0, 0, 0);      // 颜色对话框的初始颜色为红色  
    CColorDialog colorDlg(color);         // 构造颜色对话框，传入初始颜色值   
  
    if (IDOK == colorDlg.DoModal())       // 显示颜色对话框，并判断是否点击了“确定”   
    {   
        color = colorDlg.GetColor();      // 获取颜色对话框中选择的颜色值   
        SetDlgItemInt(IDC_EDIT_R1, GetRValue(color));  // 在R编辑框中显示所选颜色的R分量值   
        SetDlgItemInt(IDC_EDIT_G1, GetGValue(color));  // 在G编辑框中显示所选颜色的G分量值   
        SetDlgItemInt(IDC_EDIT_B1, GetBValue(color));  // 在B编辑框中显示所选颜色的B分量值   
    }
}

void CEighthDlg::OnButtonColor2() 
{
	// TODO: Add your control notification handler code here
	COLORREF color = RGB(255, 255, 255);      // 颜色对话框的初始颜色为红色  
    CColorDialog colorDlg(color);         // 构造颜色对话框，传入初始颜色值   
  
    if (IDOK == colorDlg.DoModal())       // 显示颜色对话框，并判断是否点击了“确定”   
    {   
        color = colorDlg.GetColor();      // 获取颜色对话框中选择的颜色值   
        SetDlgItemInt(IDC_EDIT_R2, GetRValue(color));  // 在R编辑框中显示所选颜色的R分量值   
        SetDlgItemInt(IDC_EDIT_G2, GetGValue(color));  // 在G编辑框中显示所选颜色的G分量值   
        SetDlgItemInt(IDC_EDIT_B2, GetBValue(color));  // 在B编辑框中显示所选颜色的B分量值   
    }
}

void CEighthDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	int r1, r2, g1, g2, b1, b2, x, y, r;
	char cr1[10], cr2[10], cg1[10], cg2[10], cb1[10], cb2[10],
		cx[10], cy[10], cr[10];
	GetDlgItem(IDC_EDIT_R1)->GetWindowText(cr1,10);
	GetDlgItem(IDC_EDIT_R2)->GetWindowText(cr2,10);
	GetDlgItem(IDC_EDIT_G1)->GetWindowText(cg1,10);
	GetDlgItem(IDC_EDIT_G2)->GetWindowText(cg2,10);
	GetDlgItem(IDC_EDIT_B1)->GetWindowText(cb1,10);
	GetDlgItem(IDC_EDIT_B2)->GetWindowText(cb2,10);
	GetDlgItem(IDC_EDIT_X)->GetWindowText(cx,10);
	GetDlgItem(IDC_EDIT_Y)->GetWindowText(cy,10);
	GetDlgItem(IDC_EDIT_R)->GetWindowText(cr,10);
	r1 = atoi(cr1);
	r2 = atoi(cr2);
	g1 = atoi(cg1);
	g2 = atoi(cg2);
	b1 = atoi(cb1);
	b2 = atoi(cb2);
	x = atoi(cx);
	y = atoi(cy);
	r = atoi(cr);

	if (((CButton *)GetDlgItem(IDC_CHECK))->GetCheck())
	{
		CClientDC dc(this);

		CPen pen(PS_SOLID,1,RGB(r1,g1,b1));
		CPen *pOldPen = dc.SelectObject(&pen);

		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP_B);
		CBrush brush(&bitmap);
		CBrush *pOldBrush = dc.SelectObject(&brush);

		dc.Ellipse(x-r,y-r,x+r,y+r);
		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBrush);
	}
	else
	{
		CClientDC dc(this);

		CPen pen(PS_SOLID,1,RGB(r1,g1,b1));
		CPen *pOldPen = dc.SelectObject(&pen);

		CBrush brush;
		brush.CreateSolidBrush(RGB(r2,g2,b2));
		CBrush *pOldBrush = dc.SelectObject(&brush);

		dc.Ellipse(x-r,y-r,x+r,y+r);
		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBrush);
	}
}

void CEighthDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	Invalidate();
}
