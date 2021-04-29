#ifndef LINEAR_TENSION_H
#define LINEAR_TENSION_H
#include "filter.h"

// linear tension filter, use make() to do a filter
class linear_tension : public filter {
public:
	explicit linear_tension(cv::Mat image);
	cv::Mat make() override;
private:
	cv::Vec3b get_new_pixel(int x, int y) override;
	cv::Mat m_image;

};
#endif