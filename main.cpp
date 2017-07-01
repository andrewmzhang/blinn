#include <string>
#include <iostream>
#include "dbg.h"

#include "color.h"
#include "render.h"

using namespace std;

int main() {


	log_info("Hello world test");

	cout << "Hello, world!" << endl;

	
	color::test();

	render::test();

	return 0;
}



