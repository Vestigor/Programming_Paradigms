/***********************************************************
* File:     problem_3.cpp
* Author:   Xiaolong Ma(ÂíÐ¡Áú)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: change the three values in a struct instance
* Date:     2024.9.17
* Update:   2024.9.20
***********************************************************/

#include <iostream>
#include <string>
#include <limits>

struct PersonalBasicInformation {
	//Store a person's name and age
	std::string first_name = "Bryant", last_name = "Kobe";
	int age = 41;
};

/***********************************************************
* Function Name:    ClearBuffer
* Function:         clear the buffer to prevent impact on subsequent input
* Input Parameter: 
* Returned Value:
***********************************************************/
void ClearBuffer() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/***********************************************************
* Function Name:   InputJudgmentValue
* Function:        clear the buffer to prevent impact on subsequent input
* Input Parameter: ret
* Returned Value:
***********************************************************/
void InputJudgmentValue(bool& ret)
{
	while (true) {
		std::cin >> ret;
		if (std::cin.fail()) {
			std::cout << "Input error, please re-input\n";
			ClearBuffer();
			continue;
		}
		ClearBuffer();
		break;
	}
}

/***********************************************************
* Function Name:   ClearBuffer
* Function:        change some values in the struct instance
* Input Parameter: pperson:the pointer of person
* Returned Value:  
***********************************************************/
void Modification(PersonalBasicInformation* pperson)
{
	bool first_name_change, last_name_change, age_change;
	std::cout << "If you want to change the firstname?('0' for not,'1' for yes)\n";
	InputJudgmentValue(first_name_change);
	if (first_name_change) {
		std::cout << "Please input the firstname:\n";
		std::getline(std::cin, pperson->first_name);
	}
	std::cout << "If you want to change the lastname?('0' for not,'1' for yes)\n";
	InputJudgmentValue(last_name_change);
	if (last_name_change) {
		std::cout << "Please input the lastname:\n";
		std::getline(std::cin, pperson->last_name);
	}
	std::cout << "If you want to change the age?('0' for not,'1' for yes)\n";
	InputJudgmentValue(age_change);
	if (age_change) {
		while (true) {
			std::cout << "Please input the age:\n";
			std::cin >> pperson->age;
			if (std::cin.fail() || pperson->age < 0 || pperson->age>200) {
				std::cout << "Input error, please re-input\n";
				ClearBuffer();
				continue;
			}
			ClearBuffer();
			break;
		}
	}
}

/***********************************************************
* Function Name:    main
* Function:         define a struct instance and initialize it
* Input Parameter:
* Returned Value:  0
***********************************************************/
int main()
{
	PersonalBasicInformation person;
	std::cout << "Please input the firstname:\n";
	std::getline(std::cin, person.first_name);
	std::cout<< "Please input the lastname:\n";
	std::getline(std::cin, person.last_name);
	while (true) {
		std::cout << "Please input the age:\n";
		std::cin >> person.age;
		if (std::cin.fail()|| person.age <0|| person.age>200) {
			std::cout << "Input error, please re-input\n";
			ClearBuffer();
			continue;
		}
		break;
		ClearBuffer();
	}
	std::cout << "Initial values:\n"
		<< "First Name: " << person.first_name << "\n"
		<< "Last Name:  " << person.last_name << "\n"
		<< "Age:        " << person.age << "\n";
	PersonalBasicInformation* pperson = &person;
	Modification(pperson);
	std::cout << "Values after modification through pointer:\n"
		<< "First Name: " << pperson->first_name << "\n"
		<< "Last Name:  " << pperson->last_name << "\n"
		<< "Age:        " << pperson->age << "\n";

	return 0;
}