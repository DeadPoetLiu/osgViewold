
// osgViewView.h : interface of the CosgViewView class
//

#pragma once
#include "parameter.h"
#include "MFC_OSG.h"
class CosgViewView : public CView
{
protected: // create from serialization only
	CosgViewView();
	DECLARE_DYNCREATE(CosgViewView)

// Attributes
public:
	CosgViewDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	 cOSG* mOSG;
	 StereoParameter sp;
	 Modes mode;
	 bool stereo;
	 bool lights;
    //HANDLE mThreadHandle;
    CRenderingThread* mThreadHandle;
// Implementation
public:
	virtual ~CosgViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions

private:void setMode(Modes m);
		osg::Matrixd home;
		std::string fn;
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEditPreferences();
	afx_msg void OnRenderingmodePointcloud();
	afx_msg void OnRenderingmodeTexture();
	afx_msg void OnRenderingmodeWireframe();
	afx_msg void OnRenderingmodeFlatlines();
	afx_msg void OnRenderingmodeFlat();
	afx_msg void OnRenderingmodeSmooth();
	afx_msg void OnUpdateRenderingmodePointcloud(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRenderingmodeTexture(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRenderingmodeWireframe(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRenderingmodeFlatlines(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRenderingmodeFlat(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRenderingmodeSmooth(CCmdUI *pCmdUI);
	afx_msg void OnViewLights();
	afx_msg void OnViewSethomeposition();
	afx_msg void OnViewReturnhome();
};

#ifndef _DEBUG  // debug version in osgViewView.cpp
inline CosgViewDoc* CosgViewView::GetDocument() const
   { return reinterpret_cast<CosgViewDoc*>(m_pDocument); }
#endif

