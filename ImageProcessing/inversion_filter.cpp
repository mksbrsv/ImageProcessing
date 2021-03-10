#include "inversion_filter.h"

inversion_filter::inversion_filter(cv::Mat image) : filter(), m_image(std::move(image)) {
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

cv::Vec3b inversion_filter::get_new_pixel(int x, int y) {
	cv::Vec3b source_pixel = m_image.at<cv::Vec3b>(cv::Point(x, y));
	const auto r = 255 - source_pixel[0];
	const auto g = 255 - source_pixel[1];
	const auto b = 255 - source_pixel[2];
	cv::Vec3b result_pixel = cv::Vec3b(r, g, b);
	return result_pixel;
}

cv::Mat inversion_filter::make() {
	cv::Mat result_image(m_image.rows, m_image.cols, m_image.type());
	for (int y = 0; y < m_image.rows; y++) {
		for (int x = 0; x < m_image.cols; x++) {
			const auto pixel = get_new_pixel(x, y);
			result_image.at<cv::Vec3b>(cv::Point(x, y)) = pixel;
		}
	}
	return result_image;
}




