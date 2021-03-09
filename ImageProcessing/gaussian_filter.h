#ifndef GAUSSIAN_H
#define GAUSSIAN_H
#include "matrix_filter.h"
#include <cmath>

class gaussian_filter : public matrix_filter {
public:
	void init_gas_kernel(int radius, float sigma);
	explicit gaussian_filter(int radius, float sigma, cv::Mat image);
	cv::Mat make() override; 
	
};
#endif
