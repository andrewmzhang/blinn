#include "sphere.h"


double sphere::intersection(ray *r) {


    point L = r->pt - this->center;
    double ldotvec = L * r->vec;

    double d2 = L * L - (tca * tca);
    double radius2 = radius * radius;
    if (d2 > radius2) return false;
    double thc = sqrt(radius2 - d2);

    t0 = tca - thc;
    t1 = tca + thc;



    return 0;

}
