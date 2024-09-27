/***********************************************************
* File:     problem_3.cpp
* Author:   Xiaolong Ma(ÂíÐ¡Áú)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: modify the outside string object in its own unique way
* Date:     2024.9.17
* Update:   2024.9.20
***********************************************************/

#include <iostream>
#include <string>

/***********************************************************
* Function Name:   ModifyStringByPointer
* Function:        modify string through pointer
* Input Parameter: pstr: the pointer of str
*                  after_str: the string you want to change
* Returned Value:  
***********************************************************/
void ModifyStringByPointer(std::string* pstr, std::string after_str)
{
	if (pstr != NULL)
		*pstr = after_str;
}

/***********************************************************
* Function Name:   ModifyStringByReference
* Function:        modify string through reference
* Input Parameter: rstr: the reference of str
*                  after_str: the string you want to change
* Returned Value:  0
***********************************************************/
void ModifyStringByReference(std::string& rstr, std::string after_str)
{
	rstr = after_str;
}

/***********************************************************
* Function Name:   main
* Function:        create and initialize a string object and output
* Input Parameter:
* Returned Value:  0
***********************************************************/
int main()
{
	std::string str, after_str;
	std::cout << "Please input a string object\n";
	std::getline(std::cin, str);
	std::cout << "Please input the string you want to change\n";
	std::getline(std::cin,after_str);
	std::string temp_str = str;//Temporarily store the string to see if the two methods get the same result
	std::cout << "The initial string\n" << str << "\n";
	ModifyStringByPointer(&str, after_str);
	std::cout << "STRING modified through pointer\n" << str<< "\n";
	str = temp_str;
	std::cout << "The initial string\n" << str << "\n";
	ModifyStringByReference(str, after_str);
	std::cout << "String modified through reference\n" << str << "\n";

	return 0;
}