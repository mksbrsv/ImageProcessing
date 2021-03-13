#include "morphology.h"

morphology::morphology(cv::Mat image) : m_image(std::move(image)) {
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

cv::Mat morphology::dilation() {
	return cv::Mat();
}

cv::Mat morphology::erosion() {
	return cv::Mat();
}

cv::Mat morphology::opening() {
	return cv::Mat();
}

cv::Mat morphology::closing() {
	return cv::Mat();
}
