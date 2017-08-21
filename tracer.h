#ifndef __tracer_h__
#define __tracer_h__


#include "square.h"


class sphere;

class tracer {


private:

	int count = 0;

	square** squares;
	sphere* spheres;
	int num_spheres = 0;

	int length;

	point *light;

public:

	tracer (int length);

	void add_spheres(sphere* s, int num);	

	void trace();

	void clean();

	void add_light(point *l);





};
#endif
