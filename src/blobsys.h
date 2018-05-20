
#ifndef __system__
#define __system__
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "sphere.h"


class blobsys {

private:
	int time;
	double interval;
    int num_spheres;

	std::vector<sphere*> spheres;
	std::vector<point> velocity;


	double** matrix;


public:

	blobsys(double interval, int n);

	int get_time() const;
	double get_interval() const;

    int get_numspheres() const;


	void add_sphere(sphere* sp);
    void add_matrix(double** matrix);

    void move();
};

#endif
	


