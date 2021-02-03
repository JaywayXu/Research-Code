// Search.cpp : implementation file
//

#include "stdafx.h"
#include "SGMS_MFC.h"
#include "Search.h"

#include "SGMS.h"
#include <string>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Search dialog

extern std::vector<Student> List;

Search::Search(CWnd* pParent /*=NULL*/)
	: CDialog(Search::IDD, pParent)
{
	//{{AFX_DATA_INIT(Search)
	//}}AFX_DATA_INIT
}


void Search::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Search)
	DDX_Control(pDX, IDC_COMBO_DATA, m_combo_data);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_COMBO_MENU, m_combo_menu);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Search, CDialog)
	//{{AFX_MSG_MAP(Search)
	ON_BN_CLICKED(IDC_BUTTON_Yes, OnBUTTONYes)
	ON_BN_CLICKED(IDC_BUTTON3, OnButtonS)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Search message handlers

void Search::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL Search::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_EDIT_IN)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_DATA)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_MIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_MAX)->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Search::OnBUTTONYes() 
{
	// TODO: Add your control notification handler code here
	int Count = m_list.GetCount();
	for (int temp_i = Count; temp_i>=0; temp_i--)
	{
		m_list.DeleteString(temp_i);
	}

	SetDlgItemText(IDC_EDIT_IN,"");
	SetDlgItemText(IDC_COMBO_DATA,"");
	SetDlgItemText(IDC_EDIT_MIN,"");
	SetDlgItemText(IDC_EDIT_MAX,"");

	GetDlgItem(IDC_EDIT_IN)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_DATA)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_MIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_MAX)->EnableWindow(FALSE);
	
	int index = m_combo_menu.GetCurSel();
	switch (index)
	{
		case 1:{
			GetDlgItem(IDC_COMBO_DATA)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_MIN)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_MAX)->EnableWindow(TRUE);
		}break;
		case 0:{
			GetDlgItem(IDC_EDIT_IN)->EnableWindow(TRUE);
		}break;
	}
}

void Search::OnButtonS() 
{
	// TODO: Add your control notification handler code here
	int Count = m_list.GetCount();
	for (int temp_i = Count; temp_i>=0; temp_i--)
	{
		m_list.DeleteString(temp_i);
	}

	char ch[12];
	GetDlgItemText(IDC_EDIT_IN,ch,12);
	std::string in = ch;
	int data_menu = m_combo_data.GetCurSel();
	char ch1[10], ch2[6], ch3[6];
	GetDlgItemText(IDC_COMBO_DATA,ch1,10);
	GetDlgItemText(IDC_EDIT_MIN,ch2,6);
	GetDlgItemText(IDC_EDIT_MAX,ch3,6);
	std::string data = ch1,
		smin = ch2, smax = ch3;
	double bottom = atof(ch2);
	double top = atof(ch3);

	if (!in.empty())
	{
		for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
		{
			if((*i).number.find(in) != std::string::npos || (*i).name.find(in) != std::string::npos)
			{
				CString str1 = (*i).getstr().c_str();
				m_list.AddString(str1);
			}
		}
	}
	else if (!data.empty() && !smin.empty() && !smax.empty())
	{
		for(std::vector<Student>::iterator j = List.begin();j != List.end();j++)
		{
			switch (data_menu)
			{
				case 0:if((*j).math >= bottom && (*j).math <= top)
				{CString str2 = (*j).getstr().c_str(); m_list.AddString(str2);}break;
				case 1:if((*j).physics >= bottom && (*j).physics <= top)
				{CString str2 = (*j).getstr().c_str(); m_list.AddString(str2);};break;
				case 2:if((*j).english >= bottom && (*j).english <= top)
				{CString str2 = (*j).getstr().c_str(); m_list.AddString(str2);}break;
				case 3:if((*j).get_average() >= bottom && (*j).get_average() <= top)
				{CString str2 = (*j).getstr().c_str(); m_list.AddString(str2);}break;
			}
		}
	}
	else MessageBox("请输入有效数据！");
}
