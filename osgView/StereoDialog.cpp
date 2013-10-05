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
	: CDialog(CStereoDialog::IDD, pParent)
{

}

CStereoDialog::~CStereoDialog()
{
}

void CStereoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX,IDC_CHECK1,sp.stereoDisplay);
	DDX_CBIndex(pDX,IDC_COMBO1,sp.stereoMode);
	DDX_Text(pDX,IDC_EDIT1,sp.screenWidth);
	DDX_Text(pDX,IDC_EDIT2,sp.screenHeight);
	DDX_Text(pDX,IDC_EDIT3,sp.screenDistance);
	DDX_Text(pDX,IDC_EDIT4,sp.eyeSeparation);
	/* std::ofstream out;
	out.open("out.txt",std::ofstream::out|std::ofstream::app);
	out<<"exchange"<<std::endl;
	out<<stereoMode<<std::endl;
	out.close();*/
}

void CStereoDialog::OK(){
	this->OnOK();
}

BEGIN_MESSAGE_MAP(CStereoDialog, CDialog)
END_MESSAGE_MAP()


// CStereoDialog message handlers
