
#include "math.h"
#include "dbg.h"
#include "tracer.h"
#include "square.h"
#include "ray.h"
#include "render.h"

#include <iostream>
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


void tracer::add_spheres(geometry* s, int n) {
	for (int i = 0; i < n; i++)
		this->spheres.push_back(s + i);
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
					//debug("Hit!");
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

void tracer::meta_trace() {

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


            double dist = 0;
            double dist_delta = 0.0001;

            while (dist < 1000) {
            // Determine intersection
                double meta_value = 0;
                point bullet_loc = bullet->inch_by(dist);

                for (int s = 0; s < num_spheres; s++) {
                    meta_value += this->spheres[s]->meta_value(bullet_loc.get_x(), bullet_loc.get_y(), bullet_loc.get_z());
                }

                dist += dist_delta;

                if (meta_value > 10) {
                    // Render
                    point surface = bullet_loc;

                    point normal = closest->get_normal(&surface);

                    double percent = -(normal * *light);
                    percent = std::max(0.0, percent);
                    percent = closest->albedo / M_PI * percent * this->li;
                    //debug("Light percentage %f", percent);

                    shade = closest->get_color() * percent;

                }
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

void tracer::add_light(point *l, double s) {


	this->light = new point(l->get_x(), l->get_y(), l->get_z());
	this->li = s;
}
