/***********************************************************
* File:     problem_4.cpp
* Author:   Xiaolong Ma(ÂíÐ¡Áú)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: solve the problem which is called "the mystery of scale"
* Date:     2024.9.24
* Update:   2024.9.24
***********************************************************/

#include <iostream>
#include <string>

#define MIX_DEC_NUMBER 1000000
#define MIX_SCALE 20

/***********************************************************
* Function Name:   BaseConversion
* Function:        Converts decimal to arbitrary base
* Input Parameter: figure: the number need to be converted
*                  m: base
* Returned Value:  result
***********************************************************/
std::string BaseConversion(int figure, int m)
{
	if (figure == 0)
		return "0";
	std::string result;
	char cplace;
	while (figure != 0) {
		int iplace = figure % m;
		if (iplace >= 10)
			cplace = iplace - 10 + 'A';
		else
			cplace = iplace + '0';
		result.insert(result.begin(), cplace);
		figure = (figure - iplace) / m;
	}
	return result;
}

/***********************************************************
* Function Name:   SenaryConversion
* Function:        Convert Senary to decimal
* Input Parameter: n :the number need to be converted
* Returned Value:  dec_n||-1
***********************************************************/
int SenaryConversion(std::string n)
{
	int dec_n = 0;
	for (unsigned int i = 0; i < n.length(); i++)
		dec_n = dec_n*6 + (n[i] - '0');
	if (dec_n <= MIX_DEC_NUMBER)//Check whether it is out of range
		return dec_n;
	else
		return -1;
}

/***********************************************************
* Function Name:   main
* Function:        input&output
* Input Parameter:
* Returned Value:  0
***********************************************************/
int main()
{
	std::string n;
	int dec_n = -1;
	while (true) {
		bool digital_or_not = true;
		std::cout << "Please enter a senary number[0-33233344].\n";//1000000 corresponds to the hexadecimal 33233344
		std::getline(std::cin , n);
		if (n.length() == 0) {
			std::cout << "No valid data is entered!\n";
			continue;
		}
		//Check whether pure numbers are entered, that is, a positive number is entered
		for (unsigned int i = 0; i < n.length(); i++)
			if (n[i] < '0' || n[i] >= '6')
				digital_or_not = false;
		if (digital_or_not)
			if (n.length() <= 8&& n.length()>0)//Length over 8 is clearly out of range
				dec_n = SenaryConversion(n);
		if (dec_n != -1)
			break;
		if (!digital_or_not)
			std::cout << "The input is not a positive Senary integer!\n";
		else
		    std::cout << "The input Senary number is out of range!\n";
	}
	int m;
	while (true) {
		std::cout << "Please enter the converted base.[2-20]\n";
		std::cin >> m;
		if (std::cin.fail() || m < 2 || m>MIX_SCALE) {
			std::cout << "Input error, please re-input!\n";
			//Clear buffer
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		break;
	}
	std::cout << "The converted digit is " << BaseConversion(dec_n, m) << ". \n";

	return 0;
}
