#include <bits/stdc++.h>
using namespace std;

class Vehicles {
public :
    string name;
    string model;
    int noOfTyres;
    
    Vehicles() {
        cout<<"vehicles constructor called"<<endl;
    }

    Vehicles(string _name, string _model, int _noOfTyres) {
        name = _name;
        model = _model;
        noOfTyres = _noOfTyres;
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

    // we can also call the base class constructor from the derived class constructor using the initializer list so that we can initialize the base class members as well
    // and we dont have to call the base class constructor explicitly in the derived class constructor body
    Car(string _name, string _model, int _noOfTyres, int _noOfDoors, string _TransmissionType) : Vehicles(_name, _model, _noOfTyres) {
        noOfDoors = _noOfDoors;
        TransmissionType = _TransmissionType;
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