// thirdView.cpp : implementation of the CThirdView class
//

#include "stdafx.h"
#include "third.h"

#include "thirdDoc.h"
#include "thirdView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThirdView

IMPLEMENT_DYNCREATE(CThirdView, CView)

BEGIN_MESSAGE_MAP(CThirdView, CView)
	//{{AFX_MSG_MAP(CThirdView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThirdView construction/destruction

CThirdView::CThirdView()
{
	// TODO: add construction code here

}

CThirdView::~CThirdView()
{
}

BOOL CThirdView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CThirdView drawing

void CThirdView::OnDraw(CDC* pDC)
{
	CThirdDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CThirdView printing

BOOL CThirdView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CThirdView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CThirdView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CThirdView::OnLButtonDown(UINT nFlags,CPoint point)
{
	nm_point = point;

	CView::OnLButtonDown(nFlags,point);
}

void CThirdView::OnLButtonUp(UINT nFlags,CPoint point)
{
	/*
	CDC *pDC = GetDC();
	pDC->MoveTo(nm_point);
	pDC->LineTo(point);
	ReleaseDC(pDC);
	*/
	
	CPen pen(PS_SOLID,1,RGB(252,32,156));
	CClientDC dc(this);
	CPen *pOldPen = dc.SelectObject(&pen);
	dc.MoveTo(nm_point);
	dc.LineTo(point);
	dc.SelectObject(pOldPen);
	
	//CClientDC dc(this);
	CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	CBrush *pOldBrush = dc.SelectObject(pBrush);
	dc.Rectangle(CRect(nm_point,point));
	dc.SelectObject(pOldBrush);

	CView::OnLButtonDown(nFlags,point);
}

/////////////////////////////////////////////////////////////////////////////
// CThirdView diagnostics

#ifdef _DEBUG
void CThirdView::AssertValid() const
{
	CView::AssertValid();
}

void CThirdView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CThirdDoc* CThirdView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CThirdDoc)));
	return (CThirdDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CThirdView message handlers
