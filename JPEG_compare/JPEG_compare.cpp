// test.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main()
{
	string file;
	string name;
	cout << "Please enter the file directory :";
	cin >> file;
	cout << "Please enter the file name :";
	cin >> name;

	string fname1 = file + "\\" + name + "_gray.bmp";
	string fname2 = file + "\\" + name + ".jpg";
	string fname3 = file + "\\" + name + "_compare_color.bmp";
	string fname4 = file + "\\" + name + "_compare_gray.bmp";
	string fname5 = file + "\\" + name + "_compare_combine.bmp";
	Mat image1 = imread(fname1,0);
	Mat image2 = imread(fname2,0);

	Mat image3(image1.rows, image1.cols, CV_8UC3, Scalar(0, 0, 0));
	Mat image4(image1.rows, image1.cols, CV_8UC1, Scalar(0, 0, 0));
	int d1 = 0;
	int d2 = 0;
	int posdpeak = 0;
	int negdpeak = 0;

	for (int i = 0; i < image1.rows; ++i)
	{
		for (int j = 0; j < image1.cols; ++j)
		{
			if (image1.at<uchar>(i, j) - image2.at<uchar>(i, j) > 0)
			{
				image3.at<Vec3b>(i, j)[0] = 0;
				image3.at<Vec3b>(i, j)[1] = 0;
				image3.at<Vec3b>(i, j)[2] = (image1.at<uchar>(i, j) - image2.at<uchar>(i, j))*10;
				/*image3.at<Vec3b>(i, j)[2] = 255;*/
				image4.at<uchar>(i, j) = image1.at<uchar>(i, j) - image2.at<uchar>(i, j);
				d1 += image1.at<uchar>(i, j) - image2.at<uchar>(i, j);
				d2 += pow(image1.at<uchar>(i, j) - image2.at<uchar>(i, j), 2);
				if (image1.at<uchar>(i, j) - image2.at<uchar>(i, j) > posdpeak)
					posdpeak = image1.at<uchar>(i, j) - image2.at<uchar>(i, j);
			}
			else if (image1.at<uchar>(i, j) - image2.at<uchar>(i, j) < 0)
			{
				image3.at<Vec3b>(i, j)[0] = (-image1.at<uchar>(i, j) + image2.at<uchar>(i, j))*10;
				/*image3.at<Vec3b>(i, j)[0] = 255;*/
				image3.at<Vec3b>(i, j)[1] = 0;
				image3.at<Vec3b>(i, j)[2] = 0;
				image4.at<uchar>(i, j) = -image1.at<uchar>(i, j) + image2.at<uchar>(i, j);
				d1 += -image1.at<uchar>(i, j) + image2.at<uchar>(i, j);
				d2 += pow(-image1.at<uchar>(i, j) + image2.at<uchar>(i, j), 2);
				if (image1.at<uchar>(i, j) - image2.at<uchar>(i, j) < negdpeak)
					negdpeak = image1.at<uchar>(i, j) - image2.at<uchar>(i, j);
			}
		}
	}

	Mat image5(image1.rows, image1.cols, CV_8UC3, Scalar(0, 0, 0));
	for (int i = 0; i < image1.rows; ++i)
	{
		for (int j = 0; j < image1.cols; ++j)
		{
			image5.at<Vec3b>(i, j)[0] = image1.at<uchar>(i, j);
			image5.at<Vec3b>(i, j)[1] = image1.at<uchar>(i, j);
			image5.at<Vec3b>(i, j)[2] = image1.at<uchar>(i, j);
			if (abs(image1.at<uchar>(i, j) - image2.at<uchar>(i, j)) >= 10)
				image5.at<Vec3b>(i, j)[2] = 255;
		}
	}
	cout << "d1\t=\t" << d1 << endl;
	cout << "d2\t=\t" << d2 << endl;
	cout << "positive dpeak\t=\t" << posdpeak << endl;
	cout << "negative dpeak\t=\t" << negdpeak << endl;

	imwrite(fname3, image3);
	imwrite(fname4, image4);
	imwrite(fname5, image5);

	system("pause");

	return 0;
}


