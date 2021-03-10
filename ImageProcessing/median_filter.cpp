#include "median_filter.h"

median_filter::median_filter(cv::Mat image) : filter(), m_image(std::move(image)), m_window(9, 0) {
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

cv::Mat median_filter::make() {
	// TODO impl make for median

	cv::Mat result_image(m_image.rows, m_image.cols, m_image.type());

	return result_image;
}

cv::Vec3b median_filter::get_new_pixel(int x, int y) {
	return cv::Vec3b();
}

