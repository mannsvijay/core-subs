/*
    ================================================================
     UNDERSTANDING INHERITANCE IN C++ - FULL GUIDE (ALL TYPES)
    ================================================================

    This file grows your original Vehicles -> Car / motorclyes example
    so it demonstrates EVERY major type of inheritance, plus how
    private / protected / public work - both for class MEMBERS and
    for the INHERITANCE MODE itself (two different things, both
    explained in detail in the chat message).

    WHAT'S IN THIS FILE (search these section titles):
      1) Vehicles                                   - base class
      2) Car : public Vehicles                      - SINGLE inheritance
      3) motorclyes : public Vehicles                - HIERARCHICAL inheritance
      4) SportsCar : public Car                      - MULTILEVEL inheritance
      5) Battery                                     - an unrelated class
      6) ElectricCar : public Car, public Battery     - MULTIPLE + HYBRID inheritance
      7) DemoBase / PublicChild / ProtectedChild / PrivateChild
                                                      - public vs protected vs private INHERITANCE
      8) main()                                       - runs everything, comments predict output

    The deep explanation (tables, definitions, output walkthrough) is
    in the chat message. This file's comments are tied to exact lines
    of code so you can read top to bottom and follow along.
*/

#include <bits/stdc++.h>
using namespace std;


// ================================================================
// 1) BASE CLASS: Vehicles
// ================================================================
// Every vehicle (car, motorcycle, ...) "IS-A" Vehicles, so anything
// common to ALL vehicles lives here ONCE, instead of being repeated
// in every child class below. That re-use is the whole POINT of
// inheritance: write it once in the parent, use it in every child.
//
// This class deliberately uses all 3 access levels so you can see
// how each one behaves:
class Vehicles {

private:
    // PRIVATE = usable ONLY inside Vehicles' own functions.
    // Not Car, not motorclyes, not main() - literally nobody else,
    // no matter how they inherit from Vehicles.
    string engineNumber;

protected:
    // PROTECTED = usable inside Vehicles AND inside any class that
    // inherits from Vehicles (Car, motorclyes, SportsCar, ElectricCar...).
    // Still NOT usable from main() / outside code directly.
    string name;
    string model;
    int noOfTyres;
    int fuelLevel;      // stored as a percentage: 0 to 100

public:
    // PUBLIC = usable from literally anywhere: inside the class,
    // inside child classes, and from main().

    // default constructor - runs when you create a Vehicles with no arguments
    Vehicles() {
        name = "Unknown";
        model = "Unknown";
        noOfTyres = 0;
        fuelLevel = 0;
        engineNumber = "N/A";
        cout << "vehicles constructor called" << endl;
    }

    // parameterised constructor - runs when you pass arguments
    Vehicles(string _name, string _model, int _noOfTyres) {
        name = _name;
        model = _model;
        noOfTyres = _noOfTyres;
        fuelLevel = 50;                    // every new vehicle starts half full
        engineNumber = "ENG-" + _name;      // auto-generated, just so 'private' has something to hold
        cout << "vehicles constructor called" << endl;
    }

    void start_engine() {
        cout << "engine started" << endl;
    }

    void stop_engine() {
        cout << "engine stopped" << endl;
    }

    // a PUBLIC function reading/writing a PROTECTED variable (fuelLevel)
    void refuel(int amount) {
        fuelLevel += amount;
        if (fuelLevel > 100) fuelLevel = 100;   // cap at 100%
        cout << name << " refuelled -> fuel level now " << fuelLevel << "%" << endl;
    }

    // a "getter" - the ONLY way anything outside Vehicles can ever
    // read the private engineNumber. Standard pattern: keep the
    // variable private, expose a public function for controlled access.
    string getEngineNumber() {
        return engineNumber;
    }

    // uses protected members directly - allowed because we're
    // writing this code INSIDE Vehicles itself
    void displayInfo() {
        cout << "Name: " << name << " | Model: " << model
             << " | Tyres: " << noOfTyres << " | Fuel: " << fuelLevel << "%" << endl;
    }

    ~Vehicles() {
        cout << "vehicles destructor called" << endl;
    }
};


