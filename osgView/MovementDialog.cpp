// MovementDialog.cpp : implementation file
//

#include "stdafx.h"
#include "osgView.h"
#include "MovementDialog.h"
#include "afxdialogex.h"


// CMovementDialog dialog

IMPLEMENT_DYNAMIC(CMovementDialog, CDialog)

CMovementDialog::CMovementDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMovementDialog::IDD, pParent)
{

}

CMovementDialog::~CMovementDialog()
{
}

void CMovementDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMovementDialog, CDialog)
END_MESSAGE_MAP()


// CMovementDialog message handlers
