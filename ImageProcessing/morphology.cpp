#include "morphology.h"

morphology::morphology(cv::Mat image) : m_image(std::move(image)) {
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

cv::Mat morphology::dilation() {
}

cv::Mat morphology::erosion() {
}

cv::Mat morphology::opening() {
}

cv::Mat morphology::closing() {
}
