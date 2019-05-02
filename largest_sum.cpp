#define CATCH_CONFIG_MAIN
#include "ext/catch.hpp"

using namespace std;

void find_largest_sum(int T, vector<int> I, vector<int> & M, int & S) {

    unsigned int result_mask = 0;
    S = 0;

    // to iterate over all subsets we use a bitmask
    // for simplicity we will use a int and suppose that size of I is not more than 32.
    // this kind of loop could benefit greatly of SIMD vectorization
    for (unsigned int mask = 1; mask < (1<<I.size()); mask++) {
        int sum = 0;

        // iterate over all elements of the set and sum the element if the bitmask is set
        for (int idx = 0; idx < I.size(); idx++) {
            if (mask & (1<<idx)) {
                sum += I[idx];
            }
        }

        // if we find a result that is closer to T, store it
        if (sum > S && sum <= T) {
            S = sum;
            result_mask = mask;

            // if we find the maximum sum, break the loop
            if (S == T) {
                break;
            }
        }
    }

    // build the result set from the cached bitmask
    for (int idx = 0; idx < I.size(); idx++) {
        if (result_mask & (1<<idx)) {
            M.push_back(I[idx]);
        }
    }
}

TEST_CASE( "largest sum" ) {
    int T = 11;
    vector<int> I = { 1, 2, 3, 4, 5, 6, 7 };
    vector<int> M;
    int S;
    find_largest_sum(T, I, M, S);
    vector<int> expected = { 1, 2, 3, 5 };
    REQUIRE( S == 11 );
    REQUIRE_THAT( M, Catch::Matchers::Equals(expected) );
}
