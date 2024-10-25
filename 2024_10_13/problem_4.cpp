/***********************************************************
* File:     problem_4.cpp
* Author:   Xiaolong Ma(ÂíÐ¡Áú)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: Fibonacci
* Date:     2024.10.15
* Update:   2024.10.15
***********************************************************/

#include <iostream>
#include <string>
#include <unordered_map>
#include <stdexcept> 

#include <boost/multiprecision/cpp_int.hpp> // Boost library for handling large integers



/***********************************************************
* Function Name:   MatrixMultiply
* Function:        Multiplies two 2x2 matrices
* Input Parameter:
*   - a: First matrix
*   - b: Second matrix
* Returned Value:  A new matrix that is the product of 'a' and 'b'
***********************************************************/
std::array<std::array<boost::multiprecision::cpp_int, 2>, 2> MatrixMultiply(
    const std::array<std::array<boost::multiprecision::cpp_int, 2>, 2>& a,
    const std::array<std::array<boost::multiprecision::cpp_int, 2>, 2>& b) {

    std::array<std::array<boost::multiprecision::cpp_int, 2>, 2> result = { {{0, 0}, {0, 0}} };
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

/***********************************************************
* Function Name:   MatrixPow
* Function:        Computes the power of a 2x2 matrix using exponentiation by squaring
* Input Parameter:
*   - base: The base matrix
*   - exp:  The exponent to raise the matrix to
* Returned Value:  The resulting matrix after exponentiation
***********************************************************/
std::array<std::array<boost::multiprecision::cpp_int, 2>, 2> MatrixPow(
    std::array<std::array<boost::multiprecision::cpp_int, 2>, 2> base, int exp) {

    std::array<std::array<boost::multiprecision::cpp_int, 2>, 2> result = { {{1, 0}, {0, 1}} }; // Identity matrix
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = MatrixMultiply(result, base);
        }
        base = MatrixMultiply(base, base);
        exp /= 2;
    }
    return result;
}

/***********************************************************
* Function Name:   FibonacciRuntime
* Function:        Calculates the Fibonacci number at position 'n'
* Input Parameter:
*   - n: The position in the Fibonacci sequence
* Returned Value:  The Fibonacci number at position 'n'
***********************************************************/
boost::multiprecision::cpp_int FibonacciRuntime(int n, std::unordered_map<int, boost::multiprecision::cpp_int>& fibonacci_cache) {

    if (n < 0) {
        throw std::invalid_argument("Input must be a non-negative integer.\n");
    }

    // Return cached result if available
    if (fibonacci_cache.find(n) != fibonacci_cache.end()) {
        return fibonacci_cache[n];
    }

    // Base cases for Fibonacci sequence
    if (n == 0) return 0;
    if (n == 1) return 1;

    // Define the transformation matrix for Fibonacci sequence
    std::array<std::array<boost::multiprecision::cpp_int, 2>, 2> base = { {{1, 1}, {1, 0}} };

    // Compute the power of the matrix
    std::array<std::array<boost::multiprecision::cpp_int, 2>, 2> result = MatrixPow(base, n - 1);

    // The Fibonacci number is in the top-left of the resulting matrix
    boost::multiprecision::cpp_int fib_n = result[0][0];

    // Cache the result to avoid re-calculating
    fibonacci_cache[n] = fib_n;

    return fib_n; // Return the nth Fibonacci number.
}

/***********************************************************
* Function Name:   main
* Function:        Handles user input and output for calculating Fibonacci numbers
* Input Parameter: None
* Returned Value:  0
***********************************************************/
int main() {

    //Global variable to cache Fibonacci results to avoid repeated calculation
    std::unordered_map<int, boost::multiprecision::cpp_int> fibonacci_cache;

    std::string choice;
    do {
        try {
            int n;

            //I don't recommend using large numbers unless your patience is extremely good and your computer has plenty of memory.Of course, n<=INT_MAX.
            std::cout << "Enter the position in the Fibonacci sequence (non-negative): \n(The calculation is faster when n is about 100000 or less; More than that, the calculation is slower)\n";

            std::cin >> n;
            if (std::cin.fail()) {
                throw std::invalid_argument("Input must be a non-negative integer.\n");
            }

            // Calculate and display the Fibonacci number
            auto result = FibonacciRuntime(n, fibonacci_cache);
            std::cout << "Fibonacci(" << n << ") = " << result << std::endl;
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what();
        }

        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');

        while (true) {
            std::cout << "Do you want to calculate another Fibonacci number? (y/n): ";
            std::getline(std::cin, choice);
            if (choice == "n" || choice == "N" || choice == "y" || choice == "Y")
                break;
            std::cout << "Your input is not y/n\n";
        }

    } while (choice == "y" || choice == "Y");  // Continue if user inputs 'y' or 'Y'

    return 0;
}
