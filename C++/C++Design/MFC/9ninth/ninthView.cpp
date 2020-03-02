// ninthView.cpp : implementation of the CNinthView class
//

#include "stdafx.h"
#include "ninth.h"

#include "ninthDoc.h"
#include "ninthView.h"

#include <time.h>
#include <cmath>

#define O_X 40
#define O_Y 500
#define Y_T 50
#define X_T 20

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNinthView

IMPLEMENT_DYNCREATE(CNinthView, CView)

BEGIN_MESSAGE_MAP(CNinthView, CView)
	//{{AFX_MSG_MAP(CNinthView)
	ON_COMMAND(ID_MENUITEM32771, OnMenuitem32771)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNinthView construction/destruction

CNinthView::CNinthView()
{
	// TODO: add construction code here

}

CNinthView::~CNinthView()
{
}

BOOL CNinthView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CNinthView drawing

void CNinthView::OnDraw(CDC* pDC)
{
	CNinthDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	//坐标轴
	CPen pen(PS_SOLID,1,RGB(0,0,0));
	CClientDC dc(this);
	CPen *pOldPen = dc.SelectObject(&pen);
	int x_top = (O_X+33*X_T);
	int y_bot = (O_Y-7*Y_T);
	CPoint O(O_X, O_Y);
	CPoint X(x_top, O_Y);
	CPoint Y(O_X, y_bot);
	dc.MoveTo(O);dc.LineTo(Y);dc.MoveTo(O);dc.LineTo(X);
	dc.MoveTo(Y);dc.LineTo(Y.x+10, Y.y+15);
	dc.MoveTo(Y);dc.LineTo(Y.x-10, Y.y+15);
	dc.MoveTo(X);dc.LineTo(X.x-15, X.y+10);
	dc.MoveTo(X);dc.LineTo(X.x-15, X.y-10);
	int i;
	for (i = O_Y; i>y_bot; i -= Y_T)
		{dc.MoveTo(O_X, i);dc.LineTo(O_X+10, i);}
	for (i = O_Y-Y_T/2; i>y_bot; i -= Y_T)
		{dc.MoveTo(O_X, i);dc.LineTo(O_X+4, i);}
	// for (i = O_X; i< x_top; i += X_T)
	// 	{dc.MoveTo(i, O_Y);dc.LineTo(i, O_Y-10);}
	dc.SelectObject(pOldPen);

	//画矩形
	int j = 0;
	for (i = O.x+X_T; i<x_top; i += 2*X_T)
	{
		CBrush brush,*pOldBrush;
		brush.CreateSolidBrush(RGB(rand_rgb[j][0],rand_rgb[j][1],rand_rgb[j][2]));
		pOldBrush = dc.SelectObject(&brush);
		dc.Rectangle(i, O.y-arry[j]*Y_T/10, i+X_T, O.y);
		dc.SelectObject(pOldBrush);
		brush.DeleteObject();
		CString temps;
		temps.Format("%d", arry[j]);
		dc.TextOut(i+2, O.y-arry[j]*Y_T/10-20, temps);
		j++;
	}

	//饼图
	POINT m_COpt = {900,200};
	const int m_Radius = 150;
	const int m_itemNums = 16;
	double m_percentage[16];
	for (i = 0; i<16; i++)
	{
		m_percentage[i] = (double)arry[i]/1024.0;
	}

	//CClientDC dc(this);
    //设置坐标原点
    SetViewportOrgEx(dc, m_COpt.x, m_COpt.y, NULL);

    //设置圆的外接矩形大小
    CRect pieRect(-m_Radius, -m_Radius, m_Radius, m_Radius);
    dc.Ellipse(&pieRect);

    POINT pt_start;
    POINT pt_end;

    //画饼图
    double R = m_Radius;
    const double PI = 3.1415926;
    double sum = 0;
    for (i = 0; i < m_itemNums; i++)
        sum += m_percentage[i];
    // 验证占比加起来等不等于1
    if (sum == 1)
    {
        //第一个扇形的坐标
        int angle = m_percentage[0] * 360;  //计算占的角度
        POINT pt_s_e;
        pt_start.x = (int)R; pt_start.y = 0;// pt_start = {(int)R,0};
        pt_s_e = pt_start;
        pt_end.x = int(R*cos(angle * PI / 180));
		pt_end.y = int(-R*sin(angle * PI / 180));
		// pt_end = { int(R*cos(angle * PI / 180)),int(-R*sin(angle * PI / 180)) };
		dc.SelectObject(CreateSolidBrush(RGB(rand_rgb[0][0],rand_rgb[0][1],rand_rgb[0][2]))); //上颜色
        dc.Pie(&pieRect, pt_start, pt_end);
        for (i = 1; i < m_itemNums; i++)
        {   
            pt_start = pt_end;
            angle += m_percentage[i] * 360;
			pt_end.x = int(R*cos(angle * PI / 180));
			pt_end.y = int(-R*sin(angle * PI / 180));
            // pt_end = { int(R*cos(angle * PI / 180)),int(-R*sin(angle * PI / 180)) };
            dc.SelectObject(CreateSolidBrush(RGB(rand_rgb[i][0],rand_rgb[i][1],rand_rgb[i][2]))); //上颜色
            if(i == m_itemNums - 1)
                dc.Pie(&pieRect, pt_start, pt_s_e);
            else
                dc.Pie(&pieRect, pt_start, pt_end);
        }

        // //画小矩形
        // CRect expRect;
        // int l = 0, t = 0;
        // for (i = 0; i < m_itemNums; i++)
        // {
        //     l = m_Radius + 50;
        //     t = -2*m_Radius + m_expH*i;
        //     expRect = {l,t + 10,l + m_expW,t + m_expH };
        //     dc.SelectObject(CreateSolidBrush(RGB(rand_rgb[i][0],rand_rgb[i][1],rand_rgb[i][2]))); //上颜色
        //     dc.Rectangle(&expRect);
        //     dc.TextOut(l + m_expW + 10, t + m_expH / 3, m_itemName[i]);
        // }

        // //显示百分比
        // CString s;
        // int strLen = m_itemName[0].GetLength();
        // for (int i = 0; i < m_itemNums; i++)
        // {
        //     l = -2*m_Radius - strLen*10;
        //     t = -2 * m_Radius + m_expH*i;
        //     s.Format(TEXT("%s -- %0.2f%s"), m_itemName[i],m_percentage[i] * 100,TEXT("%"));
        //     dc.TextOut(l, t + m_expH / 3, s);
        // }
    }
}

