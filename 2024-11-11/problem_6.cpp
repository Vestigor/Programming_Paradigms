/***********************************************************
* File:     problem_6.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Clion 2024
* Function: Find the largest element from various types
* Date:     2024.11.15
* Update:   2024.11.15
***********************************************************/
#include <iostream>
#include <vector>
#include <limits>
#include <type_traits>

constexpr unsigned long long kElementsNumber = 3;

/***********************************************************
* Structure Name:   String
* Function:         A wrapper for std::string with custom comparison.
***********************************************************/
struct String {
    std::string str;
    bool operator>(const String &other) const;
};

/***********************************************************
* Function Name:   operator>
* Function:        Compare two String objects.
* Input Parameter: other: The String object to compare with.
* Returned Value:  true if the current object is greater, false otherwise.
* Instructions:    Compare by length first, then lexicographically.
***********************************************************/
bool String::operator>(const String &other)const
{
    if(this->str.size()>other.str.size())
        return true;
    else if(this->str.size()<other.str.size())
        return false;
    return this->str>other.str;
}

/***********************************************************
* Function Name:   operator<<
* Function:        Overload the output stream operator for String objects
* Input Parameter: os: output stream, rect: the String object to be printed
* Returned Value:  os: modified output stream
***********************************************************/
std::ostream &operator<<(std::ostream &os, const String &st)
{
    os << st.str;
    return os;
}

/***********************************************************
* Function Name:   operator>>
* Function:        Overload the input stream operator for String objects
* Input Parameter: is: input stream, rect: the RString object to be filled with input values
* Returned Value:  is: modified input stream
***********************************************************/
std::istream &operator>>(std::istream &is, String &st)
{
    char ch;
    is >> st.str;
    return is;
}
/***********************************************************
* Function Name:   Rectangle
* Function:        Represents a rectangle with width (x) and height (y)
* Instructions:    Contains constructors and comparison operators for the Rectangle structure.
***********************************************************/
struct Rectangle {
    int x;
    int y;
    // Default constructor initializes x and y to 0
    Rectangle() : x(0), y(0) {}
    // Parameterized constructor initializes x and y to given values
    Rectangle(int x, int y) : x(x), y(y) {}

    // Overloading comparison operators to compare rectangles based on their area (x * y)
    bool operator>(const Rectangle &other) const{return this->x * this->y > other.x * other.y;}
    bool operator<(const Rectangle &other) const{return this->x* this->y < other.x* other.y;}
    bool operator==(const Rectangle &other) const{return this->x * this->y == other.x * other.y;}
    bool operator>=(const Rectangle &other) const { return this->x * this->y >= other.x * other.y; }
    bool operator<=(const Rectangle &other) const { return this->x * this->y <= other.x * other.y; }
};

/***********************************************************
* Function Name:   operator<<
* Function:        Overload the output stream operator for Rectangle objects
* Input Parameter: os: output stream, rect: the Rectangle object to be printed
* Returned Value:  os: modified output stream
***********************************************************/
std::ostream &operator<<(std::ostream &os, const Rectangle &rect)
{
    os << "Rectangle (" << rect.x << "," << rect.y << ")";
    return os;
}

/***********************************************************
* Function Name:   operator>>
* Function:        Overload the input stream operator for Rectangle objects
* Input Parameter: is: input stream, rect: the Rectangle object to be filled with input values
* Returned Value:  is: modified input stream
***********************************************************/
std::istream &operator>>(std::istream &is, Rectangle &rect)
{
    char ch;
    is >> rect.x >> ch >> rect.y;
    return is;
}

/***********************************************************
* Function Name:   operator<<
* Function:        Overload the output stream operator for pointers to Rectangle objects
* Input Parameter: os: output stream, rect: pointer to the Rectangle object to be printed
* Returned Value:  os: modified output stream
***********************************************************/
std::ostream &operator<<(std::ostream &os, const Rectangle *rect)
{
    if (rect) {
        os << "Rectangle (" << rect->x << "," << rect->y << ")";
    }
    else {
        os << "nullptr";
    }
    return os;
}

/***********************************************************
* Function Name:   operator>>
* Function:        Overload the input stream operator for pointers to Rectangle objects
* Input Parameter: is: input stream, rect: pointer to the Rectangle object to be filled with input values
* Returned Value:  is: modified input stream
***********************************************************/
std::istream &operator>>(std::istream &is, Rectangle *&rect)
{
    char ch;
    if (!rect) {
        rect = new Rectangle();
    }
    is >> rect->x >>ch>> rect->y;
    return is;
}


/***********************************************************
* Function Name:   Max
* Function:        Find the maximum value from a list of elements (single argument base case)
* Input Parameter: value: the value to be compared
* Returned Value:  The same value
***********************************************************/
template<typename T>
T Max(T value)
{
    return value;
}

