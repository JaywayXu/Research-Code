// Del.cpp : implementation file
//

#include "stdafx.h"
#include "SGMS_MFC.h"
#include "Del.h"

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
// Del dialog

extern std::vector<Student> List;

Del::Del(CWnd* pParent /*=NULL*/)
	: CDialog(Del::IDD, pParent)
{
	//{{AFX_DATA_INIT(Del)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	candel = FALSE;
}


void Del::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Del)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Del, CDialog)
	//{{AFX_MSG_MAP(Del)
	ON_BN_CLICKED(IDC_BUTTON3, OnButtonS)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonD)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Del message handlers

void Del::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void Del::OnButtonS() 
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
			SetDlgItemText(IDC_EDIT_Num,snum);
			SetDlgItemText(IDC_EDIT_Name,sname);
			SetDlgItemText(IDC_EDIT_Math,smath);
			SetDlgItemText(IDC_EDIT_Physics,sphysics);
			SetDlgItemText(IDC_EDIT_English,senglish);

			iter = i;
			candel = TRUE;
            break;
        }
        if((i+1) == List.end()) MessageBox("未找到此记录！");
    }
}

void Del::OnButtonD() 
{
	// TODO: Add your control notification handler code here
	if (candel)
	{
		if(::MessageBox(NULL, "确定要删除吗？","删除", MB_YESNO) == IDYES)
		{
			List.erase(iter);
			iter = NULL;
			candel = FALSE;

			WPARAM wParam = CMSG;
			::PostMessage(::GetParent(m_hWnd),WM_UPDATE_MSG,wParam,0);

			MessageBox("删除成功！");
			SetDlgItemText(IDC_EDIT_IN,"");
			SetDlgItemText(IDC_EDIT_Num,"");
			SetDlgItemText(IDC_EDIT_Name,"");
			SetDlgItemText(IDC_EDIT_Math,"");
			SetDlgItemText(IDC_EDIT_Physics,"");
			SetDlgItemText(IDC_EDIT_English,"");
		}
	}
	else MessageBox("请先查找到记录再删除！");
}
