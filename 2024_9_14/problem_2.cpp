/***********************************************************
* File:     problem_2.cpp
* Author:   Xiaolong Ma(ÂíÐ¡Áú)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: the square of the number in the vector
* Date:     2024.9.17
* Update:   2024.9.20
***********************************************************/

#include <iostream>
#include <vector>
#include <limits>

const int kLength = 25; //define a constant instand of 25 to facilitate future changes

/***********************************************************
* Function Name:   ClearBuffer
* Function:        clear the buffer to prevent impact on subsequent input
* Input Parameter:
* Returned Value:
***********************************************************/
void ClearBuffer() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/***********************************************************
* Function Name:   SquareVector
* Function:        square the element and return it to its original position
* Input Parameter: number: the element of vector
* Returned Value: 
***********************************************************/
void SquareVector(std::vector<float>& numbers) {
	for (int i = 0; i < kLength; i++)
		numbers[i] *= numbers[i];
}

/***********************************************************
* Function Name:    main
* Function:         input&output
* Input Parameter:
* Returned Value:  0
***********************************************************/
int main()
{
	std::vector<float> numbers(kLength);
	for (int i = 0; i < kLength; i++) {
		while (true) {
		    std::cout << "Please input float number " << (i + 1) << ": ";
			std::cin >> numbers[i];
			if (std::cin.fail()) {
				std::cout << "Invalid input, please re-input\n";
				ClearBuffer();
				continue;
			}
			ClearBuffer();
			break;
		}
	}
	std::cout << "The vector before squaring:\n";
	for (int i = 0; i < kLength; i++) {
		std::cout << numbers[i] << " ";
	}
	std::cout << "\n";
	SquareVector(numbers);
	std::cout << "The vector after squaring:\n";
	for (int i = 0; i < kLength; i++) {
		std::cout << numbers[i] << " ";
	}
	std::cout << "\n";

	return 0;
}