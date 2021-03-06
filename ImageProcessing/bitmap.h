#ifndef BITMAP_H
#define BITMAP_H
#include <opencv2/opencv.hpp>
#include <string>

class bitmap {
public:
	explicit bitmap(const std::string& file);
	bitmap(const bitmap& bitmap) = default;
	bitmap& operator=(const bitmap& bitmap) = default;
	~bitmap() = default;

	void show(const std::string& window_name) const;
private:
	cv::Mat image;
	
};

#endif
