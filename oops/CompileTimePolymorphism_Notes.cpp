/*
================================================================================
                 COMPILE-TIME POLYMORPHISM - DETAILED EXPLANATION
================================================================================

WHAT IS POLYMORPHISM?
=====================
Polymorphism means "many forms". In C++, it allows you to write a function that
can work with different types or have multiple implementations.

Two types of Polymorphism:
1. COMPILE-TIME POLYMORPHISM (Static) - Resolved at compile time
2. RUNTIME POLYMORPHISM (Dynamic) - Resolved at run time (uses virtual functions)

================================================================================
                   COMPILE-TIME POLYMORPHISM (STATIC POLYMORPHISM)
================================================================================

Definition: The compiler determines which function/operator to use at compile time
based on the function signature or operator being used. The decision is made before
the program runs.

Achieved through:
1. FUNCTION OVERLOADING
2. OPERATOR OVERLOADING

================================================================================
                          1. FUNCTION OVERLOADING
================================================================================

DEFINITION:
-----------
Defining multiple functions with the SAME NAME but DIFFERENT PARAMETERS.

RULES FOR FUNCTION OVERLOADING:
1. Functions must have the same name
2. Functions must have DIFFERENT SIGNATURES. Signature includes:
   a) NUMBER of parameters (parameter count)
   b) TYPE of parameters
   c) ORDER of parameters (when types differ)

3. Return type ALONE is NOT sufficient for overloading

WHAT CAN'T DIFFER:
- Return type alone
- Default parameter values
- Function keywords (const, volatile, etc.) for non-member functions

EXAMPLE - VALID OVERLOADS:
----------------------------
void print(int x);              // Function 1: int parameter
void print(double x);           // Function 2: double parameter ✓ Different type
void print(int x, int y);       // Function 3: 2 parameters ✓ Different count
void print(double x, int y);    // Function 4: Different order ✓ Different order
void print(const string& s);    // Function 5: string parameter ✓ Different type

EXAMPLE - INVALID OVERLOADS:
-----------------------------
int add(int x, int y);       // Function 1
double add(int x, int y);    // ✗ INVALID - Only return type differs

RESOLUTION PROCESS (Called Overload Resolution):
--------------------------------------------------
When you call a function with overloads:
1. Compiler looks at the number and types of arguments
2. Finds all functions with matching name
3. Selects the best match based on:
   a) Exact type match (highest priority)
   b) Implicit type conversion (lower priority)
4. If no unique best match is found → Compilation error (ambiguous)

Example:
    Calculator calc;
    calc.add(5, 10);        // Calls: int add(int, int)
    calc.add(5.5, 10.5);    // Calls: double add(double, double)
    calc.add(5, 10.5);      // Calls: double add(int, double)

ADVANTAGES OF FUNCTION OVERLOADING:
1. Code readability - Same operation, same function name
2. Code maintenance - All related functions have consistent naming
3. Intuitiveness - Follows mathematical/logical conventions
4. Flexibility - Handle different data types with one function name

DISADVANTAGES:
1. Can make code confusing if overloads have very different behaviors
2. Compiler must do more work during compilation
3. Harder to trace bugs when multiple overloads are involved

================================================================================
                         2. OPERATOR OVERLOADING
================================================================================

DEFINITION:
-----------
Redefining built-in operators (+, -, *, /, ==, !=, ++, etc.) to work with 
custom user-defined types (classes/structs).

WHY OPERATOR OVERLOADING?
1. Make custom types feel like built-in types
2. Improve code readability
3. Make operations more intuitive

Example without operator overloading:
    Complex C1(3, 4), C2(1, 2);
    Complex C3 = C1.add(C2);  // Not intuitive

Example with operator overloading:
    Complex C1(3, 4), C2(1, 2);
    Complex C3 = C1 + C2;  // More intuitive!

SYNTAX:
-------
ReturnType operator<op>(parameters)
{
    // Implementation
}

Where <op> is: +, -, *, /, %, ==, !=, <, >, <=, >=, ++, --, etc.

CATEGORIES OF OPERATORS:

1. UNARY OPERATORS (work on one operand):
   - Syntax: operator<op>(parameters)
   - Examples: ++, --, +, -, !, ~
   
   Example: ++C means C.operator++()

2. BINARY OPERATORS (work on two operands):
   - Syntax: operator<op>(const Type& right)
   - Examples: +, -, *, /, %, ==, !=, <, >
   
   Example: C1 + C2 means C1.operator+(C2)

3. SPECIAL OPERATORS:
   - Assignment (=): Must be member function
   - Subscript ([]): Must be member function
   - Function call (()): Must be member function
   - Arrow (->): Must be member function

OPERATORS THAT CAN'T BE OVERLOADED:
- Scope resolution (::)
- Member access (.)
- Ternary operator (? :)
- sizeof
- typeid

OVERLOADING METHODS:
---------------------
1. MEMBER FUNCTION:
   class Complex {
   public:
       Complex operator+(const Complex& B) {
           // this -> left operand
           // B -> right operand
       }
   };
   Usage: C1 + C2  // Calls: C1.operator+(C2)

2. FRIEND FUNCTION:
   class Complex {
   public:
       friend Complex operator+(const Complex& A, const Complex& B);
   };
   Usage: C1 + C2  // Calls: operator+(C1, C2)

3. NON-MEMBER FUNCTION (Global):
   Complex operator+(const Complex& A, const Complex& B) {
       // Implementation
   }

WHEN TO USE WHICH:
- Member function: Usually for unary operators, =, [], ()
- Friend function: When you need access to private members AND symmetric operations
- Non-member: For operations that don't need class internals

COMMON OPERATORS TO OVERLOAD:

A. ARITHMETIC OPERATORS:
   operator+   (Addition)
   operator-   (Subtraction)
   operator*   (Multiplication)
   operator/   (Division)
   operator%   (Modulus)

B. COMPARISON OPERATORS:
   operator==  (Equal)
   operator!=  (Not equal)
   operator<   (Less than)
   operator>   (Greater than)
   operator<=  (Less than or equal)
   operator>=  (Greater than or equal)

C. ASSIGNMENT OPERATORS:
   operator=   (Assignment)
   operator+=  (Add and assign)
   operator-=  (Subtract and assign)
   operator*=  (Multiply and assign)
   operator/=  (Divide and assign)

D. LOGICAL OPERATORS:
   operator&&  (Logical AND)
   operator||  (Logical OR)
   operator!   (Logical NOT)

E. BITWISE OPERATORS:
   operator&   (Bitwise AND)
   operator|   (Bitwise OR)
   operator^   (Bitwise XOR)
   operator~   (Bitwise NOT)
   operator<<  (Left shift)
   operator>>  (Right shift)

F. UNARY OPERATORS:
   operator++  (Pre-increment or Post-increment)
   operator--  (Pre-decrement or Post-decrement)
   operator+   (Unary plus)
   operator-   (Unary minus)
   operator*   (Dereference - for pointers)
   operator&   (Address-of)

G. OTHER OPERATORS:
   operator()  (Function call)
   operator[]  (Subscript)
   operator->  (Member access through pointer)
   operator,   (Comma)

PRE-INCREMENT vs POST-INCREMENT:
---------------------------------
To distinguish between ++C (pre) and C++ (post):

// Pre-increment
Complex operator++() {
    ++this->real;
    ++this->imag;
    return *this;  // Return by reference (optimization)
}

// Post-increment
Complex operator++(int) {
    Complex temp = *this;
    ++this->real;
    ++this->imag;
    return temp;  // Return copy (before increment)
}

Usage:
    Complex C(1, 2);
    ++C;   // Calls operator++() (pre-increment)
    C++;   // Calls operator++(int) (post-increment)

PRE is MORE EFFICIENT because it doesn't create a temporary copy!

================================================================================
                        COMPLEX NUMBER MATHEMATICS
================================================================================

Complex number: C = a + bi (where i² = -1)

ADDITION:
(a + bi) + (c + di) = (a + c) + (b + d)i

SUBTRACTION:
(a + bi) - (c + di) = (a - c) + (b - d)i

MULTIPLICATION:
(a + bi)(c + di) = (ac - bd) + (ad + bc)i
Reason: (a + bi)(c + di) = ac + adi + bci + bdi²
                         = ac + adi + bci - bd (since i² = -1)
                         = (ac - bd) + (ad + bc)i

DIVISION:
(a + bi) ÷ (c + di) = [(ac + bd) + (bc - ad)i] / (c² + d²)
Steps: Multiply numerator and denominator by conjugate (c - di)

MAGNITUDE (Modulus):
|a + bi| = √(a² + b²)

CONJUGATE:
Conjugate of (a + bi) = (a - bi)

================================================================================
                         EXAMPLES FROM CODE
================================================================================

EXAMPLE 1: Simple Arithmetic Overloading
------------------------------------------
class Complex {
    double real, imag;
    
    Complex operator+(const Complex& B) {
        Complex temp;
        temp.real = this->real + B.real;
        temp.imag = this->imag + B.imag;
        return temp;
    }
};

Usage:
    Complex C1(3, 4);  // 3 + 4i
    Complex C2(1, 2);  // 1 + 2i
    Complex C3 = C1 + C2;  // Calls C1.operator+(C2)
    // Result: (4 + 6i)

EXAMPLE 2: Multiplication
---------------------------
Complex operator*(const Complex& B) {
    Complex temp;
    temp.real = (this->real * B.real) - (this->imag * B.imag);
    temp.imag = (this->real * B.imag) + (this->imag * B.real);
    return temp;
}

Usage:
    Complex C1(3, 4);  // 3 + 4i
    Complex C2(1, 2);  // 1 + 2i
    Complex C3 = C1 * C2;
    
Calculation:
    real = (3 * 1) - (4 * 2) = 3 - 8 = -5
    imag = (3 * 2) + (4 * 1) = 6 + 4 = 10
    Result: (-5 + 10i)

EXAMPLE 3: Comparison
-----------------------
bool operator==(const Complex& B) {
    return (this->real == B.real) && (this->imag == B.imag);
}

Usage:
    Complex C1(3, 4);
    Complex C2(3, 4);
    if (C1 == C2)  // Calls C1.operator==(C2)
        cout << "Equal";

EXAMPLE 4: Function Overloading with Different Volumes
---------------------------------------------------------
class VolumeCalculator {
    
    // Cube: side
    int volume(int side) {
        return side * side * side;
    }
    
    // Rectangular box: length, width, height
    int volume(int l, int w, int h) {
        return l * w * h;
    }
    
    // Cylinder: radius, height
    double volume(double r, double h) {
        return 3.14159 * r * r * h;
    }
    
    // Sphere: radius
    double volume(double r) {
        return (4.0/3.0) * 3.14159 * r * r * r;
    }
};

Usage:
    VolumeCalculator vc;
    int cubeVol = vc.volume(5);              // Calls volume(int)
    int boxVol = vc.volume(5, 10, 8);        // Calls volume(int, int, int)
    double cylVol = vc.volume(3.5, 10.0);    // Calls volume(double, double)
    double sphereVol = vc.volume(5.0);       // Calls volume(double)

Note: Last call to volume(5.0) selects volume(double) not volume(int, int, int)
because 5.0 is explicitly a double.

================================================================================
                         TEST CASES EXPLAINED
================================================================================

TEST CASE 1: Function Overloading - Calculator
Test 1.1: add(5, 10) → Calls add(int, int) → Returns 15
Test 1.2: add(5, 10, 15) → Calls add(int, int, int) → Returns 30
Test 1.3: add(5.5, 10.5) → Calls add(double, double) → Returns 16.0
Test 1.4: add(5, 10.5) → Calls add(int, double) → Returns 15.5
Test 1.5: add(10.5, 5) → Calls add(double, int) → Returns 15.5
Test 1.6: add("Hello ", "World") → Calls add(string, string) → Returns "Hello World"

KEY POINT: Order and type matter! add(5, 10.5) ≠ add(10.5, 5) but both work!

TEST CASE 2: Operator Overloading - Complex Numbers
Test 2.1: (3+4i) + (1+2i) = (4+6i)
Test 2.2: (3+4i) - (1+2i) = (2+2i)
Test 2.3: (3+4i) * (1+2i) = (-5+10i)
Test 2.4: (3+4i) / (1+2i) = (2.2-0.4i)
Test 2.5: (3+4i) == (3+4i) → TRUE (same values)
Test 2.6: (3+4i) != (1+2i) → TRUE (different values)
Test 2.7: ++C: Increments both real and imaginary parts
Test 2.8: --C: Decrements both real and imaginary parts

TEST CASE 3: Function Overloading - Volume Calculator
Test 3.1: volume(5) [Cube] = 5³ = 125
Test 3.2: volume(5, 10, 8) [Box] = 5×10×8 = 400
Test 3.3: volume(3.5, 10.0) [Cylinder] = π × 3.5² × 10 ≈ 384.85
Test 3.4: volume(5.0) [Sphere] = (4/3) × π × 5³ ≈ 523.60

KEY POINT: The compiler chooses volume(double) for 5.0 (not volume(int, int, int))

TEST CASE 4: Chained Operations
Test 4.1: (2+3i) + (4-1i) - (1+1i) = (5+1i)
Test 4.2: (2+3i) × (4-1i) ÷ (1+1i) = (10.5-0.5i)

Shows how operator overloading enables natural chaining of operations!

TEST CASE 5: Edge Cases
Test 5.1: (0+0i) + (0+0i) = (0+0i)
Test 5.2: (-3-4i) + (2+3i) = (-1-1i)
Test 5.3: (10+5i) ÷ (2+1i) = (5+0i)

================================================================================
                         BEST PRACTICES
================================================================================

1. MEANINGFUL OPERATOR OVERLOADS:
   ✓ Overload operators that make logical sense
   ✗ Don't overload + to mean multiplication

2. CONSISTENCY:
   ✓ operator++ should behave similarly to built-in types
   ✓ If operator+ works, operator+= should too (related behavior)

3. CONST CORRECTNESS:
   ✓ Use const for parameters that won't be modified
   ✓ Mark functions const if they don't modify the object

4. RETURN TYPES:
   ✓ Most operators should return the object by reference
   ✗ Don't return dangling references to temporary objects

5. AVOID CONFUSION:
   ✓ operator++ : increment
   ✓ operator+ : addition
   ✗ Don't make similar operators do completely different things

6. IMPLEMENT RELATED OPERATORS:
   ✓ If you overload operator+, also implement operator+=
   ✓ If you overload operator==, also implement operator!=

7. USE NON-MEMBER FUNCTIONS WHEN:
   ✓ You need symmetry (e.g., int + Complex should work)
   ✓ The operation doesn't need private member access

8. PERFORMANCE:
   ✓ Use references to avoid unnecessary copying
   ✓ Consider using move semantics for efficiency

================================================================================
                         ADVANTAGES & DISADVANTAGES
================================================================================

ADVANTAGES OF COMPILE-TIME POLYMORPHISM:
1. PERFORMANCE: No runtime overhead, decisions made at compile time
2. TYPE SAFETY: Compiler checks types and catches errors early
3. READABILITY: Code is more intuitive and natural
4. NO VIRTUAL FUNCTION OVERHEAD: No vtable, no function pointer indirection
5. COMPILE TIME CHECKING: All type mismatches caught before runtime

DISADVANTAGES:
1. COMPLEXITY: Code can become harder to understand with many overloads
2. AMBIGUITY: Multiple overloads can lead to ambiguous calls
3. CODE BLOAT: Compiler generates different code for each overload
4. LESS FLEXIBLE: Can't decide at runtime which overload to call

VS RUNTIME POLYMORPHISM:
- Compile-time: Fast, safe, but inflexible
- Runtime: Flexible, slower, requires virtual functions

================================================================================
                            KEY TAKEAWAYS
================================================================================

1. Compile-time polymorphism is resolved by the compiler before execution
2. Function overloading: Same name, different parameters
3. Operator overloading: Redefine operators for custom types
4. Compiler performs overload resolution based on argument types
5. Function signature includes: name, parameter count, parameter types
6. Return type alone cannot distinguish overloads
7. Operator overloading makes custom types feel like built-in types
8. Pre-increment (++C) is more efficient than post-increment (C++)
9. Overloads must make logical sense (maintain intuitive behavior)
10. Both techniques improve code readability and maintainability

================================================================================
*/
