#pragma once
#include "filter.h"
namespace morph {
class dilation : public filter {
public:
	dilation(cv::Mat image, int size = 1);
	cv::Vec3b get_new_pixel(int x, int y) override;
	cv::Mat make() override;
	cv::Vec3b calculate_maximum(cv::Vec3b res, cv::Vec3b cur, uchar mask) const;
private:
	cv::Mat m_image;
	cv::Mat m_struct_element;
	int m_struct_size;
};
}

