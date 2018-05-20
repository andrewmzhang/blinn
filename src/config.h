//
// Created by camus on 5/19/18.
//

#ifndef BLINN_CONFIG_H
#define BLINN_CONFIG_H


#include <string>
#include <vector>
#include "color.h"
#include "sphere.h"

class config {


public:
    config(const std::string &path);

    void parse_line(const std::string &line);

    uint32_t get_num_frames() const;

    double get_intv() const;

    uint32_t get_num_spheres() const;

    const std::vector<sphere *> &get_spheres() const;

    const std::vector<std::tuple<uint8_t, uint8_t, double>> &get_springs() const;

    const color &get_background() const;

    uint32_t get_width() const;

    uint32_t get_height() const;

    std::pair<point, double> get_light() const;




private:
    std::string path;

    uint32_t width;
    uint32_t height;

    uint32_t num_frames;
    double intv;
    uint32_t num_spheres;
    std::vector<sphere *> spheres;

    std::vector<std::tuple<uint8_t, uint8_t, double>> springs;
    color background;

    std::pair<point, double> light;


};


#endif //BLINN_CONFIG_H
