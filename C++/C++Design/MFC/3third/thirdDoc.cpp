// thirdDoc.cpp : implementation of the CThirdDoc class
//

#include "stdafx.h"
#include "third.h"

#include "thirdDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThirdDoc

IMPLEMENT_DYNCREATE(CThirdDoc, CDocument)

BEGIN_MESSAGE_MAP(CThirdDoc, CDocument)
	//{{AFX_MSG_MAP(CThirdDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThirdDoc construction/destruction

CThirdDoc::CThirdDoc()
{
	// TODO: add one-time construction code here

}

CThirdDoc::~CThirdDoc()
{
}

BOOL CThirdDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CThirdDoc serialization

void CThirdDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CThirdDoc diagnostics

#ifdef _DEBUG
void CThirdDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CThirdDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CThirdDoc commands
