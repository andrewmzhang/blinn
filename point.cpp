

#include <math.h>


#include "point.h"


double point::distance(point* a, point* b) {

    double xd = a->x - b->x;
    double yd = a->y - b->y;
    double zd = a->z - b->z;

    return sqrt((xd*xd) + (yd*yd) + (zd*zd));

}



double point::get_ray(point* start, point* end) {

    return 0;

}
