#include <string>

#ifndef __color__
#define __color__
class color {

private:
	int R;
	int G;
	int B;	


public:

	color(const int R = 0, const int G = 0, const int B = 0); 

	int r() const;
	int g() const;
	int b() const;

	void set_r(const int r);
	void set_b(const int b);
	void set_g(const int g);

	void set_rgb(const int r, const int g, const int b);

	static void test();
	std::string to_string() const;


};

#endif
	


