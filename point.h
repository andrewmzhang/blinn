#ifndef __point_h__
#define __point_h__

class point {

private:
	float x;
	float y;
	float z;

public:
    point(float x, float y, float z) : x(x), y(y), z(z) {};
	static double distance(point* a, point* b);
	static double distance2(point* a, point* b);

    static double dot(point *a, point *b);

	double get_x();
	double get_y();
	double get_z();
	

};

#endif
