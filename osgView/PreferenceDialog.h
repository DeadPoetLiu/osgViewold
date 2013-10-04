#pragma once
#include "MovementDialog.h"
#include "StereoDialog.h"
#include "afxcmn.h"

// CPreferenceDialog dialog

class CPreferenceDialog : public CDialog
{
	DECLARE_DYNAMIC(CPreferenceDialog)

public:
	CPreferenceDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPreferenceDialog();
	CStereoDialog stereo;
	CMovementDialog movement;
	void UpdateVisibleWindow();
// Dialog Data
	enum { IDD = IDD_Preference };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CTabCtrl tab;
	virtual BOOL OnInitDialog();
};
