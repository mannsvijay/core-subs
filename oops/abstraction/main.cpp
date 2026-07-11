#include <bits/stdc++.h>
#include "bird.h"
using namespace std;

// This function uses abstraction.
// We don't care whether the object is a Sparrow, Eagle, or Pigeon.
// We only care that it is a Bird and can eat() and fly().
//
// This is the power of abstraction:
// one function can work for many different kinds of birds.
void birdDoesSomething(Bird *bird)
{
    // We call the common actions of any bird.
    // The actual behavior depends on the real object.
    bird->eat();
    bird->fly();
}

int main()
{
    // We create different bird objects.
    // The pointer type is Bird*, but the actual object can be any child class.
    //
    // This is important:
    // We are writing code using the general idea "Bird",
    // not caring about the exact type right now.

    // Example 1: a Sparrow object
    // Bird *bird = new Sparrow();

    // Example 2: an Eagle object
    // Bird *bird = new Eagle();

    // Example 3: a Pigeon object
    Bird *bird = new Pigeon();

    // Now we use the same function for all of them.
    birdDoesSomething(bird);

    // Why is this useful?
    // Because the same function birdDoesSomething() works for all birds.
    // We do not need to write separate code for Sparrow, Eagle, or Pigeon.
    // This is abstraction in action:
    // we use a common interface (Bird) and hide the specific details.

    // Clean up memory
    delete bird;
    return 0;
}
