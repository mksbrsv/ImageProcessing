
#ifndef erosion_H
#define erosion_H
#include "filter.h"

namespace morph {
class erosion : public filter {
public:
	erosion(cv::Mat image, int size);
	cv::Vec3b get_new_pixel(int x, int y) override;
	cv::Vec3b calculate_new_pixel(cv::Vec3b result, cv::Vec3b current) const;
	cv::Mat make() override;
private:
	cv::Mat m_image;
	int m_mask = 0;
	size_t m_size;
};
}
#endif
