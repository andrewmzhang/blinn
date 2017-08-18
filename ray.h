#ifndef __ray_h__
#define __ray_h__

#include "point.h"

class ray {

private:


    char buffer[50];

public:
    point *pt;
    point *vec;

    ray(point *pt, point *vec);
    static ray *get_ray(point *start, point *end);


    const char * to_string();





};



#endif
