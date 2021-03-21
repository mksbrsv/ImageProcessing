#include "filters.h"

void make_noise(cv::Mat &src) {
    cv::Mat noise(src.size(), src.type());
    float m = 34;
    float sigma = 5;
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
  //std::cout << "max pisky dash ebati";
  return r;
}


int main() {
	//cv::Mat img = cv::imread("C:\\Users\\arryo\\Pictures\\unn.png", cv::IMREAD_ANYCOLOR);
	cv::Mat img = cv::imread("C:\\Users\\Layzeld\\Downloads\\pic\\Annotation 2020-12-03 142825.png");
    //cv::Mat img = cv::imread("C:\\Users\\Layzeld\\Downloads\\pic\\Screenshot-1110 - Copy.png");
	cv::Mat img2 = cv::imread("C:\\Users\\Layzeld\\Downloads\\pic\\Annotation 2020-12-03 142825.png");

    make_noise(img);
	make_noise(img2);
    cv::imshow("noise",img);
    median_filter fil(img, 5);
	cv::Mat res_img = fil.make();
	cv::Mat res2_img ;

    cv::imshow("median_filter", res_img);
	cv::medianBlur(img2, res2_img,5);
	cv::imshow("medianBlur", res2_img);


	morphology mor(img);
	//cv::Mat res_img = mor.make();
	//cv::imshow("mor", res_img);
//    median_filter fil(img, 5);
//	cv::Mat res_img = fil.make();
//    cv::imshow("o", res_img);
//
	cv::waitKey(0);
}