// ================================================================
// 2) Car : public Vehicles      ->  SINGLE INHERITANCE
// ================================================================
// ONE child (Car), ONE direct parent (Vehicles) = SINGLE inheritance.
// The "public" written after the colon is the INHERITANCE MODE.
// Public inheritance (by far the most common) means:
//     Vehicles' public members    -> stay PUBLIC inside Car
//     Vehicles' protected members -> stay PROTECTED inside Car
//     Vehicles' private members   -> NEVER visible inside Car (or anywhere else)
class Car : public Vehicles {
public:
    int noOfDoors;
    string TransmissionType;

    Car() {
        cout << "Car constructor called" << endl;
    }

    // Calling the base class constructor through the initializer list.
    // SEQUENCE RULE: Vehicles(...) runs to completion FIRST, THEN
    // Car's own constructor body runs. A Car can't exist without a
    // fully-built Vehicles "inside" it first.
    Car(string _name, string _model, int _noOfTyres, int _noOfDoors, string _TransmissionType)
        : Vehicles(_name, _model, _noOfTyres) {
        noOfDoors = _noOfDoors;
        TransmissionType = _TransmissionType;
        cout << "Car constructor called" << endl;
    }

    void startAC() {
        cout << "AC started" << endl;
    }

    void stopAC() {
        cout << "AC stopped" << endl;
    }

    // Only compiles because 'name' and 'fuelLevel' are PROTECTED in
    // Vehicles. If they were private, this line would fail to compile.
    void showCarSummary() {
        cout << name << " (" << TransmissionType << ", " << noOfDoors << " doors) - "
             << fuelLevel << "% fuel left" << endl;
    }

    ~Car() {
        cout << "Car destructor called" << endl;
    }
};


// ================================================================
// 3) motorclyes : public Vehicles     ->  HIERARCHICAL INHERITANCE
// ================================================================
// Vehicles now has TWO direct children: Car (above) and motorclyes
// (this one). ONE parent, MANY children = HIERARCHICAL inheritance.
// (kept your original spelling "motorclyes" so nothing else breaks -
//  correct English spelling is "Motorcycle", just FYI!)
class motorclyes : public Vehicles {
public:
    string handleBarStyle;
    string suspensionType;

    motorclyes() {
        cout << "motorclyes constructor called" << endl;
    }

    // added this parameterised constructor (your original only had the default one)
    motorclyes(string _name, string _model, int _noOfTyres, string _handleBarStyle, string _suspensionType)
        : Vehicles(_name, _model, _noOfTyres) {
        handleBarStyle = _handleBarStyle;
        suspensionType = _suspensionType;
        cout << "motorclyes constructor called" << endl;
    }

    void wheelie() {
        cout << "we started wheelie" << endl;
    }

    void applyBrakes() {
        cout << "brakes applied, bike is slowing down" << endl;
    }

    void showBikeSummary() {
        cout << name << " (" << handleBarStyle << " handlebar, " << suspensionType << " suspension)" << endl;
    }

    ~motorclyes() {
        cout << "motorclyes destructor called" << endl;
    }
};


// ================================================================
// 4) SportsCar : public Car        ->  MULTILEVEL INHERITANCE
// ================================================================
// Chain:  Vehicles  ->  Car  ->  SportsCar   (3 levels)
// SportsCar's parent (Car) already has its OWN parent (Vehicles), so
// SportsCar is really a "grandchild" of Vehicles. A chain of 3+
// levels like this = MULTILEVEL inheritance.
class SportsCar : public Car {
public:
    int topSpeed;          // km/h
    bool turboEnabled;

    SportsCar() {
        turboEnabled = false;
        cout << "SportsCar constructor called" << endl;
    }

    // Creating ONE SportsCar secretly runs 2 base constructors first:
    // Vehicles() -> Car() -> and only then finally SportsCar() itself.
    SportsCar(string _name, string _model, int _noOfTyres, int _noOfDoors,
              string _TransmissionType, int _topSpeed)
        : Car(_name, _model, _noOfTyres, _noOfDoors, _TransmissionType) {
        topSpeed = _topSpeed;
        turboEnabled = false;
        cout << "SportsCar constructor called" << endl;
    }

    void turboBoost() {
        turboEnabled = true;
        // 'name' belongs to Vehicles (the GRANDPARENT) - still reachable
        // here because protected members keep flowing down every level.
        cout << name << " activated TURBO! Top speed: " << topSpeed << " km/h" << endl;
    }

    ~SportsCar() {
        cout << "SportsCar destructor called" << endl;
    }
};


