#include <string>
#include <iostream>
#include "dbg.h"

#include "color.h"
#include "render.h"

#include "tracer.h"

using namespace std;

int main() {


	log_info("Hello world test");

	cout << "Hello, world!" << endl;


	tracer t(3);

	t.trace();


	return 0;
}



