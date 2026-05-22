/**
 * @file tiling_problem.cpp
 * @brief implementation of tiling problem using a simple 1D vector.
 * 
 * Time complexity: O(n);
 * 
 * @details Tiling problem is a classic dp problem in which you 
 * are provided with unlimited supply of two types of tiles: 
 *A -> I shaped tile
 *B -> T shaped tile
 * and a 2 * n (n >= 1) matrix. You have find number of ways the 
 * given matrix can be filled modulo mod using the given two 
 * tiles.
 * Refer: https://leetcode.com/problems/domino-and-tromino-tiling/description/
 * 
 * @author [Hxrshthetic](https://github.com/Hxrshthetic)
 */

#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>

/**
 * @namespace math
 * @brief Math Algorithm
 */
namespace math {

    /**
     * This function calculates the number of ways to fill 2 * n 
     * matrix using given 2 types of tiles.
     * 
     * It uses a simple recurrence relation:
     * 
     *      F(n) = 2 * F(n - 1) + F(n - 3);
     * @param n size of matrix
     * @param mod modulo number
     * 
     * @return return number of ways modulo mod
     */
    uint64_t solve(int n, uint64_t mod) {
        if(n <= 2) {
            return n % mod;
        }

        if(3 == n) {
            return 5 % mod;
        }

        std::vector<uint64_t> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 5;
        for(uint64_t i = 4; i <= n; i++) {
            dp[i] = ((2 * dp[i - 1]) + dp[i - 3]) % mod;
        }

        return dp[n];
    }
}

/**
 * Function to test above algorithm
 */
static void test() {
    assert(math::solve(3, 1000) == 5);
    assert(math::solve(4, 1000) == 11);
    assert(math::solve(5, 1000) == 24);
    assert(math::solve(6, 1000) == 53);
    assert(math::solve(10, 10000) == 1255);
    assert(math::solve(10, 1000) == 255);
    assert(math::solve(50, 1000000007) == 451995198);
    assert(math::solve(100, 1000000007) == 190242381);
    std::cout << "All test case passes." << '\n';
}

/**
 * Driver function
 */
int main() {
    test();
    return 0;
}