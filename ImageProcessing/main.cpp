#include "filters.h"

   void make_noise(cv::Mat &src)
{
    cv::Mat noise(src.size(), src.type());
    float m = 34;
    float sigma = 50;
    cv::randn(noise, m, sigma); //mean and variance
    src += noise;
}
std::string type2str(int type) {
  std::string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

int main() {
	//cv::Mat img = cv::imread("C:\\Users\\arryo\\Pictures\\unn.png", cv::IMREAD_ANYCOLOR);
	//cv::Mat img = cv::imread("C:\\Users\\Layzeld\\Downloads\\pic\\Annotation 2020-12-03 142825.png");
    cv::Mat img = cv::imread("C:\\Users\\Layzeld\\Downloads\\pic\\gig8E.png");
    //make_noise(img);
    cv::imshow("noise",img);
    median_filter fil(img, 7);
	cv::Mat res_img = fil.make();
    cv::imshow("o", res_img);

    //cv::medianBlur(img, res_img, 13);
	//cv::imshow("n", res_img);
	cv::waitKey(0);

}