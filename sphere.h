#ifndef __sphere_h__
#define __sphere_h__

#include "point.h"
#include "ray.h"
#include "geometry.h"
#include "color.h"

class sphere: public geometry {

    point *center;
    double radius;
	color* c;

public:

    sphere(double x, double y, double z, double r);
    void set_color(int r, int g, int b);

    bool intersection(ray *r, double* t);
    point get_normal(point *pt);
	color get_color();

};



#endif
