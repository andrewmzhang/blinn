#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello
#include <boost/test/unit_test.hpp>


#include "color.h"
#include "render.h"



BOOST_AUTO_TEST_CASE(color_test)
{

	render::test();


}

