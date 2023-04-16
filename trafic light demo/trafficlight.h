//Make sure header files are only compiled once
#pragma once


#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/imgproc/types_c.h>	
#include <opencv2/imgproc/imgproc_c.h>	
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// function declaration
int processImgR(Mat);
int processImgG(Mat);
bool isIntersected(Rect, Rect);
void detect(Mat& frame);

// global variables
bool isFirstDetectedR = true;
bool isFirstDetectedG = true;
Rect* lastTrackBoxR;
Rect* lastTrackBoxG;
int lastTrackNumR;
int lastTrackNumG;

