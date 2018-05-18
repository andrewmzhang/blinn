#include <string>
#include <iostream>

#include "dbg.h"
#include "color.h"
#include "sphere.h"
#include "tracer.h"
#include "blobsys.h"

using namespace std;

int main() {

    debug("Debug Mode ON!");

    tracer t(100);

	sphere s(.6, .6, 1, .25);
    sphere s1(.3, .3, 1, .1);
	color red(125, 0, 0);
	point light(.5, .5, .5);

	blobsys sys(1.0, 2);

	s.set_color(125, 0, 0);
	s1.set_color(0, 125, 0);
	t.add_spheres(&s, 1);
	t.add_spheres(&s1, 1);
	t.add_light(&light, 50);

	sys.add_sphere(&s);
	sys.add_sphere(&s1);

	auto mat = new double*[2];
	mat[0] = new double[2];
	mat[1] = new double[2];

	mat[0][1] = 0.7;
	mat[1][0] = 0.7;

	sys.add_matrix(mat);
    for (int i = 0; i < 3; i++) {
        sys.move();
        t.meta_trace();
    }

    delete[] mat[0];
    delete[] mat[1];
    delete[] mat;



	return 0;
}
