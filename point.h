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
	static double get_ray(point* start, point* end);

    static point dot(point *a, point *b);

};

#endif
