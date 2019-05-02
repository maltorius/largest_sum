#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <limits.h>

int add(int a, int b) {
    int sum = a ^ b;
    int carry = a & b;
    while ( carry != 0 ) {
        carry <<= 1;
        a = sum;
        b = carry;
        sum = a ^ b;
        carry = a & b;
    }
    return sum;
}

TEST_CASE( "simple add" ) {
    REQUIRE( add(1, 1) == 2 );
}
TEST_CASE( "simple substract" ) {
    REQUIRE( add(1, -1) == 0 );
}
TEST_CASE( "positive overflow" ) {
    REQUIRE( add(INT_MAX, 1) == INT_MIN );
}
TEST_CASE( "negative underflow" ) {
    REQUIRE( add(INT_MIN, -1) == INT_MAX );
}
