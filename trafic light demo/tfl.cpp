
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
	