/////////////////////////////////////////////////////////////////////////////
// CNinthView printing

BOOL CNinthView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CNinthView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CNinthView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CNinthView diagnostics

#ifdef _DEBUG
void CNinthView::AssertValid() const
{
	CView::AssertValid();
}

void CNinthView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNinthDoc* CNinthView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNinthDoc)));
	return (CNinthDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNinthView message handlers

void CNinthView::OnMenuitem32771() 
{
	// TODO: Add your command handler code here
	srand(time(NULL));
	int i;
	for(i = 0; i<16; i++) arry[i] = 0;
	int ran;
	for(i = 0; i<1024; i++)
	{
		ran = rand()%256;
		if (ran<17) arry[0]++;
		else if (ran<33) arry[1]++;
		else if (ran<49) arry[2]++;
		else if (ran<65) arry[3]++;
		else if (ran<81) arry[4]++;
		else if (ran<97) arry[5]++;
		else if (ran<113) arry[6]++;
		else if (ran<129) arry[7]++;
		else if (ran<145) arry[8]++;
		else if (ran<161) arry[9]++;
		else if (ran<177) arry[10]++;
		else if (ran<193) arry[11]++;
		else if (ran<209) arry[12]++;
		else if (ran<225) arry[13]++;
		else if (ran<241) arry[14]++;
		else arry[15]++;
	}
	for (i = 0; i<16; i++)
	{
		for (int j = 0; j<3; j++)
		{
			rand_rgb[i][j] = rand()%255;
		}
	}
	// int test = 0;
	// for(i = 0; i<16; i++)
	// {
	// 	test += arry[i];
	// }
	// CString str; str.Format("%d",test);
	// MessageBox(str);
	Invalidate();
}
