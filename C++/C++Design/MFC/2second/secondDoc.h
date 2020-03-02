// secondDoc.h : interface of the CSecondDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SECONDDOC_H__709E1B50_70DA_471C_AE29_70879D77476B__INCLUDED_)
#define AFX_SECONDDOC_H__709E1B50_70DA_471C_AE29_70879D77476B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSecondDoc : public CDocument
{
protected: // create from serialization only
	CSecondDoc();
	DECLARE_DYNCREATE(CSecondDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSecondDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSecondDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSecondDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SECONDDOC_H__709E1B50_70DA_471C_AE29_70879D77476B__INCLUDED_)
