/***********************************************************
* File:     problem_3.cpp
* Author:   Xiaolong Ma(ÂíÐ¡Áú)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: Duplicate elements
* Date:     2024.10.13
* Update:   2024.10.13
***********************************************************/

#include<iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <unordered_map>

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

int GetId(long long x, long long y) { return static_cast<int>(x < 0 ? (x + 1ll) / y - 1 : x / y); }

/***********************************************************
* Function Name:   ContainsSimilarNearly
* Function:        Check if there are two distinct indices i and j
*                  such that abs(nums[i] - nums[j]) <= t and abs(i - j) <= k.
* Input Parameter: nums - vector of integers to check for similarity
*                  k - maximum allowable distance between indices i and j
*                  t - maximum allowable difference between nums[i] and nums[j]
* Returned Value:  true if such elements exist, otherwise false
* Instructions:    Use hash tables and bucket sorting to reduce time complexity
***********************************************************/
bool ContainsSimilarNearly(const std::vector<int>& nums, const int k, const int t)
{
	std::unordered_map<int, int>map;
	int len = nums.size();
	for (int i = 0; i < len; i++) {
		long long num = nums[i];
		//Find the bucket number corresponding to the element
		int id = GetId(num, t + 1ll);

		//When divided into the same bucket
		if (map.count(id)) 
			return true;

		//When divided into adjacent buckets
		if (map.count(id - 1) && abs(num - map[id - 1]) <= t)
			return true;
		if (map.count(id + 1) && abs(num - map[id + 1]) <= t)
			return true;
			
		map[id] = static_cast<int>(num);
		if (i >= k)
			map.erase(GetId(nums[i - k], t + 1ll));
	}
	return false;
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
		std::cout << "Please enter the integer array size [2~100000]\n";
		std::cin >> size;
		// Check if the input is valid and within the specified range
		if (std::cin.fail() || size < 2 || size>100000) {
			std::cout << "Enter illegal, please re-enter!\n";
			ClearBuffer();
			continue;
		}
		ClearBuffer();
		break;
	}

	std::cout << "\nPlease enter the integer array element. " << size << " in total. The range of a single element is [-1000000000,1000000000]\n";
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
	ClearBuffer();

	// Display the entered array elements
	std::cout << "\nThe elements in the array are:\n";
	for (int i = 0; i < size; i++) {
		std::cout << std::left << std::setw(10) << numbers[i] << " ";
		// Print a newline every 10 elements or when the last element is printed
		if ((i + 1) % 5 == 0 || i + 1 == size)
			std::cout << "\n";

	}

	int k;
	while (true) {
		std::cout << "\n\nPlease enter the distance range k [0~"<< size <<"]\n";
		std::cin >> k;
		// Check if the input is valid and within the specified range
		if (std::cin.fail() || k < 0 || k>size) {
			std::cout << "Enter illegal, please re-enter!\n";
			ClearBuffer();
			continue;
		}
		ClearBuffer();
		break;
	}

	int t;
	while (true) {
		std::cout << "\n\nPlease enter the accuracy range t [0~1000000000]\n";
		std::cin >> t;
		// Check if the input is valid and within the specified range
		if (std::cin.fail() || t < 0||t>1000000000) {
			std::cout << "Enter illegal, please re-enter!\n";
			ClearBuffer();
			continue;
		}
		ClearBuffer();
		break;
	}

	// Display the result of the duplicate check
	std::cout << "\n\n\nResult:\n" << (ContainsSimilarNearly(numbers, k,t) ? "true\n" : "false\n");

	return 0;
}
