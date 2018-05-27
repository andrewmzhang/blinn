#include <string>
#include <iostream>

#include "dbg.h"
#include "sphere.h"
#include "tracer.h"
#include "blobsys.h"

using namespace std;

int main(int argc, char **argv) {

    debug("Debug Mode ON!");

    if (argc != 2) {
        throw std::runtime_error("Wrong number of arguments");
    }

    config conf(argv[1]);

    tracer t(&conf);
    blobsys sys(&conf);


    for (int i = 0; i < conf.get_end_frame(); i++) {

        scene s = sys.move(conf);
        if (i >= conf.get_start_frame())
            t.meta_trace(s);
    }


	return 0;
}
