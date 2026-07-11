#if !defined(BIRD_H)
#define BIRD_H
#include <bits/stdc++.h>

// =========================================================
// ABSTRACTION IN SIMPLE WORDS
// =========================================================
// Abstraction means showing only the important things and
// hiding the unnecessary details.
//
// Real-life example:
// When you drive a car, you use the steering wheel, brake,
// and accelerator. You do not need to know how the engine
// works internally. That is abstraction.
//
// In OOP, abstraction helps us create a simple interface
// for a concept and let different classes implement it in their own way.
//
// Here, Bird is an abstract class.
// It defines what a bird should be able to do:
// - eat()
// - fly()
//
// But it does not define how each bird does it.
// Each bird type (Sparrow, Eagle, Pigeon) gives its own implementation.
//
// Why use abstraction?
// - To focus on what is important
// - To avoid showing unnecessary internal details
// - To create a common structure for related classes
// - To make code easier to extend and maintain
// =========================================================

class Bird
{
public:
    // This is an abstract interface.
    // Pure virtual functions mean:
    // "Every child class must provide its own version of this function."
    virtual void eat() = 0;
    virtual void fly() = 0;
};

class Sparrow : public Bird
{
public:
    void eat() override
    {
        std::cout << "Sparrow is eating\n";
    }

    void fly() override
    {
        std::cout << "Sparrow is flying\n";
    }
};

class Eagle : public Bird
{
public:
    void eat() override
    {
        std::cout << "Eagle is eating\n";
    }

    void fly() override
    {
        std::cout << "Eagle is flying\n";
    }
};

class Pigeon : public Bird
{
public:
    void eat() override
    {
        std::cout << "Pigeon is eating\n";
    }

    void fly() override
    {
        std::cout << "Pigeon is flying\n";
    }
};
#endif