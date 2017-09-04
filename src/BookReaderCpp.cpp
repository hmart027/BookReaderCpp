//============================================================================
// Name        : BookReaderCpp.cpp
// Author      : Harold Martin
// Version     :
// Copyright   : Harold Martin @2000-2017
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace cv;
using namespace std;

Rect lowResDist(cv::Mat src, float x, float y), highRes(cv::Mat src), highResBase(cv::Mat src), lowResAmp(Rect b);

vector<int> polySearch(Point point, std::vector<Vec4i> hierarchy, std::vector<std::vector<Point> > contours, int current);

String searchPath = "/media/harold/DataLPC/BReader/6-30-17/"; //"/media/harold/DataLPC/BReader/7-16-17/";
String ampFrame = "amp1000.tiff";
String distFrame = "distC1001.tiff";
String highFrame= "IMG_1793.JPG"; //"IMG_1825.JPG";
String highBaseFrame= "IMG_1824.JPG";

int main() {

	cv::Mat highResImg, lowResDistImg, highResBaseImg;
//	highResBaseImg = imread( searchPath + highBaseFrame, 0);
	highResImg = imread( searchPath + highFrame, 0);
	lowResDistImg = imread( searchPath + distFrame, 0);


//	Rect base = highResBase(highResBaseImg);
	Rect vHigh = highRes(highResImg);
	std::cout << "Got HighRes..." << std::endl;
	Rect b1 = lowResDist(lowResDistImg, vHigh.width, vHigh.height);
	std::cout << "Got Dist..." << std::endl;

	std::cout<<vHigh.width<<", "<<vHigh.height<<std::endl;
	std::cout<<b1.width<<", "<<b1.height<<std::endl;
	std::cout<<(float)vHigh.width/(float)b1.width<<", "<<(float)vHigh.height/(float)b1.height<<std::endl;


//	lowResAmp(b1);

	Mat colorImg;

/*	//Display Base outline
	cvtColor(highResBaseImg, colorImg, CV_GRAY2BGR);
	rectangle(colorImg, base, Scalar(255,255,0), 8, 8, 0);
	namedWindow("Base", 0);
	imshow("Base", colorImg);
*/

	//Display high resolution image with bounding box
	cvtColor(highResImg, colorImg, CV_GRAY2BGR);
	rectangle(colorImg, vHigh, Scalar(255,255,0), 8, 8, 0);
	namedWindow("Detected Lines HighRes", 0);
	imshow("Detected Lines HighRes", colorImg);

/*	//Display low resolution Distance image with bounding box
	cvtColor(lowResDistImg, colorImg, CV_GRAY2BGR);
	rectangle(colorImg, b1, Scalar(255,255,0), 1, 8, 0);
	namedWindow("Detected Lines LowRes", 0);
//	resize(color_dst, color_dst, Size((int)((x*color_dst.cols/(float)out.width)), (int)(y*color_dst.rows/(float)out.height)), 0, 0, INTER_LINEAR);
	imshow("Detected Lines LowRes", colorImg);
*/


/*	std::cout << "!!!Hello World!!!" << std::endl; // prints !!!Hello World!!!
	Mat src, dst, color_dst;
//	src = imread("/media/harold/DataLPC/BReader/VideoFrames/frame500.tiff", 0);
//	src = imread("/media/harold/DataLPC/BReader/testmatch/book2.JPG", 0);
	src = imread("/media/harold/DataLPC/BReader/testmatch/book2.tiff", 0);

	//HighRes
//	blur(src, src, Size(100,100), Point(-1,-1), BORDER_REPLICATE);
//	threshold(src, src, 0,255,THRESH_BINARY_INV+THRESH_OTSU);

	Canny(src, dst, 50, 200, 3);
//	cvtColor(dst, color_dst, CV_GRAY2BGR);

//	std::vector<Vec4i> lines;
//	std::vector<Vec4i> lines2;
//	HoughLinesP(dst, lines, 1, CV_PI / 180, 80, 30, 10);
////	for (size_t i = 0; i < lines.size(); i++) {
////		line(color_dst, Point(lines[i][0], lines[i][1]),
////				Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255), 3, 8);
////	}
//	approxPolyDP(lines, lines2, 2, true);
//	for (size_t i = 0; i < lines2.size(); i++) {
//		line(color_dst, Point(lines2[i][0], lines2[i][1]),
//				Point(lines2[i][2], lines2[i][3]), Scalar(0, 0, 255), 3, 8);
//	}

	std::vector<std::vector<Point> > contours, contours2;
	std::vector<Vec4i> hierarchy;
	/// Find contours
	findContours( dst, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	std::cout << contours.size() << std::endl; // prints !!!Hello World!!!

	contours2.resize(contours.size());
	for (size_t k = 0; k < contours.size(); k++)
		approxPolyDP(contours[k], contours2[k], 5, true);

	std::cout << "Got Polygons..." << std::endl;

//	approxPolyDP(contours[0], contours[0], 3, true);
//	std::cout << contours2.size() << std::endl; // prints !!!Hello World!!!

	// Draw contours
//	Mat drawing = Mat::zeros(dst.size(), CV_8UC3);
	cvtColor(src, color_dst, CV_GRAY2BGR);
//	for (int i = 0; i < contours.size(); i++) {
//		Scalar color = Scalar(255, 0, 0);
//		drawContours(color_dst, contours, i, color, 2, 8, hierarchy, 0, Point());
//	}

	std::vector<cv::Point> points;
	points.insert(points.end(), contours2[0].begin(), contours2[0].end());
	points.insert(points.end(), contours2[1].begin(), contours2[1].end());
	points.insert(points.end(), contours2[2].begin(), contours2[2].end());
	convexHull(cv::Mat(points), contours2[0]);

	int cNum = 0;
	drawContours(color_dst, contours2, cNum, Scalar(255, 0, 0), 2, 8);

//	namedWindow("Source", 1);
//	imshow("Source", src);

	//get bounding box
	rectangle(color_dst, boundingRect(contours2[cNum]), Scalar(255,255,0), 8, 8, 0);

	namedWindow("Detected Lines", 0);
	Size s(color_dst.cols*2, color_dst.rows*2);
	resize(color_dst, color_dst, s, 0, 0, INTER_LINEAR);
	imshow("Detected Lines", color_dst);*/

	waitKey(0);
	return 0;
}

