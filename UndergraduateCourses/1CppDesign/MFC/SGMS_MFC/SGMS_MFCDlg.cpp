// SGMS_MFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SGMS_MFC.h"
#include "SGMS_MFCDlg.h"

#include "SGMS.h"
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#define WM_UPDATE_MSG (WM_USER + 100)
#define CMSG 2333
#define N 2000

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

std::vector<Student> List;

/////////////////////////////////////////////////////////////////////////////
// CSGMS_MFCDlg dialog

CSGMS_MFCDlg::CSGMS_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSGMS_MFCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSGMS_MFCDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CSGMS_MFCDlg::~CSGMS_MFCDlg()
{
	if (NULL != adddlg) delete adddlg;
	if (NULL != deldlg) delete deldlg;
	if (NULL != changedlg) delete changedlg;
	if (NULL != searchdlg) delete searchdlg;
	if (NULL != sortdlg) delete sortdlg;
}

void CSGMS_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSGMS_MFCDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSGMS_MFCDlg, CDialog)
	//{{AFX_MSG_MAP(CSGMS_MFCDlg)
	ON_MESSAGE(WM_UPDATE_MSG, OnStrUpdate)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Read, OnRead)
	ON_BN_CLICKED(IDC_BUTTON_Write, OnWrite)
	ON_BN_CLICKED(IDC_BUTTON_Add, OnAdd)
	ON_BN_CLICKED(IDC_BUTTON_Del, OnDel)
	ON_BN_CLICKED(IDC_BUTTON_Change, OnChange)
	ON_BN_CLICKED(IDC_BUTTON_Search, OnSearch)
	ON_BN_CLICKED(IDC_BUTTON_Analyse, OnAnalyse)
	ON_BN_CLICKED(IDC_BUTTON_Sort, OnSort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSGMS_MFCDlg message handlers

BOOL CSGMS_MFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	sortdlg = NULL;
	adddlg = NULL;
	deldlg = NULL;
	changedlg = NULL;
	searchdlg = NULL;

	GetDlgItem(IDC_BUTTON_Write)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_Add)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_Del)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_Change)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_Search)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_Analyse)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_Sort)->EnableWindow(FALSE);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSGMS_MFCDlg::OnPaint() 
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
HCURSOR CSGMS_MFCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSGMS_MFCDlg::OnRead() 
{
	// TODO: Add your control notification handler code here
	//清空vecotr
	List.clear();

	/*
	//第一种实现，先录取到vector，再从vector输出到ListBox
	//会出现读取错误，多读一行
	std::ifstream ifile("Grade.txt");
	std::string temp_number,temp_name;
	double temp_math,temp_physics,temp_english;
	if (ifile.is_open())
	{
		while(1)
		{
			if(ifile.eof())break;
			else 
			{
				ifile >> temp_number >> temp_name >> temp_math >> temp_physics >> temp_english;
				Student temp_stu(temp_number,temp_name,temp_math,temp_physics,temp_english);
				List.push_back(temp_stu);
			}
		}
		ifile.close();
		CString teststr = List[0].getstr().c_str();
	}
	else MessageBox("文件无法打开！");

	printstrlist();
	*/
	
	//第二种实现，先录取到ListBox再转换进vector
	int i;
	int Count = m_list.GetCount();
	for (i = Count; i>=0; i--)
	{
		m_list.DeleteString(i);
	}

	std::ifstream ifile("Grade.txt");
	char line[70];
	if (ifile.is_open())
	{
		while(ifile.getline(line,70))
		{
			if(ifile.eof())break;
			m_list.AddString(line);
		}
		ifile.close();
	}
	else MessageBox("文件无法打开！");

	CString allline[N];
	std::string datastr[N];
	int len;
	Count = m_list.GetCount();
	for(i = 0; i<Count; i++)
	{
		len = m_list.GetTextLen(i);
		m_list.GetText(i, allline[i].GetBuffer(len));
		allline[i].ReleaseBuffer();
		datastr[i] = allline[i].GetBuffer(allline[i].GetLength());
		std::istringstream istr(datastr[i]);
		std::string number, name;double math,physics,english;
		istr >> number >> name >> math >> physics >> english;
		Student temp_stu(number,name,math,physics,english);
        List.push_back(temp_stu);
	}
	GetDlgItem(IDC_BUTTON_Read)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_Write)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_Add)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_Del)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_Change)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_Search)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_Analyse)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_Sort)->EnableWindow(TRUE);
}

void CSGMS_MFCDlg::OnWrite() 
{
	// TODO: Add your control notification handler code here
	//获取内容
	CString line[N];
	int len, i;
	int Count = m_list.GetCount();
	for(i = 0; i<Count; i++)
	{
		len = m_list.GetTextLen(i);
		m_list.GetText(i, line[i].GetBuffer(len));
		line[i].ReleaseBuffer();
	}
	//for(i = 0; i<Count; i++) MessageBox(line[i]);
	//写入
	std::ofstream ofile("Grade.txt");
	if (ofile.is_open())
	{
		for(i = 0; i<Count; i++)
		{
			std::string str(line[i].GetBuffer(line[i].GetLength()));
			ofile << str << std::endl;
		}
		ofile.close();
		List.clear();
		printstrlist();
		GetDlgItem(IDC_BUTTON_Read)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_Write)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_Add)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_Del)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_Change)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_Search)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_Analyse)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_Sort)->EnableWindow(FALSE);
		MessageBox("写入成功！");
	}
	else MessageBox("文件无法打开！");
}

