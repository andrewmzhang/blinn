#include <thrust/tuple.h>
#include "cmath"
#include "dbg.h"
#include "tracer.h"
#include "render.h"
#include <memory>
#include <iostream>
#include <chrono>
#include "sphere.h"
using namespace std;

tracer::tracer(config *conf) {


    this->length = conf->get_width();
    this->squares.resize(length);

    double sq_width = 1.0 / length;
    for (int i = 0; i < length; i++) {
        this->squares[i].resize(length);
        for (int j = 0; j < length; j++) {
            this->squares[i][j].set(sq_width, i * sq_width, j * sq_width);
        }
    }


}


struct gpoint {

	double x;
	double y;
	double z;

};

typedef struct gray {

	gpoint pt;
	gpoint vec;

} gray;

__device__
double dot_product(const gpoint& a, const gpoint& b) {

	return a.x*b.x + a.y*b.y + a.z*b.z;
}

__device__
gpoint normalize(gpoint& a) {
	double denom = sqrt(dot_product(a, a));
	return {a.x / denom, a.y/denom, a.z/denom};
}



__device__
bool intersection(sphere& s, gray& r, double* t, double* u) {

	gpoint L = {s.center.x - r.pt.x, s.center.y - r.pt.y, s.center.z - r.pt.z};

	double ldotvec = dot_product(L, normalize(r.vec));
	
	double d2 = dot_product(L, L) - (ldotvec * ldotvec);
	double radius2 = s.radius * s.radius;

	if (d2 > radius2) return false;
	double thc = sqrt(radius2 - d2);

	double t0 = ldotvec - thc;
	double t1 = ldotvec + thc;

	if (t0 > t1) {
		double temp = t0;
		t0 = t1;
		t1 = temp;
	}

	if (t0 < 0) {
		t0 = t1;
		if (t0 < 0)
			return false;
	}

	*t = t0;

	return true;

}




__device__
double meta_sec(sphere* spheres, sphere* b_spheres, int num_spheres, 
		gray bullet, 
		uint32_t i, uint32_t j, 
		double &meta) {

    // Determine intersection
    double t_s = 1.0/0.0;
    double t_temp = t_s;

    double t1_s = -1.0/0.0;
    double t1_temp = t1_s;
    geometry *closest = nullptr;
    for (int s = 0; s < num_spheres; s++) {
        if (intersection(b_spheres[s], bullet, &t_temp, &t1_temp)) {
            if (t_temp < t_s)
                t_s = t_temp;
            if (t1_temp > t1_s)
                t1_s = t1_temp;
            closest = &spheres[s];
        }
    }
    if (closest == nullptr) {
        return -1;
    }

    double dist = t_s;
    while (dist < t1_s) {
        double meta_value = 0.0;
        for (int i = 0; i < num_spheres; i++)  {
			sphere& sp = spheres[i];
			
			double x = bullet.pt.x + (dist * bullet.vec.x);
			double y = bullet.pt.y + (dist * bullet.vec.y);
			double z = bullet.pt.z + (dist * bullet.vec.z);

			double radius = sp.radius;

			double sp_meta = radius / 
				((x - sp.center.x) * (x - sp.center.x) + 
				 (y - sp.center.y) * (y - sp.center.y) + 
				 (z - sp.center.z) * (z - sp.center.z));
            
			meta_value += sp_meta;
        }

        meta = meta_value;
        if (meta_value > 10)
            return dist;

        dist += 0.0001;

    }
    return -1;

}

__device__
double meta_value(sphere& sp, double x, double y, double z) {

	double radius = sp.radius;

	double sp_meta = radius / 
		((x - sp.center.x) * (x - sp.center.x) + 
		 (y - sp.center.y) * (y - sp.center.y) + 
		 (z - sp.center.z) * (z - sp.center.z));
	return sp_meta;
}
__device__
thrust::tuple<double, double, double> approx_norm(double bx, double by, double bz, sphere* spheres, int num_spheres) {
    double d = 0.000000001;
    double tmp = 0.0;


    for (int s = 0; s < num_spheres; s++) {
        tmp += meta_value(spheres[s], bx + d, by, bz);
        tmp -= meta_value(spheres[s], bx, by, bz);

    }
    double normalx = tmp;

    tmp = 0.0;
    for (int s = 0; s < num_spheres; s++) {
        tmp += meta_value(spheres[s], bx, by + d,
                                           bz);
        tmp -= meta_value(spheres[s], bx, by, bz);
    }
    double normaly = (tmp);

    tmp = 0.0;
    for (int s = 0; s < num_spheres; s++) {
        tmp += meta_value(spheres[s], bx, by,
                                            bz + d);
        tmp -= meta_value(spheres[s], bx, by, bz);

    }
    double normalz = (tmp);

	double denom = sqrt(normalx * normalx + normaly*normaly + normalz*normalz);

	normalx /= denom;
	normaly /= denom;
	normalz /= denom;

    return thrust::make_tuple(normalx, normaly, normalz);
}


