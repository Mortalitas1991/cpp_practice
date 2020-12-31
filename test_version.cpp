#define BOOST_TEST_MODULE version_test_module

#include "version.h"

#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(version_test_suite)

BOOST_AUTO_TEST_CASE(version_test_version)
{
    BOOST_TEST_CHECK(GetVersion() == PROJECT_VERSION);
}

BOOST_AUTO_TEST_SUITE_END()
