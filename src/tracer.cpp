#include "cmath"
#include "dbg.h"
#include "tracer.h"
#include "render.h"
#include "sphere.h"

#include <time.h>
#include <limits>
#include <boost/progress.hpp>

using namespace std;

tracer::tracer(int length) {
	this->length = length;
	this->squares = new square*[length];
	this->num_spheres = 0;
	this->count = 0;



	double sq_width = 1.0 / length;
	for (int i = 0; i < length; i++) {

		this->squares[i]  = new square[length];
		for (int j = 0; j < length; j++) {

			this->squares[i][j].set(sq_width, i*sq_width, j*sq_width);

		}
	}


}


void tracer::add_spheres(sphere* s, int n) {
	for (int i = 0; i < n; i++) {
		this->spheres.push_back(s + i);
    }
	this->num_spheres += n;

}


void tracer::trace() {

	render r(this->length, this->length);
	color background(125, 125, 125);

	int length = this->length;

	point* camera = new point(.5, .5, -5);

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {

			color shade = background;

			point center = this->squares[i][j].get_center();

			point vec = center - (*camera);

			ray *bullet = new ray(camera, &vec);


			double t_s = numeric_limits<double>::infinity();
			double t_temp = t_s;
			geometry* closest = 0;
			for (int s = 0; s < num_spheres; s++) {
				if (this->spheres[s]->intersection(bullet, &t_temp) && t_temp < t_s) {
					t_s = t_temp;
					closest = this->spheres[s];
				}
			}

			if (closest != 0) {

				point surface = *(bullet->pt) + *(bullet->vec) * t_s;

				point normal = closest->get_normal(&surface);

				double percent = -(normal * *light);
				percent = std::max(0.0, percent);
				percent = closest->albedo / M_PI * percent * this->li;
				//debug("Light percentage %f", percent);

				shade = closest->get_color() * percent;
			}


			square* s = &this->squares[i][j];
			this->squares[i][j].set_value(&shade);
			r.set_color(&shade);
			r.set_point(s->get_center().get_x(), s->get_center().get_y());


		}
	}

	r.print(count, "hello.bmp");

	count++;
}


double tracer::meta_sec(ray* bullet, int i, int j) {

    // Determine intersection
    double t_s = numeric_limits<double>::infinity();
    double t_temp = t_s;
    
    double t1_s = -numeric_limits<double>::infinity();
    double t1_temp = t1_s;
    geometry* closest = 0;
    for (int s = 0; s < num_spheres; s++) {
        if (this->b_spheres[s].intersection(bullet, &t_temp, &t1_temp)) {
            if (t_temp < t_s)
                t_s = t_temp;
            if (t1_temp > t1_s)
                t1_s = t1_temp;
            closest = this->spheres[s];
        }
    }
    if (closest == 0) {
        return -1;
    }

    double dist = t_s;
    while (dist < t1_s) {
        double meta_value = 0.0;
        for (geometry* s : this->spheres) {
            meta_value += s->meta_value(bullet->inch_by(dist));
        }
        if (meta_value > 10)
            return dist;

        dist += 0.0001;

    }
    return -1;

}

point tracer::approx_norm(point bullet_loc) {
    point normal(0, 0, 0);
    double d = 0.000000001;
    double tmp = 0.0;

    for (int s = 0; s < num_spheres; s++) {
        tmp += this->spheres[s]->meta_value(bullet_loc.get_x() + d, bullet_loc.get_y(),
                bullet_loc.get_z());
        tmp -= this->spheres[s]->meta_value(bullet_loc.get_x(), bullet_loc.get_y(), bullet_loc.get_z());

    }
    normal.set_x(tmp);

    tmp = 0.0;
    for (int s = 0; s < num_spheres; s++) {
        tmp += this->spheres[s]->meta_value(bullet_loc.get_x(), bullet_loc.get_y() + d,
                bullet_loc.get_z());
        tmp -= this->spheres[s]->meta_value(bullet_loc.get_x(), bullet_loc.get_y(), bullet_loc.get_z());
    }
    normal.set_y(tmp);

    tmp = 0.0;
    for (int s = 0; s < num_spheres; s++) {
        tmp += this->spheres[s]->meta_value(bullet_loc.get_x(), bullet_loc.get_y(),
                bullet_loc.get_z() + d);
        tmp -= this->spheres[s]->meta_value(bullet_loc.get_x(), bullet_loc.get_y(), bullet_loc.get_z());

    }
    normal.set_z(tmp);
    normal.normalize();
    return normal;
}

void tracer::meta_trace() {

    render r(this->length, this->length);

    int length = this->length;

    time_t start_time;
    time(&start_time);

    for (sphere* sp: spheres) {
        this->b_spheres.push_back(sp->bound_radius(10.0 / num_spheres));
    }
    #pragma omp parallel for
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            color background(125, 125, 125);
            point* camera = new point(.5, .5, -5);
            debug("Starting: %d %d", i, j);
            color shade = background;
            point center = this->squares[i][j].get_center();
            point vec = center - (*camera);
            ray *bullet = new ray(camera, &vec);

            double dist = this->meta_sec(bullet, i, j);
            point bullet_loc = bullet->inch_by(dist);

            // Precondition: bullet_loc is equal to the intersection point
            if (dist > 0) {
                
                point normal = this->approx_norm(bullet_loc);
                double percent = (normal * *light);
                percent = std::max(0.0, percent);
                percent = 0.18 / M_PI * percent * this->li;
                shade = spheres[0]->get_color() * percent;

            }

            square* s = &this->squares[i][j];
            this->squares[i][j].set_value(&shade);
            r.set_point(s->get_center().get_x(), s->get_center().get_y(), &shade);
        }
    }
    
    printf("\n");
    time_t end_time;
    time(&end_time);
    log_info("Time elapsed: %.fs, %.f px/sec", difftime(end_time, start_time), length * length / difftime(end_time, start_time)); 
    r.print(count, "hello.bmp");

    count++;
}

void tracer::add_light(point *l, double s) {

	this->light = new point(l->get_x(), l->get_y(), l->get_z());
	this->li = s;
}
