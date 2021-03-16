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

	return result_image;
}

median_filter::median_filter(nd_vec&& kernel, cv::Mat image) : matrix_filter(std::move(kernel), image) {
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

cv::Vec3b median_filter::get_new_pixel(int x, int y) {
	
	std::vector<cv::Vec3b> tmp;
	tmp.reserve(9);
	tmp.resize(9);
	tmp[0] = m_image.at<cv::Vec3b>(cv::Point(x-1, y - 1));
	tmp[1] = m_image.at<cv::Vec3b>(cv::Point(x, y - 1));
	tmp[2] = m_image.at<cv::Vec3b>(cv::Point(x + 1, y - 1));
	tmp[3] = m_image.at<cv::Vec3b>(cv::Point(x - 1, y));
	tmp[4] = m_image.at<cv::Vec3b>(cv::Point(x, y));
	tmp[5] = m_image.at<cv::Vec3b>(cv::Point(x + 1, y));
	tmp[6] = m_image.at<cv::Vec3b>(cv::Point(x - 1, y + 1));
	tmp[7] = m_image.at<cv::Vec3b>(cv::Point(x , y + 1));
	tmp[8] = m_image.at<cv::Vec3b>(cv::Point(x + 1, y + 1));

	cv::Vec3b t;
	for (int i = 1; i < tmp.size(); i++)
		for (int j = 0; j < tmp.size() - 1; j++) {
			if (tmp[j][0] > tmp[j + 1][0]) {
				t = tmp[j];
				tmp[j] = tmp[j + 1];
				tmp[j + 1] = t;
			}
		}
	cv::Vec3b result_pixel = cv::Vec3b(tmp[4][0], tmp[4][1], tmp[4][2]);
	return result_pixel;

}
