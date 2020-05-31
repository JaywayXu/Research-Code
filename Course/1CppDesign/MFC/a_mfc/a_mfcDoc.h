// a_mfcDoc.h : interface of the CA_mfcDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_A_MFCDOC_H__E4F142B6_9E1D_4AF6_A52E_7A967D3D8A2F__INCLUDED_)
#define AFX_A_MFCDOC_H__E4F142B6_9E1D_4AF6_A52E_7A967D3D8A2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CA_mfcDoc : public CDocument
{
protected: // create from serialization only
	CA_mfcDoc();
	DECLARE_DYNCREATE(CA_mfcDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CA_mfcDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CA_mfcDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CA_mfcDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_A_MFCDOC_H__E4F142B6_9E1D_4AF6_A52E_7A967D3D8A2F__INCLUDED_)
