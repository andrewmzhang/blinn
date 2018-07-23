#include <string>
#include <iostream>
#include <cmath>


#include "dbg.h"
#include "sphere.h"
#include "tracer.h"
#include "blobsys.h"





using namespace std;

__global__
void add(int n, float* x, float *y) {


    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;

    for (int i = index; i < n; i += stride)
        y[i] = x[i] + y[i];
}


int main() {

    //debug("Debug Mode ON!");


    config conf("/home/caesar/code/blinn/src/config.txt");

    tracer t(&conf);

    blobsys sys(&conf);


    for (int i = 0; i < conf.get_end_frame(); i++) {

        scene s = sys.move(conf);
        if (i >= conf.get_start_frame())
            t.meta_trace(s);
    }


    return 0;
}
