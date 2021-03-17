
#ifndef erosion_H
#define erosion_H
#include "filter.h"

namespace morph {
class erosion : public filter {
public:
	erosion(cv::Mat image);
	cv::Vec3b get_new_pixel(int x, int y) override;
	cv::Mat make() override;
private:
	cv::Mat m_image;
};
}
#endif
