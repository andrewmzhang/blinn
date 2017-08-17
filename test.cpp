#define BOOST_TEST_MODULE test_01
#include <boost/test/included/unit_test.hpp>

#include "ray.h"
#include "point.h"

namespace utf = boost::unit_test;

BOOST_AUTO_TEST_CASE(ray_basic, * utf::tolerance(0.00001))
{

    point start(0, 0, 0);
    point vec(1, 1, 1);

    ray r(&start, &vec);


    BOOST_TEST(r.to_string() == std::string("Hello\n"));



}
