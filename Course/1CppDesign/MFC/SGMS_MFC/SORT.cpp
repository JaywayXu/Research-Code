// SORT.cpp : implementation file
//

#include "stdafx.h"
#include "SGMS_MFC.h"
#include "SORT.h"

#include "SGMS.h"
#include <string>
#include <cmath>

#define WM_UPDATE_MSG (WM_USER + 100)
#define CMSG 2333

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern std::vector<Student> List;

/////////////////////////////////////////////////////////////////////////////
// SORT dialog


SORT::SORT(CWnd* pParent /*=NULL*/)
	: CDialog(SORT::IDD, pParent)
{
	//{{AFX_DATA_INIT(SORT)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SORT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SORT)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SORT, CDialog)
	//{{AFX_MSG_MAP(SORT)
	ON_BN_CLICKED(IDC_X, OnX)
	ON_BN_CLICKED(IDC_NUM, OnNum)
	ON_BN_CLICKED(IDC_MATH, OnMath)
	ON_BN_CLICKED(IDC_PHYSICS, OnPhysics)
	ON_BN_CLICKED(IDC_ENGLISH, OnEnglish)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SORT message handlers

void SORT::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void SORT::OnX() 
{
	// TODO: Add your control notification handler code here
	if(List.size() != 0)
	{
		int i,j;Student T;
		for(i = 0;i < (int)List.size()-1;i++)
		{
			for(j = 0;j < (int)List.size()-1-i;j++)
			{
				if(List[j].get_average() < List[j+1].get_average()
					&& fabs(List[j].get_average()-List[j+1].get_average()) > 1E-6)
				{T = List[j];List[j] = List[j+1];List[j+1] = T;}
				else if(fabs(List[j].get_average()-List[j+1].get_average()) <= 1E-6)
				{
					if(List[j].math < List[j+1].math
						&& fabs(List[j].math-List[j+1].math) > 1E-6)
					{T = List[j];List[j] = List[j+1];List[j+1] = T;}
					else if(fabs(List[j].math-List[j+1].math) <= 1E-6)
					{
						if(List[j].physics < List[j+1].physics
							&& fabs(List[j].physics-List[j+1].physics) > 1E-6)
						{T = List[j];List[j] = List[j+1];List[j+1] = T;}
						else if(fabs(List[j].physics-List[j+1].physics) <= 1E-6)
						{
							if(List[j].english < List[j+1].english
								&& fabs(List[j].english-List[j+1].english) > 1E-6)
							{T = List[j];List[j] = List[j+1];List[j+1] = T;}
							else if(fabs(List[j].english-List[j+1].english) <= 1E-6)
							{
								std::istringstream str1(List[j].number);
								std::istringstream str2(List[j+1].number);
								long l1,l2;
								str1 >> l1; str2 >> l2;
								if(l1 < l2
									&& fabs(l1-l2) > 1E-6)
								{T = List[j];List[j] = List[j+1];List[j+1] = T;}
							}
						}
					}
				}
			}
		}
		WPARAM wParam = CMSG;
		::PostMessage(::GetParent(m_hWnd),WM_UPDATE_MSG,wParam,0);
	}
}

void SORT::OnNum() 
{
	// TODO: Add your control notification handler code here
	if(List.size() != 0)
	{
		int i,j;Student T;
		for(i = 0;i < (int)List.size()-1;i++)
		{
			for(j = 0;j < (int)List.size()-1-i;j++)
			{
				std::istringstream str1(List[j].number);
				std::istringstream str2(List[j+1].number);
				long l1,l2;
				str1 >> l1; str2 >> l2;
				if(l1 > l2
					&& fabs(l1-l2) > 1E-6)
				{T = List[j];List[j] = List[j+1];List[j+1] = T;}
			}
		}
		WPARAM wParam = CMSG;
		::PostMessage(::GetParent(m_hWnd),WM_UPDATE_MSG,wParam,0);
	}
}

void SORT::OnMath() 
{
	// TODO: Add your control notification handler code here
	if(List.size() != 0)
	{
		int i,j;Student T;
		for(i = 0;i < (int)List.size()-1;i++)
		{
			for(j = 0;j < (int)List.size()-1-i;j++)
			{
				if(List[j].math < List[j+1].math
					&& fabs(List[j].math-List[j+1].math) > 1E-6)
				{T = List[j];List[j] = List[j+1];List[j+1] = T;}
			}
		}
		WPARAM wParam = CMSG;
		::PostMessage(::GetParent(m_hWnd),WM_UPDATE_MSG,wParam,0);
	}
}

void SORT::OnPhysics() 
{
	// TODO: Add your control notification handler code here
	if(List.size() != 0)
	{
		int i,j;Student T;
		for(i = 0;i < (int)List.size()-1;i++)
		{
			for(j = 0;j < (int)List.size()-1-i;j++)
			{
				if(List[j].physics < List[j+1].physics
					&& fabs(List[j].physics-List[j+1].physics) > 1E-6)
				{T = List[j];List[j] = List[j+1];List[j+1] = T;}
			}
		}
		WPARAM wParam = CMSG;
		::PostMessage(::GetParent(m_hWnd),WM_UPDATE_MSG,wParam,0);
	}
}

void SORT::OnEnglish() 
{
	// TODO: Add your control notification handler code here
	if(List.size() != 0)
	{
		int i,j;Student T;
		for(i = 0;i < (int)List.size()-1;i++)
		{
			for(j = 0;j < (int)List.size()-1-i;j++)
			{
				if(List[j].english < List[j+1].english
					&& fabs(List[j].english-List[j+1].english) > 1E-6)
				{T = List[j];List[j] = List[j+1];List[j+1] = T;}
			}
		}
		WPARAM wParam = CMSG;
		::PostMessage(::GetParent(m_hWnd),WM_UPDATE_MSG,wParam,0);
	}
}
