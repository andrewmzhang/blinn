

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


double point::get_x() {
    return this->x;
}

double point::get_y() {
    return this->y;
}

double point::get_z() {
    return this->z;
}
