#include <iostream>

using namespace std;

/*
• Implementuje příklad z přednášky a vytvořte banku s mnoha klienty a účty.
Zaměřte se na pochopení principu zastupitelnosti a na to, jak fungují konstruktory v dědičnosti.
• Navrhněte a implementujte další jednoduché příklady dědičnosti s rozšířením společného
stavu a chování,jako například Auto, Osobní auto, Nákladní auto.
*/

class Vehicle
{
private:
string brand;
int horsepower;
float displacement;
int seats; 
public:
Vehicle(string b, int h, float d, int s);
~Vehicle();

int GetPower();
int GetSeats();
string GetName();
};

class Car : public Vehicle
{
private:
float wheelBase;
string powertrain;
public:
Car(string b, int h, float d, int s, float w, string p);
string GetPowerTrain();
};

class Motorbike : public Vehicle
{
private:
bool storage;
string licenseReq;
public:
Motorbike(string b, int h, float d, int s, bool st, string l);
};

class Boat : public Vehicle
{
private:
bool cabin;
bool speedboat;
string name;
public:
Boat(string b, int h, float d, int s, bool c, bool sp, string n);

bool IsSpeedBoat();
};

Vehicle::Vehicle(string b, int h, float d, int s)
{
    this->brand = b;
    this->horsepower = h;
    this->displacement = d;
    this->seats = s;
}

Vehicle::~Vehicle()
{
    
}

Car::Car(string b, int h, float d, int s, float w, string p) : Vehicle(b, h, d, s)
{
    this->wheelBase = w;
    this->powertrain = p;
}

Motorbike::Motorbike(string b, int h, float d, int s, bool st, string l) : Vehicle(b, h, d, s)
{
    this->storage = st;
    this->licenseReq = l;
}

Boat::Boat(string b, int h, float d, int s, bool c, bool sp, string n) : Vehicle(b, h, d, s)
{
    this->cabin = c;
    this->speedboat = sp;
    this->name = n;
}

int Vehicle::GetPower()
{
    return this->horsepower;
}

int Vehicle::GetSeats()
{
    return this->seats;
}

string Vehicle::GetName()
{
    return this->brand;
}

string Car::GetPowerTrain()
{
    return this->powertrain;
}
int main()
{
    Vehicle *Bicycle = new Vehicle("Maxbike", 0, 0, 1);
    Vehicle *Tractor = new Vehicle("John Deere", 40, 0.600, 1);
    Car *Civic = new Car("Honda", 160, 1.600, 5, 1.8, "FWD");
    Car *FairladyZ = new Car("Nissan", 200, 2.500, 2, 2.1, "RWD");;
    Motorbike *CBR = new Motorbike("Honda", 60, 0.600, 2, false, "A2");
    Motorbike *Ninja = new Motorbike("Kawasaki", 40, 0.300, 2, false, "A1");
    Boat *Titanic = new Boat("Titanic", 40000, 0, 2240, true, false, "Titanic");
    Boat *SliceOfLife = new Boat("Century", 40, 0.600, 4, true, true, "Slice of Life");

    cout << "The titanic was capable of transporting " << Titanic->GetSeats() << " passengers \n";
    cout << "The Fairlady Z's powertrain is: " << FairladyZ->GetPowerTrain();
    cout << " and has " << FairladyZ->GetPower() << " horsepower\n";
    cout << "Our tractor was manufactured by " << Tractor->GetName() << endl;

    return 0;
}