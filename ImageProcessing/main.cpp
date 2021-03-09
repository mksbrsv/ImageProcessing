#include "filters.h"

int main() {
	cv::Mat img = cv::imread("C:\\Users\\arryo\\Pictures\\unn.png");
	//cv::Mat img = cv::imread("C:\\Users\\Layzeld\\Downloads\\pic\\Annotation 2020-12-03 142825.png");

    gaussian_filter fil(12, 4, img);
	cv::Mat res_img = fil.make();
	cv::imshow("inversion filter", res_img);
	cv::waitKey(0);

}