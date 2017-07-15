#include "color.h"
#include <iostream>
#include <string>
#include "render.h"
#include "dbg.h"

using namespace std;


render::render(const int h, const int w) {

	this->height = h;
	this->width = w;

}


void render::render_frame() const {

	cout << "No render function available" << endl;

	return;
}


int render::get_width() const {

	return this->width;

}

int render::get_height() const {

	return this->height;

}

void render::set_height(int h) {

	this->height = h;

}

void render::set_width(int w) {

	this->width = w;

}



void render::test() {

	cout << "Test function" << endl;

}


const char* to_string() {


	return "Hard coded string";

}