// ================================================================
// 5) Battery       ->  a completely INDEPENDENT / UNRELATED class
// ================================================================
// This class has nothing to do with Vehicles - it doesn't inherit
// from anything. It exists purely so the NEXT class (ElectricCar)
// can inherit from two totally unrelated families at once.
class Battery {
public:
    int batteryCapacityKWh;

    Battery() {
        batteryCapacityKWh = 0;
        cout << "Battery constructor called" << endl;
    }

    Battery(int _capacity) {
        batteryCapacityKWh = _capacity;
        cout << "Battery constructor called" << endl;
    }

    void chargeBattery() {
        cout << "Battery charging... capacity " << batteryCapacityKWh << " kWh" << endl;
    }

    ~Battery() {
        cout << "Battery destructor called" << endl;
    }
};


// ================================================================
// 6) ElectricCar : public Car, public Battery
//               ->  MULTIPLE INHERITANCE (and also HYBRID inheritance!)
// ================================================================
// ElectricCar has TWO DIRECT parents at once: Car AND Battery.
// One child, more than one DIRECT parent = MULTIPLE inheritance.
//
// Now zoom out and look at the whole picture:
//     Vehicles -> Car -> ElectricCar     (a multilevel chain)
//     Battery        -> ElectricCar      (a separate, unrelated branch)
// Mixing more than one basic type together (multilevel + multiple,
// here) in one design is called HYBRID inheritance.
class ElectricCar : public Car, public Battery {
public:
    int rangeKm;     // how far it goes on a full charge

    ElectricCar() {
        rangeKm = 0;
        cout << "ElectricCar constructor called" << endl;
    }

    // IMPORTANT RULE for multiple inheritance construction order:
    // base classes run in the order THEY ARE WRITTEN in
    //      "class ElectricCar : public Car, public Battery"
    //                             ^^^ 1st       ^^^ 2nd
    // NOT the order you happen to list them in the initializer list
    // below. Car() always finishes before Battery() starts, no matter
    // how we order things here.
    ElectricCar(string _name, string _model, int _noOfTyres, int _noOfDoors,
                string _TransmissionType, int _batteryCapacity, int _rangeKm)
        : Car(_name, _model, _noOfTyres, _noOfDoors, _TransmissionType),
          Battery(_batteryCapacity) {
        rangeKm = _rangeKm;
        cout << "ElectricCar constructor called" << endl;
    }

    void showRange() {
        // uses 'name' (from Vehicles, via Car) AND batteryCapacityKWh
        // (from Battery) in the SAME function - proof both parent
        // lines are genuinely connected here.
        cout << name << " goes " << rangeKm << " km on a full charge ("
             << batteryCapacityKWh << " kWh battery)" << endl;
    }

    ~ElectricCar() {
        cout << "ElectricCar destructor called" << endl;
    }
};
// A NOTE ON THE "DIAMOND PROBLEM" (you do NOT have this issue here,
// just good to know it exists): Battery is unrelated to Vehicles, so
// there's only one path to Vehicles (through Car) - no conflict. If
// Battery had ALSO inherited from Vehicles, ElectricCar would end up
// with 2 separate copies of Vehicles inside it, which is ambiguous.
// Fixing that needs a keyword called "virtual inheritance" - a more
// advanced topic, ask if you ever want to go there!


// ================================================================
// 7) BONUS DEMO: public vs protected vs private INHERITANCE
// ================================================================
// A DIFFERENT idea from private/protected/public MEMBERS (used inside
// Vehicles above). This is about the keyword written AFTER the colon
// when a class inherits, e.g. the "public" in:
//        class Car : public Vehicles
//                     ^^^^^^
// That keyword decides how the BASE class's public and protected
// members get relabelled once they land inside the derived class.
// (Private members of the base are NEVER touchable in a derived
//  class, no matter which of these 3 keywords you use.)
//
// Small standalone classes below, kept separate from the Vehicles
// family, just so the 3 keywords are easy to compare side by side.

class DemoBase {
public:
    int pubVar;
protected:
    int protVar;
private:
    int privVar;
public:
    DemoBase() {
        pubVar = 1;
        protVar = 2;
        privVar = 3;
    }
};

// -- PUBLIC inheritance (the default / 99% of the time choice) --
// base's public stays public | base's protected stays protected
class PublicChild : public DemoBase {
public:
    void test() {
        cout << "PublicChild sees -> pubVar: " << pubVar << ", protVar: " << protVar << endl;
        // privVar is NOT reachable here - private never passes down, no matter the mode
    }
};