__device__
gpoint inch_by(gray b, double x) {
	
	double startx = b.pt.x;
	double starty = b.pt.y;
	double startz = b.pt.z;

	double deltax = b.vec.x;
	double deltay = b.vec.y;
	double deltaz = b.vec.z;


	return {startx + x * deltax, starty + x * deltay, startz + x * deltaz};
}


__global__
void gpu_meta_trace(
		sphere* spheres, int num_spheres,
		point light, double li,
		sphere* b_spheres, int num_b_spheres, 
		point* centers, render& r,
		int length) {

    for (int iter = 0; iter < length * length; iter++) {

        int i = iter / length;
        int j = iter % length;
		
        //color background(0);
		int backgroundR = 0;
		int backgroundG = 0;
		int backgroundB = 0;
        gpoint camera = {.5, .5, -5};
        point center = centers[iter];
		gpoint vec = {center.x - camera.x, center.y - camera.y, center.z - camera.z};



        double meta;
		gpoint nvec = normalize(vec);
		gray gbullet = {camera, nvec};
        double dist = meta_sec(spheres, b_spheres, num_spheres, gbullet, i, j, meta);
		

        gpoint bullet_loc = inch_by(gbullet, dist);
        // Precondition: bullet_loc is equal to the intersection point
        if (dist > 0) {
			
			thrust::tuple<double, double, double> normal = approx_norm(bullet_loc.x, bullet_loc.y, bullet_loc.z, 
					spheres, num_spheres);// this->approx_norm(bullet_loc);
            double percent = 
				(thrust::get<0>(normal) * light.x) + 
				(thrust::get<1>(normal)  * light.y) + 
				(thrust::get<2>(normal)  * light.z);
            percent = (percent > 0) ? percent : 0.0;
            percent = 0.18 / M_PI * percent * li;

			double mixR = 0;
			double mixG = 0;
			double mixB = 0;

            for (int i = 0; i < num_spheres; i++) {
				sphere& sp = spheres[i];
				double x = bullet_loc.x;
				double y = bullet_loc.y;
				double z = bullet_loc.z;

				double radius = sp.radius;

                double sp_meta = radius / 
					((x - sp.center.x) * (x - sp.center.x) + 
					 (y - sp.center.y) * (y - sp.center.y) + 
					 (z - sp.center.z) * (z - sp.center.z));
				double mult = sp_meta / meta;

				mixR += sp.c.R * mult;
				mixB += sp.c.B * mult;
				mixG += sp.c.G * mult;

            }

			backgroundR = mixR * percent;
			backgroundG = mixG * percent;
			backgroundB = mixB * percent;
        }

		int x = centers[iter].x;
		int y = centers[iter].y;
		r.frame[x][y][0] = backgroundR;
		r.frame[x][y][1] = backgroundG;
		r.frame[x][y][2] = backgroundB;
        
	}


}


void tracer::meta_trace(scene &scene) {

    this->count = scene.get_count();

    num_spheres = scene.get_spheres().size();
    spheres = scene.get_spheres();

    point light = scene.get_light();
    double li = scene.get_li();

    render r(this->length, this->length);

    log_info("Starting frame: %d", count);
    auto start = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();

    this->b_spheres.clear();
    for (auto &sp : spheres) {
        b_spheres.push_back(sp.bound_radius(10.0 / num_spheres));
    }

	vector<square*> ptrs (squares.size());
	for (unsigned i=0, e=ptrs.size(); i<e; ++i) {
		    ptrs[i] = &(squares[i][0]); // assuming !thing[i].empty()
	}

	point* centers_flat = new point[length * length];

	for (int iter = 0; iter < length * length; iter++) {
		int i = iter / length;
		int j = iter % length;
		centers_flat[iter] = (&ptrs[0])[i][j].get_center();
	}

	sphere* gpu_spheres;
	sphere* gpu_b_spheres;
	point* gpu_centers;

	std::cout << num_spheres<< " " << sizeof(sphere) <<  std::endl;


	cudaDeviceSynchronize();
	cudaMallocManaged(&gpu_spheres, num_spheres*sizeof(sphere));
	cudaMallocManaged(&gpu_b_spheres, num_spheres * sizeof(sphere));
	cudaMallocManaged(&gpu_centers, (length * length) * sizeof(point));
	cudaDeviceSynchronize();
	std::cout << spheres.data() << std::endl;
	
	for (int i = 0; i < num_spheres; i++) {
		sphere s = spheres[i];
		std::cout << s.radius << std::endl;
		gpu_spheres[i] = s;
	}
	
	std::memcpy(gpu_b_spheres, b_spheres.data(), num_spheres * sizeof(sphere));
	std::memcpy(gpu_centers, centers_flat, (length * length) * sizeof(point));
	cudaDeviceSynchronize();
	
	gpu_meta_trace<<<1, 1>>>(
		gpu_spheres, num_spheres,
		light, li,
		gpu_b_spheres, b_spheres.size(), 
		gpu_centers, r, length);

	cudaDeviceSynchronize();


    auto end = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
    double time = ((double) (end - start)) / 1000.0;
    fflush(stderr);
    log_info("Time elapsed: %.3fs, %.3f px/sec", time, length * length / time);
    fflush(stderr);

    r.print(count, "hello.bmp");
	
	delete[] centers_flat;
	cudaFree(gpu_spheres);
	cudaFree(gpu_b_spheres);
	cudaFree(gpu_centers);
	cudaDeviceSynchronize();
	log_info("Finished frame");
    count++;
}


