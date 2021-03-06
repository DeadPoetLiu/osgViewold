
// osgViewView.cpp : implementation of the CosgViewView class
//

#include "stdafx.h"
#include "camera.h"
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
#include <fstream>
#include <Windows.h>
#include "IO.h"
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
	ON_COMMAND(ID_VIEW_LIGHTS, &CosgViewView::OnViewLights)
	ON_COMMAND(ID_VIEW_SETHOMEPOSITION, &CosgViewView::OnViewSethomeposition)
	ON_COMMAND(ID_VIEW_RETURNHOME, &CosgViewView::OnViewReturnhome)
	ON_COMMAND(ID_VIEW_STEREO, &CosgViewView::OnViewStereo)
	ON_COMMAND(ID_FILE_LOADACT, &CosgViewView::OnFileLoadact)
	ON_COMMAND(ID_FILE_LOADTXT, &CosgViewView::OnFileLoadtxt)
	ON_COMMAND(ID_FILE_UNLOADACT, &CosgViewView::OnFileUnloadact)
	ON_COMMAND(ID_FILE_UNLOADTXT, &CosgViewView::OnFileUnloadtxt)
END_MESSAGE_MAP()

// CosgViewView construction/destruction

CosgViewView::CosgViewView():stereo(false),lights(false)
{
	// TODO: add construction code here
	//OnViewSethomeposition();
	
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
	//ClientToScreen(&point);
	//OnContextMenu(this, point);
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
	fn=csFileName.GetString();
//	std::ofstream inf("file.txt");
//	inf<<fn;
//	inf.close();
	/*std::ifstream in("conf.txt");
	if(in){
		in.close();
		this->home=::ReadMatrix(in);
		this->OnViewReturnhome();

	}
	else*/
	 //   this->OnViewSethomeposition();
	std::ifstream in(fn+".conf");
	if(in){
	home=::ReadMatrix(in);
	in.close();
	this->OnViewReturnhome();
	}else{
		this->OnViewSethomeposition();
	}
	/*if(this->mOSG->mModel!=nullptr)
	   OnViewLights();*/

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
	std::ofstream out(fn+".conf");
	
	
	::WriteMatrix(out,home);
	out.close();
	/* CString csFileName = GetDocument()->GetFileName();

    std::string fileName=csFileName.GetString();
	std::ofstream out(fileName+".cfg");
	::WriteMatrix(out,home);
	out.close();*/
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
 //   mOSG->getViewer()->getEventQueue()->keyPress(nChar);

    // Close Window on Escape Key
	switch(nChar){
	case VK_F1:
		this->OnViewStereo();
		break;
	case VK_F2:
		this->changeAspectRatio(1.1);
		break;
	case VK_F3:
		 this->changeAspectRatio(1/1.1);
		 break;
	case VK_F4:
		this->mOSG->movingRate*=2;
		break;
	case VK_F5:
		this->mOSG->movingRate/=2;
		break;
	case 'U':
		dc.scale*=1.5;
	
		if(this->actNode.valid()){
			auto old=actNode.get();
			actNode=dc.result();
			mOSG->mRoot->replaceChild(old,actNode.get());
		}
		if(this->textNode.valid()){
			auto old=textNode.get();
			textNode=dc.readText(this->photoMatrixArray);
			mOSG->mRoot->replaceChild(old,textNode.get());

		}
	    break;
	case 'I':
		dc.scale/=1.5;
		if(this->actNode.valid()){
			auto old=actNode.get();
			actNode=dc.result();
			mOSG->mRoot->replaceChild(old,actNode.get());
		}
		if(this->textNode.valid()){
			auto old=textNode.get();
			textNode=dc.readText(this->photoMatrixArray);
			mOSG->mRoot->replaceChild(old,textNode.get());

		}
		break;
	case 'O':
		dc.stepLength+=1;
		if(this->actNode.valid()){
			auto old=actNode.get();
			actNode=dc.result();
			mOSG->mRoot->replaceChild(old,actNode.get());
		}
		break;
	case 'P':
		if(dc.stepLength>1){
		dc.stepLength-=1;
		if(this->actNode.valid()){
			auto old=actNode.get();
			actNode=dc.result();
			mOSG->mRoot->replaceChild(old,actNode.get());
		}
		}
		break;
	case 'B':
		
		this->mOSG->path->clear();
		this->mOSG->path->push_back(this->mOSG->trackball->getCenter());
		this->mOSG->cur=0;
		this->mOSG->step=0;
	    break;
	
	case 'E':
		;
		this->mOSG->path->push_back(this->mOSG->trackball->getCenter());
		this->mOSG->cur=0;
		this->mOSG->step=0;
		break;

	case 'M':
		if(this->mOSG->path->size()>1)
		   this->mOSG->movingCamera=!this->mOSG->movingCamera;
		break;
	
	 default:
		 if(nChar>='0'&&nChar<='9')
		       this->selectPhoto(nChar-'0');

		

	}
 //   if(nChar == VK_ESCAPE)
 //   {
 //    //  GetParent()->SendMessage(WM_CLOSE);
 //   }
	//else if(nChar == VK_F1)
 //   {
	//	this->OnViewStereo();
	//	/*stereo= !stereo;
	//	mOSG->getViewer()->getCamera()->setDisplaySettings(new osg::DisplaySettings()); 
 //       mOSG->getViewer()->getCamera()->getDisplaySettings()->setStereo(stereo);
	//	mOSG->getViewer()->getCamera()->getDisplaySettings()->setStereoMode(osg::DisplaySettings::HORIZONTAL_SPLIT);*/
 //   }
	//else if(
	//
}

