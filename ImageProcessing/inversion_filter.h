#ifndef INVERS_FILTER
#define INVERS_FILTER
#include "filter.h"

// inversion filter, use make() to do a filter
class inversion_filter : public filter {
public:
	explicit inversion_filter(cv::Mat image);
	cv::Mat make() override;
private:
	cv::Vec3b get_new_pixel(int x, int y) override;
	cv::Mat m_image;
	
};

#endif
