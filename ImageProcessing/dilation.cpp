#include "dilation.h"

namespace morph {

	dilation::dilation(cv::Mat image, int size) : m_image(std::move(image)), m_struct_size(size) {
		if (m_image.empty())
			throw std::logic_error("Can't open image");
		m_struct_element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * m_struct_size + 1, 2 * m_struct_size + 1), cv::Point(m_struct_size, m_struct_size));
	}

	cv::Vec3b dilation::get_new_pixel(int x, int y) {
		return cv::Vec3b();
	}

	cv::Mat dilation::make() {
		cv::Mat result_image(m_image.rows, m_image.cols, CV_8UC3);
		cv::Vec3b result_pixel(0, 0, 0);
		cv::Vec3b current_pixel(0, 0, 0);
		uchar mask_i = 0;
		for (int y = 1; y < m_image.rows - 1; y++) {
			for (int x = 1; x < m_image.cols - 1; x++) {
				uchar b = 0;
				for (int j = -m_struct_size; j < m_struct_size; j++) {
					for (int i = -m_struct_size; i < m_struct_size; i++) {
						if (m_struct_element.at<uchar>(cv::Point(i, j)) && m_image.at<cv::Vec3b>(cv::Point(x + i, y + j))[0] > b) {
							b = m_image.at<cv::Vec3b>(cv::Point(x + i, y + j))[0];
							result_pixel = m_image.at<cv::Vec3b>(cv::Point(x + i, y + j));
						}
					}
				}
				result_image.at<cv::Vec3b>(cv::Point(x, y)) = result_pixel;
			}
		}
		//cv::dilate(m_image, result_image, m_struct_element);
		return result_image;
	}

	cv::Vec3b dilation::calculate_maximum(cv::Vec3b res, cv::Vec3b cur, uchar mask) const {
		if (mask == 1) {
			const int b = std::max(res[0], cur[0]);
			const int g = std::max(res[1], cur[1]);
			const int r = std::max(res[2], cur[2]);
			return cv::Vec3b(std::clamp(b, 0, 255), std::clamp(g, 0, 255), std::clamp(r, 0, 255));
		}
		return res;
	}

}
