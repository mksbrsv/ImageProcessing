#include "filter.h"
namespace morph {
	class grad : public filter {
	public:
		grad(cv::Mat image, int size, cv::Mat strc);
		cv::Vec3b get_new_pixel(int x, int y) override;
		cv::Vec3b get_new_pixel(int x, int y, cv::Mat& strc, cv::Mat& ero, cv::Mat& dil);

		cv::Mat make() override;
	private:
		cv::Mat m_image;
		size_t m_size;
		cv::Mat m_strc;

	};
}

