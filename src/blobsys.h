
#ifndef __system__
#define __system__
#include <string>
#include <vector>
#include "sphere.h"
#include "config.h"


class blobsys {

private:
	int time;
	double interval;
    int num_spheres;

	std::vector<sphere*> spheres;
	std::vector<point> velocity;
    std::vector<std::tuple<uint8_t, uint8_t, double>> springs;


    std::vector<std::vector<double>> matrix;


public:

    blobsys(config *conf);

	int get_time() const;
	double get_interval() const;

    int get_numspheres() const;


	void add_sphere(sphere* sp);

    void move();
};

#endif
	


