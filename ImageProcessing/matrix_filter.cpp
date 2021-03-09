#include "matrix_filter.h"

matrix_filter::matrix_filter(nd_vec&& kernel) : m_kernel(kernel){
}

matrix_filter::matrix_filter() : m_kernel(0){
}

cv::Vec3b matrix_filter::get_new_pixel(int x, int y) {
	int radius_x = m_kernel.size() / 2;
	int radius_y = m_kernel[0].size() / 2;
	return cv::Vec3b();
}
