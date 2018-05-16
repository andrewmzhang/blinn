#ifndef __tracer_h__
#define __tracer_h__


#include "square.h"
#include "geometry.h"
#include <vector>
#include "ray.h"
#include "sphere.h"

class tracer {


private:

	int count;

	square** squares;
	std::vector<sphere*> spheres;
    std::vector<sphere> b_spheres;
    int num_spheres;

	int length;
	double li;
	point *light;


    double meta_sec(ray* ray, int i, int j);

public:

	tracer (int length);

	void add_spheres(sphere* s, int num);

	void trace();

	void inch_trace();

	void clean();

	void add_light(point *l, double str);

    void meta_trace();

    point approx_norm(point pt);

};
#endif
