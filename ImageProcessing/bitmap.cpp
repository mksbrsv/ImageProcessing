#include "bitmap.h"

bitmap::bitmap(const std::string& file) : image(){
	image = cv::imread(file, 1);
	if (image.empty()) {
		throw std::logic_error("File is not correct");
	}
}

void bitmap::show(const std::string& window_name) const {
	cv::namedWindow(window_name);
	cv::imshow(window_name, image);
}

