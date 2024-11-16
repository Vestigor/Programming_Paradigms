/***********************************************************
* File:     problem_4.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Clion 2024
* Function: Testing the performance of virtual functions versus non-virtual functions.
* Date:     2024.11.16
* Update:   2024.11.16
***********************************************************/
#include <iostream>
#include <ctime>

typedef unsigned long long  ULL;

/***********************************************************
* Class Name:   Base
* Function:     Base class demonstrating the use of virtual and non-virtual functions.
***********************************************************/
class Base {
public:
    virtual void virtual_function()
    {
        for (int i = 0; i < 1000; ++i) {
            ULL temp = i * i;
        }
    }

    void non_virtual_function()
    {
        for (int i = 0; i < 1000; ++i) {
            ULL temp = i * i;
        }
    }
};

/***********************************************************
* Class Name:   Derived
* Function:     Derived class that overrides the virtual function from Base.
***********************************************************/
class Derived : public Base {
public:
    void virtual_function()
    {
        for (int i = 0; i < 1000; ++i) {
            ULL temp = i * i; // Simple computation
        }
    }
};

/***********************************************************
* Function Name:   main
* Function:        Measures the performance of virtual and non-virtual function calls.
* Input Parameter: None
* Returned Value:  0
* Instructions:    Creates an instance of Derived, calls the functions in a loop, and
*                  records the time taken for both virtual and non-virtual function calls.
***********************************************************/
int main()
{

    Base *base = new Derived();// Create a Derived object as a Base pointer
    clock_t start_time, end_time;// Variables for timing

    // Measure time for virtual function calls
    start_time = clock();
    for (int i = 0; i < 10000000; ++i) {
        base->virtual_function();
    }
    end_time = clock();
    double virtual_time = 1000.0 * (end_time - start_time) / CLOCKS_PER_SEC;

    // Measure time for non-virtual function calls
    start_time = clock();
    for (int i = 0; i < 10000000; ++i) {
       base->non_virtual_function();
    }
    end_time = clock();
    double non_virtual_time = 1000.0 * (end_time - start_time) / CLOCKS_PER_SEC;


    std::cout << "虚函数调用时间: " << virtual_time << " ms" << std::endl;
    std::cout << "非虚函数调用时间: " << non_virtual_time << " ms" << std::endl;

    // Clean up dynamically allocated memory
    delete base;
    return 0;
}

