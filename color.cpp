#include <iostream>
#include "color.h"
#include "dbg.h"
#include <sstream>

using namespace std;

color::color(int r, int g, int b) :R(r), G(g), B(b) {


}

void color::set_r(const int r) {
	this->R = r;
}
void color::set_g(const int g) {
	this->G = g;
}
void color::set_b(const int b) {
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

const char* color::to_string(void) const {
	stringstream stringStream;
	stringStream << "R: " << this->R << " G: " << this->G << " B: " << this->B << "\0";
	string copyOfStr = stringStream.str();

	cout << "R: " << this->R << " G: " << this->G << " B: " << this->B << "\0" << endl;

	return copyOfStr.c_str();

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

}
