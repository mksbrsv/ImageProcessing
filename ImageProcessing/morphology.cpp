#include "morphology.h"

morphology::morphology(cv::Mat image) : m_image(std::move(image)) {
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

cv::Vec3b morphology::get_new_pixel(int x, int y, cv::Mat& mask) {
	return cv::Vec3b();
}

cv::Mat morphology::make() {
	cv::Mat result_image = m_image.clone();
	const int morph_size = 1;
	cv::Mat struct_element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * morph_size + 1, 2 * morph_size + 1), cv::Point(morph_size, morph_size));
	cv::Mat tmp(struct_element.rows, struct_element.cols, CV_8UC3);
	cv::Vec3b pic = { 23, 124, 255 };
	
	for(int y = morph_size; y < m_image.rows-morph_size; y++) {
		for(int x = morph_size; x < m_image.cols-morph_size; x++) {
			const auto pixel = get_new_pixel(x, y, struct_element);
			result_image.at<cv::Vec3b>(cv::Point(x, y)) = pixel;
		}
	}
	return result_image;
}

void morphology::normalize(cv::Mat& image) {
	//image.convertTo(image, CV_32F, 1.f / 255); // convert to 32 bit float image
	image.convertTo(image, CV_8UC1, 1.f / 255); // convert to 1 channel 8 bit usigned (binary) image
}

bool morphology::is_satisfied(cv::Mat& part, cv::Mat& mask) {
	std::cout << part.size << "\t" << mask.size << std::endl;
	std::cout << mask.type() << part.type();
	for (int x = 0; x < part.rows; x++) {
		for (int y = 0; y < part.cols; y++) {
			if (part.at<uchar>(cv::Point(x, y)) != mask.at<uchar>(cv::Point(x, y)))
				return false;
		}
	}
	return true;
}


cv::Mat morphology::dilation() const {
	cv::Mat result_image(m_image.rows, m_image.cols, CV_8UC3);
	return result_image;
}

cv::Mat morphology::erosion() const {
	cv::Mat result_image(m_image.rows, m_image.cols, CV_8UC3);

	return result_image;
}

cv::Mat morphology::opening() const {
	cv::Mat result_image(m_image.rows, m_image.cols, CV_8UC3);

	return result_image;
}

cv::Mat morphology::closing() const {
	cv::Mat result_image(m_image.rows, m_image.cols, CV_8UC3);

	return result_image;
}
