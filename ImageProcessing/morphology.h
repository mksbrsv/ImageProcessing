#ifndef MORPHOLOGY_H
#define MORPHOLOGY_H
#include <opencv2/opencv.hpp>

class morphology {
public:
	morphology(cv::Mat image);
	morphology(const morphology& morphology) = delete;
	~morphology() = default;

	cv::Mat dilation() const;
	cv::Mat erosion() const;
	cv::Mat opening() const;
	cv::Mat closing() const;

protected:
	cv::Mat m_image;

};

#endif
