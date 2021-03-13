#ifndef MORPHOLOGY_H
#define MORPHOLOGY_H
#include <opencv2/opencv.hpp>

class morphology {
public:
	morphology(cv::Mat image);
	morphology(const morphology& morf) = delete;
	~morphology() = default;

	cv::Mat dilation();
	cv::Mat erosion();
	cv::Mat opening();
	cv::Mat closing();

protected:
	cv::Mat m_image;
	
};

#endif
