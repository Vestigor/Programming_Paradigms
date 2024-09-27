/***********************************************************
* File:     problem_1.cpp
* Author:   Xiaolong Ma(ÂíÐ¡Áú)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: to count the occurrence of the word ¡®that¡¯ in a file
* Date:     2024.9.17
* Update:   2024.9.20
***********************************************************/

#include <iostream>
#include <string>
#include <limits>
#include <fstream>//File related operations
#include <algorithm>//Letter case conversion

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
* Function Name:   SpecialTreatment
* Function:        turn words like "that's" into "that"
* Input Parameter: word
* Returned Value:
***********************************************************/
std::string SpecialTreatment(std::string word)
{
	std::string new_word;
	for (unsigned int i = 0; i < word.length();i++) {
		if (i > 0 && i < word.length() - 1)
			if (word[i] == 39 && word[i - 1] == 't' && (word[i + 1] >= 65 && word[i + 1] <= 87 || word[i + 1] >= 95 && word[i + 1] <= 122))
				break;
		new_word = new_word + word[i];
	}
	return new_word;
}

/***********************************************************
* Function Name:   ReadAndCountOccurrences
* Function:        read a file and cout the number of the occurrence of the word 'that'
* Input Parameter: filename: name of the file
*                  is_case_sensitive: case sensitive or not
*                                     '1' means 'case sensitive'
*                                     '0' means 'not case sensitive'
* Returned Value:  number: the number of the occurrence of the word ¡®that¡¯ in the file
***********************************************************/
int ReadAndCountOccurrences(std::string& file_name,bool is_case_sensitive, bool discrepancy_that)
{
	std::string target_word = "that";
	std::ifstream file;
	std::cout << "Please input the name of the file you want to read(e.g.'example.txt' ,Press 'Q' to open the built-in file)\n";
	while (true) {
		std::getline(std::cin, file_name);
		if (file_name == "Q" || file_name == "q")
			file_name = "example.txt";
		if (file_name == "") {
			std::cout << "File name is empty!\n";
			std::cout << "Pleaseinput the name of the file:(Press 'Q' to open the built-in file)\n";
			continue;
		}
		file.open(file_name);//Open the file
		if (!file.is_open()) {
			std::cout << "Unable to open the file!\n";
			std::cout << "Please check the file name and re-input:(Press 'Q' to open the built-in file)\n";
			continue;
		}
		break;
	}
	std::string word;
	int number = 0;
	while (file >> word) {
		if (discrepancy_that)
			word = SpecialTreatment(word);
		word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());//Remove punctuation at the end of words
		if(!is_case_sensitive)
			std::transform(word.begin(), word.end(), word.begin(), ::tolower);//Converts uppercase letters to lowercase
		if (word == target_word)
			number++;
	}
	file.close();//Close the file
	return number;
}

/***********************************************************
* Function Name:   main
* Function:        input&output
* Input Parameter:
* Returned Value: 0
***********************************************************/
int main()
{
	std::cout << "Now we will counts the occurrence of the word ¡®that¡¯ in a file. You should make sure the language in the file is standard!\n";
	bool is_case_sensitive, discrepancy_that;
	while (true) {
		std::cout << "Case sensitive or not?('0' for not,'1' for yes): ";
		std::cin >> is_case_sensitive;
		if (std::cin.fail()) {
			std::cout << "Input error, please re-input\n";
			ClearBuffer();
			continue;
		}
		ClearBuffer();
		break;
	}
	while (true) {
		std::cout << "Whether to count words like 'that's' ? ('0' for not, '1' for yes) : ";
		std::cin >> discrepancy_that;
		if (std::cin.fail()) {
			std::cout << "Input error, please re-input\n";
			ClearBuffer();
			continue;
		}
		ClearBuffer();
		break;
	}
	std::string file_name = "example.txt";
	int number = ReadAndCountOccurrences(file_name, is_case_sensitive, discrepancy_that);
	std::cout << "The number of the occurrence of the word 'that' in " << file_name << " is " << number <<".\n";

	return 0;
}