#include "filter.h"
namespace morph {
class dilation : public filter {
public:
	dilation(cv::Mat image, int size, cv::Mat strc);
	cv::Vec3b get_new_pixel(int x, int y) override;
	cv::Vec3b get_new_pixel(int x, int y, cv::Mat& strc);

	cv::Mat make() override;
private:
	//void calculate_contrast();
	cv::Mat m_image;
	size_t m_size;
	cv::Mat m_strc;

};
}

