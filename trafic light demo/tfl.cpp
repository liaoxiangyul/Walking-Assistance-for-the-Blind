
#include "trafficlight.h"
#include <wiringPi.h>
#include <stdio.h> 
#include <wiringPiI2C.h>
#include <cmath>


	//Determine whether two rectangular areas intersect
bool isIntersected(Rect r1, Rect r2)
	{
		int minX = max(r1.x, r2.x);
		int minY = max(r1.y, r2.y);
		int maxX = min(r1.x + r1.width, r2.x + r2.width);
		int maxY = min(r1.y + r1.height, r2.y + r2.height);

		if (minX < maxX && minY < maxY)
			return true;
		else
			return false;
	}
	
	
    //Contour processing function: red
int processImgR(Mat src)
	{
		Mat tmp;
        //Define the vector variable 'contours' that holds the contours
		vector<vector<Point>> contours;
		
		//Define the vector variable 'hierarchy' that holds the hierarchy of the contours
		vector<Vec4i> hierarchy;
		
		//Define a vector variable 'hull' for saving the convex hull
		vector<Point> hull;

		CvPoint2D32f tempNode;
		CvMemStorage* storage = cvCreateMemStorage();
		CvSeq* pointSeq = cvCreateSeq(CV_32FC2, sizeof(CvSeq), sizeof(CvPoint2D32f), storage);

		Rect* trackBox;
		Rect* result;
		int resultNum = 0;

		int area = 0;
		src.copyTo(tmp);

		//extract contour
		findContours(tmp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

		if (contours.size() > 0)
		{
			trackBox = new Rect[contours.size()];
			result = new Rect[contours.size()];

			//Determine the area to track
			for (int i = 0; i < contours.size(); i++)
			{
				cvClearSeq(pointSeq);
				
				// Get the point set of the convex hull
				convexHull(Mat(contours[i]), hull, true);
				int hullcount = (int)hull.size();
				
				// Convex Hull Save Points
				for (int j = 0; j < hullcount - 1; j++)
				{
					tempNode.x = hull[j].x;
					tempNode.y = hull[j].y;
					cvSeqPush(pointSeq, &tempNode);
				}

				trackBox[i] = cvBoundingRect(pointSeq);
			}
            //Determine whether it is the first detection
			if (isFirstDetectedR)
			{
				lastTrackBoxR = new Rect[contours.size()];
				for (int i = 0; i < contours.size(); i++)
					lastTrackBoxR[i] = trackBox[i];
				lastTrackNumR = contours.size();
				isFirstDetectedR = false;
			}
			
			//Compare the current rectangle with the rectangle saved in the previous frame one by one, if there is overlap, save the current rectangle to result
			else
			{
				for (int i = 0; i < contours.size(); i++)
				{
					for (int j = 0; j < lastTrackNumR; j++)
					{
						if (isIntersected(trackBox[i], lastTrackBoxR[j]))
						{
							result[resultNum] = trackBox[i];
							break;
						}
					}
					resultNum++;
				}
				delete[] lastTrackBoxR;
				lastTrackBoxR = new Rect[contours.size()];
				for (int i = 0; i < contours.size(); i++)
				{
					lastTrackBoxR[i] = trackBox[i];
				}
				lastTrackNumR = contours.size();
			}

			delete[] trackBox;
		}
		else
		{
			isFirstDetectedR = true;
			result = NULL;
		}
		cvReleaseMemStorage(&storage);
		
        //Calculate the sum of the areas of the rectangles
		if (result != NULL)
		{
			for (int i = 0; i < resultNum; i++)
			{
				area += result[i].area();
			}
		}
		delete[] result;

		return area;
	}
	
	
	//Contour processing function: green
int processImgG(Mat src)
	{
		Mat tmp;

        //Define the vector variable 'contours' that holds the contours
		vector<vector<Point> > contours;
		
		//Define the vector variable 'hierarchy' that holds the hierarchy of the contours
		vector<Vec4i> hierarchy;
		
		//Define a vector variable 'hull' for saving the convex hull
		vector< Point > hull;

		CvPoint2D32f tempNode;
		CvMemStorage* storage = cvCreateMemStorage();
		CvSeq* pointSeq = cvCreateSeq(CV_32FC2, sizeof(CvSeq), sizeof(CvPoint2D32f), storage);

		Rect* trackBox;
		Rect* result;
		int resultNum = 0;

		int area = 0;

		src.copyTo(tmp);
		
		//extract contour
		findContours(tmp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

		if (contours.size() > 0)
		{
			trackBox = new Rect[contours.size()];
			result = new Rect[contours.size()];

			//Determine the area to track
			for (int i = 0; i < contours.size(); i++)
			{
				cvClearSeq(pointSeq);
				
				// Get the point set of the convex hull
				convexHull(Mat(contours[i]), hull, true);
				int hullcount = (int)hull.size();
				
                // Convex Hull Save Points
				for (int j = 0; j < hullcount - 1; j++)
				{
					tempNode.x = hull[j].x;
					tempNode.y = hull[j].y;
					cvSeqPush(pointSeq, &tempNode);
				}

				trackBox[i] = cvBoundingRect(pointSeq);
			}

            //Determine whether it is the first detection
			if (isFirstDetectedG)
			{
				lastTrackBoxG = new Rect[contours.size()];
				for (int i = 0; i < contours.size(); i++)
					lastTrackBoxG[i] = trackBox[i];
				lastTrackNumG = contours.size();
				isFirstDetectedG = false;
			}
			
			//Compare the current rectangle with the rectangle saved in the previous frame one by one, if there is overlap, save the current rectangle to result
			else
			{
				for (int i = 0; i < contours.size(); i++)
				{
					for (int j = 0; j < lastTrackNumG; j++)
					{
						if (isIntersected(trackBox[i], lastTrackBoxG[j]))
						{
							result[resultNum] = trackBox[i];
							break;
						}
					}
					resultNum++;
				}
				delete[] lastTrackBoxG;
				lastTrackBoxG = new Rect[contours.size()];
				for (int i = 0; i < contours.size(); i++)
				{
					lastTrackBoxG[i] = trackBox[i];
				}
				lastTrackNumG = contours.size();
			}

			delete[] trackBox;
		}
		else
		{
			isFirstDetectedG = true;
			result = NULL;
		}
		cvReleaseMemStorage(&storage);

       //Calculate the sum of the areas of the rectangles
		if (result != NULL)
		{
			for (int i = 0; i < resultNum; i++)
			{
				area += result[i].area();
			}
		}
		delete[] result;

		return area;
	}
	


int main()
{
	// Initialize the number of red and green areas
	int redCount = 0;
	int greenCount = 0;
	
    //Create mat for reading, creating, manipulating and displaying images
	Mat frame;
	Mat img;
	Mat imgYCrCb;
	Mat imgGreen;
	Mat imgRed;

	// adjust the brightness parameter
	double a = 0.3;
	double b = (1 - a) * 125;
	
    //Import camera video
	VideoCapture capture(0);
	if (!capture.isOpened())
	{
		std::cerr << "Cannot open camera" << std::endl;
		return -1;
	}
	
	//Adjust the size and frame number of imported videos
	capture.set(cv::CAP_PROP_FRAME_WIDTH,640);
	capture.set(cv::CAP_PROP_FRAME_HEIGHT,480);
    capture.set(cv::CAP_PROP_FPS,5);

	// frame processing
		while (1)
		{
			//Get a frame of image
			Mat frame;
			capture >> frame; 

			//Brightness and Contrast Adjustment
			frame.convertTo(img, img.type(), a, b);

			//Convert to YCrCb color space
			cvtColor(img, imgYCrCb, CV_BGR2YCrCb);

			imgRed.create(imgYCrCb.rows, imgYCrCb.cols, CV_8UC1);
			imgGreen.create(imgYCrCb.rows, imgYCrCb.cols, CV_8UC1);

			//Decomposition of the three components of YCrCb
			vector<Mat> planes;
			split(imgYCrCb, planes);
			
			//Traverse to split red and green based on Cr component
			MatIterator_<uchar> it_Cr = planes[1].begin<uchar>(),
			it_Cr_end = planes[1].end<uchar>();
			MatIterator_<uchar> it_Red = imgRed.begin<uchar>();
			MatIterator_<uchar> it_Green = imgGreen.begin<uchar>();
			

			for (; it_Cr != it_Cr_end; ++it_Cr, ++it_Red, ++it_Green)
			{
				// RED, 145<Cr<470 
				if (*it_Cr > 145 && *it_Cr < 470)
					*it_Red = 255;
				else
					*it_Red = 0;
			
				// GREEN 95<Cr<110 
				if (*it_Cr > 95 && *it_Cr < 110)
					*it_Green = 255;
				else
					*it_Green = 0;

			}

			//expansion and corrosion
			dilate(imgRed, imgRed, Mat(15, 15, CV_8UC1), Point(-1, -1));
			erode(imgRed, imgRed, Mat(1, 1, CV_8UC1), Point(-1, -1));
			dilate(imgGreen, imgGreen, Mat(15, 15, CV_8UC1), Point(-1, -1));
			erode(imgGreen, imgGreen, Mat(1, 1, CV_8UC1), Point(-1, -1));

			redCount = processImgR(imgRed);
			greenCount = processImgG(imgGreen);
			cout << "red:" << redCount << ";  " << "green:" << greenCount << endl;
			
			//Traffic light condition judgment
			if (redCount == 0 && greenCount == 0)
			{
				cv::putText(frame, "lights out", Point(40, 150), cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(255, 255, 255), 8, 8, 0);
            
            }
            else if (redCount > greenCount)
            {
            
            cv::putText(frame, "red light", Point(40, 150), cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(0, 0, 255), 8, 8, 0);
            }
            else 
			{
            
			cv::putText(frame, "green light", Point(40, 150), cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(0, 255, 0), 8, 8, 0);
         
			}


			imshow("video", frame);
		
		}

		return 0;
	}

	

