#include "median_filter.h"

median_filter::median_filter(cv::Mat image) : filter(), m_image(std::move(image)), m_window(9, 0) {
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

cv::Mat median_filter::make() {
	return cv::Mat();
}

