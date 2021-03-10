#include "filters.h"
void make_noise(cv::Mat& image) {
	cv::Mat noise(image.rows, image.cols, image.type());
	const float m = 34.f;
	const float sigma = 50.f;
	cv::randn(noise, m, sigma);
	image += noise;
}

int main() {
	cv::Mat img = cv::imread("C:\\Users\\arryo\\Pictures\\unn.png");
	//cv::Mat img = cv::imread("C:\\Users\\Layzeld\\Downloads\\pic\\Annotation 2020-12-03 142825.png");

	median_filter fil(img);
	cv::Mat res_img = fil.make();
	cv::imshow("inversion filter", img);
	cv::waitKey(0);

}