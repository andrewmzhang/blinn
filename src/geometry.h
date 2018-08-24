#ifndef __geometry_h__
#define __geometry_h__

#include "ray.h"
#include "color.cuh"
#include "point.h"

class geometry {

public:
    double albedo = .18;
    virtual bool intersection(ray* r, double* t) = 0;
    virtual color get_color() = 0;
    virtual point get_normal(point* p) = 0;

    virtual bool is_meta() = 0;
    virtual double meta_value(double x, double y, double z) = 0;
    virtual double meta_value(point p) = 0;
    virtual void set_k(double k) = 0;
    
    virtual void set_center(double x, double y, double z) = 0;

};


#endif
