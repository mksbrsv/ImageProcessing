﻿#include "gaussian_filter.h"

// radius will be 2 * radius + 1
void gaussian_filter::init_gas_kernel(int radius, float sigma) {
	int size = 2 * radius + 1;
	m_kernel.resize(size);
	for(auto& x : m_kernel) {
		x.resize(size);
	}
	float norm = 0;
	for (int i = -radius; i <= radius; i++) {
		for (int j = -radius; j <= radius; j++) {
			m_kernel[i + radius][j + radius] = static_cast<float>(exp(-(i * i + j * j))) / (sigma * sigma);
			norm += m_kernel[i + radius][j + radius];
		}
	}
	for(int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m_kernel[i][j] /= norm;
		}
	}
}

gaussian_filter::gaussian_filter(int radius, float sigma, cv::Mat image) : matrix_filter(std::move(image)) {
	init_gas_kernel(radius, sigma);
}

cv::Mat gaussian_filter::make() {
	cv::Mat result_image(m_image.rows, m_image.cols, CV_8UC3);
	for(int y = 0; y < m_image.rows; y++) {
		for(int x = 0; x < m_image.cols; x++) {
			const auto pixel = get_new_pixel(x, y);
			result_image.at<cv::Vec3b>(cv::Point(x, y)) = pixel;
		}
	}
	return result_image;
}

