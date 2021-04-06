#include "closing.h"
#include "dilation.h"
#include "erosion.h"
morph::closing::closing(cv::Mat image, int size, cv::Mat strc) : m_image(std::move(image)), m_size(size), m_strc(std::move(strc))
{
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

cv::Vec3b morph::closing::get_new_pixel(int x, int y)
{
	return cv::Vec3b();
}

cv::Mat morph::closing::make()
{
	cv::Mat img = m_image;
	morph::dilation dil(img, m_size, m_strc);
	cv::Mat dil_img = dil.make();
	morph::erosion ero(dil_img, m_size, m_strc);
	cv::Mat ero_img = ero.make();

	return ero_img;
}
