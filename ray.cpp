#include "ray.h"
#include <sstream>


using namespace std;


ray::ray(point *pt, point *vec) {

    this->pt = new point(pt->get_x(), pt->get_y(), pt->get_z());

    this->vec = new point(vec->get_x(), vec->get_y(), vec->get_z());

}


const char * ray::to_string() {


}
