/***********************************************************
* File:     problem_1.cpp
* Author:   Xiaolong Ma(ÂíÐ¡Áú)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: Duplicate elements
* Date:     2024.10.13
* Update:   2024.10.13
***********************************************************/

#include <iostream>
#include <vector>
#include <iomanip>
#include <unordered_set>

#define INT_MAX 2147483647

/***********************************************************
* Function Name:   ClearBuffer
* Function:        Clear the input buffer to handle invalid inputs
* Input Parameter:
* Returned Value:  void
***********************************************************/
void ClearBuffer() 
{
	std::cin.clear();// Clear error flags on cin
	std::cin.ignore(INT_MAX, '\n'); // Ignore characters in input buffer until a newline
}


/***********************************************************
* Function Name:   ContainsDuplicate
* Function:        Check whether the given integer vector contains duplicates
* Input Parameter: nums: a reference to a vector of integers
* Returned Value:  true if duplicates exist, otherwise false
* Instructions  :  Use hash table to reduce time complexity
***********************************************************/
bool ContainsDuplicate(const std::vector<int>& nums)
{
	std::unordered_set<int> temp;// Use a set to track seen numbers
	for (int n : nums) {
		if (temp.find(n) != temp.end())// If number already exists in set, return true
			return true;
		temp.insert(n);// Add the number to the set
	}
	return false;// No duplicates found
}

/***********************************************************
* Function Name:   main
* Function:        Handle user input, store integers in a vector,
*                  and determine if duplicates exist
* Input Parameter:
* Returned Value:  0
***********************************************************/
int main()
{
	int size;// Variable to store the size of the integer array
	while (true) {
		std::cout << "Please enter the integer array size[1~100000]\n";
		std::cin >> size;
		// Check if the input is valid and within the specified range
		if (std::cin.fail() || size <= 0 || size>100000) {
			std::cout << "Enter illegal, please re-enter!\n";
			ClearBuffer();
			continue;
		}
		ClearBuffer();
		break;
	}

	std::cout << "Please enter the integer array element. "<<size<<"in total. The range of a single element is[-1000000000,1000000000]\n";
	std::vector<int> numbers(size);
	for (int i = 0; i < size; i++) {
		std::cin >> numbers[i];
		if (std::cin.fail() || numbers[i] < -1000000000 || numbers[i] >1000000000) {
			std::cout << "Invalid input, please re-enter from scratch!\n";
			ClearBuffer();
			i = -1; // Reset the index to start over
			continue;
		}
	}

	// Display the entered array elements
	std::cout << "The elements in the array are:\n";
	for (int i = 0; i < size; i++) {
		std::cout << std::left << std::setw(10)<< numbers[i] << " ";
		// Print a newline every 10 elements or when the last element is printed
		if ((i + 1) % 5 == 0 || i + 1 == size)
			std::cout << "\n";
		
	}

	// Display the result of the duplicate check
	std::cout <<"\nResult:\n" << (ContainsDuplicate(numbers) ? "true\n" : "false\n");

	return 0;
}