// -- PROTECTED inheritance --
// base's public BECOMES protected | base's protected stays protected
class ProtectedChild : protected DemoBase {
public:
    void test() {
        cout << "ProtectedChild sees -> pubVar: " << pubVar << ", protVar: " << protVar << endl;
    }
};

// -- PRIVATE inheritance --
// base's public BECOMES private | base's protected BECOMES private
class PrivateChild : private DemoBase {
public:
    void test() {
        cout << "PrivateChild sees -> pubVar: " << pubVar << ", protVar: " << protVar << endl;
    }
};
// Note: none of these 3 demo classes print anything when destroyed
// (no cout was added in their destructors) - keeping this demo's
// output focused purely on the access-level idea.


// ================================================================
// 8) main()
// ================================================================
int main() {

    cout << "\n---------- STEP 1: Car object (SINGLE inheritance) ----------" << endl;
    // Vehicles(...) constructor runs FIRST (prints its line),
    // THEN Car's own constructor body runs (prints its line).
    Car A("Swift", "VXI", 4, 4, "Manual");
    A.start_engine();              // inherited from Vehicles
    A.stop_engine();               // inherited from Vehicles
    A.startAC();                   // Car's own
    A.refuel(30);                  // inherited from Vehicles - fuel 50 -> 80
    A.displayInfo();                // inherited from Vehicles
    A.showCarSummary();            // Car's own function, using Vehicles' protected data
    cout << "Engine number (via getter): " << A.getEngineNumber() << endl;

    // A.wheelie();             // ERROR if uncommented: Car never inherited from motorclyes
    // cout << A.engineNumber;  // ERROR if uncommented: private in Vehicles - nobody outside can touch it
    // cout << A.fuelLevel;     // ERROR if uncommented: protected in Vehicles - main() is "outside", can't touch it


    cout << "\n---------- STEP 2: motorclyes object (HIERARCHICAL inheritance) ----------" << endl;
    motorclyes M("Duke", "390", 2, "Sport", "USD Forks");
    M.start_engine();
    M.wheelie();
    M.applyBrakes();
    M.showBikeSummary();
    M.stop_engine();


    cout << "\n---------- STEP 3: SportsCar object (MULTILEVEL inheritance) ----------" << endl;
    // construction order here: Vehicles -> Car -> SportsCar (3 levels)
    SportsCar S("Nova", "GT", 4, 2, "Automatic", 320);
    S.start_engine();       // from Vehicles (grandparent)
    S.startAC();            // from Car (parent)
    S.turboBoost();         // SportsCar's own


    cout << "\n---------- STEP 4: ElectricCar object (MULTIPLE + HYBRID inheritance) ----------" << endl;
    // construction order here: Car FIRST, then Battery, then ElectricCar
    // (Car is listed first in "class ElectricCar : public Car, public Battery")
    ElectricCar E("Volt", "EV1", 4, 4, "Automatic", 75, 450);
    E.start_engine();       // from Vehicles (through Car)
    E.chargeBattery();      // from Battery
    E.showRange();          // ElectricCar's own - uses BOTH parent lines at once


    cout << "\n---------- STEP 5: public vs protected vs private INHERITANCE ----------" << endl;
    PublicChild pc;
    ProtectedChild prc;
    PrivateChild prvc;
    pc.test();
    prc.test();
    prvc.test();

    cout << "PublicChild's pubVar reached directly from main(): " << pc.pubVar << endl;   // WORKS
    // cout << prc.pubVar;   // ERROR if uncommented: pubVar became PROTECTED here, main() can't reach it
    // cout << prvc.pubVar;  // ERROR if uncommented: pubVar became PRIVATE here, main() can't reach it


    cout << "\n---------- STEP 6: everything gets destroyed now (watch the order!) ----------" << endl;
    // We created, in this order:  A, M, S, E, pc, prc, prvc
    // Destructors ALWAYS fire in the EXACT REVERSE order objects were
    // built - just like a stack of plates (the last one placed on top
    // is the first one you take off). So as main() ends, destruction
    // order is:   prvc, prc, pc, E, S, M, A
    // And for a compound object like E or S, ITS OWN destructor runs
    // first, then its immediate parent's, then the grandparent's -
    // child always before parent (the opposite order from how they
    // were built).

    return 0;
} // <- everything local is destroyed right here, bottom to top