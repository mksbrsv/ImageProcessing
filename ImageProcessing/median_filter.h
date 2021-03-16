#ifndef MEDIAN_H
#define MEDIAN_H
#include "matrix_filter.h"


class median_filter : public matrix_filter {
	using nd_vec = std::vector<std::vector<float>>;

public:
	median_filter(cv::Mat image);
	cv::Mat make() override;
	median_filter(nd_vec&& kernel, cv::Mat image);
private:
	cv::Vec3b get_new_pixel(int x, int y) override;
	cv::Mat m_image;
	
};

#endif
