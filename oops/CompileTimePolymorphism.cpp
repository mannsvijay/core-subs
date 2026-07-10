/*
================================================================================
                    COMPILE-TIME POLYMORPHISM (STATIC POLYMORPHISM)
================================================================================

DEFINITION:
-----------
Compile-time polymorphism (also called Static Polymorphism) is when the compiler
decides which function to call at compile time itself. The decision is made based
on the function signature (name, number of parameters, types of parameters).

Compile-time polymorphism is achieved through:
1. FUNCTION OVERLOADING - Same function name with different parameters
2. OPERATOR OVERLOADING - Redefining operators for custom types

================================================================================
                        PART 1: FUNCTION OVERLOADING
================================================================================

Function Overloading allows you to have multiple functions with the SAME NAME
but DIFFERENT SIGNATURES (parameters).

Rules for Function Overloading:
1. Functions must have same name
2. Functions must have different NUMBER of parameters, OR
3. Functions must have different TYPE of parameters, OR
4. Functions must have different ORDER of parameters

Return type ALONE is NOT enough to overload a function.

Example:
    void print(int x);           // Function 1
    void print(double x);        // Function 2 - Different TYPE
    void print(int x, int y);    // Function 3 - Different NUMBER of parameters
    void print(double x, int y); // Function 4 - Different ORDER

================================================================================
*/

/*
    ================================================================
     COMPILE-TIME POLYMORPHISM IN C++ - FUNCTION & OPERATOR OVERLOADING
    ================================================================

    Builds on your Add / Complex code. "Polymorphism" = one name,
    many forms. There are 2 big categories:
        - COMPILE-TIME polymorphism (this file) -> decided BEFORE the
          program runs, purely by matching argument types. Covers
          function overloading and operator overloading.
        - RUN-TIME polymorphism (needs virtual functions + the
          inheritance from last time) -> decided WHILE the program is
          running. Not covered here - ask if you want that one next!

    WHAT'S IN THIS FILE:
      1) Add        - FUNCTION OVERLOADING (same name, different params)
      2) Complex     - OPERATOR OVERLOADING (+, -, unary -, *, ==, !=, +=, <<)
      3) main()      - runs everything, comments predict the output

    Deep explanation (tables, rules, the "why") is in the chat message.
    This file's comments are tied to exact lines so you can read top
    to bottom and follow along.
*/

#include <iostream>
using namespace std;


// ================================================================
// 1) FUNCTION OVERLOADING: class Add
// ================================================================
// "Overloading" = same function NAME, but a DIFFERENT parameter list
// - different COUNT of params, and/or different TYPES, and/or a
// different ORDER of types. The compiler decides which version to
// run by matching your arguments against every signature available -
// and it does this matching at COMPILE time, before the program ever
// runs. That's exactly why it's called compile-time polymorphism:
// one name (sum), many forms (5 versions below), picked in advance.
class Add
{
public:
    // overload 1: two ints
    int sum(int x, int y)
    {
        cout << "[sum(int,int)] ";
        return x + y;
    }

    // overload 2: three ints -> different PARAMETER COUNT
    int sum(int x, int y, int z)
    {
        cout << "[sum(int,int,int)] ";
        return x + y + z;
    }

    // overload 3: two doubles -> different PARAMETER TYPE
    double sum(double x, double y)
    {
        cout << "[sum(double,double)] ";
        return x + y;
    }

    // overload 4: int then double
    double sum(int x, double y)
    {
        cout << "[sum(int,double)] ";
        return x + y;
    }

    // overload 5: double then int -> proves ORDER of types matters
    // too. sum(int,double) and sum(double,int) use the exact same 2
    // types, just in a different order, so they count as 2 distinct
    // signatures.
    double sum(double x, int y)
    {
        cout << "[sum(double,int)] ";
        return x + y;
    }

    // -----------------------------------------------------------
    // WHAT DOES *NOT* COUNT AS OVERLOADING:
    // You cannot create a new overload using ONLY a different return
    // type - the compiler never looks at return type to tell two
    // functions apart, only the parameter list. Uncommenting this
    // will NOT compile (verified for real in the chat message):
    //
    //     double sum(int x, int y) { return x + y; }
    //
    // (identical parameters to overload 1 above -> "redefinition" error)
    // -----------------------------------------------------------
};


// ================================================================
// 2) OPERATOR OVERLOADING: class Complex
// ================================================================
// Operator overloading is really just function overloading wearing a
// costume: you're still writing a function, it just has a special
// name (operator+, operator-, ...) and a special CALLING syntax
// (A + B instead of A.add(B)). Under the hood, "A + B" literally
// MEANS "A.operator+(B)" - proved with a test case below.
//
//     syntax:   Ret_type operator<symbol>(parameters) { ... }
class Complex
{
public:
    int real;
    int imag;

    Complex()
    {
        real = imag = -1;
    }

    Complex(int r, int i) : real(r), imag(i) {}

    // ---- Complex + Complex (binary) ----
    Complex operator+(const Complex &B)
    {
        Complex temp;                    // this -> A instance
        temp.real = this->real + B.real;
        temp.imag = this->imag + B.imag;
        return temp;
    }

