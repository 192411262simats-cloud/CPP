#include <iostream>
#include <string>

class Person {
protected:
    std::string name;
    int age;

public:
    Person(const std::string& n, int a) : name(n), age(a) {}
};

class Address {
    std::string city;
    int pin;

public:
    Address(const std::string& c, int p) : city(c), pin(p) {}

    std::string str() const {
        return city + "-" + std::to_string(pin);
    }
};

class Student : public Person {
    long long regNo;
    Address home;

public:
    Student(const std::string& n, int a, long long r,
            const std::string& city, int pin)
        : Person(n, a), regNo(r), home(city, pin) {}

    void print() const {
        std::cout << regNo << ' ' << name << " (" << age << ") "
                  << home.str() << '\n';
    }
};

class Engine {
public:
    Engine() { std::cout << "Engine "; }
    ~Engine() { std::cout << "~Engine "; }
};

class Vehicle {
public:
    Vehicle() { std::cout << "Vehicle "; }
    ~Vehicle() { std::cout << "~Vehicle"; }
};

class Car : public Vehicle {
    Engine engine;

public:
    Car() { std::cout << "Car "; }
    ~Car() { std::cout << "~Car "; }
};

int main() {
    Student s("Kavya", 19, 192311001, "Salem", 636001);
    s.print();

    {
        Car c;
        std::cout << "| ";
    }
    std::cout << '\n';
    return 0;
}
