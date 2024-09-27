/***********************************************************
* File:     problem_4.cpp
* Author:   Xiaolong Ma(ÂíÐ¡Áú)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: solve the problem which is called "the mystery of A+B"
* Date:     2024.9.24
* Update:   2024.9.24
***********************************************************/

#include <iostream>
#include <string>

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
* Function Name:   LengthInput
* Function:        Enter the length of 'A' or 'B' and handle errors
* Input Parameter: ch:'A' or 'B'
* Returned Value:  len
***********************************************************/
int LengthInput(char ch)
{
	int len;
	while (true) {
		std::cout << "Please enter the length of " << ch << ".[1 - 100]\n";
		std::cin >> len;
		if (std::cin.fail() || len < 1 || len>100) {
			std::cout << "Input error, please re-input!\n";
			ClearBuffer();
			continue;
		}
		ClearBuffer();
		break;
	}
	return len;
}

/***********************************************************
* Function Name:   DigitalInput
* Function:        Enter 'A' or 'B' and handle errors
* Input Parameter: ch :'A' or 'B'
*                  len:the length of 'A' or 'B'
* Returned Value:  num
***********************************************************/
std::string DigitalInput(char ch, int len)
{
	std::string num;
	while (1) {
		bool digital_or_not=true;
		std::cout << "Please enter a positive integer " << ch << ".\n";
		std::getline(std::cin , num);
		for (unsigned int i = 0; i < num.length(); i++)
			if (num[i] < '0' || num[i] > '9')//Check whether the numbers are pure numbers
				digital_or_not = false;
		if (!digital_or_not) {
			std::cout << "The input is not a positive integer!\n";
			continue;
		}
		if (num.length() != len) {
			std::cout << "The data length does not meet requirements!\n";
			continue;
		}
		break;
	}
	return num;
}

/***********************************************************
* Function Name:   AdditionOperation
* Function:        add A and B
* Input Parameter: A B
* Returned Value:  result
***********************************************************/
std::string AdditionOperation(std::string A, std::string B)
{
	unsigned int len = A.length() > B.length() ? A.length() : B.length();
	//Add length to prevent overstepping
	while (A.length() < len) 
		A.insert(A.begin(), '0');
	while (B.length() < len)
		B.insert(B.begin(), '0');
	std::string result;
	bool carry = false;//Confirm whether to carry
	for (int i = len-1; i >= 0; i--) {
		char temp = A[i]-'0' + B[i]-'0';
		if (carry)
			temp += 1;
		if (temp >= 10) {
			temp -= 10;
			carry = true;
		}
		else
			carry = false;
		//Calculates from low to high, placing new characters in front of the string to avoid subsequent transposition operations
		result.insert(result.begin(), '0' + temp);
	}
	if(carry)
		result.insert(result.begin(), '1');

	return result;
}

/***********************************************************
* Function Name:   main
* Function:        main function
* Input Parameter:
* Returned Value:  0
***********************************************************/
int main()
{
	std::string A, B;
	int len_A, len_B;
	len_A = LengthInput('A');
	A = DigitalInput('A', len_A);
	len_B = LengthInput('B');
	B = DigitalInput('B', len_B);
	std::cout << "The calculated result is \n" << AdditionOperation(A, B) << "\n";

	return 0;
}