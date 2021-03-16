#include "morphology.h"

morphology::morphology(cv::Mat image) : m_image(std::move(image)) {
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

cv::Mat morphology::dilation() const {
	cv::Mat result_image = m_image.clone();
	return result_image;
}

cv::Mat morphology::erosion() const {
	return cv::Mat();
}

cv::Mat morphology::opening() const {
	return cv::Mat();
}

cv::Mat morphology::closing() const {
	return cv::Mat();
}
