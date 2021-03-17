#ifndef MORPHOLOGY_H
#define MORPHOLOGY_H
#include <opencv2/opencv.hpp>
#include "filter.h"

class morphology : public filter {
public:
	morphology(cv::Mat image);
	morphology(const morphology& morphology) = delete;
	cv::Vec3b get_new_pixel(int x, int y) override { return cv::Vec3b(); };
	cv::Vec3b get_new_pixel(int x, int y, cv::Mat& mask);
	cv::Mat make() override;

	void normalize(cv::Mat& image);
	bool is_satisfied(cv::Mat& part, cv::Mat& mask);

	cv::Mat dilation() const;
	cv::Mat erosion() const;
	cv::Mat opening() const;
	cv::Mat closing() const;

protected:
	cv::Mat m_image;

};



#endif
