#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../include/park.h"

TEST_CASE("sum")
{
    REQUIRE(sum(1, 2) == 3);
    REQUIRE(sum(2, 3) == 5);
    REQUIRE(sum(3, 4) == 7);
}