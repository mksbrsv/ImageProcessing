#include "gray_filter.h"

grayscale_filter::grayscale_filter(cv::Mat image) : filter(), m_image(std::move(image)) {
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

cv::Vec3b grayscale_filter::get_new_pixel(int x, int y) {
	cv::Vec3b source_pixel = m_image.at<cv::Vec3b>(cv::Point(x, y));
	const auto r = (0.36 * source_pixel[0]);
	const auto g = (0.53 * source_pixel[1]);
	const auto b = (0.11 * source_pixel[2]);
	const auto gray = r + g + b;
	cv::Vec3b result_pixel = cv::Vec3b(gray, gray, gray);
	return result_pixel;
}

cv::Mat grayscale_filter::make() {
	cv::Mat result_image(m_image.rows, m_image.cols, CV_8UC3);
	for(int y = 0; y < m_image.rows; y++) {
		for(int x = 0; x < m_image.cols; x++) {
			const auto pixel = get_new_pixel(x, y);
			result_image.at<cv::Vec3b>(cv::Point(x, y)) = pixel;
		}
	}
	return result_image;
}
