#include <string>
#include <iostream>
#include "dbg.h"

#include "color.h"
#include "render.h"

#include "draw.h"

using namespace std;

int main() {


	log_info("Hello world test");

	cout << "Hello, world!" << endl;


	//	color::test();

	//	render::test();

	/*
	draw::setcolor(255, 0, 0);          // fully red, no green or blue
	draw::filled_circle(0.5, 0.5, 0.5); // center 0.5, 0.5 and radius 0.5
	draw::setcolor(255, 255, 255);      // white
	draw::filled_circle(0.5, 0.5, 0.3); // smaller circle
	draw::setcolor(draw::RED);          // predefined alias for red
	draw::filled_circle(0.5, 0.5, 0.1); // smaller circle

	*/

	return 0;
}



