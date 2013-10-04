#pragma once


// CStereoDialog dialog

class CStereoDialog : public CDialog
{
	DECLARE_DYNAMIC(CStereoDialog)

public:
	CStereoDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CStereoDialog();
	int stereoMode;
// Dialog Data
	enum { IDD = IDD_Stereo };

public:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
