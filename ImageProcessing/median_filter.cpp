#include "median_filter.h"

median_filter::median_filter(cv::Mat image) : matrix_filter(), m_image(std::move(image)){
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

cv::Mat median_filter::make() {
	//auto im_gray = m_image;
	cv::cvtColor(m_image, m_image, cv::COLOR_BGR2GRAY);
	cv::Mat result_image(m_image.rows, m_image.cols, CV_8UC3);
	for (int y = 1; y < m_image.rows-1; y++) {
		for (int x = 1; x < m_image.cols-1; x++) {
			const auto pixel = get_new_pixel(x, y);
			result_image.at<cv::Vec3b>(cv::Point(x, y)) = pixel;
		}
	}
	cv::cvtColor(m_image, m_image, cv::COLOR_GRAY2BGR);

	return result_image;
}

median_filter::median_filter(nd_vec&& kernel, cv::Mat image) : matrix_filter(std::move(kernel), image) {
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

cv::Vec3b median_filter::get_new_pixel(int x, int y) {
	
	std::vector<uchar> tmp;
	tmp.reserve(9);
	tmp.resize(9);
	tmp[0] = m_image.at<uchar>(cv::Point(x-1, y - 1));
	tmp[1] = m_image.at<uchar>(cv::Point(x, y - 1));
	tmp[2] = m_image.at<uchar>(cv::Point(x + 1, y - 1));
	tmp[3] = m_image.at<uchar>(cv::Point(x - 1, y));
	tmp[4] = m_image.at<uchar>(cv::Point(x, y));
	tmp[5] = m_image.at<uchar>(cv::Point(x + 1, y));
	tmp[6] = m_image.at<uchar>(cv::Point(x - 1, y + 1));
	tmp[7] = m_image.at<uchar>(cv::Point(x , y + 1));
	tmp[8] = m_image.at<uchar>(cv::Point(x + 1, y + 1));

	std::sort(tmp.begin(),tmp.end());
	return tmp[4];


	
	/*cv::Vec3b result_pixel = cv::Vec3b(
		std::clamp(static_cast<int>(result_r), 0, 255),
		std::clamp(static_cast<int>(result_g), 0, 255),
		std::clamp(static_cast<int>(result_b), 0, 255));*/
	//return result_pixel;

}
