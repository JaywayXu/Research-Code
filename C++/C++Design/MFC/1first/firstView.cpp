// firstView.cpp : implementation of the CFirstView class
//

#include "stdafx.h"
#include "first.h"

#include "firstDoc.h"
#include "firstView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFirstView

IMPLEMENT_DYNCREATE(CFirstView, CView)

BEGIN_MESSAGE_MAP(CFirstView, CView)
	//{{AFX_MSG_MAP(CFirstView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_MENUITEM32771,OnClick)
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFirstView construction/destruction

CFirstView::CFirstView()
{
	// TODO: add construction code here

}

CFirstView::~CFirstView()
{
}

BOOL CFirstView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFirstView drawing

void CFirstView::OnDraw(CDC* pDC)
{
	CFirstDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CFirstView printing

BOOL CFirstView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFirstView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFirstView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CFirstView::OnLButtonDown(UINT nFlags,CPoint point)
{
	MessageBox("clicked!");
}

void CFirstView::OnClick()
{
	MessageBox("Congratulations!");
}

/////////////////////////////////////////////////////////////////////////////
// CFirstView diagnostics

#ifdef _DEBUG
void CFirstView::AssertValid() const
{
	CView::AssertValid();
}

void CFirstView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFirstDoc* CFirstView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFirstDoc)));
	return (CFirstDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFirstView message handlers
