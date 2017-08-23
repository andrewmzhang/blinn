#include <string>
#include <iostream>
#include "dbg.h"

#include "color.h"
#include "render.h"
#include "sphere.h"
#include "tracer.h"

using namespace std;

int main() {



	tracer t(500);

	sphere s(.5, .5, 1, .25);
	color red(125, 0, 0);
	point light(.5, .5, .5);


	s.set_color(125, 0, 0);
	t.add_spheres(&s, 1);
	t.add_light(&light);

	t.trace();



	return 0;
}
