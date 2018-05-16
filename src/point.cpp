

#include <math.h>

#include "ray.h"

using namespace std;


point::point() {


}

double point::distance(point* a, point* b) {

    double xd = a->x - b->x;
    double yd = a->y - b->y;
    double zd = a->z - b->z;

    return sqrt((xd*xd) + (yd*yd) + (zd*zd));

}

double point::distance2(point* a, point* b) {

    double xd = a->x - b->x;
    double yd = a->y - b->y;
    double zd = a->z - b->z;

    return (xd*xd) + (yd*yd) + (zd*zd);

}


double point::get_x() const {
    return this->x;
}

double point::get_y() const {
    return this->y;
}

double point::get_z() const {
    return this->z;
}


point point::operator+ (const point& b) {

    return point(
                    b.get_x() + this->get_x(),
                    b.get_y() + this->get_y(),
                    b.get_z() + this->get_z()
                );


}


point point::operator- (const point& b) {

    return point(
                    -b.get_x() + this->get_x(),
                    -b.get_y() + this->get_y(),
                    -b.get_z() + this->get_z()
                );


}

double point::operator* (const point& b) {


    return (this->x * b.x) + (this->y * b.y) + (this->z * b.z);


}

point* point::normalize(void) {

	double length = sqrt(*this * *this);

	if (length == 0)
		return 0;

	this->x = this->x / length;
	this->y = this->y / length;
	this->z = this->z / length;

	return this;
}

point point::operator* (const double& d) {

	return point( d * this->x, d * this->y, d * this->z);

}


void point::set_x(double x) {
    point::x = x;
}

void point::set_y(double y) {
    point::y = y;
}

void point::set_z(double z) {
    point::z = z;
}
