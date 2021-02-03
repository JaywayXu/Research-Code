// ADD.cpp : implementation file
//

#include "stdafx.h"
#include "SGMS_MFC.h"
#include "ADD.h"

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

extern std::vector<Student> List;

/////////////////////////////////////////////////////////////////////////////
// ADD dialog


ADD::ADD(CWnd* pParent /*=NULL*/)
	: CDialog(ADD::IDD, pParent)
{
	//{{AFX_DATA_INIT(ADD)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ADD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ADD)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ADD, CDialog)
	//{{AFX_MSG_MAP(ADD)
	ON_BN_CLICKED(IDC_BUTTON1, OnADD)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ADD message handlers

void ADD::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void ADD::OnADD() 
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
		for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
		{
			if(number == (*i).number || name == (*i).name)
			{
				MessageBox("库中已有该学号或姓名！");
				break;
			}
			if((i+1) == List.end())
			{
				double math, physics, english;
				math = atof(ch3); physics = atof(ch4); english = atof(ch5);
				Student stu(number,name,math,physics,english);
				List.push_back(stu);

				WPARAM wParam = CMSG;
				::PostMessage(::GetParent(m_hWnd),WM_UPDATE_MSG,wParam,0);

				MessageBox("添加成功！");
				SetDlgItemText(IDC_EDIT_Num,"");
				SetDlgItemText(IDC_EDIT_Name,"");
				SetDlgItemText(IDC_EDIT_Math,"");
				SetDlgItemText(IDC_EDIT_Physics,"");
				SetDlgItemText(IDC_EDIT_English,"");
				break;
			}
		}
	}
}
