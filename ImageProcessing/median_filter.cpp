#include "median_filter.h"

median_filter::median_filter(cv::Mat image) : filter(), m_image(std::move(image)), m_window(9, 0) {
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

cv::Mat median_filter::make() {
}

void median_filter::insertion_sort() {
	for(auto it = m_window.begin(); it != m_window.end(); ++it) {
		const auto insertion_point = std::upper_bound(m_window.begin(), it, *it);
		std::rotate(insertion_point, it, it + 1);
	}
}
