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

	point* normalize(void);
	
	point operator+(const point& p);
	point operator-(const point& p);
	double operator*(const point& p);
	point operator*(const double& p);

	double get_x() const;
	double get_y() const;
	double get_z() const;


};

#endif
