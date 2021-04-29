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

void choose_filter(cv::Mat& image, int choice) {
	using cv::imshow;
	switch(choice) {
	case 1: {
		grayscale_filter gray(image);
		imshow("grayscale", gray.make());
		break;
	}
	case 2: {
		inversion_filter inv(image);
		imshow("inversion", inv.make());
		break;
	}
	case 3: {
		blur_filter blue(image);
		imshow("blur", blue.make());
		break;
	}
	case 4: {
		gaussian_filter gaus(5, 3, image);
		imshow("gaussian", gaus.make());
		break;
	}
	case 5: {
		median_filter med(image, 7);
		imshow("median", med.make());
		break;
	}
	case 6: {
		morph::erosion ero(image, 7, struct_elem(7));
		imshow("erosion", ero.make());
		break;
	}
	case 7: {
		morph::dilation dil(image, 7, struct_elem(7));
		imshow("dilation", dil.make());
		break;
	}
	case 8: {
		morph::closing clo(image, 7, struct_elem(7));
		imshow("closing", clo.make());
		break;
	}
	case 9: {
		morph::opening ope(image, 7, struct_elem(7));
		imshow("opening", ope.make());
		break;
	}
	case 10: {
		perfect_reflector per(image);
		imshow("perfect reflector", per.make());
		break;
	}
	case 11: {
		linear_tension lin(image);
		imshow("linear tension", lin.make());
		break;
	}
	case 12: {
		morph::grad grad(image, 7, struct_elem(7));
		imshow("grad", grad.make());
		break;
	}
	case 13: {
		std::cout << "Exit.....\n";
		break;
	}
	default: 
		std::cout << "Wrong number\n";
		break;
	}
}

int main() {
	using std::cout;
	using std::cin;
	using std::endl;
	cv::Mat img = cv::imread("C:\\Users\\arryo\\Pictures\\unn.png", cv::IMREAD_ANYCOLOR);
    //cv::Mat img = cv::imread("C:\\Users\\Layzeld\\Downloads\\test\\aa.png");

	int choice = 0;
	while (true) {
		cout << "Choose a filter:\n";
		cout << "1 - Grayscale\n2 - Inversion\n3 - Blur\n4 - Gaussian Blur\n5 - Median\n6 - Erosion\n7 - Dilation\n8 - Closing\n9 - Opening\n10 - Perfect Reflector\n11 - Linear Tension\n12 - Grad\n13 - Exit\n>> ";
		cin >> choice;
		choose_filter(img, choice);
		if (choice == 13) break;
	}

   // make_noise(img);
//    cv::imshow("orig",img);
//	morph::closing fil(img,7, struct_elem(7));
//	cv::Mat res_img = fil.make();
//
//    cv::imshow("erosion", res_img);
//
//
//	cv::waitKey(0);
}