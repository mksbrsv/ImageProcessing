#include "median_filter.h"

median_filter::median_filter(cv::Mat image) : matrix_filter(), m_image(std::move(image)){
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

cv::Mat median_filter::make() {	
	cv::Mat result_image(m_image.rows, m_image.cols, CV_8UC3);
	for (int y = 1; y < m_image.rows - 1; y++) {
		for (int x = 1; x < m_image.cols - 1; x++) {
			const auto pixel = get_new_pixel(x, y);
			result_image.at<cv::Vec3b>(cv::Point(x, y)) = pixel;
		}
	}
	result_image.resize(result_image.rows - 1, result_image.cols - 1);
	return result_image;
}

median_filter::median_filter(nd_vec&& kernel, cv::Mat image) : matrix_filter(std::move(kernel), image) {
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

cv::Vec3b median_filter::get_new_pixel(int x, int y) {
	std::vector<cv::Vec3b> pixels;
	pixels.reserve(9);
	pixels.resize(9);
	pixels[0] = m_image.at<cv::Vec3b>(cv::Point(x - 1, y - 1));
	pixels[1] = m_image.at<cv::Vec3b>(cv::Point(x, y - 1));
	pixels[2] = m_image.at<cv::Vec3b>(cv::Point(x + 1, y - 1));
	pixels[3] = m_image.at<cv::Vec3b>(cv::Point(x - 1, y));
	pixels[4] = m_image.at<cv::Vec3b>(cv::Point(x, y));
	pixels[5] = m_image.at<cv::Vec3b>(cv::Point(x + 1, y));
	pixels[6] = m_image.at<cv::Vec3b>(cv::Point(x - 1, y + 1));
	pixels[7] = m_image.at<cv::Vec3b>(cv::Point(x, y + 1));
	pixels[8] = m_image.at<cv::Vec3b>(cv::Point(x + 1, y + 1));

	cv::Vec3b tmp_pixel;
	for (int i = 1; i < pixels.size(); i++)
		for (int j = 0; j < pixels.size() - 1; j++) {
			if (pixels[j][0] > pixels[j + 1][0]) {
				tmp_pixel = pixels[j];
				pixels[j] = pixels[j + 1];
				pixels[j + 1] = tmp_pixel;
			}
		}
	cv::Vec3b result_pixel = cv::Vec3b(pixels[4][0], pixels[4][1], pixels[4][2]);
	return result_pixel;
}


