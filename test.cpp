#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello
#include <boost/test/unit_test.hpp>


#include "color.h"
#include "render.h"



BOOST_AUTO_TEST_CASE(cirle_test)
{

	render r(100, 100);

	r.set_circle(.5, .5, .2);	

	r.print(0, "hello.bmp");
}

