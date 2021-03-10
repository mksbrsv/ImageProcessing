#include "gaussian_filter.h"
#define _USE_MATH_DEFINES
#include <math.h>

void gaussian_filter::init_gas_kernel(int radius, float sigma) {
	int size = 2 * radius + 1;
	m_kernel.resize(size);
	for(auto& x : m_kernel) {
		x.resize(size);
	}
	float norm = 0;
	float r;
	for (int i = -radius; i <= radius; i++) {
		for (int j = -radius; j <= radius; j++) {
			r = static_cast<float>(sqrt(i * i + j * j));
			m_kernel[i + radius][j + radius] = static_cast<float>(exp(-((r*r)/sigma))) / (M_PI * sigma);
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
	if (m_image.empty())
		throw std::logic_error("Can't open image");
	init_gas_kernel(radius, sigma);
}

cv::Mat gaussian_filter::make() {
	cv::Mat result_image(m_image.rows, m_image.cols, m_image.type());
	for(int y = 0; y < m_image.rows; y++) {
		for(int x = 0; x < m_image.cols; x++) {
			const auto pixel = get_new_pixel(x, y);
			result_image.at<cv::Vec3b>(cv::Point(x, y)) = pixel;
		}
	}
	return result_image;
}


