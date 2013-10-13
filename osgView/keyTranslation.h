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
#include<osg/PositionAttitudeTransform>

 class tankInputDeviceStateType
 {
    public:
       tankInputDeviceStateType::tankInputDeviceStateType() : 
		  moveDirection(osg::Vec3(0,0,0)) ,rotate(false){}
       osg::Vec3 moveDirection;
	   bool rotate;
	 //  osg::Quat rotation;
 };

 class myKeyboardEventHandler : public osgGA::GUIEventHandler
 {
   public:
       myKeyboardEventHandler(tankInputDeviceStateType* tids):scale(0.1)
       {
          tankInputDeviceState = tids;
       }
    // ...
    protected:
       tankInputDeviceStateType* tankInputDeviceState;
	   float scale;

    bool myKeyboardEventHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
    {
       switch(ea.getEventType())
       {
       case(osgGA::GUIEventAdapter::KEYDOWN):
          {
             switch(ea.getKey())
             {
			 case osgGA::GUIEventAdapter::KeySymbol::KEY_Left:
                tankInputDeviceState->moveDirection = osg::Vec3(-scale,0,0);
                return false;
                break;
			 case osgGA::GUIEventAdapter::KeySymbol::KEY_Right:
                tankInputDeviceState->moveDirection = osg::Vec3(scale,0,0);
                return false;
                break;
			 case osgGA::GUIEventAdapter::KeySymbol::KEY_Up:
                tankInputDeviceState->moveDirection = osg::Vec3(0,scale,0);
				
                return false;

                break;
			case osgGA::GUIEventAdapter::KeySymbol::KEY_Down:
                tankInputDeviceState->moveDirection = osg::Vec3(0,-scale,0);
                return false;
			
			case osgGA::GUIEventAdapter::KeySymbol::KEY_Plus:
                scale*=2;
                return false;
			case osgGA::GUIEventAdapter::KeySymbol::KEY_Minus:
                scale/=2;
                return false;
			case osgGA::GUIEventAdapter::KeySymbol::KEY_R:
                tankInputDeviceState->rotate=true;
                return false;
             default:
                return false;
             } 
          }
	   case(osgGA::GUIEventAdapter::KEYUP):
		    tankInputDeviceState->moveDirection = osg::Vec3(0,0,0);
			tankInputDeviceState->rotate=false;
                return false;
       default:
          return false;
       }
    }

 };


	class updateTankPosCallback : public osg::NodeCallback {
    public:
       updateTankPosCallback::updateTankPosCallback(tankInputDeviceStateType* tankIDevState)
          : tankPos(0.,0.,0.),rot(0)
       {
          tankInputDeviceState = tankIDevState;
       }
       virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
       {
          osg::PositionAttitudeTransform* pat =
             dynamic_cast<osg::PositionAttitudeTransform*> (node);
          if(pat)
          {
             
			  tankPos.set(tankPos+tankInputDeviceState->moveDirection);

                pat->setPosition(tankPos);
				
				if(tankInputDeviceState->rotate){
				rot+=0.1;
				pat->setAttitude(osg::Quat(rot,osg::Vec3(0,1,0)));

				}
             
          }
          traverse(node, nv); 
       }
    protected:
       osg::Vec3d tankPos;
	   double  rot;
       tankInputDeviceStateType* tankInputDeviceState; };