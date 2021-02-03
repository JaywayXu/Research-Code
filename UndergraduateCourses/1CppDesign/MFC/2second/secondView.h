// secondView.h : interface of the CSecondView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SECONDVIEW_H__C707F187_514C_4BD7_AE5A_F1CB2B7FCA2B__INCLUDED_)
#define AFX_SECONDVIEW_H__C707F187_514C_4BD7_AE5A_F1CB2B7FCA2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSecondView : public CView
{
protected: // create from serialization only
	CSecondView();
	DECLARE_DYNCREATE(CSecondView)

// Attributes
public:
	CSecondDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSecondView)
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
	virtual ~CSecondView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSecondView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in secondView.cpp
inline CSecondDoc* CSecondView::GetDocument()
   { return (CSecondDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SECONDVIEW_H__C707F187_514C_4BD7_AE5A_F1CB2B7FCA2B__INCLUDED_)
