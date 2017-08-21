#include "tracer.h"
#include "square.h"
#include "ray.h"
#include "sphere.h"

tracer::tracer(int length) {
	this->length = length;
	this->squares = new square*[length];

	double sq_width = 1.0 / length;
	for (int i = 0; i < length; i++) {

		this->squares[i]  = new square[length];
		for (int j = 0; j < length; j++) {

			this->squares[i][j].set(sq_width, i*sq_width, j*sq_width);
			

		}
	}



}


void tracer::add_spheres(sphere* s, int n) {
	this->num_spheres = n;
	this->spheres = s;

}


void tracer::trace() {
	
	int length = this->length;

	point* camera = new point(.5, .5, -5);

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			
			point center = this->squares[i][j].get_center();

			point vec = center - (*camera);

			ray *bullet = new ray(camera, &vec);


			double t_s = 11111;
			double t_temp = t_s;
			sphere* closest = 0;			
			for (int s = 0; s < num_spheres; s++) {
				if (this->spheres[s].intersection(bullet, &t_temp) && t_temp < t_s) {
					t_s = t_temp;
					closest = &(this->spheres[s]);
				}
			}

			if (closest == 0)
				continue;
			
			point surface = *(bullet->pt) + *(bullet->vec) * t_s;

			point normal = closest->get_normal(&surface);
			
			double percent = normal * *light;
			
						
			
			
		}
	}




	count++;
}


void tracer::add_light(point *l) {


	this->light = new point(l->get_x(), l->get_y(), l->get_z());

}
