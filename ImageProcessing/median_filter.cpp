#include "median_filter.h"

median_filter::median_filter(cv::Mat image,int size) : matrix_filter(), m_image(std::move(image)), size(size){
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

cv::Mat median_filter::make() {	
	cv::Mat result_image(m_image.rows, m_image.cols, CV_8UC3);
	for (int y = 0; y < m_image.rows; y++) {
		for (int x = 0; x < m_image.cols; x++) {
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
	int vec_size = size * size;
	tmp.reserve(vec_size);
	tmp.resize(vec_size);
	int k = 0;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) {
			tmp[k] = m_image.at<cv::Vec3b>(cv::Point(x + j, y + i));
			k++;
		}
	cv::Vec3b t;
	for (int i = 1; i < tmp.size(); i++)
		for (int j = 0; j < tmp.size() - 1; j++) {
			if (tmp[j][0] > tmp[j + 1][0]) {
				t = tmp[j];
				tmp[j] = tmp[j + 1];
				tmp[j + 1] = t;
			}
			}
	int m = vec_size / 2;
	return tmp[m];
}
}
