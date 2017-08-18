#include "ray.h"
#include "point.h"
#include <sstream>
#include <iostream>
#include <stdio.h>


using namespace std;


ray::ray(point *pt, point *vec) {

    this->pt = new point(pt->get_x(), pt->get_y(), pt->get_z());

    this->vec = new point(vec->get_x(), vec->get_y(), vec->get_z());

}


const char * ray::to_string() {

    sprintf(this->buffer,
        "pt: <%f, %f, %f>    vec: <%f, %f, %f>\n",
        pt->get_x(),
        pt->get_y(),
        pt->get_z(),
        vec->get_x(),
        vec->get_y(),
        vec->get_z()
    );

    return buffer;


}
