// PreferenceDialog.cpp : implementation file
//

#include "stdafx.h"
#include "osgView.h"
#include "PreferenceDialog.h"
#include "afxdialogex.h"


// CPreferenceDialog dialog

IMPLEMENT_DYNAMIC(CPreferenceDialog, CDialog)

CPreferenceDialog::CPreferenceDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPreferenceDialog::IDD, pParent)
{

}

CPreferenceDialog::~CPreferenceDialog()
{
}

void CPreferenceDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, tab);
	//stereo.DoDataExchange(pDX);


}


BEGIN_MESSAGE_MAP(CPreferenceDialog, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CPreferenceDialog::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CPreferenceDialog message handlers


void CPreferenceDialog::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	 UpdateVisibleWindow();
	*pResult = 0;
}


BOOL CPreferenceDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	tab.InsertItem(TCIF_TEXT, 0, _T("Stereo"), 0,0,0,0);
     tab.InsertItem(TCIF_TEXT, 1, _T("Movement"), 0,0,0,0);
	 stereo.Create(CStereoDialog::IDD, this);
	 movement.Create(CMovementDialog::IDD, this);
	 stereo.SetWindowPos(GetDlgItem(IDC_TAB1), 0, 0, 0, 0, 
      SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
   movement.SetWindowPos(GetDlgItem(IDC_TAB1), 0, 0, 0, 0, 
      SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	 UpdateVisibleWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPreferenceDialog::UpdateVisibleWindow()
{
   int current = tab.GetCurSel();

   stereo.ShowWindow(current == 0 ? SW_SHOW : SW_HIDE);
   movement.ShowWindow(current == 1 ? SW_SHOW : SW_HIDE);

}

void CPreferenceDialog::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	

	CDialog::OnOK();
	stereo.OK();
}
