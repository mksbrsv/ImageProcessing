#include "Grad.h"
#include "dilation.h"
#include "erosion.h"
morph::grad::grad(cv::Mat image, int size, cv::Mat strc) : m_image(std::move(image)), m_size(size), m_strc(std::move(strc))
{
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

cv::Vec3b morph::grad::get_new_pixel(int x, int y)
{
	return cv::Vec3b();
}

cv::Vec3b morph::grad::get_new_pixel(int x, int y, cv::Mat& strc, cv::Mat& ero, cv::Mat& dil)
{

	uchar B = std::clamp(static_cast<int>(dil.at<cv::Vec3b>(cv::Point(x,y))[0])- static_cast<int>(ero.at<cv::Vec3b>(cv::Point(x, y))[0]),0,255);
	uchar G = std::clamp(static_cast<int>(dil.at<cv::Vec3b>(cv::Point(x, y))[1]) - static_cast<int>(ero.at<cv::Vec3b>(cv::Point(x, y))[1]), 0, 255);
	uchar R = std::clamp(static_cast<int>(dil.at<cv::Vec3b>(cv::Point(x, y))[2]) - static_cast<int>(ero.at<cv::Vec3b>(cv::Point(x, y))[2]), 0, 255);

	cv::Vec3b result_pixel = cv::Vec3b(B,G,R);
	return result_pixel;
}



cv::Mat morph::grad::make()
{
	cv::Mat img = m_image;
	morph::erosion ero(img, m_size, m_strc);
	morph::dilation dil(img, m_size,m_strc);

	cv::Mat ero_img = ero.make();
	cv::Mat dil_img = dil.make();

	cv::Mat result_image(m_image.rows, m_image.cols, CV_8UC3);
	std::cout << m_strc << "\n";
	for (int y = 0; y < m_image.rows; y++)
		for (int x = 0; x < m_image.cols; x++)
			result_image.at<cv::Vec3b>(cv::Point(x, y)) = get_new_pixel(x, y, m_strc, ero_img, dil_img);
	return result_image;

}


