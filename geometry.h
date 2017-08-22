#ifndef __geometry_h__
#define __geometry_h_

#include "ray.h"

class geometry {



public:
    double albedo = .18;
    virtual bool intersection(ray* r, double* t) = 0;



};


#endif
