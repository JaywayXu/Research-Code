// thirdDoc.h : interface of the CThirdDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_THIRDDOC_H__232EEFD1_9624_4962_9027_F49553B0C9CD__INCLUDED_)
#define AFX_THIRDDOC_H__232EEFD1_9624_4962_9027_F49553B0C9CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CThirdDoc : public CDocument
{
protected: // create from serialization only
	CThirdDoc();
	DECLARE_DYNCREATE(CThirdDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThirdDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CThirdDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CThirdDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THIRDDOC_H__232EEFD1_9624_4962_9027_F49553B0C9CD__INCLUDED_)
