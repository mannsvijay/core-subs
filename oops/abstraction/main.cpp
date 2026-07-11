#include <bits/stdc++.h>
#include "bird.h"
using namespace std;

// This function uses abstraction.
// We don't care whether the object is a Sparrow, Eagle, or Pigeon.
// We only care that it is a Bird and can eat() and fly().
void birdDoesSomething(Bird *bird)
{
    bird->eat();
    bird->fly();
}

int main()
{
    // We create different bird objects.
    // The pointer type is Bird*, but the actual object can be any child class.

    // Bird *bird = new Sparrow();
    // Bird *bird = new Eagle();
    Bird *bird = new Pigeon();

    birdDoesSomething(bird);

    // Why is this useful?
    // Because the same function birdDoesSomething() works for all birds.
    // We do not need to write separate code for Sparrow, Eagle, or Pigeon.
    // This is abstraction in action:
    // we use a common interface (Bird) and hide the specific details.

    delete bird;
    return 0;
}
