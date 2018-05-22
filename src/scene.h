//
// Created by andrewmzhang on 5/22/2018.
//

#ifndef BLINN_SCENE_H
#define BLINN_SCENE_H


#include <vector>
#include "sphere.h"
#include "config.h"

class scene {

private:

    std::vector<sphere> spheres;
    point light;
    double li;
    uint32_t count;


public:

    scene();

    scene(config &conf);

    const std::vector<sphere> &get_spheres() const;

    void set_spheres(const std::vector<sphere *> &spheres);

    const point &get_light() const;

    void set_light(const point &light);

    double get_li() const;

    void set_li(double li);

    uint32_t get_count() const;

    void set_count(uint32_t count);


};


#endif //BLINN_SCENE_H
