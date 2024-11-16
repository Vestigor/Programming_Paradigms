/***********************************************************
* File:     problem_6.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Compiler: CLion 2024
* Function: solve the problem 3
* Date:     2024.11.16
* Update:   2024.11.16
***********************************************************/
#include <string>

/***********************************************************
* Class Name:     Traveler
* Function:       Base class representing a traveler with a name.
* Instructions:   Includes copy constructor and assignment operator.
***********************************************************/
class Traveler {
public:
    Traveler(const std::string &str) : name(str) {}
    Traveler(const Traveler &other) : name(other.name) {}

    Traveler &operator=(const Traveler &other)
    {
        if (this != &other) {
            name = other.name;
        }
        return *this;
    }

private:
    std::string name;
};

/***********************************************************
* Class Name:     Pager
* Function:       Class representing a pager with a message.
* Instructions:   Includes copy constructor and assignment operator.
***********************************************************/
class Pager {
public:
    Pager(const std::string &str) : message(str) {}
    Pager(const Pager &other) : message(other.message) {}

    Pager &operator=(const Pager &other)
    {
        if (this != &other) {
            message = other.message;
        }
        return *this;
    }

private:
    std::string message;
};

/***********************************************************
* Class Name:     BusinessTraveler
* Function:       Derived class representing a business traveler.
* Instructions:   Inherits from Traveler and includes a Pager object.
***********************************************************/
class BusinessTraveler : public Traveler {
public:
    BusinessTraveler() : Traveler(""), pager("") {}
    BusinessTraveler(const std::string &str) : Traveler(str), pager(str) {}
    BusinessTraveler(const BusinessTraveler &other) : Traveler(other), pager(other.pager) {}

    BusinessTraveler &operator=(const BusinessTraveler &other)
    {
        if (this != &other) {
            Traveler::operator=(other);
            pager = other.pager;
        }
        return *this;
    }

private:
    Pager pager;
};

/***********************************************************
* Function Name:   main
* Function:        test
* Input Parameter: None
* Returned Value:  0
***********************************************************/
int main()
{
    BusinessTraveler bt1("John");
    BusinessTraveler bt2 = bt1;
    BusinessTraveler bt3;
    bt3 = bt1;

    return 0;
}
