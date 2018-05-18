#ifndef __SQUARE_H__
#define __SQUARE_H__


#include "point.h"
#include "color.h"

class square {

private:
	double x;
	double y;

	color value;

	double width;

public:


// Squares are defined by upper left corner co-ordinate
// Their z co-ord is by default 0. Z refers to depth into the screen


	square();
	square(double width, double x, double y);
	point get_center();
	void set(double width, double x, double y);
	void set_value(color* val);
};


#endif
