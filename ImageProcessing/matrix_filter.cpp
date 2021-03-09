#include "matrix_filter.h"

matrix_filter::matrix_filter(cv::Mat image) : m_image(std::move(image)) {
}

matrix_filter::matrix_filter(nd_vec&& kernel, cv::Mat image) : m_kernel(kernel), m_image(std::move(image)) {
}

matrix_filter::matrix_filter() : m_kernel(0){
}

cv::Vec3b matrix_filter::get_new_pixel(int x, int y) {
	const int radius_x = m_kernel.size() / 2;
	const int radius_y = m_kernel[0].size() / 2;
	float result_r = 0;
	float result_g = 0;
	float result_b = 0;
	for(int i = -radius_y; i <= radius_y; i++) {
		for (int j = -radius_x; j <= radius_x; j++) {
			const int id_x = std::clamp(x + j, 0, m_image.cols - 1);
			const int id_y = std::clamp(y + i, 0, m_image.rows - 1);
			cv::Vec3b neighbor_pixel = m_image.at<cv::Vec3b>(cv::Point(id_x, id_y));
			result_r += neighbor_pixel[0] * m_kernel[j + radius_x][ i + radius_y];
			result_g += neighbor_pixel[1] * m_kernel[j + radius_x][ i + radius_y];
			result_b += neighbor_pixel[2] * m_kernel[j + radius_x][ i + radius_y];
		}
	}
	cv::Vec3b result_pixel = cv::Vec3b(
		std::clamp(static_cast<int>(result_r), 0, 255),
		std::clamp(static_cast<int>(result_g), 0, 255),
		std::clamp(static_cast<int>(result_b), 0 , 255));
	return result_pixel;
}