double tracer::meta_sec(ray *bullet, uint32_t i, uint32_t j, double &meta) {

    // Determine intersection
    double t_s = numeric_limits<double>::infinity();
    double t_temp = t_s;

    double t1_s = -numeric_limits<double>::infinity();
    double t1_temp = t1_s;
    geometry *closest = nullptr;
    for (int s = 0; s < num_spheres; s++) {
        if (this->b_spheres[s].intersection(bullet, &t_temp, &t1_temp)) {
            if (t_temp < t_s)
                t_s = t_temp;
            if (t1_temp > t1_s)
                t1_s = t1_temp;
            closest = &this->spheres[s];
        }
    }
    if (closest == nullptr) {
        return -1;
    }

    double dist = t_s;
    while (dist < t1_s) {
        double meta_value = 0.0;
        for (geometry &s : this->spheres) {
            meta_value += s.meta_value(bullet->inch_by(dist));
        }

        meta = meta_value;
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
        tmp += this->spheres[s].meta_value(bullet_loc.get_x() + d, bullet_loc.get_y(),
                                           bullet_loc.get_z());
        tmp -= this->spheres[s].meta_value(bullet_loc.get_x(), bullet_loc.get_y(), bullet_loc.get_z());

    }
    normal.set_x(tmp);

    tmp = 0.0;
    for (int s = 0; s < num_spheres; s++) {
        tmp += this->spheres[s].meta_value(bullet_loc.get_x(), bullet_loc.get_y() + d,
                                           bullet_loc.get_z());
        tmp -= this->spheres[s].meta_value(bullet_loc.get_x(), bullet_loc.get_y(), bullet_loc.get_z());
    }
    normal.set_y(tmp);

    tmp = 0.0;
    for (int s = 0; s < num_spheres; s++) {
        tmp += this->spheres[s].meta_value(bullet_loc.get_x(), bullet_loc.get_y(),
                                            bullet_loc.get_z() + d);
        tmp -= this->spheres[s].meta_value(bullet_loc.get_x(), bullet_loc.get_y(), bullet_loc.get_z());

    }
    normal.set_z(tmp);
    normal.normalize();
    return normal;
}


void tracer::trace() {

    render r(this->length, this->length);
    color background(125, 125, 125);

    int length = this->length;

    unique_ptr<point> camera = make_unique<point>(.5, .5, -5);


    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {

            color shade = background;
            point center = this->squares[i][j].get_center();
            point vec = center - (*camera);
            unique_ptr<ray> bullet = make_unique<ray>(camera.get(), &vec);


            double t_s = numeric_limits<double>::infinity();
            double t_temp = t_s;
            geometry *closest = nullptr;
            for (int s = 0; s < num_spheres; s++) {
                if (this->spheres[s].intersection(bullet.get(), &t_temp) && t_temp < t_s) {
                    t_s = t_temp;
                    closest = &this->spheres[s];
                }
            }

            if (closest != nullptr) {

                point surface = *(bullet->pt) + *(bullet->vec) * t_s;

                point normal = closest->get_normal(&surface);

                double percent = -(normal * light);
                percent = std::max(0.0, percent);
                percent = closest->albedo / M_PI * percent * this->li;
                //debug("Light percentage %f", percent);

                shade = closest->get_color() * percent;
            }


            square *s = &this->squares[i][j];
            this->squares[i][j].set_value(&shade);
            r.set_color(&shade);
            r.set_point(s->get_center().get_x(), s->get_center().get_y());


        }
    }

    r.print(count, "hello.bmp");

    count++;
}

// I want to move this to the gpu
// need to move r, b_sheres
/*
    for (int iter = 0; iter < length * length; iter++) {

        int i = iter / length;
        int j = iter % length;

        color background(125, 125, 125);
        unique_ptr<point> camera = make_unique<point>(.5, .5, -5);
        color shade = background;
        point center = this->squares[i][j].get_center();
        point vec = center - (*camera);
        unique_ptr<ray> bullet = make_unique<ray>(camera.get(), &vec);


        double meta;
        double dist = this->meta_sec(bullet.get(), i, j, meta);
        point bullet_loc = bullet->inch_by(dist);

        // Precondition: bullet_loc is equal to the intersection point
        if (dist > 0) {

            point normal = this->approx_norm(bullet_loc);
            double percent = (normal * light);
            percent = std::max(0.0, percent);
            percent = 0.18 / M_PI * percent * li;

            color mix;

            for (auto sp : spheres) {
                double sp_meta = sp.meta_value(bullet_loc);
                mix = mix + sp.get_color() * (sp_meta / meta);
            }


            shade = mix * percent;

        }

        square *s = &this->squares[i][j];
        r.set_point(s->get_center().get_x(), s->get_center().get_y(), &shade);

    }
	*/

	// End of tracing code
