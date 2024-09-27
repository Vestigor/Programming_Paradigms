/***********************************************************
* File:     problem_2.cpp
* Author:   Xiaolong Ma(ÂíÐ¡Áú)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: solve the problem which is called "the code of the code box the chocolate locked in"
* Date:     2024.9.24
* Update:   2024.9.24
***********************************************************/

#include <iostream>
#include <string>
#include <limits>

/***********************************************************
* Function Name:   NumberOfMaogeDigits
* Function:        calculate the number of Maoge digits
* Input Parameter: n:the length of Maoge digits
* Returned Value:  number_maoge_digits: the number of Maoge digits
* Instruction:     On a scale from 0 to 9,
*                  there are 5 even numbers (0,2,4,6,8)
*				   and 4 prime numbers(2,3,5,7)
***********************************************************/
int NumberOfMaogeDigits(int n)
{
	int number_maoge_digits = 5;
	if (n > 1) {
		for (int i = 1; i < n ; i++) {
			if (i % 2)
				number_maoge_digits *= 4;//prime number
			else
				number_maoge_digits *= 5;//even number
		}
	}
	return number_maoge_digits;
}

/***********************************************************
* Function Name:   main
* Function:        input&output
* Input Parameter:
* Returned Value: 0
***********************************************************/
int main()
{
	int n;
	while (true) {
		std::cout << "Please enter the code box prompt number[1-14].\n";//When n=15, the number of digits exceeds the upper limit of the int type
		std::cin >> n;
		if (std::cin.fail() || n <= 0 || n > 15) {
			std::cout << "Input error, please re-input!\n";
			//Clear buffer
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		break;
	}
	std::cout << "The number of digits whose length is n and the number of maoge is \n" << NumberOfMaogeDigits(n) << "\n";

	return 0;
}