    // ---- Complex + int -> operator+ OVERLOADED again, this time
    // taking an int (adds only to the real part). Exact same idea as
    // sum(int,int) vs sum(double,double) above: whichever operator+
    // matches your right-hand side's type is the one that runs.
    Complex operator+(int scalar)
    {
        Complex temp;
        temp.real = this->real + scalar;
        temp.imag = this->imag;
        return temp;
    }

    // ---- Complex - Complex (binary) ----
    Complex operator-(const Complex &B)
    {
        Complex temp;
        temp.real = this->real - B.real;
        temp.imag = this->imag - B.imag;
        return temp;
    }

    // ---- -Complex (UNARY minus - notice ZERO extra parameters!) ----
    // C++ tells this apart from the BINARY operator-(const Complex&)
    // above purely by parameter COUNT - once again, plain overloading
    // rules doing the work.
    Complex operator-()
    {
        Complex temp;
        temp.real = -this->real;
        temp.imag = -this->imag;
        return temp;
    }

    // ---- Complex * Complex -> (a+bi)(c+di) = (ac-bd) + (ad+bc)i ----
    Complex operator*(const Complex &B)
    {
        Complex temp;
        temp.real = (this->real * B.real) - (this->imag * B.imag);
        temp.imag = (this->real * B.imag) + (this->imag * B.real);
        return temp;
    }

    // ---- == (existing) ----
    bool operator==(const Complex &B)
    {
        return (this->real == B.real) && (this->imag == B.imag);
    }

    // ---- != -> reuses == instead of repeating the comparison logic ----
    bool operator!=(const Complex &B)
    {
        return !(*this == B);
    }

    // ---- += -> modifies THIS object directly (unlike +, which
    // builds and returns a brand new temp) and returns a REFERENCE
    // to itself so the result can be reused in a bigger expression.
    Complex& operator+=(const Complex &B)
    {
        this->real += B.real;
        this->imag += B.imag;
        return *this;
    }

    void print()
    {
        printf("[%d + i%d]\n", this->real, this->imag);
    }
};

// ---- << -> lets us write "cout << A" instead of "A.print()" ----
// This CANNOT be a member function of Complex. For a member function
// the left-hand side is always the object itself (that's what 'this'
// means) - but here the true left-hand side is 'cout' (an ostream),
// not a Complex. So it has to be a free / non-member function instead.
// (real and imag are public here, so no 'friend' keyword is needed.
//  If they were private, we'd write "friend ostream& operator<<(...)"
//  INSIDE the class to give this function access to them.)
ostream& operator<<(ostream &out, const Complex &c)
{
    out << "[" << c.real << " + i" << c.imag << "]";
    return out;   // returning the stream is what allows cout << A << B << endl to chain
}


// ================================================================
// 3) main()
// ================================================================
int main()
{
    cout << "========== PART 1: FUNCTION OVERLOADING (Add) ==========" << endl;
    Add add;

    cout << "add.sum(5, 5)        = " << add.sum(5, 5) << endl;             // exact match: sum(int,int)
    cout << "add.sum(5, 5, 5)     = " << add.sum(5, 5, 5) << endl;          // exact match: sum(int,int,int)
    cout << "add.sum(5.5, 2.2)    = " << add.sum(5.5, 2.2) << endl;         // exact match: sum(double,double)
    cout << "add.sum(5, 2.5)      = " << add.sum(5, 2.5) << endl;           // exact match: sum(int,double)
    cout << "add.sum(2.5, 5)      = " << add.sum(2.5, 5) << endl;           // exact match: sum(double,int)

    // no EXACT match exists for these two -> compiler quietly
    // converts your argument to the closest available type:
    cout << "add.sum(5.5f, 2.2f)  = " << add.sum(5.5f, 2.2f) << endl;       // float PROMOTES to double
    cout << "add.sum('A', 'B')    = " << add.sum('A', 'B') << endl;         // char PROMOTES to int (65+66)


    cout << "\n========== PART 2: OPERATOR OVERLOADING (Complex) ==========" << endl;
    Complex A(3, 4);
    Complex B(1, 2);
    cout << "A = "; A.print();
    cout << "B = "; B.print();

    cout << "\n-- addition --" << endl;
    Complex C = A + B;
    cout << "A + B            = "; C.print();
    cout << "A.operator+(B)   = "; A.operator+(B).print();   // proves "A + B" IS "A.operator+(B)"

    Complex Cscalar = A + 10;
    cout << "A + 10 (int overload of +) = "; Cscalar.print();

    cout << "\n-- subtraction (binary) vs negation (unary) --" << endl;
    Complex D = A - B;
    cout << "A - B = "; D.print();
    Complex E = -A;
    cout << "-A    = "; E.print();

    cout << "\n-- multiplication --" << endl;
    Complex F = A * B;
    cout << "A * B = "; F.print();

    cout << "\n-- comparisons --" << endl;
    Complex G(3, 4);
    cout << "A == G ? " << (A == G) << endl;    // same real & imag
    cout << "A == B ? " << (A == B) << endl;
    cout << "A != B ? " << (A != B) << endl;

    cout << "\n-- += (modifies A itself, unlike +) --" << endl;
    cout << "before: A = "; A.print();
    A += B;
    cout << "after A += B: A = "; A.print();

    cout << "\n-- operator<< (stream insertion, cout << object) --" << endl;
    cout << "A is now " << A << ", and B is " << B << endl;

    return 0;
}