Rect lowResAmp(Rect b){
	Mat src, dst, color_dst;
	Rect out;
	// "/media/harold/DataLPC/BReader/testmatch/book2.JPG"
	src = imread(searchPath + ampFrame, 0);
	src = src(Rect(b.x+30, b.y+25, b.width, b.height));

	//HighRes
	blur(src, src, Size(2, 2), Point(-1, -1), BORDER_REPLICATE);
	threshold(src, src, 0, 255, THRESH_BINARY_INV + THRESH_OTSU);

	Canny(src, dst, 50, 200, 3);
	cvtColor(dst, color_dst, CV_GRAY2BGR);

	std::vector<std::vector<Point> > contours, contours2;
	std::vector<Vec4i> hierarchy;
	/// Find contours
	findContours(dst, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE,
			Point(0, 0));
	std::cout << contours.size() << std::endl; // prints !!!Hello World!!!

	contours2.resize(contours.size());
	for (size_t k = 0; k < contours.size(); k++)
		approxPolyDP(contours[k], contours2[k], 5, true);

	std::cout << "Got Polygons..." << std::endl;

	// Draw contours
	cvtColor(src, color_dst, CV_GRAY2BGR);
	std::vector<cv::Point> points;
	for (int i = 0; i < contours.size(); i++) {
		//		Scalar color = Scalar(255, 0, 0);
		//		drawContours(color_dst, contours, i, color, 2, 8, hierarchy, 0, Point());
		points.insert(points.end(), contours2[i].begin(), contours2[i].end());
	}
	convexHull(cv::Mat(points), contours2[0]);

	int cNum = 0;
	//	drawContours(color_dst, contours2, cNum, Scalar(255, 0, 0), 2, 8);

	//	namedWindow("Source", 1);
	//	imshow("Source", src);

	//get bounding box
	out = boundingRect(contours2[cNum]);
	rectangle(color_dst, out, Scalar(255, 255, 0), 8, 8, 0);

	namedWindow("Detected Lines LowResAmp", 0);
	imshow("Detected Lines LowResAmp", color_dst);

	std::cout << out.width << ", " << out.height << std::endl;

	return out;

}

