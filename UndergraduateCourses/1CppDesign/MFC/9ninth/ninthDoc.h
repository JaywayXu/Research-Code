// ninthDoc.h : interface of the CNinthDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NINTHDOC_H__6D0AE860_70A2_4A32_A13C_2DD5D516F1BE__INCLUDED_)
#define AFX_NINTHDOC_H__6D0AE860_70A2_4A32_A13C_2DD5D516F1BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CNinthDoc : public CDocument
{
protected: // create from serialization only
	CNinthDoc();
	DECLARE_DYNCREATE(CNinthDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNinthDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNinthDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNinthDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NINTHDOC_H__6D0AE860_70A2_4A32_A13C_2DD5D516F1BE__INCLUDED_)
