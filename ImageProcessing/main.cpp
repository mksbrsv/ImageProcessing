#include "filters.h"

void make_noise(cv::Mat &src) {
    cv::Mat noise(src.size(), src.type());
    float m = 34;
    float sigma = 20;
    cv::randn(noise, m, sigma); //mean and variance
    src += noise;
}
std::string type2str(int type) {
  std::string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
  case CV_8U: r = "8U";
	  break;
  case CV_8S: r = "8S";
	  break;
  case CV_16U: r = "16U";
	  break;
  case CV_16S: r = "16S";
	  break;
  case CV_32S: r = "32S";
	  break;
  case CV_32F: r = "32F";
	  break;
  case CV_64F: r = "64F";
	  break;
  default: r = "User";
	  break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

int main() {
	cv::Mat img = cv::imread("C:\\Users\\arryo\\Pictures\\index.png", cv::IMREAD_ANYCOLOR);
	//cv::Mat img = cv::imread("C:\\Users\\Layzeld\\Downloads\\pic\\Annotation 2020-12-03 142825.png");
    //cv::Mat img = cv::imread("C:\\Users\\Layzeld\\Downloads\\pic\\Screenshot-1110.png");

	morph::erosion mor(img);
	int morph_size = 1;
	cv::Mat se = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * morph_size + 1, 2 * morph_size + 1), cv::Point(morph_size, morph_size));
	cv::Vec3b p = se.at<cv::Vec3b>(cv::Point(0, 0));
	std::cout << p;
	cv::Mat res_img = mor.make();
	cv::imshow("mor", res_img);
	cv::Mat out;
	cv::dilate(img, out, se, cv::Point(morph_size, morph_size));
	cv::imshow("out", out);
	std::cout << "img chan" << img.channels() << std::endl;
	std::cout << "res_img chan" << img.channels() << std::endl;
	std::cout << "img type" << img.type() << std::endl;
	std::cout << "res_img type" << img.type() << std::endl;
//    median_filter fil(img, 5);
//	cv::Mat res_img = fil.make();
//    cv::imshow("o", res_img);
//
	cv::waitKey(0);
}