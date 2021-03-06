#ifndef INVERS_FILTER
#define INVERS_FILTER
#include "filter.h"
#include "bitmap.h"

class inversion_filter : public filter{
public:
	explicit inversion_filter(const bitmap& image);
	bitmap make();
private:
	bitmap image;
	
};

#endif
