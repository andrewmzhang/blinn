#ifndef __geometry_h__
#define __geometry_h_

#include "ray.h"

class geometry {

    virtual double intersection(ray* r) = 0;



};


#endif
