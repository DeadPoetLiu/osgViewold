// StereoDialog.cpp : implementation file
//

#include "stdafx.h"
#include "osgView.h"
#include "StereoDialog.h"
#include "afxdialogex.h"
#include <fstream>

// CStereoDialog dialog

IMPLEMENT_DYNAMIC(CStereoDialog, CDialog)

CStereoDialog::CStereoDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CStereoDialog::IDD, pParent),stereoMode(2)
{

}

CStereoDialog::~CStereoDialog()
{
}

void CStereoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX,IDC_COMBO1,stereoMode);
	/* std::ofstream out;
	out.open("out.txt",std::ofstream::out|std::ofstream::app);
	out<<"exchange"<<std::endl;
	out<<stereoMode<<std::endl;
	out.close();*/
}


BEGIN_MESSAGE_MAP(CStereoDialog, CDialog)
END_MESSAGE_MAP()


// CStereoDialog message handlers
