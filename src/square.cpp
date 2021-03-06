#include "color.cuh"
#include "square.h"
#include "point.h"

square::square() {
	this->x = 0;
	this->y = 0;
	
	this->width = 0;

}


square::square(double width, double x, double y) {


	this->x = x;
	this->y = y;

	this->width = width;

}


void square::set(double width, double x, double y) {
	this->x = x;
	this->y = y;
	this->width = width;
}


point square::get_center() {
	

	point pt(this->x + (this->width / 2.0), this->y + (this->width / 2.0), 0);


	return pt;
}

void square::set_value(color* val) {

	this->value.set_r(val->r());
	this->value.set_g(val->g());
	this->value.set_b(val->b());

}
