#ifndef __sphere_h__
#define __sphere_h__

#include "point.h"
#include "ray.h"
#include "geometry.h"

class sphere: public geometry {

    point *center;
    double radius;

public:

    bool intersection(ray *r, double* t);

    point get_normal(point *pt);
	

};



#endif
