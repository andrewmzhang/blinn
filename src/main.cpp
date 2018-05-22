#include <string>
#include <iostream>

#include "dbg.h"
#include "sphere.h"
#include "tracer.h"
#include "blobsys.h"

using namespace std;

int main() {

    debug("Debug Mode ON!");

    config conf("C:\\Users\\andrewmzhang\\CLionProjects\\blinn\\src\\config.txt");

    tracer t(&conf);

    blobsys sys(&conf);


    for (int i = 0; i < conf.get_num_frames(); i++) {

        scene s = sys.move(conf);
        t.meta_trace(s);
    }


	return 0;
}
