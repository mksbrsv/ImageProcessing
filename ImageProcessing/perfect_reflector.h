#ifndef PERFECT_REFLECTOR_H
#define PERFECT_REFLECTOR_H
#include "filter.h"

// perfect reflector filter, use make() to do a filter
class perfect_reflector : public filter {
public:
	explicit perfect_reflector(cv::Mat image);
	cv::Mat make() override;
private:
	cv::Vec3b get_new_pixel(int x, int y) override;
	cv::Mat m_image;

};

#endif
