//
// Created by camus on 5/19/18. Format borrowed from Joao Carreira's Cirrus project.
//

#include "config.h"

#include <fstream>
#include <sstream>
#include <iostream>


config::config(const std::string &configstr) : configstr(configstr) {


    std::ifstream fin(configstr.c_str(), std::ifstream::in);

    if (!fin) {
        throw std::runtime_error("Error opening config file: " + configstr);
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

    std::cout << "Parsing line: " << line << std::endl;

    if ("num_spheres:") {
        iss >> num_spheres;
    } else if (s == ";") {
        int n;
        iss >> n;
    } else if (s == "model_type:") {
        std::string model;
        iss >> model;
        if (model == "LogisticRegression") {
            model_type = LOGISTICREGRESSION;
        } else if (model == "Softmax") {
            model_type = SOFTMAX;
        } else {
            throw std::runtime_error(std::string("Unknown model : ") + model);
        }
    } else {
        throw std::runtime_error("Unrecognized option: " + line);
    }

    if (iss.fail()) {
        throw std::runtime_error("Error parsing configuration file");
    }

}