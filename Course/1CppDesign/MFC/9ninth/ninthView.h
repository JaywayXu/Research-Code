// ninthView.h : interface of the CNinthView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NINTHVIEW_H__2886E891_B9F8_4F7B_A556_BC1B66A3832D__INCLUDED_)
#define AFX_NINTHVIEW_H__2886E891_B9F8_4F7B_A556_BC1B66A3832D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CNinthView : public CView
{
protected: // create from serialization only
	CNinthView();
	DECLARE_DYNCREATE(CNinthView)

// Attributes
public:
	CNinthDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNinthView)
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
	virtual ~CNinthView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNinthView)
	afx_msg void OnMenuitem32771();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int arry[16];
	int rand_rgb[16][3];
};

#ifndef _DEBUG  // debug version in ninthView.cpp
inline CNinthDoc* CNinthView::GetDocument()
   { return (CNinthDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NINTHVIEW_H__2886E891_B9F8_4F7B_A556_BC1B66A3832D__INCLUDED_)
