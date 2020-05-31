// firstDoc.h : interface of the CFirstDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIRSTDOC_H__01BA9B9E_3579_48DE_B15A_7F7037BF7D57__INCLUDED_)
#define AFX_FIRSTDOC_H__01BA9B9E_3579_48DE_B15A_7F7037BF7D57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFirstDoc : public CDocument
{
protected: // create from serialization only
	CFirstDoc();
	DECLARE_DYNCREATE(CFirstDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFirstDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFirstDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFirstDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIRSTDOC_H__01BA9B9E_3579_48DE_B15A_7F7037BF7D57__INCLUDED_)
