#ifndef __tracer_h__
#define __tracer_h__


#include "square.h"
#include "geometry.h"
#include <vector>
#include "ray.h"
#include "sphere.h"

class tracer {


private:

    uint32_t count;

    std::vector<std::vector<square>> squares;
	std::vector<sphere*> spheres;
    std::vector<sphere> b_spheres;
    uint32_t num_spheres;

    uint32_t length;


	double li;
    point light;


    double meta_sec(ray *ray, uint32_t i, uint32_t j, double &meta);

public:

    explicit tracer(uint32_t length);

    void add_spheres(sphere *s, uint32_t num);

	void trace();

    void add_light(point l, double str);

    void meta_trace();

    point approx_norm(point pt);


};
#endif
