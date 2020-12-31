#define BOOST_TEST_MODULE ip_filter_test_module

#include "ip_filter.h"

#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ip_filter_test)

BOOST_AUTO_TEST_CASE(get_ip_test)
{
    BOOST_CHECK(get_ip("113.162.145.156	111	0 15 ") == "113.162.145.156");
    BOOST_CHECK(get_ip("113.162.145.156	invalid") == "113.162.145.156");
}

BOOST_AUTO_TEST_SUITE_END()
