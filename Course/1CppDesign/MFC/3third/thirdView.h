// thirdView.h : interface of the CThirdView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_THIRDVIEW_H__5A073F15_01C4_4F6B_BB35_63FE0484F963__INCLUDED_)
#define AFX_THIRDVIEW_H__5A073F15_01C4_4F6B_BB35_63FE0484F963__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CThirdView : public CView
{
protected: // create from serialization only
	CThirdView();
	DECLARE_DYNCREATE(CThirdView)

// Attributes
public:
	CThirdDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThirdView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CThirdView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CThirdView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void OnLButtonDown(UINT nFlags,CPoint point);
	void OnLButtonUp(UINT nFlags,CPoint point);

private:
	CPoint nm_point;
};

#ifndef _DEBUG  // debug version in thirdView.cpp
inline CThirdDoc* CThirdView::GetDocument()
   { return (CThirdDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THIRDVIEW_H__5A073F15_01C4_4F6B_BB35_63FE0484F963__INCLUDED_)
