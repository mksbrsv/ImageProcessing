#ifndef MATRIX_FILTER_H
#define MATRIX_FILTER_H
#include "filter.h"

class matrix_filter : public filter {
public:
	using nd_vec = std::vector<std::vector<float>>;
	explicit matrix_filter(cv::Mat image);
	matrix_filter(nd_vec&& kernel, cv::Mat image);

protected:
	matrix_filter();
	cv::Vec3b get_new_pixel(int x, int y) override;
	nd_vec m_kernel;
	cv::Mat m_image;
};
#endif
