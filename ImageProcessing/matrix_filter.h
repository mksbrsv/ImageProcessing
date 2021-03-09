#ifndef MATRIX_FILTER_H
#define MATRIX_FILTER_H
#include "filter.h"
#include <vector>

class matrix_filter : public filter {
	using nd_vec = std::vector<std::vector<float>>;
public:
	explicit matrix_filter(nd_vec&& kernel);
protected:
	matrix_filter();
	cv::Vec3b get_new_pixel(int x, int y) override;
	nd_vec m_kernel;
};
#endif
