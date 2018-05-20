#include <string>
#include <iostream>

#include "dbg.h"
#include "sphere.h"
#include "tracer.h"
#include "blobsys.h"

using namespace std;

int main() {

    debug("Debug Mode ON!");

    config conf("/home/camus/code/blinn/src/config.txt");

    tracer t(&conf);

    blobsys sys(&conf);


    for (int i = 0; i < conf.get_num_frames(); i++) {

        sys.move();
        t.meta_trace();
    }


	return 0;
}
