#ifndef __sphere_h__
#define __sphere_h__

#include "point.h"

class sphere: public geometry {

    point *center;
    double radius;

public:

    double intersection(ray *r);


};



#endif