void CSGMS_MFCDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here
	// ADD dlg;
	// dlg.DoModal();

	//非模态对话框
	if (NULL == adddlg)   
    {   
        adddlg = new ADD();   
        adddlg->Create(IDD_ADD_DIALOG, this);   
    } 
    adddlg->ShowWindow(SW_SHOW);

	// //清空ListBox
	// int i;
	// int Count = m_list.GetCount();
	// for (i = Count; i>=0; i--)
	// {
	// 	m_list.DeleteString(i);
	// }

	// for(std::vector<Student>::iterator x = List.begin();x != List.end();x++)
	// {
	// 	CString str = (*x).getstr().c_str();
	// 	m_list.AddString(str);
	// }
}

void CSGMS_MFCDlg::OnDel() 
{
	// TODO: Add your control notification handler code here
	// Del dlg;
	// dlg.DoModal();

	if (NULL == deldlg)   
    {   
        deldlg = new Del();   
        deldlg->Create(IDD_DEL_DIALOG, this);   
    } 
    deldlg->ShowWindow(SW_SHOW);
}

void CSGMS_MFCDlg::OnChange() 
{
	// TODO: Add your control notification handler code here
	// Change dlg;
	// dlg.DoModal();

	if (NULL == changedlg)   
    {   
        changedlg = new Change();   
        changedlg->Create(IDD_HANGE_DIALOG, this);   
    } 
    changedlg->ShowWindow(SW_SHOW);
}

void CSGMS_MFCDlg::OnSearch() 
{
	// TODO: Add your control notification handler code here
	// Search dlg;
	// dlg.DoModal();

	if (NULL == searchdlg)   
    {   
        searchdlg = new Search();   
        searchdlg->Create(IDD_SEARCH_DIALOG, this);   
    } 
    searchdlg->ShowWindow(SW_SHOW);
}

void CSGMS_MFCDlg::OnAnalyse() 
{
	// TODO: Add your control notification handler code here
	double math_average = 0,english_average = 0,physics_average = 0,average_average = 0;
    double math_dev = 0,english_dev = 0,physics_dev = 0,average_dev = 0;
    double math_qua = 0,english_qua = 0,physics_qua = 0,average_qua = 0;

    all_average(math_average,physics_average,english_average,average_average);
    standard_deviation(math_dev,physics_dev,english_dev,average_dev,
        math_average,physics_average,english_average,average_average);
    qualified_rate(math_qua,physics_qua,english_qua,average_qua);

	CString ave; ave.Format("平均成绩：\n数学：%.1f\n物理：%.1f\n英语：%.1f\n总体：%.1f\n\
	\n标准差：\n数学：%.3f\n物理：%.3f\n英语：%.3f\n总体：%.3f\n\
	\n合格率：\n数学：%.3f\n物理：%.3f\n英语：%.3f\n总体：%.3f",
	 math_average,physics_average,english_average,average_average,
	 math_dev,physics_dev,english_dev,average_dev,
	 math_qua,physics_qua,english_qua,average_qua);
	MessageBox(ave);
}

void CSGMS_MFCDlg::OnSort() 
{
	// TODO: Add your control notification handler code here
	// SORT dlg;
	// dlg.DoModal();

	//非模态对话框
	if (NULL == sortdlg)   
    {   
        sortdlg = new SORT();   
        sortdlg->Create(IDD_SORT_DIALOG, this);   
    } 
    sortdlg->ShowWindow(SW_SHOW);
}

void CSGMS_MFCDlg::printstrlist()
{
	//清空ListBox
	int i;
	int Count = m_list.GetCount();
	for (i = Count; i>=0; i--)
	{
		m_list.DeleteString(i);
	}

	for(std::vector<Student>::iterator x = List.begin();x != List.end();x++)
	{
		CString str = (*x).getstr().c_str();
		m_list.AddString(str);
	}
}

void CSGMS_MFCDlg::all_average(
    double &math_average,double &physics_average,double &english_average,double &average_average)
{
    for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
    {
        math_average += (*i).math;
        physics_average += (*i).physics;
        english_average += (*i).english;
        average_average += (*i).get_average();
    }
    math_average /= List.size();
    physics_average /= List.size();
    english_average /= List.size();
    average_average /= List.size();
}

void CSGMS_MFCDlg::standard_deviation(
    double &math_dev,double &physics_dev,double &english_dev,double &average_dev,
    double math_average,double physics_average,double english_average,double average_average)
{  
    for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
    {
        math_dev += ((*i).math - math_average)*((*i).math - math_average);
        physics_dev += ((*i).physics - physics_average)*((*i).physics - physics_average);
        english_dev += ((*i).english - english_average)*((*i).english - english_average);
        average_dev += ((*i).get_average() - average_average)*((*i).get_average() - average_average);
    }
    math_dev = sqrt(math_dev/List.size());
    physics_dev = sqrt(physics_dev/List.size());
    english_dev = sqrt(english_dev/List.size());
    average_dev = sqrt(average_dev/List.size());
}

void CSGMS_MFCDlg::qualified_rate(
    double &math_qua,double &physics_qua,double &english_qua,double &average_qua)
{
    for(std::vector<Student>::iterator i = List.begin();i != List.end();i++)
    {
        if((*i).math >= 60)math_qua += 1;
        if((*i).physics >= 60)physics_qua += 1;
        if((*i).english >= 60)english_qua += 1;
        if((*i).get_average() >= 60)average_qua += 1;
    }
    math_qua = (math_qua/List.size());
    physics_qua = (physics_qua/List.size());
    english_qua = (english_qua/List.size());
    average_qua = (average_qua/List.size());
}

LRESULT CSGMS_MFCDlg::OnStrUpdate(WPARAM wParam, LPARAM lParam)
{
	if (wParam == CMSG)
	{
		printstrlist();
	}
	return 0;
}
