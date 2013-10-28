#pragma once

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/api/win32/GraphicsWindowWin32>
#include <osgGA/TrackballManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgDB/DatabasePager>
#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <string>

class cOSG
{
public:
    cOSG(HWND hWnd);
    ~cOSG();

    void InitOSG(std::string filename);
    void InitManipulators(void);
    void InitSceneGraph(void);
    void InitCameraConfig(void);
    void SetupWindow(void);
    void SetupCamera(void);
    void PreFrameUpdate(void);
    void PostFrameUpdate(void);
    void Done(bool value) { mDone = value; }
    bool Done(void) { return mDone; }
    //static void Render(void* ptr);

    osgViewer::Viewer* getViewer() { return mViewer; }
	 osg::ref_ptr<osg::Node> mModel;
	 osg::ref_ptr<osgGA::TrackballManipulator> trackball;
	 bool changeHome;
private:
    bool mDone;
    std::string m_ModelName;
    HWND m_hWnd;
    osgViewer::Viewer* mViewer;
    
   osg::PositionAttitudeTransform * xform;
    
    osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator;
public:
	bool movingCamera;
	osg::Vec3 start;
	osg::Vec3 end;
	osg::ref_ptr<osg::Group> mRoot;
	double movingRate;
	double step;
	osg::ref_ptr<osg::Vec3Array> path;
	int cur;
};

class CRenderingThread : public OpenThreads::Thread
{
public:
    CRenderingThread( cOSG* ptr );
    virtual ~CRenderingThread();

    virtual void run();

protected:
    cOSG* _ptr;
    bool _done;
};
