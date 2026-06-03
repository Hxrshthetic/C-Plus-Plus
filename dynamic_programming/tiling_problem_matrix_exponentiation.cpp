/**
 * @file tiling_problem.cpp
 * @brief implementation of tiling problem using a simple 1D vector.
 * 
 * Time complexity: O(logn);
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
 * 
 * @see tiling_problem.cpp
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
     * This function calculates product of two matrices.
     * Time complexity: O(n^3), since n = 3 => Time: O(1).
     * 
     * @param A, B matrices
     * @param mod modulus number
     */
    std::vector<std::vector<uint64_t>> multiply(std::vector<std::vector<uint64_t>>& A, std::vector<std::vector<uint64_t>>& B, uint64_t mod) {
        std::vector<std::vector<uint64_t>> res(3, std::vector<std::uint64_t>(3, 0));
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                for(int k = 0; k < 3; k++) {
                    res[i][j] = (res[i][j] + ((A[i][k] * B[k][j]) % mod)) % mod; 
                }
            }
        }

        return res;
    }

   /**
     * This function finds nth power of a matrix.
     * Time complexity: O(log(n))
     * 
     * @param A matrix
     * @param n power
     * @param mod modulus number
     */
    std::vector<std::vector<uint64_t>> matrix_exponentiation(std::vector<std::vector<uint64_t>>& A, uint64_t n, uint64_t mod) {
        if(0 == n) {
            return {
                {1, 0, 0},
                {0, 1, 0},
                {0, 0, 1}
            };
        }

        if(1 == n) {
            return A;
        }

        std::vector<std::vector<uint64_t>> half = matrix_exponentiation(A, n / 2, mod);

        std::vector<std::vector<uint64_t>> res = multiply(half, half, mod);

        if(n & 1) {
            res = multiply(res, A, mod);
        }

        return res;
    }

    /**
     * This function calculates the number of ways to fill 2 * n 
     * matrix using given 2 types of tiles.
     * 
     * It uses a simple recurrence relation and matrix exponentiation:
     * 
     *      F(n) = 2 * F(n - 1) + F(n - 3);
     * 
     * @param n size of matrix
     * @param mod modulo number
     * 
     * @return return number of ways modulo mod
     */
    uint64_t solve(uint64_t n, uint64_t mod) {
        if(n <= 2) {
            return n % mod;
        }

        if(3 == n) {
            return 5 % mod;
        }

        std::vector<std::vector<uint64_t>> A(3, std::vector<uint64_t>(3));
        std::vector<std::vector<uint64_t>> base(3, std::vector<uint64_t>(1));

        A = {
            {2, 0, 1},
            {1, 0, 0},
            {0, 1, 0}
        };

        base = {
            {5},
            {2},
            {1}
        };

        std::vector<std::vector<uint64_t>> aPowN(3, std::vector<uint64_t>(3, 0));
        aPowN = matrix_exponentiation(A, n - 3, mod);

        std::vector<std::vector<uint64_t>> ans(3, std::vector<uint64_t>(1, 0));
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 1; j++) {
                for(int k = 0; k < 3; k++) {
                    ans[i][j] = (ans[i][j] + ((aPowN[i][k] * base[k][j]) % mod)) % mod;
                }
            }
        }

        return ans[0][0];
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