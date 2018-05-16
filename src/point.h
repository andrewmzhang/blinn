#ifndef __point_h__
#define __point_h__

class point {

private:
    double x;
    double y;
    double z;

public:
    
    point();
    point(double x, double y, double z) : x(x), y(y), z(z) {};
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

    void set_x(double x);

    void set_y(double y);

    void set_z(double z);




};

#endif
