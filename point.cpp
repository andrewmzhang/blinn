

#include <math.h>

#include "ray.h"
#include "point.h"

using namespace std;

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
