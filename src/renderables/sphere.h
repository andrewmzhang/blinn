#ifndef __sphere_h__
#define __sphere_h__

#include <memory>
#include "basics/point.h"
#include "basics/ray.h"
#include "basics/geometry.h"
#include "basics/color.h"

class sphere: public geometry {

protected:
    std::shared_ptr<point> center;
    double radius;
	std::shared_ptr<color> c;
    double k;

    bool meta;


public:

    point get_center();

    double get_radius();
    sphere(double x, double y, double z, double r);
    void set_color(int r, int g, int b);

    void set_color(color c);

    bool intersection(ray *r, double* t) override;
    bool intersection(ray *r, double* t, double* u);
    point get_normal(point *pt) override;
	color get_color() override;

    bool is_meta() override;
    double meta_value(double x, double y, double z) override;
    double meta_value(point) override;
    void set_k(double k) override;

    void set_center(double x, double y, double z) override;

    sphere bound_radius(double k);

};



#endif