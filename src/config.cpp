//
// Created by camus on 5/19/18. Format borrowed from Joao Carreira's Cirrus project.
//

#include "config.h"
#include "dbg.h"

#include <fstream>


config::config(const std::string &path) : path(path) {


    std::ifstream fin(path.c_str(), std::ifstream::in);

    if (!fin) {
        throw std::runtime_error("Error opening config file: " + path);
    }

    std::string line;
    while (getline(fin, line)) {
        parse_line(line);
    }


}


void config::parse_line(const std::string &line) {

    std::istringstream iss(line);

    std::string s;

    iss >> s;

    log_info("Parsing line: %s", s.c_str());

    if (s == "num_spheres:") {
        iss >> num_spheres;
    } else if (s == "sphere:") {
        double x;
        double y;
        double z;
        double rad;

        int r;
        int g;
        int b;

        if (spheres.size() == num_spheres && num_spheres > 0) {
            throw std::runtime_error(
                    std::string("num spheres and list spheres mismatch"));
        }

        iss >> x >> y >> z >> rad >> r >> g >> b;

        auto *sp = new sphere(x, y, z, rad);
        sp->set_color(r, g, b);
        spheres.push_back(sp);


    } else if (s == "spring:") {
        uint32_t start;
        uint32_t end;
        double k;
        iss >> start >> end >> k;
        auto pair = std::make_tuple((uint8_t) start, (uint8_t) end, k);
        springs.push_back(std::move(pair));


    } else if (s == "interval:") {
        iss >> intv;
    } else if (s == "num_frames:") {
        iss >> this->num_frames;
    } else if (s == "background:") {
        int r, g, b;
        iss >> r >> g >> b;
        background.set_rgb(r, g, b);
    } else if (s == "size:") {

        iss >> width >> height;

    } else if (s == "light:") {

        double x, y, z, i;

        iss >> x >> y >> z >> i;

        light.first.set_x(x);
        light.first.set_y(y);
        light.first.set_z(z);
        light.second = i;


    } else {
        throw std::runtime_error(std::string("No such thing as: ") + s);
    }

/*
    if (iss.fail()) {
        throw std::runtime_error("Error parsing configuration file");
    }
*/


}

double config::get_intv() const {
    return intv;
}

uint32_t config::get_num_spheres() const {
    return num_spheres;
}

uint32_t config::get_num_frames() const {
    return num_frames;
}

const std::vector<sphere *> &config::get_spheres() const {
    return spheres;
}

const std::vector<std::tuple<uint8_t, uint8_t, double>> &config::get_springs() const {
    return springs;
}

const color &config::get_background() const {
    return background;
}

uint8_t config::get_width() const {
    return width;
}

uint8_t config::get_height() const {
    return height;
}

std::pair<point, double> config::get_light() const {

    return light;

};
