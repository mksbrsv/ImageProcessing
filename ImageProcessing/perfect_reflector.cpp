#include "perfect_reflector.h"

int Max_B;
int Max_G;
int Max_R;

int GetMax(cv::Mat image, uchar cn){
    int max = 0;
    for (int y = 0; y < image.rows; y++)
        for (int x = 0; x < image.cols; x++)
            if (image.at<cv::Vec3b>(cv::Point(x, y))[cn] > max)
                max = image.at<cv::Vec3b>(cv::Point(x, y))[cn];
    return max;
}

perfect_reflector::perfect_reflector(cv::Mat image) : filter(), m_image(std::move(image)) {
	Max_B = GetMax(m_image, 0);
	Max_G = GetMax(m_image, 1);
	Max_R = GetMax(m_image, 2);

	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

cv::Mat perfect_reflector::make(){
	cv::Mat result_image(m_image.rows, m_image.cols, CV_8UC3);
	for (int y = 0; y < m_image.rows; y++) {
		for (int x = 0; x < m_image.cols; x++) {
			const auto pixel = get_new_pixel(x, y);
			result_image.at<cv::Vec3b>(cv::Point(x, y)) = pixel;
		}
	}
	return result_image;
}

cv::Vec3b perfect_reflector::get_new_pixel(int x, int y)
{
	int brigt_of_B = m_image.at<cv::Vec3b>(cv::Point(x, y))[0] * (255 / Max_B);
	int brigt_of_G = m_image.at<cv::Vec3b>(cv::Point(x, y))[1] * (255 / Max_G);
	int brigt_of_R = m_image.at<cv::Vec3b>(cv::Point(x, y))[2] * (255 / Max_R);

	cv::Vec3b result_pixel = cv::Vec3b(brigt_of_B, brigt_of_G, brigt_of_R);
	return result_pixel;
}
