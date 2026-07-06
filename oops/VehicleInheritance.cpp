#include <iostream>
#include <string>

using namespace std;

// Vehicle is the base class for all vehicle types.
// It stores shared data and provides common behavior.
class Vehicle
{
protected:
    string name;      // Vehicle name (e.g. "Maruti 800")
    string model;     // Vehicle model (e.g. "LXI")
    int noOfTyres;    // Number of tyres on the vehicle

public:
    // Constructor initializes shared vehicle properties.
    Vehicle(string _name, string _model, int _noOfTyres)
    {
        cout << "Vehicle constructor called" << endl;
        this->name = _name;
        this->model = _model;
        this->noOfTyres = _noOfTyres;
    }

    // Method inherited by all derived classes.
    // It prints a message showing the vehicle engine starting.
    void start_engine()
    {
        cout << "Engine is starting " << name << " " << model << endl;
    }

    // Another common method shared with derived classes.
    // It prints a message when the engine stops.
    void stop_engine()
    {
        cout << "Engine is stopping " << name << " " << model << endl;
    }

    // Destructor for Vehicle.
    // It runs when the object is destroyed.
    ~Vehicle()
    {
        cout << "Vehicle destructor called" << endl;
    }
};

// Car is a derived class of Vehicle.
// It inherits shared vehicle members and adds car-specific members.
class Car : public Vehicle
{
protected:
    int noOfDoors;            // Number of doors in the car
    string transmissionType;  // Transmission type of the car

public:
    // Car constructor calls the Vehicle constructor first.
    // Then it initializes car-specific data members.
    Car(string _name, string _model, int _noOfTyres, int _noOfDoors, string _transmissionType) : Vehicle(_name, _model, _noOfTyres)
    {
        cout << "Car constructor called" << endl;
        this->noOfDoors = _noOfDoors;
        this->transmissionType = _transmissionType;
    }

    // A method only Car objects have.
    // It starts the car's air conditioning.
    void startAC()
    {
        cout << "AC has started in " << name << " " << model << endl;
    }

    // Destructor for the Car class.
    ~Car()
    {
        cout << "Car destructor called" << endl;
    }
};

// MotorCycle is another derived class from Vehicle.
// This shows hierarchical inheritance because Vehicle is shared with Car.
class MotorCycle : public Vehicle
{
protected:
    string handleBarStyle;   // Handlebar style for the motorcycle
    string suspensionType;   // Suspension type for the motorcycle

public:
    // Motorcycle constructor initializes Vehicle first.
    // Then it sets motorcycle-specific members.
    MotorCycle(string _name, string _model, int _noOfTyres, string _handleBarStyle, string _suspensionType) : Vehicle(_name, _model, _noOfTyres)
    {
        cout << "MotorCycle constructor called" << endl;
        this->handleBarStyle = _handleBarStyle;
        this->suspensionType = _suspensionType;
    }

    // Motorcycle-specific method.
    // This method is not available in Vehicle or Car.
    void wheelie()
    {
        cout << "Wheelie is happening on " << name << " " << model << endl;
    }

    // Destructor for MotorCycle.
    ~MotorCycle()
    {
        cout << "MotorCycle destructor called" << endl;
    }
};

int main()
{
    Car A("Maruti 800", "LXI", 4, 4, "Manual");
    A.start_engine();
    A.startAC();
    A.stop_engine();

    // MotorCycle M("BMW", "VXI", 2, "U", "Hard");
    // M.start_engine();
    // M.wheelie();
    // M.stop_engine();
    return 0;
}