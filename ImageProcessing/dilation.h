#pragma once
#include "filter.h"
namespace morph {
class dilation : public filter {
public:
	dilation(cv::Mat image);
	cv::Vec3b get_new_pixel(int x, int y) override;
	cv::Mat make() override;
private:
	void calculate_contrast();
	cv::Mat m_image;
	int m_min = 0;
	int m_max = 0;
	int m_contrast = 0;
	bool m_is_calculated = false;
};
}