void CosgViewView::setStereo(){
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
		/*setting->setScreenWidth(sp.screenWidth/100);
		setting->setScreenHeight(sp.screenHeight/100);
		setting->setScreenDistance(sp.screenDistance);
		setting->setEyeSeparation(sp.eyeSeparation/1000);*/


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
	    setStereo();

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


void CosgViewView::OnViewLights()
{
	// TODO: Add your command handler code here
	

	
	 osg::StateSet* stateset = mOSG->mRoot->getOrCreateStateSet();
	 lights=!lights;
	 if(lights)
	 stateset->setMode(GL_LIGHTING,osg::StateAttribute::ON|osg::StateAttribute::PROTECTED);
	 else
		 stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF|osg::StateAttribute::PROTECTED);
}


void CosgViewView::OnViewSethomeposition()
{
	home=this->mOSG->trackball->getMatrix();
	std::ofstream out("C:\\Users\\w\\Desktop\\out.txt",std::ofstream::app);
	out<<home<<std::endl;

	out.close();
	// TODO: Add your command handler code here
	//std::ofstream out("conf.txt");
	/*static int seq=0;
	home=this->mOSG->trackball->getMatrix();
	if(seq%2==0)
		mOSG->start=mOSG->trackball->getCenter();
	else
		mOSG->end=mOSG->trackball->getCenter();

	seq++;*/
	/**::WriteMatrix(out,home);
	out.close();*/
	// home=viewer->getCamera()->getViewMatrix();

}
//struct Track{
//public:osg::Vec3 start;
//	osg::Vec3 end;
//	double step;
//	osgGA::TrackballManipulator * m;
//	Track(const osg::Vec3 & s,const osg::Vec3 e,osgGA::TrackballManipulator * ms):start(s),end(e),m(ms),step(0.0001){};
//	void open(){
//
//		for(double p=0;p<=1;p+=step){
//		//  Sleep(1);
//			m->setCenter(start*p+end*(1-p));
//			
//		}
//	}
//
//
//
//};

void CosgViewView::OnViewReturnhome()
{
	// TODO: Add your command handler code here

	

  // viewer->getCamera()->setViewMatrix(home);
	/* std::ifstream in("conf.txt");
	 osg::Matrixd f;
	 f=::ReadMatrix(in);
	 std::ofstream out("out.txt");
	 ::WriteMatrix(out,f);
	 out.close();*/
	 this->mOSG->trackball->setByMatrix(home);
	// osg::Vec3 start=mOSG->trackball->getCenter();
	//auto temp=start+osg::Vec3(10,0,0);
	//Track track(start, temp,mOSG->trackball);
	////start=temp;
	//track.open();

	//this->mOSG->trackball->setCenter(mOSG->trackball->getCenter()+osg::Vec3d(100,1,1));
	 
	//mOSG->movingCamera=true;
}


void CosgViewView::OnViewStereo()
{
	// TODO: Add your command handler code here
	sp.stereoDisplay=!sp.stereoDisplay;
	setStereo();
	//mOSG->movingCamera=true;
	
}





void CosgViewView::changeAspectRatio(double rate)
{
	 double fovy,aspectRatio,z1,z2;
	 auto camera=this->mOSG->getViewer()->getCamera();
	 camera->getProjectionMatrixAsPerspective(fovy,aspectRatio,z1,z2);
     aspectRatio*=rate;
	//aspectRatio=10;
    camera->setProjectionMatrixAsPerspective(fovy,aspectRatio,z1,z2);
}


