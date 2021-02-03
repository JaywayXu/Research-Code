// secondView.cpp : implementation of the CSecondView class
//

#include "stdafx.h"
#include "second.h"

#include "secondDoc.h"
#include "secondView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSecondView

IMPLEMENT_DYNCREATE(CSecondView, CView)

BEGIN_MESSAGE_MAP(CSecondView, CView)
	//{{AFX_MSG_MAP(CSecondView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSecondView construction/destruction

CSecondView::CSecondView()
{
	// TODO: add construction code here

}

CSecondView::~CSecondView()
{
}

BOOL CSecondView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSecondView drawing

void CSecondView::OnDraw(CDC* pDC)
{
	CSecondDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	pDC->MoveTo(30,30);
	pDC->LineTo(300,400);
	pDC->LineTo(280,5);
	pDC->LineTo(30,30);
	ReleaseDC(pDC);

}

/////////////////////////////////////////////////////////////////////////////
// CSecondView printing

BOOL CSecondView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSecondView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSecondView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSecondView diagnostics

#ifdef _DEBUG
void CSecondView::AssertValid() const
{
	CView::AssertValid();
}

void CSecondView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSecondDoc* CSecondView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSecondDoc)));
	return (CSecondDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSecondView message handlers