/***********************************************************
* Function Name:   Max
* Function:        Find the maximum value from a list of elements (recursive case)
* Input Parameter: first: the first element, args: the rest of the elements to compare
* Returned Value:  The maximum element
* Instructions:    If T is a pointer, dereference the values for comparison; otherwise, directly compare the values
***********************************************************/
template<typename T, typename... Args>
T Max(T first, Args... args)
{
    T max_of_rest = Max(args...);// Recursively find the largest of the remaining arguments

    // If T is a pointer type, dereference the values for comparison
    if constexpr (std::is_pointer_v<T>)
        return (*max_of_rest > *first) ? max_of_rest : first;
    else
        return (max_of_rest > first ) ? max_of_rest : first;
}

/***********************************************************
* Function Name:   Input
* Function:        Input elements into a vector
* Input Parameter: elements: a reference to the vector where elements will be stored
* Returned Value:  None
* Instructions:    Continue inputting until the vector reaches kElementsNumber; handle invalid input.
***********************************************************/
template<typename T>
void Input(std::vector<T>& elements)
{
    std::cout<<"Please enter" <<kElementsNumber<<" elements.\n";
    // Continue adding elements until the vector reaches kElementsNumber
    while(elements.size() < kElementsNumber) {
        T element;

        // If T is a pointer, dynamically allocate memory for the element
        if constexpr (std::is_pointer_v<T>)
            element = new std::remove_pointer_t<T>();

        std::cin >> element;
        if(std::cin.fail()) {
            std::cout<<"Invalid input, please start entering from item "<<elements.size()+1<<" again!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(),'\n');

            // If T is a pointer, delete the allocated memory to avoid memory leak
            if constexpr (std::is_pointer_v<T>)
                delete element;
            continue;
        }
        elements.push_back(element);
    }
}

/***********************************************************
* Function Name:   Select
* Function:        Prompt the user to select an operation
* Input Parameter: None
* Returned Value:  The selected operation (a character between 'A' and 'G')
* Instructions:    Ensure the input is valid; if not, prompt the user again.
***********************************************************/
char Select()
{
    char select;
    while(true) {
        std::cout << "Please select an operation: ";
        std::cin >> select;
        if(std::cin.fail()||select<'A'||select>'G') {
            std::cout << "Invalid input, please try again!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(),'\n');
            continue;
        }
        break;
    }
    return select;
}

/***********************************************************
* Function Name:   main
* Function:        Display a menu, handle user input, and perform the operation to find the largest element
* Input Parameter: None
* Returned Value:  0
***********************************************************/
int main()
{
    std::cout<<"To Find The Largest Element!\n";
    std::cout<<"+-------------------------+\n";
    std::cout<<"|        A.int            |\n";
    std::cout<<"|        B.double         |\n";
    std::cout<<"|        C.char           |\n";
    std::cout<<"|        D.string         |\n";
    std::cout<<"|        E.Rectangle      |\n";
    std::cout<<"|        F.Rectangle*     |\n";
    std::cout<<"|        G.QUIT           |\n";
    std::cout<<"+-------------------------+\n";
    std::vector<int> int_elements;
    std::vector<double> double_elements;
    std::vector<char> char_elements;
    std::vector<String> string_elements;
    std::vector<Rectangle> rectangle_elements;
    std::vector<Rectangle*> prectangle_elements;

    while(true) {
        char selection=Select();
        if(selection == 'A') {
            Input(int_elements);
            std::cout<<"The max element is "<<Max(int_elements[0], int_elements[1], int_elements[2])<<"\n";
            int_elements.clear();// Clear the vector for the next operation
        }
        else if(selection == 'B') {
            Input(double_elements);
            std::cout<<"The max element is "<<Max(double_elements[0],double_elements[1],double_elements[2])<< "\n";
            double_elements.clear();
        }
        else if(selection == 'C') {
            Input(char_elements);
            std::cout << "The max element is " << Max(char_elements[0], char_elements[1], char_elements[2]) <<"\n";
            char_elements.clear();
        }
        else if(selection == 'D') {
            Input(string_elements);
            std::cout << "The max element is " << Max(string_elements[0], string_elements[1], string_elements[2]) <<"\n";
            string_elements.clear();
        }
        else if(selection == 'E') {
            Input(rectangle_elements);
            std::cout << "The max element is " << Max(rectangle_elements[0], rectangle_elements[1], rectangle_elements[2]) <<"\n";
            rectangle_elements.clear();
        }

        else if(selection == 'F') {
            Input(prectangle_elements);
            std::cout << "The max element is " << Max(prectangle_elements[0], prectangle_elements[1],prectangle_elements[2]) << "\n";
            prectangle_elements.clear();
        }
        else
            break;
    }
    return 0;

}