Rect lowResDist(cv::Mat src, float x, float y){
	Mat src2, dst, color_dst;
	Rect out;
	//"/media/harold/DataLPC/BReader/testmatch/book2.tiff"
//	flip(src, src, 1);

	blur(src, src2, Size(5,5), Point(-1,-1), BORDER_REPLICATE);
//	threshold(src, src2, 0,255,THRESH_BINARY_INV+THRESH_OTSU);
	Canny(src2, dst, 50, 200, 3);
//	Canny(src, dst, 20, 60, 3);

	std::vector<std::vector<Point> > contours, contours2;
	std::vector<Vec4i> hierarchy;
	/// Find contours
	findContours( dst, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	std::cout << contours.size() << std::endl; // prints !!!Hello World!!!

	contours2.resize(contours.size());
	for (size_t k = 0; k < contours.size(); k++)
		approxPolyDP(contours[k], contours2[k], 5, true);

	std::cout << "Got Polygons..." << std::endl;

	// Draw contours
	cvtColor(src, color_dst, CV_GRAY2BGR);

	std::vector<cv::Point> points;
	for (uint i = 0; i < contours.size(); i++) {
//		Scalar color = Scalar(255, 0, 0);
//		drawContours(color_dst, contours, i, color, 2, 8, hierarchy, 0, Point());
		points.insert(points.end(), contours2[i].begin(), contours2[i].end());
	}

	convexHull(cv::Mat(points), contours2[0]);

	int cNum = 0;
	drawContours(color_dst, contours2, cNum, Scalar(255, 0, 0), 1, 8);

//	namedWindow("Source", 1);
//	imshow("Source", src);

	//get bounding box
	out = boundingRect(contours2[cNum]);
	rectangle(color_dst, out, Scalar(255,255,0), 1, 8, 0);

	namedWindow("Detected Lines LowRes", 0);
//	resize(color_dst, color_dst, Size((int)((x*color_dst.cols/(float)out.width)), (int)(y*color_dst.rows/(float)out.height)), 0, 0, INTER_LINEAR);
	imshow("Detected Lines LowRes", color_dst);

	return out;
}

Rect highRes(cv::Mat src){
	Mat src2, dst, color_dst;
	Rect out;
	// "/media/harold/DataLPC/BReader/testmatch/book2.JPG"

	//HighRes
	blur(src, src2, Size(100,100), Point(-1,-1), BORDER_REPLICATE);
	threshold(src2, src2, 0,255,THRESH_BINARY_INV+THRESH_OTSU);
	namedWindow("Blured HighRes", 0);
	imshow("Blured HighRes", src2);

	Canny(src2, dst, 50, 200, 3);
	cvtColor(dst, color_dst, CV_GRAY2BGR);

	std::vector<std::vector<Point> > contours, contours2;
	std::vector<Vec4i> hierarchy;
	/// Find contours
	findContours( dst, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	std::cout << contours.size() << std::endl; // prints !!!Hello World!!!

	contours2.resize(contours.size());
	for (size_t k = 0; k < contours.size(); k++){
		convexHull(contours[k], contours2[k],contourArea(contours[k], true)<0, true);
//		approxPolyDP(contours[k], contours2[k], arcLength(Mat(contours[k]), true)*0.02, true);
	}

	Point center(src.cols/2, src.rows/2);
	//Check hierarchy tree
	vector<int> res = polySearch(center, hierarchy, contours, 0);
	while((res[0]==-1) && (res[2]!=-1)){
		res = polySearch(center, hierarchy, contours, res[2]);
	}

	// Draw contours
	cvtColor(src2, color_dst, CV_GRAY2BGR);
	std::vector<cv::Point> points;
/*	double scale = 255.0/contours2.size();
	for (uint i = 0; i < contours2.size(); i++) {
		//Check if center is inside the polygon
		if(pointPolygonTest(contours2[i], center, false)<=0) continue;

		std::cout<< i<<", "<< contourArea(contours2[i], true)<<std::endl;

		//Draw the polygon in the grayscale blured image
		Scalar color = Scalar(255, i*scale, 255-i*scale);
		drawContours(color_dst, contours2, i, color, 8, 8, hierarchy, 0, Point());

		// Compute the polygomn moments
		Moments m = moments(contours2[i], false);

		std::cout << " " << m.m10/m.m00 << ", " << m.m01/m.m00 << std::endl;

//		drawContours(color_dst, contours2, 1, color, 8, 8, hierarchy, 0, Point());
		points.insert(points.end(), contours2[i].begin(), contours2[i].end());
	}
	namedWindow("Detected Lines HighRes0", 0);
	imshow("Detected Lines HighRes0", color_dst);*/

	points.insert(points.end(), contours2[res[1]].begin(), contours2[res[1]].end());
	convexHull(cv::Mat(points), contours2[0]);

	int cNum = 0;
	//get bounding box
	out = boundingRect(contours2[cNum]);

	return out;
}

vector<int> polySearch(Point point, std::vector<Vec4i> hierarchy, std::vector<std::vector<Point> > contours, int current){
	// first index is whether the point is contained and second is which children has it.
	// Third is who is next
	vector<int> out(3);
	int* hEntry = hierarchy[current].val;
	int nextChild = hEntry[2], nextSibling = hEntry[0];
	// If point is not within current contour return -1
	if(pointPolygonTest(contours[current], point, false)<0){
		out[0]=-1;
		out[1]=-1;
	}else{
		//Otherwise check if contours has children containing the point
		out[0]=1;
		//Depth first search
		vector<int> ret;
		int childrenCount = 0;
		while(nextChild!=-1){
			ret = polySearch(point, hierarchy, contours, nextChild);
			childrenCount++;
			nextChild = ret[2];
		}
		//If there is only one children return it.
		if(childrenCount==1){
			out[1]=ret[1];
		}else{//If more than one children are contained returned the parent
			out[1]=current;
		}
	}
	out[2]=nextSibling;

	return out;
}

Rect highResBase(cv::Mat src){
	Mat src2, dst, color_dst;
	Rect out;

	//HighRes
	blur(src, src2, Size(40,40), Point(-1,-1), BORDER_REPLICATE);
	namedWindow("Blured HighRes Base", 0);
	imshow("Blured HighRes Base", src2);
//	threshold(src2, src2, 0,255,THRESH_BINARY_INV + THRESH_OTSU);
//	namedWindow("TH HighRes Base", 0);
//	imshow("TH HighRes Base", src2);

	Canny(src2, dst, 5, 180, 5); //(src2, dst, 50, 200, 3); 5 15 3
	namedWindow("Edges HighRes Base", 0);
	imshow("Edges HighRes Base", dst);

	cvtColor(dst, color_dst, CV_GRAY2BGR);

	std::vector<std::vector<Point> > contours, contours2;
	std::vector<Vec4i> hierarchy;
	/// Find contours
//	findContours( dst, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	findContours( dst, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_L1, Point(0, 0) );
	std::cout << contours.size() << std::endl; // prints !!!Hello World!!!

	contours2.resize(contours.size());
	for (size_t k = 0; k < contours.size(); k++)
		approxPolyDP(contours[k], contours2[k],arcLength(Mat(contours[k]), true)*0.02, true);

	std::cout << "Got Polygons..." << std::endl;

	// Draw contours
	cvtColor(src, color_dst, CV_GRAY2BGR);
	std::vector<cv::Point> points;
	for (int i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(255, 0, 0);
		drawContours(color_dst, contours2, i, color, 2, 8, hierarchy, 0, Point());
		points.insert(points.end(), contours2[i].begin(), contours2[i].end());
	}
	convexHull(cv::Mat(points), contours2[0]);

	int cNum = 0;
//	drawContours(color_dst, contours2, cNum, Scalar(255, 0, 0), 2, 8);

//	namedWindow("Source", 1);
//	imshow("Source", src);

	namedWindow("DLHiB", 0);
	imshow("DLHiB", color_dst);

	//get bounding box
	out = boundingRect(contours2[cNum]);
/*	rectangle(color_dst, out, Scalar(255,255,0), 8, 8, 0);

	namedWindow("Detected Lines HighRes", 0);
	imshow("Detected Lines HighRes", color_dst);

	std::cout<<out.width<<", "<<out.height<<std::endl;*/

	return out;
}
