#include <string>
#include <sstream>

#ifndef __color__
#define __color__
class color {

private:

	std::string str;

	void normalize();



public:
	
	int R;
	int G;
	int B;

	color(int k);
	color(const int R = 0, const int G = 0, const int B = 0);

	int r() const;
	int g() const;
	int b() const;

	void set_r(int r);
	void set_b(int b);
	void set_g(int g);

	void set_rgb(int r, int g, int b);

	color operator*(const double& p);

    color operator+(const color &p);

	static void test();
	const char* to_string();


};

#endif
