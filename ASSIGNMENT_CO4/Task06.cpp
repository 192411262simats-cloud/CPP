#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Vehicle {
protected:
    std::string registration;
    double dailyRate;
    bool rented = false;

public:
    Vehicle(const std::string& reg, double rate)
        : registration(reg), dailyRate(rate) {}

    virtual std::string typeName() const = 0;
    virtual double rentalCharge(int days) const = 0;
    virtual ~Vehicle() = default;

    const std::string& getRegistration() const {
        return registration;
    }

    bool isRented() const {
        return rented;
    }

    bool rent() {
        if (rented) return false;
        rented = true;
        return true;
    }

    bool returnVehicle() {
        if (!rented) return false;
        rented = false;
        return true;
    }

    void list() const {
        std::cout << typeName() << " | " << registration
                  << " | daily rate: " << dailyRate
                  << " | " << (rented ? "Rented" : "Available") << '\n';
    }
};

class Bicycle : public Vehicle {
public:
    Bicycle(const std::string& r, double rate) : Vehicle(r, rate) {}

    std::string typeName() const override { return "Bicycle"; }

    double rentalCharge(int days) const override {
        return dailyRate * days;
    }
};

class MotorVehicle : public Vehicle {
protected:
    double fuelOrChargeLevel;
    std::string serviceDueDate;

public:
    MotorVehicle(const std::string& r, double rate, double level,
                 const std::string& serviceDate)
        : Vehicle(r, rate),
          fuelOrChargeLevel(level),
          serviceDueDate(serviceDate) {}
};

class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(const std::string& r, double rate, double fuel,
               const std::string& date)
        : MotorVehicle(r, rate, fuel, date) {}

    std::string typeName() const override { return "TwoWheeler"; }

    double rentalCharge(int days) const override {
        return dailyRate * days;
    }
};

class Car : public MotorVehicle {
protected:
    int seatingCapacity;

public:
    Car(const std::string& r, double rate, double fuel,
        const std::string& date, int seats)
        : MotorVehicle(r, rate, fuel, date), seatingCapacity(seats) {}

    std::string typeName() const override { return "Car"; }

    double rentalCharge(int days) const override {
        return dailyRate * days;
    }
};

class ElectricCar : public Car {
    double batteryCapacityKWh;
    double pricePerKWh;

public:
    ElectricCar(const std::string& r, double rate, double charge,
                const std::string& date, int seats,
                double batteryKWh, double kWhPrice)
        : Car(r, rate, charge, date, seats),
          batteryCapacityKWh(batteryKWh),
          pricePerKWh(kWhPrice) {}

    std::string typeName() const override { return "ElectricCar"; }

    double rentalCharge(int days) const override {
        return dailyRate * days + batteryCapacityKWh * pricePerKWh;
    }
};

// Extension: new class added without modifying existing vehicle classes.
class ElectricBus : public Vehicle {
    int seats;
    double batteryCapacityKWh;

public:
    ElectricBus(const std::string& r, double rate, int s, double battery)
        : Vehicle(r, rate), seats(s), batteryCapacityKWh(battery) {}

    std::string typeName() const override { return "ElectricBus"; }

    double rentalCharge(int days) const override {
        return dailyRate * days + batteryCapacityKWh * 0.20;
    }
};

int main() {
    std::vector<std::unique_ptr<Vehicle>> ownedFleet;

    ownedFleet.push_back(std::make_unique<Bicycle>("BI-101", 100));
    ownedFleet.push_back(std::make_unique<TwoWheeler>(
        "TW-202", 250, 80, "2026-12-01"));
    ownedFleet.push_back(std::make_unique<Car>(
        "CA-303", 1500, 60, "2026-12-15", 5));
    ownedFleet.push_back(std::make_unique<ElectricCar>(
        "EV-404", 1800, 90, "2026-12-20", 5, 60, 0.20));
    ownedFleet.push_back(std::make_unique<ElectricBus>(
        "EB-505", 5000, 30, 300));

    // Array of base-class pointers for uniform fleet processing.
    std::vector<Vehicle*> fleet;
    for (const auto& vehicle : ownedFleet) {
        fleet.push_back(vehicle.get());
    }

    std::cout << "FLEET LIST\n";
    for (Vehicle* vehicle : fleet) {
        vehicle->list();
    }

    std::cout << "\nRENT AND RETURN DEMONSTRATION\n";
    Vehicle* selected = nullptr;

    for (Vehicle* vehicle : fleet) {
        if (vehicle->getRegistration() == "CA-303") {
            selected = vehicle;
            break;
        }
    }

    if (selected != nullptr && selected->rent()) {
        std::cout << "Rented " << selected->getRegistration() << '\n';

        const int bookedDays = 2;
        const int actualDays = 4;
        const double lateFeePerDay = 200.0;

        const double base = selected->rentalCharge(bookedDays);
        const double late =
            std::max(0, actualDays - bookedDays) * lateFeePerDay;

        if (selected->returnVehicle()) {
            std::cout << "Base charge: " << base << '\n';
            std::cout << "Late charge: " << late << '\n';
            std::cout << "Total charge: " << base + late << '\n';
        }
    }

    std::cout << "\nFLEET AFTER RETURN\n";
    for (Vehicle* vehicle : fleet) {
        vehicle->list();
    }

    return 0;
}