void CosgViewView::OnFileLoadact()
{
	// TODO: Add your command handler code here
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY ,
		"(*.act)|*.act", this);
	
	// dlg.m_ofn.lpstrInitialDir = (BSTR)directoryName;  //设置对话框默认呈现的路径
	
	std::string strFilePath;
	if(dlg.DoModal() == IDOK)
	{
		strFilePath=dlg.GetPathName( ).GetBuffer();
		dc.actFile=strFilePath;
		this->actNode=this->dc.result().get();
		mOSG->mRoot->addChild(actNode);
		
	}
}





void CosgViewView::OnFileLoadtxt()
{
	// TODO: Add your command handler code here
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY ,
		"(*.txt)|*.txt", this);
	
	// dlg.m_ofn.lpstrInitialDir = (BSTR)directoryName;  //设置对话框默认呈现的路径

	std::string strFilePath;
	if(dlg.DoModal() == IDOK)
	{
		strFilePath=dlg.GetPathName( ).GetBuffer();
		dc.textFile=strFilePath;
		this->photoMatrixArray.clear();
		this->textNode=dc.readText(this->photoMatrixArray).get();
		mOSG->mRoot->addChild(textNode);

	}
}


void CosgViewView::OnFileUnloadact()
{
	// TODO: Add your command handler code here
	if(this->actNode.valid())
		mOSG->mRoot->removeChild(actNode.get());

}


void CosgViewView::OnFileUnloadtxt()
{
	// TODO: Add your command handler code here
	if(this->textNode.valid()){
		mOSG->mRoot->removeChild(textNode.get());
		this->photoMatrixArray.clear();
	}
}








boolean CosgViewView::selectPhoto(int seq)
{
	if(seq>=0&&seq<this->photoMatrixArray.size()&&this->textNode.valid()){
		hideAll();
		auto t=this->textNode->getChild(seq);
		t->setNodeMask(0xffffffff );
		std::ofstream out("C:\\Users\\w\\Desktop\\selectPhoto.txt",std::ofstream::app);
	//	this->mOSG->trackball->setTransformation(osg::Vec3(0,0,0)*photoMatrixArray[seq],osg::Matrixd::inverse(photoMatrixArray[seq]).getRotate());
	//	this->mOSG->getViewer()->setCameraManipulator(NULL);
		/*auto diandao=osg::Matrixd(0 ,1, 0, 0,
        1, 0, 0, 0,
        0, 0, 1, 0,
        0 ,0, 0 ,1);*/
		
		/*auto diandao=osg::Matrixd( 1, 0, 0,0
        1, 0, 0, 0,
        0, 0, 1, 0,
        0 ,0, 0 ,1);*/
		auto rot=osg::Matrix3(1,0,0,0,0,-1,0,1,0);
		out<<"photoMatrixArray[seq]"<<endl;
		out<<photoMatrixArray[seq]<<endl;
		out<<"diandao"<<endl;
		//out<<diandao<<endl;
//		auto mat= photoMatrixArray[seq]* diandao;
	/*	out<<"mat"<<endl;
		out<<mat<<std::endl;*/

	    out<<"pre"<<endl;
		out<<this->mOSG->trackball->getMatrix()<<endl;

		//this->mOSG->getViewer()->getCamera()->setProjectionMatrixAsPerspective( 0.6199,1.7778,1,300);
		auto anotherm=photoMatrixArray[seq];
		anotherm(0,0)=-anotherm(0,0);
		anotherm(1,0)=-anotherm(1,0);
		anotherm(2,0)=-anotherm(2,0);
		anotherm(3,0)=-anotherm(3,0);

		osg::Quat qRotAboutAxisByDegree; 
		qRotAboutAxisByDegree.makeRotate( osg::DegreesToRadians(90.), osg::Z_AXIS);
		anotherm.setRotate(anotherm.getRotate() * qRotAboutAxisByDegree); 
		
		this->mOSG->trackball->setByMatrix(anotherm);
		
		//this->mOSG->trackball->se
		//this->mOSG->trackball->setByMatrix(anotherm);
		//this->mOSG->trackball->setRotation(this->mOSG->trackball->getRotation()* );
		out<<"get matrix"<<endl;
		out<<this->mOSG->trackball->getMatrix()<<endl;

		out.close();
		//this->mOSG->trackball->setDistance(-1);
	//	mOSG->getViewer()->getCamera()->setViewMatrix( osg::Matrixd::inverse(this->photoMatrixArray[seq]));
	//	this->mOSG->getViewer()->setCameraManipulator(mOSG->trackball.get());
		
		return true;
	}
	else
		return false;
}


void CosgViewView::hideAll(void)
{
	for(int i=0;i<this->photoMatrixArray.size();i++){
		auto t=this->textNode->getChild(i);
		t->setNodeMask(0x0);
	}
}
