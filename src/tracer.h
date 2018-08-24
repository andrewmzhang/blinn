#ifndef __tracer_h__
#define __tracer_h__


#include "square.h"
#include "geometry.h"
#include <vector>
#include "ray.h"
#include "sphere.h"
#include "config.h"
#include "scene.h"

class tracer {


private:

    std::vector<std::vector<square>> squares;
    uint32_t length;


    double meta_sec(ray *ray, uint32_t i, uint32_t j, double &meta);

    point approx_norm(point pt);

    std::vector<sphere> spheres;
    std::vector<sphere> b_spheres;
    uint32_t num_spheres;
    point light;
    double li;

    uint32_t count;

    void meta_loop();

public:

    explicit tracer(config *conf);
	void trace();

    void meta_trace(scene &scene, bool clean = false);

};
#endif
