//
// Created by camus on 5/19/18.
//

#ifndef BLINN_CONFIG_H
#define BLINN_CONFIG_H


#include <string>

class config {


public:
    config(const std::string &configstr);

    void parse_line(const std::string &line);

private:
    std::string configstr;

    uint32_t num_spheres;


};


#endif //BLINN_CONFIG_H
