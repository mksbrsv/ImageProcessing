#include "linear_tension.h"
namespace {
	int CB;
	int CG;
	int CR;
	int minB;
	int minG;
	int minR;
	int max;
}

int calculate_contrast(cv::Mat& image, uchar cn, int& min) {
    min = 255;
    max = 0;
    for (int y = 0; y < image.rows; y++) {
	    for (int x = 0; x < image.cols; x++) {
		    if (image.at<cv::Vec3b>(cv::Point(x, y))[cn] < min) {
			    min = image.at<cv::Vec3b>(cv::Point(x, y))[cn];
		    }
		    if (image.at<cv::Vec3b>(cv::Point(x, y))[cn] > max) {
			    max = image.at<cv::Vec3b>(cv::Point(x, y))[cn];
		    }
	    }
    }
    return max - min;
}

linear_tension::linear_tension(cv::Mat image) : filter(), m_image(std::move(image)) {
    CB = calculate_contrast(m_image, 0, minB);
    CG = calculate_contrast(m_image, 1, minG);
    CR = calculate_contrast(m_image, 2, minR);
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

cv::Mat linear_tension::make(){
	cv::Mat result_image(m_image.rows, m_image.cols, CV_8UC3);
	for (int y = 0; y < m_image.rows; y++) {
		for (int x = 0; x < m_image.cols; x++) {
			const auto pixel = get_new_pixel(x, y);
			result_image.at<cv::Vec3b>(cv::Point(x, y)) = pixel;
		}
	}
	return result_image;
}

cv::Vec3b linear_tension::get_new_pixel(int x, int y)
{
    const int intensity_of_B = (m_image.at<cv::Vec3b>(cv::Point(x, y))[0] - minB) * (255 - 0) / CB;
    const int intensity_of_G = (m_image.at<cv::Vec3b>(cv::Point(x, y))[1] - minG) * (255 - 0) / CG;
    const int intensity_of_R = (m_image.at<cv::Vec3b>(cv::Point(x, y))[2] - minR) * (255 - 0) / CR;

    cv::Vec3b result_pixel = cv::Vec3b(intensity_of_B, intensity_of_G, intensity_of_R);
    return result_pixel;
}
