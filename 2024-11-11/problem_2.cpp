/***********************************************************
* File:     problem_2.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Compiler: CLion 2024
* Function: Implement operations for 4x4 matrices including addition, multiplication,
*           assignment, and element access.
* Date:     2024.11.16
* Update:   2024.11.16
***********************************************************/
#include <iostream>
#include <array>
#include <vector>

/***********************************************************
* Class Name:    Matrix
* Function:      Represents a 4x4 matrix with basic operations including
*                addition, multiplication, and element access.
***********************************************************/
class Matrix {
private:
    std::array<std::array<float, 4>, 4> data;

public:
    Matrix();

    Matrix(const std::array<float, 16> &arr);
    Matrix(const std::vector<float> &arr);

    Matrix Add(const Matrix &other) const{return *this + other;}

    Matrix Multiply(const Matrix &other) const{return *this * other;}

    Matrix& operator=(const Matrix &other);

    Matrix operator+(const Matrix &other) const;

    Matrix operator-(const Matrix &other) const;

    Matrix operator*(const Matrix &other) const;

    Matrix &operator+=(const Matrix &other);

    float &operator()(const int row, const int col){return data[row][col];}

    float operator()(const int row, const int col) const{return data[row][col];}

    void Print() const;
};

/***********************************************************
 * Constructor Name: Matrix (Default)
 * Function:         Initializes the matrix with values inputted from standard input.
 * Input Parameter:  None
 ***********************************************************/
Matrix::Matrix()
{
    std::cout << "Enter 16 values for the matrix: ";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cin >> data[i][j];
        }
    }
}

/***********************************************************
 * Constructor Name: Matrix (Array)
 * Function:         Initializes the matrix using a 16-element array.
 * Input Parameter:  arr: A constant reference to an array of 16 floats.
 ***********************************************************/
Matrix::Matrix(const std::array<float, 16> &arr)
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            data[i][j] = arr[i * 4 + j];
        }
    }
}

/***********************************************************
 * Constructor Name: Matrix (Vector)
 * Function:         Initializes the matrix using a vector of 16 floats.
 * Input Parameter:  arr: A reference to a vector of 16 floats.
 ***********************************************************/
Matrix::Matrix(const std::vector<float>& arr)
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            data[i][j] = arr[i * 4 + j];
        }
    }
}

/***********************************************************
 * Operator:         operator+
 * Function:         Adds two matrices and returns a new matrix as the result.
 * Input Parameter:  other: A constant reference to the matrix to be added.
 * Returned Value:   A new Matrix object containing the result of the addition.
 ***********************************************************/
Matrix Matrix::operator+(const Matrix &other) const
{
    Matrix result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.data[i][j] = this->data[i][j] + other.data[i][j];
        }
    }
    return result;
}

/***********************************************************
 * Operator:         operator-;
 * Function:         Subtracts one matrix from another and returns a new matrix as the result.
 * Input Parameter:  other: A constant reference to the matrix to be subtracted.
 * Returned Value:   A new Matrix object containing the result of the subtraction.
 ***********************************************************/
Matrix Matrix::operator-(const Matrix &other) const
{
    Matrix result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.data[i][j] = this->data[i][j] - other.data[i][j];
        }
    }
    return result;
}

/***********************************************************
 * Operator:         operator*
 * Function:         Multiplies two matrices and returns a new matrix as the result.
 * Input Parameter:  other: A constant reference to the matrix to be multiplied.
 * Returned Value:   A new Matrix object containing the result of the multiplication.
 ***********************************************************/
Matrix Matrix::operator*(const Matrix &other) const
{
    Matrix result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.data[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                result.data[i][j] += this->data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

/***********************************************************
 * Operator:         operator=
 * Function:         Assignment operator to copy the values from another matrix.
 * Input Parameter:  other: A constant reference to the matrix to be copied.
 * Returned Value:   A reference to the modified matrix (*this).
 ***********************************************************/
Matrix & Matrix::operator=(const Matrix &other)
{
    if (this == &other)
        return *this;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            this->data[i][j] = other.data[i][j];
        }
    }
    return *this;
}

/***********************************************************
 * Operator:         operator+=
 * Function:         Adds another matrix to the current matrix (in-place).
 * Input Parameter:  other: A constant reference to the matrix to be added.
 * Returned Value:   A reference to the modified matrix (*this).
 ***********************************************************/
Matrix& Matrix::operator+=(const Matrix &other)
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            this->data[i][j] += other.data[i][j];
        }
    }
    return *this;
}

/***********************************************************
 * Operator:         operator()
 * Function:         Accesses and modifies an element at a specified row and column.
 * Input Parameter:  row: The row index, col: The column index.
 * Returned Value:   A reference to the float at the specified position.
 ***********************************************************/
void Matrix::Print() const
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

/***********************************************************
* Function Name:   main
* Function:        Demonstrate the use of the Matrix class and its operations
* Input Parameter: None
* Returned Value:  0
* Instructions:    Create and print matrices, perform matrix addition, multiplication, 
*                  and demonstrate usage of operator overloading.
***********************************************************/
int main()
{
    // Using the default constructor to create a matrix and input elements
    Matrix mat1;
    std::cout << "Matrix 1: \n";
    mat1.Print();

    // Create a matrix using an array of 16 elements
    std::array<float, 16> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    Matrix mat2(arr);
    std::cout << "Matrix 2: \n";
    mat2.Print();

    // Perform matrix addition
    Matrix result = mat1.Add(mat2);
    std::cout << "Result of Matrix1 + Matrix2: \n";
    result.Print();

    // Perform matrix multiplication
    Matrix result2 = mat1.Multiply(mat2);
    std::cout << "Result of Matrix1 * Matrix2: \n";
    result2.Print();

    // Using the += operator to add mat2 to mat1
    mat1 += mat2;
    std::cout << "Matrix1 after adding Matrix2: \n";
    mat1.Print();

    // Access and modify an element using the operator()
    std::cout << "Element at (0, 0) of mat1: " << mat1(0, 0) << std::endl;
    mat1(0, 0) = 99.99;
    std::cout << "Updated element at (0, 0) of mat1: " << mat1(0, 0) << std::endl;

    return 0;
}
