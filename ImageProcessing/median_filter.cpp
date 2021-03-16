#include "median_filter.h"

median_filter::median_filter(cv::Mat image, int size) : matrix_filter(), m_image(std::move(image)), m_size(size){
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

median_filter::median_filter(nd_vec&& kernel, cv::Mat image) : matrix_filter(std::move(kernel), image) {
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

cv::Mat median_filter::make() {	
	cv::Mat result_image(m_image.rows, m_image.cols, CV_8UC3);
	for (int y = 0; y < m_image.rows - m_size; y++) {
		for (int x = 0; x < m_image.cols - m_size; x++) {
			const auto pixel = get_new_pixel(x, y);
			result_image.at<cv::Vec3b>(cv::Point(x, y)) = pixel;
		}
	}
	// TODO: fix cropping image
	const int width = result_image.rows;
	const int height = result_image.cols;
	cv::Rect crop(0, 0, width - m_size * 3, height - m_size * 3);
	result_image = result_image(crop);
	return result_image;
}


cv::Vec3b median_filter::get_new_pixel(int x, int y) {
	std::vector<cv::Vec3b> pixels;
	int vec_size = m_size * m_size;
	pixels.reserve(vec_size);
	pixels.resize(vec_size);
	int k = 0;
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			pixels[k] = m_image.at<cv::Vec3b>(cv::Point(x + j, y + i));
			k++;
		}
	}
	cv::Vec3b tmp_pixel;
	for (int i = 1; i < pixels.size(); i++) {
		for (int j = 0; j < pixels.size() - 1; j++) {
			if (pixels[j][0] > pixels[j + 1][0]) {
				tmp_pixel = pixels[j];
				pixels[j] = pixels[j + 1];
				pixels[j + 1] = tmp_pixel;
			}
		}
	}
	const int center = vec_size / 2;
	return pixels[center];
}

