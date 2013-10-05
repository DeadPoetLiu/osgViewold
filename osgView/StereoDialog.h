#pragma once
#include "parameter.h"

// CStereoDialog dialog

class CStereoDialog : public CDialog
{
	DECLARE_DYNAMIC(CStereoDialog)

public:
	CStereoDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CStereoDialog();
	StereoParameter  sp;
// Dialog Data
	enum { IDD = IDD_Stereo };
	void OK();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	DECLARE_MESSAGE_MAP()
};
