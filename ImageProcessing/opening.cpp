#include "opening.h"
#include "dilation.h"
#include "erosion.h"
morph::opening::opening(cv::Mat image, int size, cv::Mat strc) : m_image(std::move(image)), m_size(size), m_strc(std::move(strc))
{
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

cv::Vec3b morph::opening::get_new_pixel(int x, int y)
{
    return cv::Vec3b();
}

cv::Mat morph::opening::make()
{
	cv::Mat img = m_image;
	morph::erosion ero(img, m_size, m_strc);
	cv::Mat ero_img = ero.make();
	morph::dilation dil(ero_img, m_size, m_strc);
	cv::Mat dil_img = dil.make();

	return dil_img;
}
