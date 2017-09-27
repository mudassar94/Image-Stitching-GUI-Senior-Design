#pragma unmanaged

#include <opencv2\opencv.hpp>
#pragma managed

#include "Stitcher.hpp"
//#include <cstdio>
#include <fstream>

using namespace std;
using namespace cv;

int make_panorama(const std::vector<std::string> &fileNames) {
	// Open a Log file
	ofstream logFile;
	logFile.open("Log.txt");

	// Define mode for stitching as panoroma 
	// (One out of many functions of Stitcher)
	Stitcher::Mode mode = Stitcher::PANORAMA;

	// Array for pictures
	vector<Mat> imgs;

	// Get all the images that need to be 
	// stitched as with their names and paths passed through fileNames
	for (int i = 0; i < fileNames.size(); ++i)
	{
		// Read the ith argument or image 
		// and push into the image array
		Mat img = imread(fileNames[i]);
		if (img.empty())
		{
			// Exit if image is not present
			logFile << "Can't read image '" << fileNames[i] << "'\n";
			return -1;
		}
		imgs.push_back(img);
	}

	// Define object to store the stitched image
	Mat pano;

	// Create a Stitcher class object with mode panoroma
	Ptr<Stitcher> stitcher = Stitcher::create(mode, false);

	// Command to stitch all the images present in the image array
	Stitcher::Status status = stitcher->stitch(imgs, pano);

	if (status != Stitcher::OK)
	{
		// Check if images could not be stiched
		// status is OK if images are stiched successfully
		logFile << "Can't stitch images\n";
		return -1;
	}

	// Store a new image stiched from the given 
	//set of images as "result.jpg"
	imwrite("result.jpg", pano);

	logFile << "All is good!\n";
	logFile.close();

	return 0;
}
