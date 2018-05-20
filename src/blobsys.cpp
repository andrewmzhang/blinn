#include <iostream>
#include "blobsys.h"

using namespace std;

blobsys::blobsys(config *conf) {
    this->interval = conf->get_intv();
    this->num_spheres = conf->get_num_spheres();
    this->spheres = conf->get_spheres();
    this->springs = conf->get_springs();

    this->matrix.resize(num_spheres);
    for (int i = 0; i < num_spheres; i++)
        matrix[i].resize(num_spheres);

    for (auto spring: springs) {
        uint8_t i = get<0>(spring);
        uint8_t j = get<1>(spring);
        double k = get<2>(spring);
        matrix[i][j] = k;
        matrix[j][i] = k;
    }

    velocity.resize(num_spheres);

}


int blobsys::get_time(void) const {
	return this->time;
}
double blobsys::get_interval(void) const {
	return this->interval;
}

int blobsys::get_numspheres(void) const {
    return this->num_spheres;
}

void blobsys::move() {
    double t_int = get_interval();

    for (int i = 0; i < num_spheres; i++) {
        sphere *sp = spheres.at(i);
        auto center = sp->get_center() + velocity[i] * t_int;
        sp->set_center(center.get_x(), center.get_y(), center.get_z());
        
    }

    for (int i = 0; i < num_spheres; i++) {
        point accel_vec(0,0,0);
        for (int j = 0; j < num_spheres; j++) {
            if (i == j)
                continue;

            double k = matrix[i][j];
            point sc1 = spheres[i]->get_center();
            point sc2 = spheres[j]->get_center();
            double x = point::distance2(&sc1, &sc2);
            double force = -k * x;
            
            point accel_dir = sc1 - sc2;
            accel_vec.set_x(accel_vec.get_x() + (force * accel_dir.get_x()));
            accel_vec.set_y(accel_vec.get_y() + (force * accel_dir.get_y()));
            accel_vec.set_z(accel_vec.get_z() + (force * accel_dir.get_z()));
        }
        auto curr_vel = velocity[i];
        curr_vel = curr_vel + accel_vec * t_int;
        velocity[i] = curr_vel;
    }


}

void blobsys::add_sphere(sphere *sp) {

	point point(0, 0, 0);
	velocity.push_back(point);
    spheres.push_back(sp);

}
