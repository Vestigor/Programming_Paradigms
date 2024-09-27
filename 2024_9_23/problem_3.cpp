/***********************************************************
* File:     problem_3.cpp
* Author:   Xiaolong Ma(ÂíÐ¡Áú)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: solve the problem which is called "eat chocolate"
* Date:     2024.9.24
* Update:   2024.9.24
***********************************************************/

#include <iostream>
#include <string>
#include <limits>

#define LUCKY_NUMBER 7//The lucky number should be a positive integer

//The nodes of a linked list and the data they store
struct Node {
    int data;
    Node* next;
};

//Using a class representing a circular linked
class LinkList {
public:
	LinkList();
	~LinkList();
	int Interposition(int number);
	void Del(int& last_chocolate);
private:
	Node* head;//stores the address of the first node in the linked list
};

/***********************************************************
* Function Name:   constructor
* Function:        Initialize 'head'
* Input Parameter:
* Returned Value:  0
***********************************************************/
LinkList::LinkList()
{
	head = NULL;
}

/***********************************************************
* Function Name:   destructor
* Function:        Delete linked list nodes to free memory and avoid memory leaks
* Input Parameter:
* Returned Value:  0
***********************************************************/
LinkList::~LinkList()
{
	if (head == NULL)
		return;
	Node* p = head;
	while (p->next != head) {
		Node* current = p->next;
		delete p;
		p = current;
	}
	delete head;
}

/***********************************************************
* Function Name:   Interposition
* Function:        Form a circular linked list by defining and inserting nodes
* Input Parameter: number: the data in the node, which represents the number of points in the linked list
* Returned Value:  -1&1:indicates whether memory is allocated successfully
***********************************************************/
int LinkList::Interposition(int number)
{
	Node* newNode = new(std::nothrow) Node;//Open space;return the space address on success and return NULL on failure
	if (newNode == NULL)
		return -1;
	newNode->data = number;
	if (head == NULL) {
		head = newNode;
		newNode->next = head;
	}
	else {
		Node* temp = head;
		while (temp->next != head)
			temp = temp->next;
		temp->next = newNode;
		newNode->next = head;
	}
	return 1;
}

/***********************************************************
* Function Name:   Del
* Function:        Delete the nodes that meet the requirements until the last node is left
* Input Parameter: n,last_chocolate
* Returned Value:  
***********************************************************/
void LinkList::Del(int& last_chocolate)
{
	Node* current = head;
	//If the lucky number is 1, take the data of the last node directly 
	if (LUCKY_NUMBER == 1) {
		while (current->next != head)
			current = current->next;
		last_chocolate = current->data;
	}
	else {
		int num = 1;
		while (head->next != head) {
			bool contain_lucky_number = false;
			int temp_num = num + 1;
			while (temp_num > 0) {
				if (temp_num % 10 == LUCKY_NUMBER) {
					contain_lucky_number = true;
					break;
				}
				temp_num = (temp_num - temp_num % 10) / 10;
			}
			if ((num + 1) % LUCKY_NUMBER == 0 || contain_lucky_number) {
				Node* temp = current->next;
				if (current->next == head)
					head = head->next;
				current->next = temp->next;
				delete temp;
			}
			else
				current = current->next;
			num++;
		}
		last_chocolate = head->data;
	}
}

/***********************************************************
* Function Name:   main
* Function:        input&output
* Input Parameter:
* Returned Value:  0
***********************************************************/
int main()
{
	int n, last_chocolate;
	while (true) {
		std::cout << "Please enter the number of chocolates.\n";
		std::cout << "(It is recommended that the operation time is less than 50000, otherwise the operation time is too long.)\n";
		std::cin >> n;
		if (std::cin.fail()||n<=0||n>50000) {
			std::cout << "Input error, please re-input!\n";
			//Clear buffer
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		break;
	}
	LinkList chocolate;
	for (int i = 1; i <= n; i++) {
		int memory_allocation=chocolate.Interposition(i);
		if (memory_allocation == -1) {
			std::cout << " Memory allocation failed!\n";
			return 0;
		}
	}
	chocolate.Del(last_chocolate);
	std::cout<<"The chocolate brought to Kuanye is the number "<< last_chocolate <<".\n";

	return 0;
}
