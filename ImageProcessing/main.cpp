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
cv::Mat struct_elem(int size)
{
	unsigned int i;
	cv::Mat element;
	do
	{
		std::cout << "1 - A rectangular structuring element\n"
			<< "2 - A cross-shaped structuring element\n"
			<< "3 - An elliptic structuring element\n";

		std::cin >> i;
	} while (i > 3 || i < 1);
	switch (i)
	{
	case 1: element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(size, size), cv::Point(size / 2, size / 2)); break;
	case 2: element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(size, size), cv::Point(size / 2, size / 2)); break;
	case 3: element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(size, size), cv::Point(size / 2, size / 2)); break;

	default: element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(size, size), cv::Point(size / 2, size / 2)); break;
	}


	return element;
}

int main() {
	//cv::Mat img = cv::imread("C:\\Users\\arryo\\Pictures\\unn.png", cv::IMREAD_ANYCOLOR);
    cv::Mat img = cv::imread("C:\\Users\\Layzeld\\Downloads\\test\\aa.png");

   // make_noise(img);
    cv::imshow("orig",img);
	morph::closing fil(img,7, struct_elem(7));
	cv::Mat res_img = fil.make();

    cv::imshow("erosion", res_img);


	cv::waitKey(0);
}