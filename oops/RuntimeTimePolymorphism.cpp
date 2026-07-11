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
// This is possible because we use the keyword virtual.
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
