// hange.cpp : implementation file
//

#include "stdafx.h"
#include "SGMS_MFC.h"
#include "hange.h"

#include "SGMS.h"
#include <string>
#include <vector>

#define WM_UPDATE_MSG (WM_USER + 100)
#define CMSG 2333

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Change dialog

extern std::vector<Student> List;

Change::Change(CWnd* pParent /*=NULL*/)
	: CDialog(Change::IDD, pParent)
{
	//{{AFX_DATA_INIT(Change)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Change::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Change)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Change, CDialog)
	//{{AFX_MSG_MAP(Change)
	ON_BN_CLICKED(IDC_BUTTON3, OnButtonS)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonC)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Change message handlers

void Change::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void Change::OnButtonS() 
{
	// TODO: Add your control notification handler code here
	char ch[12];
	GetDlgItemText(IDC_EDIT_IN,ch,12);
	std::string temp_data = ch;
	for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
    {
        if(temp_data == (*i).number || temp_data == (*i).name)
        {
			CString snum, sname, smath, sphysics, senglish;
			snum = (*i).number.c_str();
			sname = (*i).name.c_str();
			smath.Format("%.1f", (*i).math);
			sphysics.Format("%.1f", (*i).physics);
			senglish.Format("%.1f", (*i).english);

			GetDlgItem(IDC_EDIT_Num)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_Name)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_Math)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_Physics)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_English)->EnableWindow(TRUE);

			SetDlgItemText(IDC_EDIT_Num,snum);
			SetDlgItemText(IDC_EDIT_Name,sname);
			SetDlgItemText(IDC_EDIT_Math,smath);
			SetDlgItemText(IDC_EDIT_Physics,sphysics);
			SetDlgItemText(IDC_EDIT_English,senglish);

			iter = i;
            break;
        }
        if((i+1) == List.end()) MessageBox("未找到此记录！");
    }
}

void Change::OnButtonC() 
{
	// TODO: Add your control notification handler code here
	char ch1[12], ch2[12], ch3[6], ch4[6], ch5[6];
	GetDlgItemText(IDC_EDIT_Num,ch1,12);
	GetDlgItemText(IDC_EDIT_Name,ch2,12);
	GetDlgItemText(IDC_EDIT_Math,ch3,6);
	GetDlgItemText(IDC_EDIT_Physics,ch4,6);
	GetDlgItemText(IDC_EDIT_English,ch5,6);
	std::string number, name, smath, sphysics, senglish;
	number = ch1; name = ch2, smath = ch3, sphysics = ch4, senglish = ch5;
	if (number.empty() || name.empty() || smath.empty() || sphysics.empty() || senglish.empty())
	{
		MessageBox("请输入正确的数据");
	}
	else
	{
		double math, physics, english;
		math = atof(ch3); physics = atof(ch4); english = atof(ch5);
		(*iter).number = number;
		(*iter).name = name;
		(*iter).math = math;
		(*iter).physics = physics;
		(*iter).english = english;
		iter = NULL;

		WPARAM wParam = CMSG;
		::PostMessage(::GetParent(m_hWnd),WM_UPDATE_MSG,wParam,0);

		MessageBox("修改成功！");
		SetDlgItemText(IDC_EDIT_IN,"");
		SetDlgItemText(IDC_EDIT_Num,"");
		SetDlgItemText(IDC_EDIT_Name,"");
		SetDlgItemText(IDC_EDIT_Math,"");
		SetDlgItemText(IDC_EDIT_Physics,"");
		SetDlgItemText(IDC_EDIT_English,"");

		GetDlgItem(IDC_EDIT_Num)->EnableWindow(FALSE);//只读。
		GetDlgItem(IDC_EDIT_Name)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_Math)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_Physics)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_English)->EnableWindow(FALSE);
	}

}

BOOL Change::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_EDIT_Num)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Name)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Math)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Physics)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_English)->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
