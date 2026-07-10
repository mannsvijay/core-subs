/*
================================================================================
          COMPILE-TIME POLYMORPHISM - ADDITIONAL EXAMPLES & PITFALLS
================================================================================
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// ============================================================================
//             EXAMPLE 1: STRINGS - OPERATOR OVERLOADING
// ============================================================================

class MyString
{
private:
    char* data;
    int length;

public:
    // Constructor
    MyString(const char* s = "")
    {
        if (s == nullptr)
            length = 0;
        else
            length = strlen(s);
        
        data = new char[length + 1];
        if (s != nullptr)
            strcpy(data, s);
        else
            data[0] = '\0';
    }

    // Destructor
    ~MyString()
    {
        delete[] data;
    }

    // operator+ : String concatenation
    MyString operator+(const MyString& other)
    {
        char* temp = new char[length + other.length + 1];
        strcpy(temp, data);
        strcat(temp, other.data);
        MyString result(temp);
        delete[] temp;
        return result;
    }

    // operator* : Repeat string
    MyString operator*(int n)
    {
        if (n <= 0) return MyString("");
        
        char* temp = new char[(length * n) + 1];
        temp[0] = '\0';
        
        for (int i = 0; i < n; i++)
            strcat(temp, data);
        
        MyString result(temp);
        delete[] temp;
        return result;
    }

    // operator[] : Character access
    char operator[](int index)
    {
        if (index >= 0 && index < length)
            return data[index];
        return '\0';
    }

    // operator== : Compare strings
    bool operator==(const MyString& other)
    {
        return strcmp(data, other.data) == 0;
    }

    // operator< : Compare strings lexicographically
    bool operator<(const MyString& other)
    {
        return strcmp(data, other.data) < 0;
    }

    // Print function
    void print() const
    {
        cout << data;
    }

    int getLength() const { return length; }
};

// ============================================================================
//             EXAMPLE 2: VECTOR2D - GEOMETRIC OPERATIONS
// ============================================================================

class Vector2D
{
public:
    double x, y;

    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}

    // operator+ : Vector addition
    Vector2D operator+(const Vector2D& v)
    {
        return Vector2D(x + v.x, y + v.y);
    }

    // operator- : Vector subtraction
    Vector2D operator-(const Vector2D& v)
    {
        return Vector2D(x - v.x, y - v.y);
    }

    // operator* : Scalar multiplication (vector * scalar)
    Vector2D operator*(double scalar)
    {
        return Vector2D(x * scalar, y * scalar);
    }

    // Dot product (using * operator)
    double operator*(const Vector2D& v) const
    {
        return (x * v.x) + (y * v.y);
    }

    // Magnitude
    double magnitude() const
    {
        return sqrt(x * x + y * y);
    }

    // Normalize (make unit vector)
    Vector2D normalize()
    {
        double mag = magnitude();
        if (mag == 0) return Vector2D(0, 0);
        return Vector2D(x / mag, y / mag);
    }

    void print() const
    {
        cout << "(" << x << ", " << y << ")";
    }
};

// ============================================================================
//             EXAMPLE 3: ARRAY CLASS - ADVANCED OVERLOADING
// ============================================================================

class IntArray
{
private:
    int* data;
    int size;

public:
    // Constructor
    IntArray(int n) : size(n)
    {
        data = new int[n];
        for (int i = 0; i < n; i++)
            data[i] = 0;
    }

    // Destructor
    ~IntArray()
    {
        delete[] data;
    }

    // operator[] : Array access with bounds checking
    int& operator[](int index)
    {
        if (index < 0 || index >= size)
        {
            cout << "ERROR: Index out of bounds!\n";
            return data[0];  // Return first element as fallback
        }
        return data[index];
    }

    // operator= : Assignment
    IntArray& operator=(const IntArray& other)
    {
        if (this != &other)
        {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (int i = 0; i < size; i++)
                data[i] = other.data[i];
        }
        return *this;
    }

    // operator== : Equality
    bool operator==(const IntArray& other) const
    {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++)
            if (data[i] != other.data[i]) return false;
        return true;
    }

    // operator() : Sum all elements (callable object)
    int operator()() const
    {
        int sum = 0;
        for (int i = 0; i < size; i++)
            sum += data[i];
        return sum;
    }

    // operator() : Get element at index (callable object)
    int operator()(int index) const
    {
        if (index < 0 || index >= size)
            return -1;
        return data[index];
    }

    int getSize() const { return size; }

    void print() const
    {
        cout << "[";
        for (int i = 0; i < size; i++)
        {
            cout << data[i];
            if (i < size - 1) cout << ", ";
        }
        cout << "]";
    }
};

// ============================================================================
//             EXAMPLE 4: MATRIX CLASS - MATHEMATICAL OPERATIONS
// ============================================================================

class Matrix2x2
{
public:
    double a, b, c, d;  // [a b]
                        // [c d]

    Matrix2x2(double a = 0, double b = 0, double c = 0, double d = 0)
        : a(a), b(b), c(c), d(d) {}

    // operator+ : Matrix addition
    Matrix2x2 operator+(const Matrix2x2& m)
    {
        return Matrix2x2(a + m.a, b + m.b, c + m.c, d + m.d);
    }

    // operator- : Matrix subtraction
    Matrix2x2 operator-(const Matrix2x2& m)
    {
        return Matrix2x2(a - m.a, b - m.b, c - m.c, d - m.d);
    }

    // operator* : Matrix multiplication
    Matrix2x2 operator*(const Matrix2x2& m)
    {
        return Matrix2x2(
            a * m.a + b * m.c,
            a * m.b + b * m.d,
            c * m.a + d * m.c,
            c * m.b + d * m.d
        );
    }

    // Determinant
    double determinant() const
    {
        return (a * d) - (b * c);
    }

    // Trace (sum of diagonal elements)
    double trace() const
    {
        return a + d;
    }

    void print() const
    {
        cout << "[" << a << " " << b << "]\n"
             << "[" << c << " " << d << "]\n";
    }
};

// ============================================================================
//             EXAMPLE 5: COMMON PITFALLS & HOW TO AVOID THEM
// ============================================================================

class Student
{
public:
    string name;
    int rollNo;

    Student(string n = "", int r = 0) : name(n), rollNo(r) {}

    // PITFALL 1: Forgetting to check for self-assignment
    // BAD ✗
    Student& operator_bad_assignment(const Student& other)
    {
        name = other.name;
        rollNo = other.rollNo;
        return *this;  // Can cause issues with pointer members
    }

    // GOOD ✓
    Student& operator=(const Student& other)
    {
        if (this != &other)  // Check for self-assignment
        {
            name = other.name;
            rollNo = other.rollNo;
        }
        return *this;
    }

    // PITFALL 2: Forgetting to return reference from assignment
    // BAD ✗ (returns value)
    // Student operator_bad_assign(const Student& other)

    // GOOD ✓ (returns reference)
    // Student& operator=(const Student& other)

    // PITFALL 3: Wrong operator for comparison
    // Check for equality (should use ==, not =)
    bool operator==(const Student& other)
    {
        return (name == other.name) && (rollNo == other.rollNo);
    }

    void print()
    {
        cout << "Name: " << name << ", Roll: " << rollNo << endl;
    }
};

// ============================================================================
//             EXAMPLE 6: AMBIGUOUS OVERLOADS
// ============================================================================

class TestAmbiguous
{
public:
    // These two overloads can be ambiguous!
    void process(int x)
    {
        cout << "process(int): " << x << endl;
    }

    void process(double x)
    {
        cout << "process(double): " << x << endl;
    }

    // AMBIGUITY EXAMPLE:
    // process(5);    ✓ Calls process(int) - exact match
    // process(5.5);  ✓ Calls process(double) - exact match
    // process(5L);   ✓ Calls process(int) - long matches int better
};

// ============================================================================
//                         MAIN FUNCTION
// ============================================================================

int main()
{
    cout << "====================================================================\n"
         << "         COMPILE-TIME POLYMORPHISM - ADDITIONAL EXAMPLES\n"
         << "====================================================================\n\n";

    // ========== EXAMPLE 1: STRING OPERATIONS ==========
    cout << string(70, '=') << endl;
    cout << "EXAMPLE 1: CUSTOM STRING CLASS WITH OPERATOR OVERLOADING" << endl;
    cout << string(70, '=') << "\n";

    MyString str1("Hello");
    MyString str2("World");

    cout << "str1: ";
    str1.print();
    cout << "\nstr2: ";
    str2.print();
    cout << "\n\n";

    cout << "str1 + str2 = ";
    (str1 + str2).print();
    cout << "\n\n";

    cout << "str1 * 3 = ";
    (str1 * 3).print();
    cout << "\n\n";

    cout << "str1[0] = '" << str1[0] << "'\n";
    cout << "str1[1] = '" << str1[1] << "'\n\n";

    MyString str3("Hello");
    cout << "str1 == str3? " << (str1 == str3 ? "YES" : "NO") << "\n";
    cout << "str1 < str2? " << (str1 < str2 ? "YES" : "NO") << "\n\n";

    // ========== EXAMPLE 2: VECTOR OPERATIONS ==========
    cout << string(70, '=') << endl;
    cout << "EXAMPLE 2: VECTOR2D CLASS WITH GEOMETRIC OPERATIONS" << endl;
    cout << string(70, '=') << "\n";

    Vector2D v1(3, 4);
    Vector2D v2(1, 2);

    cout << "Vector v1: ";
    v1.print();
    cout << " (magnitude: " << v1.magnitude() << ")\n";

    cout << "Vector v2: ";
    v2.print();
    cout << " (magnitude: " << v2.magnitude() << ")\n\n";

    Vector2D v3 = v1 + v2;
    cout << "v1 + v2 = ";
    v3.print();
    cout << "\n";

    Vector2D v4 = v1 - v2;
    cout << "v1 - v2 = ";
    v4.print();
    cout << "\n";

    Vector2D v5 = v1 * 2.0;
    cout << "v1 * 2 = ";
    v5.print();
    cout << "\n";

    double dotProduct = v1 * v2;
    cout << "v1 · v2 (dot product) = " << dotProduct << "\n\n";

    Vector2D normalized = v1.normalize();
    cout << "Normalized v1: ";
    normalized.print();
    cout << " (magnitude: " << normalized.magnitude() << ")\n\n";

    // ========== EXAMPLE 3: ARRAY OPERATIONS ==========
    cout << string(70, '=') << endl;
    cout << "EXAMPLE 3: ARRAY CLASS WITH OPERATOR OVERLOADING" << endl;
    cout << string(70, '=') << "\n";

    IntArray arr1(5);
    arr1[0] = 10;
    arr1[1] = 20;
    arr1[2] = 30;
    arr1[3] = 40;
    arr1[4] = 50;

    cout << "arr1: ";
    arr1.print();
    cout << "\n\n";

    cout << "arr1[0] = " << arr1[0] << "\n";
    cout << "arr1[2] = " << arr1[2] << "\n";
    cout << "arr1[4] = " << arr1[4] << "\n\n";

    cout << "Sum of all elements using arr1(): " << arr1() << "\n";
    cout << "Element at index 2 using arr1(2): " << arr1(2) << "\n\n";

    IntArray arr2(5);
    arr2 = arr1;  // Using operator=
    cout << "arr2 after assignment from arr1: ";
    arr2.print();
    cout << "\n\n";

    cout << "arr1 == arr2? " << (arr1 == arr2 ? "YES" : "NO") << "\n\n";

    cout << "Accessing out of bounds (arr1[10]):\n";
    cout << "Value: " << arr1[10] << "\n\n";

    // ========== EXAMPLE 4: MATRIX OPERATIONS ==========
    cout << string(70, '=') << endl;
    cout << "EXAMPLE 4: MATRIX CLASS WITH MATHEMATICAL OPERATIONS" << endl;
    cout << string(70, '=') << "\n";

    Matrix2x2 m1(1, 2, 3, 4);
    Matrix2x2 m2(5, 6, 7, 8);

    cout << "Matrix m1:\n";
    m1.print();

    cout << "\nMatrix m2:\n";
    m2.print();

    cout << "\nm1 + m2:\n";
    (m1 + m2).print();

    cout << "m1 - m2:\n";
    (m1 - m2).print();

    cout << "m1 * m2 (matrix multiplication):\n";
    (m1 * m2).print();

    cout << "Determinant of m1: " << m1.determinant() << "\n";
    cout << "Trace of m1: " << m1.trace() << "\n\n";

    // ========== EXAMPLE 5: PITFALLS ==========
    cout << string(70, '=') << endl;
    cout << "EXAMPLE 5: COMMON PITFALLS & SOLUTIONS" << endl;
    cout << string(70, '=') << "\n\n";

    Student s1("Alice", 101);
    Student s2("Bob", 102);

    cout << "s1: ";
    s1.print();
    cout << "s2: ";
    s2.print();
    cout << "\n";

    s1 = s2;
    cout << "After s1 = s2:\n";
    cout << "s1: ";
    s1.print();

    cout << "s1 == s2? " << (s1 == s2 ? "YES" : "NO") << "\n\n";

    // Self-assignment test
    cout << "Self-assignment: s1 = s1\n";
    s1 = s1;
    cout << "s1: ";
    s1.print();
    cout << "\n\n";

    // ========== EXAMPLE 6: AMBIGUOUS CALLS ==========
    cout << string(70, '=') << endl;
    cout << "EXAMPLE 6: FUNCTION OVERLOADING - OVERLOAD RESOLUTION" << endl;
    cout << string(70, '=') << "\n\n";

    TestAmbiguous test;

    test.process(5);        // Calls process(int)
    test.process(5.5);      // Calls process(double)
    test.process(5L);       // Calls process(int) - long matches int better

    cout << "\n" << string(70, '=') << endl;
    cout << "                    END OF ADDITIONAL EXAMPLES" << endl;
    cout << string(70, '=') << "\n\n";

    return 0;
}
