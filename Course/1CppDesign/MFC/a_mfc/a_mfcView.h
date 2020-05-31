// a_mfcView.h : interface of the CA_mfcView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_A_MFCVIEW_H__185BAC50_71AD_4485_A5D7_33545D096050__INCLUDED_)
#define AFX_A_MFCVIEW_H__185BAC50_71AD_4485_A5D7_33545D096050__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CA_mfcView : public CView
{
protected: // create from serialization only
	CA_mfcView();
	DECLARE_DYNCREATE(CA_mfcView)

// Attributes
public:
	CA_mfcDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CA_mfcView)
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
	virtual ~CA_mfcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CA_mfcView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CPoint nm_pOrigin;
    BOOL nm_button;

public:
	void OnLButtonDown(UINT,CPoint);
	void OnLButtonUp(UINT,CPoint);
    void OnMouseMove(UINT,CPoint);

public:
    afx_msg void OnC1();
    afx_msg void OnCTest();
};

#ifndef _DEBUG  // debug version in a_mfcView.cpp
inline CA_mfcDoc* CA_mfcView::GetDocument()
   { return (CA_mfcDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_A_MFCVIEW_H__185BAC50_71AD_4485_A5D7_33545D096050__INCLUDED_)
