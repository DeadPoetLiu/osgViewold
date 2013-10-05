
// osgViewView.cpp : implementation of the CosgViewView class
//

#include "stdafx.h"
#include "all.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "osgView.h"
#endif
#include <fstream>
#include "osgViewDoc.h"
#include "osgViewView.h"
#include "PreferenceDialog.h"
#include <osg/ShadeModel> 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CosgViewView

IMPLEMENT_DYNCREATE(CosgViewView, CView)

BEGIN_MESSAGE_MAP(CosgViewView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CosgViewView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_EDIT_PREFERENCES, &CosgViewView::OnEditPreferences)
	ON_COMMAND(ID_RENDERINGMODE_POINTCLOUD, &CosgViewView::OnRenderingmodePointcloud)
	ON_COMMAND(ID_RENDERINGMODE_TEXTURE, &CosgViewView::OnRenderingmodeTexture)
	ON_COMMAND(ID_RENDERINGMODE_WIREFRAME, &CosgViewView::OnRenderingmodeWireframe)
	ON_COMMAND(ID_RENDERINGMODE_FLATLINES, &CosgViewView::OnRenderingmodeFlatlines)
	ON_COMMAND(ID_RENDERINGMODE_FLAT, &CosgViewView::OnRenderingmodeFlat)
	ON_COMMAND(ID_RENDERINGMODE_SMOOTH, &CosgViewView::OnRenderingmodeSmooth)
	ON_UPDATE_COMMAND_UI(ID_RENDERINGMODE_POINTCLOUD, &CosgViewView::OnUpdateRenderingmodePointcloud)
	ON_UPDATE_COMMAND_UI(ID_RENDERINGMODE_TEXTURE, &CosgViewView::OnUpdateRenderingmodeTexture)
	ON_UPDATE_COMMAND_UI(ID_RENDERINGMODE_WIREFRAME, &CosgViewView::OnUpdateRenderingmodeWireframe)
	ON_UPDATE_COMMAND_UI(ID_RENDERINGMODE_FLATLINES, &CosgViewView::OnUpdateRenderingmodeFlatlines)
	ON_UPDATE_COMMAND_UI(ID_RENDERINGMODE_FLAT, &CosgViewView::OnUpdateRenderingmodeFlat)
	ON_UPDATE_COMMAND_UI(ID_RENDERINGMODE_SMOOTH, &CosgViewView::OnUpdateRenderingmodeSmooth)
END_MESSAGE_MAP()

// CosgViewView construction/destruction

CosgViewView::CosgViewView():stereo(false)
{
	// TODO: add construction code here

}

CosgViewView::~CosgViewView()
{
}

BOOL CosgViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CosgViewView drawing

void CosgViewView::OnDraw(CDC* /*pDC*/)
{
	CosgViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CosgViewView printing


void CosgViewView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CosgViewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CosgViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CosgViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CosgViewView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CosgViewView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CosgViewView diagnostics

#ifdef _DEBUG
void CosgViewView::AssertValid() const
{
	CView::AssertValid();
}

void CosgViewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CosgViewDoc* CosgViewView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CosgViewDoc)));
	return (CosgViewDoc*)m_pDocument;
}
#endif //_DEBUG


// CosgViewView message handlers


void CosgViewView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	// Get Filename from DocumentOpen Dialog
    CString csFileName = GetDocument()->GetFileName();

    // Init the osg class
    mOSG->InitOSG(csFileName.GetString());

    // Start the thread to do OSG Rendering
    //mThreadHandle = (HANDLE)_beginthread(&cOSG::Render, 0, mOSG); 
    mThreadHandle = new CRenderingThread(mOSG);
    mThreadHandle->start();
}


int CosgViewView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	 mOSG = new cOSG(m_hWnd);

    return 1;
	
}


void CosgViewView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	 delete mThreadHandle;
    if(mOSG != 0) delete mOSG;

    //WaitForSingleObject(mThreadHandle, 1000);

    CView::OnDestroy();
}


BOOL CosgViewView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true;
}


void CosgViewView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	// Pass Key Presses into OSG
    mOSG->getViewer()->getEventQueue()->keyPress(nChar);

    // Close Window on Escape Key
    if(nChar == VK_ESCAPE)
    {
        GetParent()->SendMessage(WM_CLOSE);
    }
	if(nChar == VK_F1)
    {
		stereo= !stereo;
		mOSG->getViewer()->getCamera()->setDisplaySettings(new osg::DisplaySettings()); 
        mOSG->getViewer()->getCamera()->getDisplaySettings()->setStereo(stereo);
		mOSG->getViewer()->getCamera()->getDisplaySettings()->setStereoMode(osg::DisplaySettings::HORIZONTAL_SPLIT);
    }
	
}


