// secondDoc.cpp : implementation of the CSecondDoc class
//

#include "stdafx.h"
#include "second.h"

#include "secondDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSecondDoc

IMPLEMENT_DYNCREATE(CSecondDoc, CDocument)

BEGIN_MESSAGE_MAP(CSecondDoc, CDocument)
	//{{AFX_MSG_MAP(CSecondDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSecondDoc construction/destruction

CSecondDoc::CSecondDoc()
{
	// TODO: add one-time construction code here

}

CSecondDoc::~CSecondDoc()
{
}

BOOL CSecondDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSecondDoc serialization

void CSecondDoc::Serialize(CArchive& ar)
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
// CSecondDoc diagnostics

#ifdef _DEBUG
void CSecondDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSecondDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSecondDoc commands
