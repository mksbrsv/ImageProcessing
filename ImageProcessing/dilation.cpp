#include "dilation.h"

namespace morph {

	dilation::dilation(cv::Mat image) : m_image(std::move(image)) {
		cv::cvtColor(m_image, m_image, cv::COLOR_BGR2GRAY);
	}

	cv::Vec3b dilation::get_new_pixel(int x, int y) {
		cv::Vec3b pixel = m_image.at<cv::Vec3b>(cv::Point(x, y));
		if (!m_is_calculated) {
			calculate_contrast();
			m_is_calculated = true;
		}
		const auto intensity = static_cast<uchar>(pixel[0] - m_min / m_contrast * 255);
		cv::Vec3b result_pixel = { intensity, intensity, intensity };
		return result_pixel;
	}

	cv::Mat dilation::make() {
		cv::Mat result_image(m_image.rows, m_image.cols, CV_8UC3);
		for (int y = 0; y < m_image.rows; y++) {
			for (int x = 0; x < m_image.cols; x++) {
				const auto pixel = get_new_pixel(x, y);
				result_image.at<cv::Vec3b>(cv::Point(x, y)) = pixel;
			}
		}
		return result_image;

	}

	void dilation::calculate_contrast() {
		m_min = m_image.at<cv::Vec3b>(cv::Point(0, 0))[0];
		m_max = m_image.at<cv::Vec3b>(cv::Point(0, 0))[0];
		for (int y = 0; y < m_image.rows; y++) {
			for (int x = 0; x < m_image.cols; x++) {
				if (m_image.at<cv::Vec3b>(cv::Point(x, y))[0] < m_min)
					m_min = m_image.at<cv::Vec3b>(cv::Point(x, y))[0];
				if (m_image.at<cv::Vec3b>(cv::Point(x, y))[0] > m_max)
					m_max = m_image.at<cv::Vec3b>(cv::Point(x, y))[0];
			}
			m_contrast = m_max - m_min;
		}
	}

}
