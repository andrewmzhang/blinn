//
// Created by andrewmzhang on 5/22/2018.
//

#include "scene.h"

scene::scene() = default;

scene::scene(config &conf) {

    for (sphere *sp: conf.get_spheres()) {
        point center = sp->get_center();
        sphere s(center.get_x(), center.get_y(), center.get_z(), sp->get_radius());
        s.set_color(sp->get_color());
        this->spheres.push_back(std::move(s));
    }

    this->count = 0;
    this->light = conf.get_light().first;
    this->li = conf.get_light().second;

}

const std::vector<sphere> &scene::get_spheres() const {
    return spheres;
}

void scene::set_spheres(const std::vector<sphere *> &spheres) {
    for (sphere *sp: spheres) {
        point center = sp->get_center();
        sphere s(center.get_x(), center.get_y(), center.get_z(), sp->get_radius());
        s.set_color(sp->get_color());
        this->spheres.push_back(std::move(s));
    }
}

const point &scene::get_light() const {
    return light;
}

void scene::set_light(const point &light) {
    scene::light = light;
}

double scene::get_li() const {
    return li;
}

void scene::set_li(double li) {
    scene::li = li;
}

uint32_t scene::get_count() const {
    return count;
}

void scene::set_count(uint32_t count) {
    scene::count = count;
}

