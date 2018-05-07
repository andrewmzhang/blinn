#ifndef __tracer_h__
#define __tracer_h__


#include "square.h"
#include "geometry.h"
#include <vector>


class tracer {


private:

	int count;

	square** squares;
	std::vector<geometry*> spheres;
	int num_spheres;

	int length;
	double li;
	point *light;


public:

	tracer (int length);

	void add_spheres(geometry* s, int num);

	void trace();

	void inch_trace();

	void clean();

	void add_light(point *l, double str);

	void meta_trace();





};
#endif
