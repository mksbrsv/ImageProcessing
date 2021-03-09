#include "blur_filter.h"

blur_filter::blur_filter(cv::Mat image) : matrix_filter(std::move(image)) {
	if (m_image.empty())
		throw std::logic_error("Can't open image");
	int size_x = 17; 
	int size_y = 17;
	m_kernel.resize(size_y);
	for(auto& x : m_kernel) {
		x.resize(size_x);
	}
	for(auto& y : m_kernel) {
		for (auto& x : y) {
			x = 1.f / static_cast<float>(size_x * size_y);
		}
	}
	
}

cv::Mat blur_filter::make() {
	cv::Mat result_image(m_image.rows, m_image.cols, CV_8UC3);
	for(int y = 0; y < m_image.rows; y++) {
		for(int x = 0; x < m_image.cols; x++) {
			const auto pixel = get_new_pixel(x, y);
			result_image.at<cv::Vec3b>(cv::Point(x, y)) = pixel;
		}
	}
	return result_image;
}
