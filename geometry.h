#ifndef __geometry_h__
#define __geometry_h__

#include "ray.h"
#include "color.h"
#include "point.h"

class geometry {



public:
    double albedo = .18;
    geometry() {};
    virtual bool intersection(ray* r, double* t) = 0;
    virtual color get_color() = 0;
    virtual point get_normal(point* p) = 0;




};


#endif
