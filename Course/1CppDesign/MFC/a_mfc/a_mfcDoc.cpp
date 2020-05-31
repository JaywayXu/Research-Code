// a_mfcDoc.cpp : implementation of the CA_mfcDoc class
//

#include "stdafx.h"
#include "a_mfc.h"

#include "a_mfcDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CA_mfcDoc

IMPLEMENT_DYNCREATE(CA_mfcDoc, CDocument)

BEGIN_MESSAGE_MAP(CA_mfcDoc, CDocument)
	//{{AFX_MSG_MAP(CA_mfcDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CA_mfcDoc construction/destruction

CA_mfcDoc::CA_mfcDoc()
{
	// TODO: add one-time construction code here

}

CA_mfcDoc::~CA_mfcDoc()
{
}

BOOL CA_mfcDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CA_mfcDoc serialization

void CA_mfcDoc::Serialize(CArchive& ar)
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
// CA_mfcDoc diagnostics

#ifdef _DEBUG
void CA_mfcDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CA_mfcDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CA_mfcDoc commands
