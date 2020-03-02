// ninthDoc.cpp : implementation of the CNinthDoc class
//

#include "stdafx.h"
#include "ninth.h"

#include "ninthDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNinthDoc

IMPLEMENT_DYNCREATE(CNinthDoc, CDocument)

BEGIN_MESSAGE_MAP(CNinthDoc, CDocument)
	//{{AFX_MSG_MAP(CNinthDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNinthDoc construction/destruction

CNinthDoc::CNinthDoc()
{
	// TODO: add one-time construction code here

}

CNinthDoc::~CNinthDoc()
{
}

BOOL CNinthDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CNinthDoc serialization

void CNinthDoc::Serialize(CArchive& ar)
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
// CNinthDoc diagnostics

#ifdef _DEBUG
void CNinthDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNinthDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNinthDoc commands