void CosgViewView::OnEditPreferences()
{
	//	// TODO: Add your command handler code here
	CPreferenceDialog aDlg; // Create a local dialog object
// Display the dialog as modal
	aDlg.stereo.sp=sp;
   /* std::ofstream out;
	out.open("out.txt",std::ofstream::out|std::ofstream::app);
	out<<"OnEditPreferences"<<std::endl;*/
	if(aDlg.DoModal() == IDOK)
    {   
		this->sp=aDlg.stereo.sp;
		//out<<aDlg.stereo.stereoMode<<std::endl;
		mOSG->getViewer()->getCamera()->setDisplaySettings(new osg::DisplaySettings()); 
        auto setting=mOSG->getViewer()->getCamera()->getDisplaySettings();
		setting->setStereo(sp.stereoDisplay);
		switch(sp.stereoMode){
		case 0:
			setting->setStereoMode(osg::DisplaySettings::QUAD_BUFFER);
			break;
		case 1:
			setting->setStereoMode(osg::DisplaySettings::HORIZONTAL_SPLIT);
			break;
		case 2:
			setting->setStereoMode(osg::DisplaySettings::VERTICAL_SPLIT);
			break;
		case 3:
			setting->setStereoMode(osg::DisplaySettings::LEFT_EYE);
			break;
		case 4:
			setting->setStereoMode(osg::DisplaySettings::RIGHT_EYE);
			break;
		default:
			break;

		}
		setting->setScreenWidth(sp.screenWidth/100);
		setting->setScreenHeight(sp.screenHeight/100);
		setting->setScreenDistance(sp.screenDistance);
		setting->setEyeSeparation(sp.eyeSeparation/1000);

    }/*else{
		out<<"cancel"<<std::endl;
	}
	out.close();*/
}

void CosgViewView::setMode(Modes m){
	mode=m;
	osg::StateSet* stateset = mOSG->mModel->getOrCreateStateSet();
	osg::PolygonMode::Mode em;
	osg::ShadeModel::Mode sm;
	switch(m){
	case Modes::pointCloud:
		 em=osg::PolygonMode::POINT ;
		break;
	case Modes::texture:
		em=osg::PolygonMode::FILL;
		break;
	case Modes::wireframe:
		em=osg::PolygonMode::LINE;
		break;
	case Modes::flat:
		sm=osg::ShadeModel::FLAT;
		break;
	case Modes::flatLines:
		sm=osg::ShadeModel::Mode::FLAT;
		break;
	case Modes::smooth:
		sm=osg::ShadeModel::SMOOTH;
		break;
	}

	
	if(m== Modes::pointCloud|| m== Modes::texture||m== Modes::wireframe){
		osg::PolygonMode *pm = new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, em );
        stateset->setAttributeAndModes( pm, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	}
	else{
		osg::ShadeModel* smp = new osg::ShadeModel(); 
		smp->setMode(sm);
		stateset->setAttribute(smp);
	

	}

}
void CosgViewView::OnRenderingmodePointcloud()
{
	setMode(Modes::pointCloud);
	// TODO: Add your command handler code here
	/*mode=Modes::pointCloud;
	osg::StateSet* stateset = mOSG->mModel->getOrCreateStateSet();
	   osg::PolygonMode *pm = new osg::PolygonMode(
            osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::POINT );
        stateset->setAttributeAndModes( pm, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);*/
}


void CosgViewView::OnRenderingmodeTexture()
{
	// TODO: Add your command handler code here
	setMode(Modes::texture);
}


void CosgViewView::OnRenderingmodeWireframe()
{
	// TODO: Add your command handler code here
	setMode(Modes::wireframe);
}


void CosgViewView::OnRenderingmodeFlatlines()
{
	// TODO: Add your command handler code here
	setMode(Modes::flatLines);
}


void CosgViewView::OnRenderingmodeFlat()
{
	// TODO: Add your command handler code here
	setMode(Modes::flat);
}


void CosgViewView::OnRenderingmodeSmooth()
{
	// TODO: Add your command handler code here
	setMode(Modes::smooth);
}


void CosgViewView::OnUpdateRenderingmodePointcloud(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI-> SetCheck(mode==Modes::pointCloud);
}


void CosgViewView::OnUpdateRenderingmodeTexture(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI-> SetCheck(mode==Modes::texture);
}


void CosgViewView::OnUpdateRenderingmodeWireframe(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI-> SetCheck(mode==Modes::wireframe);
}


void CosgViewView::OnUpdateRenderingmodeFlatlines(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI-> SetCheck(mode==Modes::flatLines);
}


void CosgViewView::OnUpdateRenderingmodeFlat(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI-> SetCheck(mode==Modes::flat);
}


void CosgViewView::OnUpdateRenderingmodeSmooth(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI-> SetCheck(mode==Modes::smooth);
}
