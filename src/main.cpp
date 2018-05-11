#include <string>
#include <iostream>

#include "color.h"
#include "sphere.h"
#include "tracer.h"

using namespace std;

int main() {


    tracer t(100);

	sphere s(.5, .5, 1, .25);
    sphere s1(.5, .7, 1, .1);
	color red(125, 0, 0);
	point light(.5, .5, .5);


	s.set_color(125, 0, 0);
	s1.set_color(0, 125, 0);
	t.add_spheres(&s, 1);
	t.add_spheres(&s1, 1);
	t.add_light(&light, 50);


    t.meta_trace();

    s1.set_center(0.1, 0.3, .25);


	return 0;
}
