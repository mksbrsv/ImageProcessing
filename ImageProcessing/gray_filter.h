#ifndef GRAY_H
#define GRAY_H
#include "filter.h"

// grayscale filter, use make() to do a filter 
class grayscale_filter : public filter {
public:
	explicit grayscale_filter(cv::Mat image);
	cv::Mat make() override;
private:
	cv::Vec3b get_new_pixel(int x, int y) override;
	cv::Mat m_image;
	
};
#endif
