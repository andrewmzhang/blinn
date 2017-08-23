#ifndef __tracer_h__
#define __tracer_h__


#include "square.h"
#include "geometry.h"


class tracer {


private:

	int count;

	square** squares;
	geometry* spheres;
	int num_spheres;

	int length;

	point *light;

public:

	tracer (int length);

	void add_spheres(geometry* s, int num);

	void trace();

	void clean();

	void add_light(point *l);





};
#endif
