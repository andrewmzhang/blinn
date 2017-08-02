#define BOOST_TEST_MODULE decorator_13
#include <boost/test/included/unit_test.hpp>

namespace utf = boost::unit_test;
namespace fpc = boost::test_tools::fpc;

BOOST_AUTO_TEST_CASE(test1, * utf::tolerance(0.0005))
{
      BOOST_TEST( 0.001 == 0.000 );
        BOOST_TEST( 1.100 == 1.101 );
}

BOOST_AUTO_TEST_CASE(test2, * utf::tolerance(0.005))
{
      BOOST_TEST( 0.001 == 0.000 );
        BOOST_TEST( 1.100 == 1.101 );
}

BOOST_AUTO_TEST_CASE(test3, * utf::tolerance(0.05F))
{
      BOOST_TEST( 0.001 == 0.000 );
        BOOST_TEST( 1.100 == 1.101 );
}

