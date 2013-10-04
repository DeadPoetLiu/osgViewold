#pragma once


// CMovementDialog dialog

class CMovementDialog : public CDialog
{
	DECLARE_DYNAMIC(CMovementDialog)

public:
	CMovementDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMovementDialog();

// Dialog Data
	enum { IDD = IDD_Movement };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
