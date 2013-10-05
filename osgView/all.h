#pragma once
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/Point>
#include <osg/PolygonOffset>
#include <osgUtil/SmoothingVisitor>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>










#include<osgViewer/Viewer>
#include <osgUtil/Optimizer>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/CompositeViewer>

#include <osgGA/TerrainManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/TerrainManipulator>

#include <osg/Material>
#include <osg/Geode>
#include <osg/BlendFunc>
#include <osg/Depth>
#include <osg/Projection>
#include <osg/MatrixTransform>
#include <osg/Camera>
#include <osg/io_utils>
#include <osg/ShapeDrawable>

#include <osgText/Text>

#include <sstream>
#include <cmath>

#include<osgDB/ReadFile>
//#include "CommonFunctions.h"
//#include "PointIntersector.h"
#include "StdAfx.h"
extern osg::Camera* createHUDCamera( double left, double right, double bottom, double top );


class KeyboardEventHandler : public osgGA::GUIEventHandler
{
public:
    
        KeyboardEventHandler(osg::StateSet* stateset):
            _stateset(stateset)
        {
            _point = new osg::Point;
            _point->setDistanceAttenuation(osg::Vec3(0.0,0.0000,0.05f));
            _stateset->setAttribute(_point.get());
        }
    
        virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&)
        {
            switch(ea.getEventType())
            {
                case(osgGA::GUIEventAdapter::KEYDOWN):
                {
                    if (ea.getKey()=='+' || ea.getKey()==osgGA::GUIEventAdapter::KEY_KP_Add)
                    {
                       changePointSize(1.0f);
                       return true;
                    }
                    else if (ea.getKey()=='-' || ea.getKey()==osgGA::GUIEventAdapter::KEY_KP_Subtract)
                    {
                       changePointSize(-1.0f);
                       return true;
                    }
                    else if (ea.getKey()=='<')
                    {
                       changePointAttenuation(1.1f);
                       return true;
                    }
                    else if (ea.getKey()=='>')
                    {
                       changePointAttenuation(1.0f/1.1f);
                       return true;
                    }
                    break;
                }
                default:
                    break;
            }
            return false;
        }
        
        
        float getPointSize() const
        {
            return _point->getSize();
        }
        
        void setPointSize(float psize)
        {
            if (psize>0.0)
            {
                _point->setSize(psize);
            }
         //   std::cout<<"Point size "<<psize<<std::endl;
        }

        void changePointSize(float delta)
        {
            setPointSize(getPointSize()+delta);
        }

        void changePointAttenuation(float scale)
        {
            _point->setDistanceAttenuation(_point->getDistanceAttenuation()*scale);
        }
        
        osg::ref_ptr<osg::StateSet> _stateset;
        osg::ref_ptr<osg::Point>    _point;
        
};