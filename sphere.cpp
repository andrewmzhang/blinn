#include "sphere.h"
#include <cmath>
#include "dbg.h"

bool sphere::intersection(ray *r, double *t) {


    point L = *r->pt - *this->center;
    double ldotvec = L * *r->vec;

    double d2 = L * L - (ldotvec * ldotvec);
    double radius2 = radius * radius;
    if (d2 > radius2) return false;
    double thc = sqrt(radius2 - d2);

    double t0 = ldotvec - thc;
    double t1 = ldotvec + thc;

    if (t0 > t1) {
	    double temp = t0;
		t0 = t1;
		t1 = temp;
	}

    if (t0 < 0) {
	    t0 = t1;
	    if (t0 < 0) 
		    return false;
    }

    *t = t0;


    return true;

}

point sphere::get_normal(point *pt) {
	
	if (point::distance(pt, this->center) - radius > .0001) {
		log_err("pt does not appear to be on the sphere\n");
		return *pt;
	}


	point normal = ((*pt) - *(this->center));

	normal.normalize();

	return normal;

}



