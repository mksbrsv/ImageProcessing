#include "median_filter.h"
#include <math.h>
bool median_filter::compare(cv::Mat& part, cv::Mat& mask)
{
	std::cout << part.size << "\t" << mask.size << std::endl;
	std::cout << mask.type() << part.type();
	for (int x = 0; x < part.rows; x++) {
		for (int y = 0; y < part.cols; y++) {
			if (part.at<uchar>(cv::Point(x, y)) != mask.at<uchar>(cv::Point(x, y)))
				return false;
		}
	}
	return true;
}

median_filter::median_filter(cv::Mat image, int size) : matrix_filter(), m_image(std::move(image)), m_size(size){
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

median_filter::median_filter(nd_vec&& kernel, cv::Mat image) : matrix_filter(std::move(kernel), image), m_size(kernel.size()) {
	if (m_image.empty())
		throw std::logic_error("Can't open image");
}

cv::Mat median_filter::make() {	
	cv::Mat result_image= m_image;
	for (int y = 0; y < m_image.rows; y++) {
		for (int x = 0; x < m_image.cols; x++) {
			const auto pixel = get_new_pixel(x, y);
			result_image.at<cv::Vec3b>(cv::Point(x, y)) = pixel;
		}
	}
	return result_image;
}

void quicksort(std::vector<uchar> arr, int left, int right) {
	int min = (left + right) / 2;
	//cout << "QS:" << left << "," << right << "\n";

	int i = left;
	int j = right;
	uchar pivot = arr[min];

	while (left < j || i < right)
	{
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;

		if (i <= j) {
			//std::swap(i, j, arr);
			i++;
			j--;
		}
		else {
			if (left < j)
				quicksort(arr, left, j);
			if (i < right)
				quicksort(arr, i, right);
			return;
		}
	}
}

cv::Vec3b median_filter::get_new_pixel(int x, int y) {
	std::vector<cv::Vec3b> pixels;
	std::vector<uchar> R;
	std::vector<uchar> G;
	std::vector<uchar> B;
	int radius = m_size / 2;
	int k = 0;
	for (int i = -radius; i <= radius; i++) {
		for (int j = -radius; j <= radius; j++) {
			if (x + j < 0 || y + i < 0 || m_image.cols - 1 < x + j || m_image.rows - 1 < y + i){}
			else
			{
				pixels.push_back(m_image.at<cv::Vec3b>(cv::Point(x + j, y + i)));
				B.push_back(pixels[k][0]);
				G.push_back(pixels[k][1]);
				R.push_back(pixels[k][2]);
				k++;
			}
		}
	}
	std::sort(R.begin(), R.end());
	std::sort(B.begin(), B.end());
	std::sort(G.begin(), G.end());
	const int center = k / 2;
	cv::Vec3b result_pixel = cv::Vec3b(B[center], G[center], R[center]);
	return result_pixel;
}

