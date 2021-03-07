#ifndef INVERS_FILTER
#define INVERS_FILTER
#include "filter.h"

class inversion_filter : public filter {
public:
	explicit inversion_filter(const cv::Mat& image);
	explicit inversion_filter(cv::Mat&& image);
	cv::Vec3b get_new_pixel(int x, int y) override;
	cv::Mat make();
private:
	cv::Mat m_image;
	
};

#endif
