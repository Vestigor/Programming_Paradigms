/***********************************************************
* File:     problem_5.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Clion 2024
* Function:  solve the problem 4
* Date:     2024.11.16
* Update:   2024.11.16
***********************************************************/
#include <iostream>

/***********************************************************
* Class Name:   Shape
* Function:      Base class for shapes with virtual methods for drawing and cloning.
***********************************************************/
class Shape {
public:
    virtual ~Shape() = default;

    virtual Shape *clone() const {return new Shape(*this);}

    virtual void draw() const{std::cout<<"Drawing shape.\n";}
};

/***********************************************************
* Class Name:   Circle
* Function:      Derived class representing a circle.
***********************************************************/
class Circle : public Shape {
public:
    Circle() = default;
    Circle *clone() const override{return new Circle(*this);}

    void draw() const override{std::cout << "Drawing circle.\n";}
};

/***********************************************************
* Class Name:   Rectangle
* Function:      Derived class representing a rectangle.
***********************************************************/
class Rectangle : public Shape {
public:
    Rectangle() = default;

    Rectangle *clone() const override{return new Rectangle(*this);}

    void draw() const override{std::cout << "Drawing rectangle.\n\n";}
};

/***********************************************************
* Function Name:   main
* Function:        Demonstrates the use of Shape, Circle, and Rectangle classes.
* Input Parameter: None
* Returned Value:  0
* Instructions:    Create instances of Shape, Circle, and Rectangle, clone them,
*                  and demonstrate drawing each object.
***********************************************************/
int main()
{
    Shape *circle = new Circle();
    Shape *rectangle = new Rectangle();

    circle->draw();
    rectangle->draw();

    // Clone the objects
    auto *cloned_circle = circle->clone();
    auto *cloned_rectangle = rectangle->clone();

    // Draw the cloned  objects
    cloned_circle->draw();
    cloned_rectangle->draw();

    // Clean up dynamically allocated memory
    delete circle;
    delete rectangle;
    delete cloned_circle;
    delete cloned_rectangle;

    return 0;
}
