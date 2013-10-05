#pragma once
struct StereoParameter{
	int stereoDisplay;
	int stereoMode;
	double screenWidth;
	double screenHeight;
	double screenDistance;
	double eyeSeparation;
	StereoParameter():stereoDisplay(0),stereoMode(0),screenWidth(50),screenHeight(28),screenDistance(1),eyeSeparation(60){}


};

struct MoveMentParameter{
	bool b1,b2,b3,b4;
	double height,distance;
	MoveMentParameter():b1(false),b2(false),b3(false),b4(false),height(5),distance(1){};
};