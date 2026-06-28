#include <bits/stdc++.h>
using namespace std;

class Student {
public:

    //attributes
    int age;
    int numberOfsubs;
    string name;
    int id;

    //constructor - default
    Student() {
        cout<<"default constructor called"<<endl;
    }

    //parameterized constructor
    Student(string name,int age,int numberOfsubs,int id) {
        cout<<"parameterized constructor called"<<endl;
        this->name = name;
        this->age = age;
        this->numberOfsubs = numberOfsubs;
        this->id = id;
    }

    //copy constructor
    Student(const Student &srcobj) {
        cout<<"copy constructor called"<<endl;
        this->name = srcobj.name;
        this->age = srcobj.age;
        this->numberOfsubs = srcobj.numberOfsubs;
        this->id = srcobj.id;
    }


    //behaviors
    void study() {
        cout<<this->name <<" studying"<<endl; // we use this here as this a pointer to the current object
    }

    void sleep() {
        cout<<this->name<<" sleeping"<<endl; // we use this here as this a pointer to the current object
    }

    void bunk() {
        cout<<this->name<<" bunking"<<endl;
    }


    //destructor default
    ~Student() {
        cout<<this->name<<" default destructor called"<<endl;
    }
};

int main() {
    // Student s1;
    // s1.name = "manan";
    // s1.age = 21;
    // s1.id = 1;
    // s1.numberOfsubs = 6;

    // s1.study();

    // Student s2;
    // s2.name = "hardik";
    // s2.age = 22;
    // s2.id = 2;
    // s2.numberOfsubs = 5;

    // s2.bunk();


    Student S1("manan",21,6,1); // parameterized constructor called
    // Student S2 ("hardik",8,6,2);
    // Student S3 ("meena",45,0,3);
    // Student S4 ("rajeev",49,0,4);
    // Student S5 ("manbhari",80,0,5);


    Student S6 = S1; // copy constructor called
    Student S7(S1); // copy constructor called
    S6.name = "manan2";


    //dynamic memory allocation - in this case we have to use new keyword to allocate memory in heap 
    // in this all the objects will be created in heap memory and we have to delete them manually using delete keyword
    //earlier we have created the objects in stack memory and they will be deleted automatically when the function ends
    Student *S8 = new Student("kushal",22,4,6); // parameterized constructor called
    
    return 0;
}