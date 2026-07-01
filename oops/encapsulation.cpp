/*
    =====================================================
    ENCAPSULATION CONCEPT DEMONSTRATION
    =====================================================
    
    WHAT IS ENCAPSULATION?
    Encapsulation is one of the core OOP principles that bundles data (attributes)
    and methods (functions) within a class while hiding internal details.
    It provides data security and controlled access through public interface.
    
    KEY BENEFITS:
    1. Data Hiding: Private members cannot be accessed directly from outside
    2. Data Protection: Setters can validate data before assigning
    3. Flexibility: Can change internal implementation without affecting external code
    4. Control: Public methods control HOW data is accessed/modified
*/

#include <iostream>
#include <string>

using namespace std;

class Student
{
    /*
        PRIVATE SECTION:
        These members are ENCAPSULATED (hidden).
        They cannot be accessed directly from outside the class.
        Only class methods can access them.
        This is the DATA HIDING principle.
    */
private:
    // Student Attributes (Data Members)
    int id;          // Student ID - hidden from direct access
    int age;         // Student Age - hidden from direct access
    string name;     // Student Name - hidden from direct access
    int nos;         // Number of subjects - hidden from direct access
    
    float *gpa;      // Pointer to GPA - dynamically allocated
    string gf;       // Girlfriend name - private business (hidden)

    /*
        PRIVATE METHOD:
        This method can only be called from within the class.
        It's an internal detail that the outside world doesn't need to know.
    */
    void gfchatting()
    {
        cout << this->name << " chatting with gf" << endl;
    }

    /*
        PUBLIC SECTION:
        These members form the INTERFACE between class and outside world.
        They provide controlled access to private data.
        This is the CONTROLLED ACCESS principle.
    */
public:
    // ====== CONSTRUCTOR 1: DEFAULT CONSTRUCTOR ======
    // Called when object is created without arguments
    // Example: Student s;
    Student()
    {
        cout << "Student Default ctor called" << endl;
    }

    // ====== CONSTRUCTOR 2: PARAMETERISED CONSTRUCTOR ======
    // Called when object is created with specific values
    // Example: Student A(1, 12, "Ranu", 5, 7.8, "Menu");
    // This initializes ALL member attributes
    Student(int id, int age, string name, int nos, float gpa, string gf)
    {
        cout << "Student Parameterised ctor called" << endl;
        
        // Initialize private members using parameter values
        this->id = id;
        this->age = age;
        this->name = name;
        this->nos = nos;
        
        // Dynamically allocate memory for GPA
        // Why? To demonstrate pointer usage and proper memory management
        this->gpa = new float(gpa);
        this->gf = gf;
    }

    // ====== CONSTRUCTOR 3: COPY CONSTRUCTOR ======
    // Called when an object is copied from another object
    // Example: Student B = A;  or  Student C(A);
    // This creates a new object with the same data as source object
    Student(const Student &srcobj)
    {
        cout << "Student copy ctor called" << endl;
        
        // Copy all attributes from source object
        this->id = srcobj.id;
        this->age = srcobj.age;
        this->name = srcobj.name;
        this->nos = srcobj.nos;
        // Note: GPA pointer is NOT copied (shallow copy issue - left for demonstration)
    }

    // ====== GETTER METHODS: Provide READ-ONLY access to private data ======
    // These follow encapsulation by allowing controlled read access
    
    // Get GPA: Returns the value pointed by gpa pointer
    float getGpa() const
    {
        return *this->gpa;  // Dereference pointer to get actual value
    }

    // Get Age: Returns student's age
    float getAge() const
    {
        return this->age;
    }

    // Get Name: Returns student's name
    string getName() const
    {
        return this->name;
    }

    // Get ID: Returns student's ID
    int getId() const
    {
        return this->id;
    }

    // Get Number of Subjects: Returns subject count
    int getNumberOfSubjects() const
    {
        return this->nos;
    }

    // ====== SETTER METHODS: Provide CONTROLLED WRITE access to private data ======
    // These allow modification BUT with validation/protection
    // Example of ENCAPSULATION: We control WHAT and HOW data is modified
    
    // Set GPA: WITH validation
    // This demonstrates why setters are important - we can validate data
    void setGpa(float a)
    {
        // VALIDATION: Only allow valid GPA values (0.0 to 10.0)
        // This is a layer of protection/authentication that a direct assignment wouldn't have
        if (a >= 0.0 && a <= 10.0)
        {
            *this->gpa = a;
            cout << "GPA updated successfully to " << a << endl;
        }
        else
        {
            cout << "Invalid GPA! Please enter value between 0.0 and 10.0" << endl;
        }
    }

    // Set Age: WITH validation
    void setAge(int newAge)
    {
        // VALIDATION: Age should be reasonable
        if (newAge > 0 && newAge < 100)
        {
            this->age = newAge;
            cout << "Age updated successfully to " << newAge << endl;
        }
        else
        {
            cout << "Invalid Age! Please enter reasonable age" << endl;
        }
    }

