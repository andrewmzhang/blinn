#include "sphere.h"
#include <cmath>
#include "dbg.h"

bool sphere::intersection(ray *r, double *t) {


    point L =  *(this->center) - *(r->pt);
    double ldotvec = L * *(r->vec->normalize());

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
		log_err("pt does not appear to be on the sphere %f\n", point::distance(pt, this->center));
	}


	point normal = ((*pt) - *(this->center));

	normal.normalize();

	return normal;

}

bool sphere::is_meta() {
    return meta;
}

double sphere::meta_value(double x, double y , double z) {

    return k / ((x - center->get_x()) * (x - center->get_x()) + (y - center->get_y()) * (y - center->get_y()) + (z - center->get_z()) * (z - center->get_z()));

}

void sphere::set_k(double k) {


}


color sphere::get_color() {
	return *(this->c);
}

sphere::sphere(double x, double y, double z, double r) {

    this->center = new point(x, y, z);
    this->radius = r;
    this->albedo = .18;

}

void sphere::set_color(int r, int g, int b) {

    this->c = new color(r, g, b);


}

void sphere::set_center(double x, double y, double z) {

    this->center = new point(x, y, z);

}