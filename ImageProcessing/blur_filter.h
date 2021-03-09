#ifndef BLUR_FILTER_H
#define BLUR_FILTER_H
#include "matrix_filter.h"

class blur_filter : public matrix_filter{
public:
	blur_filter(cv::Mat image);
	cv::Mat make() override;
};
#endif
