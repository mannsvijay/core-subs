#include <bits/stdc++.h>
using namespace std;

class Vehicles {
public :
    int name;
    string model;
    int noOfTyres;
    
    Vehicles() {
        cout<<"vehicles constructor called"<<endl;
    }

    void start_engine() {
        cout<<"engine started"<<endl;

    }

    void stop_engine() {
        cout<<"engine stopped"<<endl;
    }

    ~Vehicles() {
        cout<<"vehicles destructor called"<<endl;
    }
};

class Car : public Vehicles {
public :
    int noOfDoors;
    string TransmissionType;

    Car() {
        cout<<"Car constructor called"<<endl;
    }
    void startAC() {
        cout<<"AC started"<<endl;
    }

    ~Car() {
        cout<<"Car destructor called"<<endl;
    }
};

class motorclyes : public Vehicles {
public:
    string handleBarStyle;
    string suspensionType;

    motorclyes() {
        cout<<"motorclyes constructor called"<<endl;
    }

    void wheelie() {
        cout<<"we started wheelie"<<endl;
    }

    ~motorclyes() {
        cout<<"motorclyes destructor called"<<endl;
    }
};


int main() {
    // Vehicles C;
    // C.start_engine();
    // C.stop_engine();
    
    Car A;  // vehicle object created, Vehicles constructor called then Car constructor called
    A.start_engine(); // engine started
    A.stop_engine();  // engine stopped
    A.startAC(); // AC started
    // A.wheelie(); // ERROR! Car class does not have wheelie() method
    //car destructor called then vehicles destructor called



    return 0;
}