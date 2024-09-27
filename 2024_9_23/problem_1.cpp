/***********************************************************
* File:     problem_1.cpp
* Author:   Xiaolong Ma(ÂíÐ¡Áú)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: solve the problem which is called "buy chocolate"
* Date:     2024.9.23
* Update:   2024.9.24
***********************************************************/

#include <iostream>
#include <string>

/***********************************************************
* Function Name:   PalindromeJudgment
* Function:        determines whether a string can become a palindrome string after deleting a character
* Input Parameter: str: the string you input
* Returned Value:  true or false
***********************************************************/
bool PalindromeJudgment(std::string str)
{
	if (str.length() <3)
		return true;
	std::string modified_str;
	modified_str.resize(str.length() - 1);//Initializes the string size
	for (unsigned int i = 0; i < str.length(); i++) {
		//Delete a character to form a new string
		for (unsigned int j = 0, k = 0; j < str.length() - 1; j++, k++) {
			if (k == i)
				k++;
			else
				modified_str[j] = str[k];
		}
		unsigned int left = 0, right = modified_str.length() - 1;
		//determines whether a string can become a palindrome string
		for (; left<=right; left++, right--) {
			if (modified_str[left] != modified_str[right])
				break;
		}
		if (left > right)
			return true;
	}
	return false;
}

/***********************************************************
* Function Name:   main
* Function:        input&output
* Input Parameter:
* Returned Value:  0
***********************************************************/
int main()
{
	std::string str;
	std::cout << "Please enter a non-empty string.\n";
	std::getline(std::cin, str);
	if (str.length() == 0)
		std::cout << "Input does not meet the requirements!\n";
	else
	    std::cout << (PalindromeJudgment(str) ? "True" : "False") << "\n";

	return 0;
}