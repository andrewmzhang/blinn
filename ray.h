#ifndef __ray_h__
#define __ray_h__

#include "point.h"

class ray {

private:
    point *pt;
    point *vec;

    char buffer[50];

public:

    ray(point *pt, point *vec);
    static ray *get_ray(point *start, point *end);


    const char * to_string();





};



#endif
