#ifndef __sphere_h__
#define __sphere_h__

#include "point.h"
#include "ray.h"
#include "geometry.h"
#include "color.h"

class sphere: public geometry {

protected:
    point *center;
    double radius;
	color* c;
    double k;

    bool meta;


public:

    sphere(double x, double y, double z, double r);
    void set_color(int r, int g, int b);

    bool intersection(ray *r, double* t);
    bool intersection(ray *r, double* t, double* u);
    point get_normal(point *pt);
	color get_color();

    bool is_meta();
    double meta_value(double x, double y, double z);
    double meta_value(point);
    void set_k(double k);

    void set_center(double x, double y, double z);

    sphere bound_radius(double k);
};



#endif
