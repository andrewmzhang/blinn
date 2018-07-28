#include <iostream>
#include "color.cuh"
#include "dbg.h"

using namespace std;

__device__
color::color(int k) {


}


color::color(int r, int g, int b) :R(r), G(g), B(b) {

	normalize();

}


void color::normalize() {
	this->set_r(this->R);
	this->set_b(this->B);
	this->set_g(this->G);
}

void color::set_r(int r) {
	if (r > 255)
		r = 255;
	if (r < 0)
		r = 0;
	this->R = r;
}
void color::set_g(int g) {
	if (g > 255)
		g = 255;
	if (g < 0)
		g = 0;
	this->G = g;
}
void color::set_b(int b) {
	if (b > 255)
		b = 255;
	if (b < 0)
		b = 0;
	this->B = b;
}

int color::r(void) const {
	return this->R;
}
int color::g(void) const {
	return this->G;
}

int color::b(void) const {
	return this->B;
}

void color::set_rgb(int r, int g, int b) {
	this->set_r(r);
	this->set_g(g);
	this->set_b(b);
}


color color::operator*(const double& p) {
	return color(this->r() * p, this->g() * p, this->b() * p);
}

color color::operator+(const color &p) {
    return color(this->r() + p.r(), this->g() + p.g(), this->b() + p.b());
}

const char* color::to_string(void) {
	stringstream ss;

	ss << "R: " << this->R << " G: " << this->G << " B: " << this->B << "\0";

	str = ss.str();
	return str.c_str();
}

void color::test(void) {

	color* white = new color();
	color* black = new color(255, 255, 255);

	log_info("White: %s", white->to_string());

	log_info("Black: %s", black->to_string());
	log_info("Changing White...");
	white->set_r(10);
	white->set_g(20);
	white->set_b(30);
	log_info("White is now: %s", white->to_string());

	delete white;
	delete black;

}
