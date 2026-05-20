/**
 * @file tribonacci.cpp
 * @brief Implementation of nth tribonacci (extended version of fibonacci) number using
 * matrix exponentiation.
 * 
 * Time complexity: O(log(n));
 *  
 * @details https://www.geeksforgeeks.org/dsa/tribonacci-numbers
 * 
 * @author [Hxrshthetic](https://github.com/Hxrshthetic)
 */

#include <iostream>
#include <cstdint>
#include <cassert>
#include <vector>

/**
 * @namespace math
 * @brief Math algorithms
 */
namespace math {

    /**
     * This function calculates product of two matrices.
     * Time complexity: O(n^3), since n = 3 => Time: O(1).
     * 
     * @param A, B matrices
     * @param mod modulus number
     */
    std::vector<std::vector<uint64_t>> multiply(const std::vector<std::vector<uint64_t>>& A, const std::vector<std::vector<uint64_t>>& B, uint64_t mod) {
        std::vector<std::vector<uint64_t>> res(3, std::vector<uint64_t>(3, 0));

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
     * @param A matrix
     * @param n power
     * @param mod modulus number
     */
    std::vector<std::vector<uint64_t>> matrix_exponentiate(const std::vector<std::vector<uint64_t>>& A, uint64_t n, uint64_t mod) { 
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

        std::vector<std::vector<uint64_t>> half = matrix_exponentiate(A, n / 2, mod);
        std::vector<std::vector<uint64_t>> res = multiply(half, half, mod);

        if(n & 1) {
            res = multiply(res, A, mod);
        }

        return res;
    }

    /**
     * This function calculates Nth tribonacci number modulo given mod
     * @param n nth tribonacci number
     * @param mod modulo number
     */
    uint64_t tribonacci(uint64_t n, uint64_t mod) {
        if(n <= 1) {
            return 0;
        }

        if(2 == n) {
            return 1;
        }

        std::vector<std::vector<uint64_t>> A(3, std::vector<uint64_t>(3));
        std::vector<std::vector<uint64_t>> base(3, std::vector<uint64_t>(1));

        A = {
            {1, 1, 1},
            {1, 0, 0},
            {0, 1, 0}
        };
        base = {
            {1},
            {0},
            {0}
        };

        std::vector<std::vector<uint64_t>> aPowN(3, std::vector<uint64_t>(3, 0));
        aPowN = matrix_exponentiate(A, n - 2, mod);

        std::vector<std::vector<uint64_t>> result(3, std::vector<uint64_t>(1, 0));

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 1; j++) {
                for(int k = 0; k < 3; k++) {
                    result[i][j] = ((result[i][j] % mod) + ((aPowN[i][k] * base[k][j]) % mod)) % mod;
                }
            }
        }

        return result[0][0] % mod;
    }
}

/**
 * Function to test above algorithm
 */
static void test() {
    assert(math::tribonacci(6, 1000000007) == 7);
    std::cout << ("Test case 1 Passed\n");
    assert(math::tribonacci(10, 1000000007) == 81);
    std::cout << ("Test case 2 Passed\n");
    assert(math::tribonacci(50, 1000000007) == 171504990);
    std::cout << ("Test case 3 Passed\n");
    assert(math::tribonacci(50, 100000) == 29233);
    std::cout << ("Test case 4 Passed\n");
    assert(math::tribonacci(70, 1000000007) == 878948754);
    std::cout << ("Test case 5 Passed\n");
    assert(math::tribonacci(70, 100000) == 77176);
    std::cout << ("Test case 6 Passed\n");
    assert(math::tribonacci(70, 10000) == 7176);
    std::cout << ("Test case 7 Passed\n");
    assert(math::tribonacci(500, 1000000007) == 217072921);
    std::cout << ("Test case 8 Passed\n");
}

/**
 * Driver function
 */
int main() {
    test();
    uint64_t mod = 1000000007;
    std::cout << ("Enter the value of N: ");
    uint64_t n = 0;
    std::cin >> n;
    std::cout << n << ("th Tribonacci number in modulo ") << mod << ": "
              << math::tribonacci(n, mod) << std::endl;
    return 0;
}
