#include "erosion.h"

namespace morph {

	erosion::erosion(cv::Mat image, int size) : m_image(std::move(image)), m_size(size) {
		if (m_image.empty())
			throw std::logic_error("Can't open image");
	}

	cv::Vec3b erosion::get_new_pixel(int x, int y) {
		std::vector<cv::Vec3b> elems;
		cv::Vec3b c;
		std::vector<uchar> R;
		std::vector<uchar> G;
		std::vector<uchar> B;
		int radius = m_size / 2;
		int k = 0;

		for (int i = -radius; i <= radius; i++) {
			for (int j = -radius; j <= radius; j++) {
				if (x + j < 0 || y + i < 0 || m_image.cols - 1 < x + j || m_image.rows - 1 < y + i) {}
				else
				{
					elems.push_back(m_image.at<cv::Vec3b>(cv::Point(x + j, y + i)));
					B.push_back(elems[k][0]);
					G.push_back(elems[k][1]);
					R.push_back(elems[k][2]);
					k++;
				}
			}
		}
		std::sort(R.begin(), R.end());
		std::sort(B.begin(), B.end());
		std::sort(G.begin(), G.end());
		cv::Vec3b result_pixel = cv::Vec3b(B[0], G[0], R[0]);
		return result_pixel;
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
	
		for (int y = 0; y < m_image.rows; y++)
			for (int x = 0; x < m_image.cols; x++)
				result_image.at<cv::Vec3b>(cv::Point(x, y)) = get_new_pixel(x,y);
		return result_image;
	}
}