    // Set Name: Allow name modification
    void setName(string newName)
    {
        // Validation: Name should not be empty
        if (newName.length() > 0)
        {
            this->name = newName;
            cout << "Name updated successfully to " << newName << endl;
        }
        else
        {
            cout << "Invalid Name! Name cannot be empty" << endl;
        }
    }

    // ====== BEHAVIOUR/ACTION METHODS ======
    // These represent what a student CAN DO
    
    void study()
    {
        cout << this->name << " is Studying" << endl;
    }

    void sleep()
    {
        cout << this->name << " is Sleeping" << endl;
    }

    void bunk()
    {
        cout << this->name << " is Bunking class" << endl;
    }

    // Public method to trigger private behavior
    // This shows encapsulation: external code calls public method,
    // which internally calls private method
    void callGirlfriend()
    {
        cout << this->name << " making a phone call..." << endl;
        this->gfchatting();  // Calling private method from within public method
    }

    // Display all student information
    void displayInfo() const
    {
        cout << "\n===== STUDENT INFORMATION =====" << endl;
        cout << "ID: " << this->id << endl;
        cout << "Name: " << this->name << endl;
        cout << "Age: " << this->age << endl;
        cout << "Subjects: " << this->nos << endl;
        cout << "GPA: " << *this->gpa << endl;
        cout << "================================\n" << endl;
    }

    // ====== DESTRUCTOR ======
    // Called when object is destroyed
    // Cleans up dynamically allocated memory
    ~Student()
    {
        cout << "Student Default dtor called" << endl;
        delete this->gpa;  // Free dynamically allocated memory
    }
};

// =====================================================
// MAIN FUNCTION: DEMONSTRATING ENCAPSULATION
// =====================================================
int main()
{
    cout << "\n ===== ENCAPSULATION DEMONSTRATION ===== \n" << endl;

    // ====== CREATING OBJECTS ======
    cout << "--- Creating Student Objects ---" << endl;
    
    // Create first student using parameterised constructor
    Student A(1, 12, "Ranu", 5, 7.8, "Menu");
    cout << endl;

    // Create second student for comparison
    Student B(2, 13, "Raj", 6, 8.5, "Priya");
    cout << endl;

    // ====== DEMONSTRATING DATA HIDING & CONTROLLED ACCESS ======
    cout << "--- Demonstrating Getter Methods (READ ACCESS) ---" << endl;
    cout << "Getting data through public methods (SAFE & CONTROLLED)" << endl;
    cout << "Student A Name: " << A.getName() << endl;
    cout << "Student A Age: " << A.getAge() << endl;
    cout << "Student A ID: " << A.getId() << endl;
    cout << endl;

    // ====== THIS WOULD NOT WORK (Data Hiding in action) ======
    // cout << A.id << endl;        // ERROR! 'id' is private
    // cout << A.gpa << endl;       // ERROR! 'gpa' is private
    // ^^ These are HIDDEN due to encapsulation!

    cout << "--- Demonstrating GPA Getter ---" << endl;
    cout << "Student A GPA: " << A.getGpa() << endl;
    cout << "Student B GPA: " << B.getGpa() << endl;
    cout << endl;

    // ====== DEMONSTRATING SETTER WITH VALIDATION ======
    cout << "--- Demonstrating Setter Methods (WRITE ACCESS with VALIDATION) ---" << endl;
    
    // Valid GPA update
    cout << "\nAttempting to set valid GPA (6.7):" << endl;
    A.setGpa(6.7);
    
    // Invalid GPA attempt - will be rejected by validation
    cout << "\nAttempting to set invalid GPA (15.5):" << endl;
    A.setGpa(15.5);  // This will be REJECTED due to validation in setter
    
    cout << "\nStudent A GPA after updates: " << A.getGpa() << endl;
    cout << endl;

    // ====== DEMONSTRATING MORE SETTERS ======
    cout << "--- Updating Student Information ---" << endl;
    A.setName("Ranu Sharma");
    A.setAge(13);
    cout << endl;

    // Invalid age attempt
    cout << "Attempting invalid age (150):" << endl;
    A.setAge(150);  // Will be rejected
    cout << endl;

    // ====== DEMONSTRATING BEHAVIOR METHODS ======
    cout << "--- Student Actions/Behaviors ---" << endl;
    A.study();
    A.sleep();
    A.bunk();
    cout << endl;

    // ====== DEMONSTRATING PRIVATE METHOD ACCESS ======
    cout << "--- Accessing Private Methods Indirectly ---" << endl;
    cout << "Private method gfchatting() cannot be called directly!" << endl;
    cout << "But can be called through public method callGirlfriend():" << endl;
    A.callGirlfriend();  // Public method calls private method internally
    cout << endl;

    // ====== DISPLAYING STUDENT INFORMATION ======
    cout << "--- Complete Student Information ---" << endl;
    A.displayInfo();
    B.displayInfo();

    // ====== COPY CONSTRUCTOR DEMONSTRATION ======
    cout << "--- Copy Constructor in Action ---" << endl;
    Student C = A;  // Copy constructor called
    cout << endl;

    return 0;

    // Note: Destructors will be called automatically when objects go out of scope
    // This demonstrates proper resource cleanup (memory deallocation)
}
