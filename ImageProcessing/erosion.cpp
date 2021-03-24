#include "erosion.h"

namespace morph {

	erosion::erosion(cv::Mat image) : m_image(std::move(image)){
	}

	cv::Vec3b erosion::get_new_pixel(int x, int y) {
		return cv::Vec3b();
	}

	cv::Vec3b erosion::calculate_new_pixel(cv::Vec3b result, cv::Vec3b current) const {
		if (m_mask == 1) {
			const int b = std::max(result[0], current[0]);
			const int g = std::max(result[1], current[1]);
			const int r = std::max(result[2], current[2]);
			return cv::Vec3b(std::clamp(b, 0, 255), std::clamp(g, 0, 255), std::clamp(r, 0, 255));
		}
		return result;
	}

	cv::Mat erosion::make() {
		cv::Mat result_image(m_image.rows, m_image.cols, CV_8UC3);
		cv::Vec3b result_pixel = { 0, 0, 0 };
		const int morph_size = 1;
		cv::Mat struct_element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * morph_size + 1, 2 * morph_size + 1), cv::Point(morph_size, morph_size));
		for (int y = 1; y < m_image.rows-1; y++) {
			for (int x = 1; x < m_image.cols-1; x++) {
				for(int j = -1; j <= 1; j++) {
					for (int i = -1; i <= 1; i++) {
						cv::Vec3b current_pixel = m_image.at<cv::Vec3b>(cv::Point(x + i, y + j));
						m_mask = struct_element.at<uchar>(cv::Point(1 + i, 1 + j));
						result_pixel = calculate_new_pixel(result_pixel, current_pixel);
					}
				}
				result_image.at<cv::Vec3b>(cv::Point(x, y)) = result_pixel;
			}
		}
		return result_image;
	}
}
