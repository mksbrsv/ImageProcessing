#include "filter.h"
namespace morph {
	class opening : public filter {
	public:
		opening(cv::Mat image, int size, cv::Mat strc);
		cv::Vec3b get_new_pixel(int x, int y) override;
		cv::Mat make() override;
	private:
		cv::Mat m_image;
		size_t m_size;
		cv::Mat m_strc;

	};
}

