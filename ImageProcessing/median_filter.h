#ifndef MEDIAN_H
#define MEDIAN_H
#include "filter.h"

class median_filter : public filter {
public:
	median_filter(cv::Mat image);
	cv::Mat make() override;
private:
	cv::Mat m_image;
	std::vector<int> m_window;
	
};

#endif
