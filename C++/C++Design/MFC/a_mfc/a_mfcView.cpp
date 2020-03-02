// a_mfcView.cpp : implementation of the CA_mfcView class
//

#include "stdafx.h"
#include "a_mfc.h"

#include "a_mfcDoc.h"
#include "a_mfcView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CA_mfcView

IMPLEMENT_DYNCREATE(CA_mfcView, CView)

BEGIN_MESSAGE_MAP(CA_mfcView, CView)
	//{{AFX_MSG_MAP(CA_mfcView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_COMMAND(ID_MENUITEM32772,OnC1)
    ON_COMMAND(TEST_TEST,OnCTest)
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CA_mfcView construction/destruction

CA_mfcView::CA_mfcView()
{
	// TODO: add construction code heres
}

CA_mfcView::~CA_mfcView()
{
}

BOOL CA_mfcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CA_mfcView drawing

void CA_mfcView::OnDraw(CDC* pDC)
{
	CA_mfcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CA_mfcView printing

BOOL CA_mfcView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CA_mfcView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CA_mfcView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CA_mfcView diagnostics

#ifdef _DEBUG
void CA_mfcView::AssertValid() const
{
	CView::AssertValid();
}

void CA_mfcView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CA_mfcDoc* CA_mfcView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CA_mfcDoc)));
	return (CA_mfcDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CA_mfcView message handlers

void CA_mfcView::OnLButtonDown(UINT nFLages,CPoint Point)
{
    nm_pOrigin = Point;
    //nm_button = TRUE;
	//MessageBox("Clicked!");
 
    CView::OnLButtonDown(nFLages, Point);
}

void CA_mfcView::OnLButtonUp(UINT nFlages,CPoint Point)
{
    /*
	HDC hdc;
	hdc = ::GetDC(m_hWnd);
	MoveToEx(hdc,nm_pOrigin.x,nm_pOrigin.y,NULL);
	LineTo(hdc,Point.x,Point.y);
	::ReleaseDC(m_hWnd,hdc);
    */
    /*
    CPen pen(PS_SOLID,5,RGB(0,255,0));
    CClientDC dc(this);
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.MoveTo(nm_pOrigin);
    dc.LineTo(Point);
    dc.SelectObject(pOldPen);
    */
    //nm_button = FALSE;

    CBitmap bitmap;
	//加载位图资源
	bitmap.LoadBitmap(IDB_BITMAP2);
 	//创建并获取设备描述表
	CBrush brush(&bitmap);
	CClientDC dc(this);
	//利用位图画刷填充矩形区域
	dc.FillRect(CRect(nm_pOrigin,Point),&brush);
 
	CView::OnLButtonUp(nFlages, Point);
}

void CA_mfcView::OnMouseMove(UINT nFlages,CPoint Point)
{
    /*
    if(TRUE == nm_button)
    {
        CPen pen(PS_SOLID,1,RGB(144,133,233));
        CClientDC dc(this);
        CPen* pOldPen = dc.SelectObject(&pen);
        dc.MoveTo(nm_pOrigin);
        dc.LineTo(Point);
        dc.SelectObject(pOldPen);
        nm_pOrigin = Point;
    }*/
}

void CA_mfcView::OnC1() {
    MessageBox("OK");
}

void CA_mfcView::OnCTest(){

}
