#define CATCH_CONFIG_MAIN
#include "ext/catch.hpp"
#include <limits.h>

int add(int a, int b) {

    // when adding binary there can be 3 different results
    // 0+0=00, 1+0=01, 0+1=01, 1+1=10
    // we set the sum to the low bit and the carry to the high bit
    int sum = a ^ b;
    int carry = a & b;

    // we will recursively add until there is nothing to do => carry is zero
    while ( carry != 0 ) {
        // between addition we need to shift the carry to accumulate on the higher bit
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
