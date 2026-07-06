#include <iostream>
#include <string>
using namespace std;

// Base class: Vehicle
// This class has the common properties that all vehicles share.
class Vehicle {
protected: //
    string name;
    string model;
    int noOfTyres;

public:
    // Default constructor sets simple default values.
    Vehicle() : name("Unknown"), model("Unknown"), noOfTyres(0) {
        cout << "Vehicle default constructor called" << endl;
    }

    // Parameterized constructor initializes the vehicle details.
    Vehicle(const string& _name, const string& _model, int _noOfTyres)
        : name(_name), model(_model), noOfTyres(_noOfTyres) {
        cout << "Vehicle parameterized constructor called" << endl;
    }

    // Start the vehicle engine.
    void startEngine() {
        cout << "[Vehicle] " << name << " " << model << " engine started" << endl;
    }

    // Stop the vehicle engine.
    void stopEngine() {
        cout << "[Vehicle] " << name << " " << model << " engine stopped" << endl;
    }

    // Print the basic vehicle details.
    void showDetails() {
        cout << "Vehicle details: " << name << " " << model
             << " with " << noOfTyres << " tyres" << endl;
    }
};

// Single inheritance: Car inherits from Vehicle.
class Car : public Vehicle {
public:
    int noOfDoors;
    string transmissionType;

    // Default constructor calls Vehicle default constructor implicitly.
    Car() : noOfDoors(4), transmissionType("Manual") {
        name = "DefaultCar";
        model = "Basic";
        noOfTyres = 4;
        cout << "Car default constructor called" << endl;
    }

    // Parameterized constructor initializes both Vehicle and Car data.
    Car(const string& _name, const string& _model, int _noOfTyres, int _noOfDoors, const string& _transmissionType)
        : Vehicle(_name, _model, _noOfTyres), noOfDoors(_noOfDoors), transmissionType(_transmissionType) {
        cout << "Car parameterized constructor called" << endl;
    }

    // Open the trunk of the car.
    void openTrunk() {
        cout << "[Car] " << name << " " << model << " trunk opened" << endl;
    }

    // Print car-specific details plus the inherited vehicle details.
    void showCarDetails() {
        showDetails();
        cout << "Car details: " << noOfDoors << " doors, "
             << transmissionType << " transmission" << endl;
    }
};

// Hierarchical inheritance: Motorcycle also inherits from Vehicle.
class Motorcycle : public Vehicle {
public:
    string handleBarStyle;

    Motorcycle() : handleBarStyle("Standard") {
        name = "DefaultBike";
        model = "Standard";
        noOfTyres = 2;
        cout << "Motorcycle default constructor called" << endl;
    }

    Motorcycle(const string& _name,
               const string& _model,
               int _noOfTyres,
               const string& _handleBarStyle)
        : Vehicle(_name, _model, _noOfTyres),
          handleBarStyle(_handleBarStyle) {
        cout << "Motorcycle parameterized constructor called" << endl;
    }

    // Perform a wheelie, which is specific to motorcycles.
    void doWheelie() {
        cout << "[Motorcycle] " << name << " " << model << " does a wheelie" << endl;
    }

    // Print motorcycle-specific details.
    void showMotorcycleDetails() {
        showDetails();
        cout << "Motorcycle details: handlebar style = " << handleBarStyle << endl;
    }
};

// Multilevel inheritance: SportsCar inherits from Car.
class SportsCar : public Car {
public:
    int horsepower;

    SportsCar() : horsepower(300) {
        name = "DefaultSportsCar";
        model = "Sport";
        noOfTyres = 4;
        noOfDoors = 2;
        transmissionType = "Automatic";
        cout << "SportsCar default constructor called" << endl;
    }

    SportsCar(const string& _name,
              const string& _model,
              int _noOfTyres,
              int _noOfDoors,
              const string& _transmissionType,
              int _horsepower)
        : Car(_name, _model, _noOfTyres, _noOfDoors, _transmissionType),
          horsepower(_horsepower) {
        cout << "SportsCar parameterized constructor called" << endl;
    }

    // Use a sports car feature.
    void boostSpeed() {
        cout << "[SportsCar] " << name << " " << model
             << " boosts speed with " << horsepower << " horsepower" << endl;
    }

    // Print sports car details.
    void showSportsCarDetails() {
        showCarDetails();
        cout << "SportsCar details: " << horsepower << " HP" << endl;
    }
};

// Multiple inheritance: Boat inherits from Vehicle.
class Boat : public Vehicle {
public:
    string hullType;

    Boat() : hullType("Displacement") {
        name = "DefaultBoat";
        model = "Boat";
        noOfTyres = 0;
        cout << "Boat default constructor called" << endl;
    }

    Boat(const string& _name,
         const string& _model,
         const string& _hullType)
        : Vehicle(_name, _model, 0),
          hullType(_hullType) {
        cout << "Boat parameterized constructor called" << endl;
    }

    // Anchor the boat.
    void dropAnchor() {
        cout << "[Boat] " << name << " " << model << " drops anchor" << endl;
    }

    // Print boat-specific details.
    void showBoatDetails() {
        showDetails();
        cout << "Boat details: hull type = " << hullType << endl;
    }
};

// AmphibiousVehicle uses multiple inheritance from Car and Boat.
// This shows how a class can inherit from more than one base class.
class AmphibiousVehicle : public Car, public Boat {
public:
    AmphibiousVehicle()
        : Car("AmphibiousCar", "AmphiModel", 4, 2, "Automatic"),
          Boat("AmphibiousBoat", "AmphiModel", "Planing") {
        cout << "AmphibiousVehicle constructor called" << endl;
    }

    // Transform mode on land or water.
    void transformMode() {
        cout << "[AmphibiousVehicle] Switching mode between car and boat" << endl;
    }

    // Show details from both Car and Boat sides.
    void showAmphibiousDetails() {
        cout << "AmphibiousVehicle details from Car side:" << endl;
        Car::showCarDetails();
        cout << "AmphibiousVehicle details from Boat side:" << endl;
        Boat::showBoatDetails();
    }
};

int main() {
    cout << "\n=== Single inheritance example ===" << endl;
    Car myCar("Toyota", "Corolla", 4, 4, "Automatic");
    myCar.showCarDetails();
    myCar.startEngine();
    myCar.openTrunk();
    myCar.stopEngine();

    cout << "\n=== Hierarchical inheritance example ===" << endl;
    Motorcycle myBike("Yamaha", "R15", 2, "Clip-on");
    myBike.showMotorcycleDetails();
    myBike.startEngine();
    myBike.doWheelie();
    myBike.stopEngine();

    cout << "\n=== Multilevel inheritance example ===" << endl;
    SportsCar mySportsCar("Ferrari", "488 GTB", 4, 2, "Automatic", 660);
    mySportsCar.showSportsCarDetails();
    mySportsCar.startEngine();
    mySportsCar.boostSpeed();
    mySportsCar.stopEngine();

    cout << "\n=== Multiple inheritance example ===" << endl;
    AmphibiousVehicle myAmphibian;
    myAmphibian.showAmphibiousDetails();
    myAmphibian.Car::startEngine();
    myAmphibian.Boat::dropAnchor();
    myAmphibian.transformMode();

    cout << "\n=== End of inheritance examples ===" << endl;
    return 0;
}
