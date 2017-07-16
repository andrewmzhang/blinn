#include <iostream>
#include "color.h"
#include "dbg.h"
#include <sstream>
#include <string>

using namespace std;

color::color(int r, int g, int b) :R(r), G(g), B(b) {

}

void color::set_r(const int r) {
	this->R = r % 256;
}
void color::set_g(const int g) {
	this->G = g % 256;
}
void color::set_b(const int b) {
	this->B = b % 256;
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
