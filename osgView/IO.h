
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
#include<osg/PositionAttitudeTransform>
#include<fstream>

inline osg::Matrixd ReadMatrix(std::istream & in){
	osg::Matrixd m;
	double e;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
          in>> m(i,j);
		}
	}
	return m;
}


inline void WriteMatrix(std::ostream & out,const osg::Matrixd & m){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
          out<< m(i,j)<<" ";
		}
		out<<std::endl;
	}
}