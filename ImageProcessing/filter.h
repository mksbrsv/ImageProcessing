#ifndef FILTER_H
#define FILTER_H
#include <opencv2/opencv.hpp>

class filter {
public:
	// return new color of pixel at point(x, y)
	virtual cv::Vec3b get_new_pixel(int x, int y) = 0;
	virtual cv::Mat make() = 0; 
	virtual ~filter() = default;
};

#endif
