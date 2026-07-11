#include <iostream>
using namespace std;

// =========================================================
// RUNTIME POLYMORPHISM (also called dynamic polymorphism)
// =========================================================
// This means: the correct function is chosen while the
// program is running, based on the actual object type.
//
// Easy idea:
// - A base class pointer can point to different child objects.
// - The same function name (like draw()) can behave differently.
// - C++ decides which version to use automatically.
//
// Why is this possible?
// Because we use the keyword virtual.
//
// What does virtual do?
// ----------------------
// It tells C++:
// "If this function is overridden in a child class,
//  then when I call it through a base-class pointer,
//  use the child version automatically."
//
// Without virtual:
// - C++ uses static binding.
// - It calls the function based on the pointer type.
// - So a Shape* pointer will call Shape's version.
//
// With virtual:
// - C++ uses dynamic binding.
// - It calls the function based on the real object type.
// - So a Shape* pointer pointing to a Circle will call Circle's version.
//
// Very simple example:
// Imagine a parent class called Animal and a child class called Dog.
// Both have a function called speak().
// If you call speak() through an Animal pointer, then:
// - without virtual -> Animal's speak() runs
// - with virtual -> Dog's speak() runs
//
// Behind the scenes, virtual functions use something called a vtable
// (virtual table). But for now, you only need to know this:
// virtual makes function calls behave in a smarter, more flexible way.
// =========================================================

class Shape
{
public:
    // virtual means: "this function can be overridden by child classes"
    virtual void draw() const
    {
        cout << "Drawing a generic shape..." << endl;
    }
};

class Circle : public Shape
{
public:
    // override means: "I am intentionally replacing the base version"
    void draw() const override
    {
        cout << "Drawing a circle..." << endl;
    }
};

class Rectangle : public Shape
{
public:
    void draw() const override
    {
        cout << "Drawing a rectangle..." << endl;
    }
};

class Triangle : public Shape
{
public:
    void draw() const override
    {
        cout << "Drawing a triangle..." << endl;
    }
};

// This function accepts a Shape pointer.
// It can receive Circle, Rectangle, or Triangle too.
// Because draw() is virtual, the correct version runs.
void drawShape(Shape *shape)
{
    shape->draw();
}

int main()
{
    cout << "=== Runtime Polymorphism Demo ===" << endl;

    // A small comparison to show what virtual changes.
    // This is a non-virtual example.
    class Animal
    {
    public:
        void speak()
        {
            cout << "Animal makes a sound" << endl;
        }
    };

    class Dog : public Animal
    {
    public:
        void speak()
        {
            cout << "Dog barks" << endl;
        }
    };

    cout << "--- Without virtual ---" << endl;
    Animal *animal = new Dog();
    animal->speak();
    // Even though the real object is a Dog, this calls Animal's speak()
    // because speak() is NOT virtual here.
    delete animal;

    cout << endl;

    // 1) Normal object of the base class
    Shape baseShape;
    baseShape.draw();
    cout << endl;

    // 2) Upcasting: storing a child object in a base-class pointer
    // This is allowed because a Circle IS-A Shape.
    Shape *shape1 = new Circle();
    drawShape(shape1);
    delete shape1;

    // 3) Another child object with the same base pointer
    Shape *shape2 = new Rectangle();
    drawShape(shape2);
    delete shape2;

    // 4) Another child object
    Shape *shape3 = new Triangle();
    drawShape(shape3);
    delete shape3;

    cout << endl;

    // 5) Direct call on a child object
    // This is not polymorphism. It calls the Circle version directly.
    Circle circleObj;
    circleObj.draw();

    cout << endl;

    // 6) Safe downcasting (advanced idea)
    // Sometimes we want to check if a base pointer really points to a Circle.
    Shape *unknownShape = new Circle();
    Circle *safeCircle = dynamic_cast<Circle *>(unknownShape);

    if (safeCircle != nullptr)
    {
        cout << "The object is really a Circle." << endl;
        safeCircle->draw();
    }

    delete unknownShape;

    cout << endl;

    // Easy summary:
    // - virtual = allows overriding
    // - override = shows that we are replacing the base function
    // - runtime polymorphism = the right function runs based on the
    //   real object type at runtime

    return 0;
}
