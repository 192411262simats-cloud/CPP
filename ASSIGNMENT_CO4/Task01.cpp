#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Staff {
protected:
    std::string name;
    int id;

public:
    Staff(const std::string& n, int i) : name(n), id(i) {}
    virtual double pay() const = 0;

    virtual void print() const {
        std::cout << name << " (" << id << "): " << pay() << '\n';
    }

    virtual ~Staff() = default;
};

class Professor : public Staff {
    double basic, research;
    static constexpr double DA_RATE = 0.42;

public:
    Professor(const std::string& n, int i, double b, double r)
        : Staff(n, i), basic(b), research(r) {}

    double pay() const override {
        return basic + basic * DA_RATE + research;
    }
};

class LabAssistant : public Staff {
    double basic;
    static constexpr double DA_RATE = 0.42;

public:
    LabAssistant(const std::string& n, int i, double b)
        : Staff(n, i), basic(b) {}

    double pay() const override {
        return basic + basic * DA_RATE;
    }
};

class GuestFaculty : public Staff {
    double hours, rate;

public:
    GuestFaculty(const std::string& n, int i, double h, double r)
        : Staff(n, i), hours(h), rate(r) {}

    double pay() const override {
        return hours * rate;
    }
};

int main() {
    std::vector<std::unique_ptr<Staff>> payroll;

    payroll.push_back(std::make_unique<Professor>("Anita", 101, 50000, 8000));
    payroll.push_back(std::make_unique<LabAssistant>("Ravi", 102, 30000));
    payroll.push_back(std::make_unique<GuestFaculty>("Meera", 103, 20, 1500));

    for (const auto& member : payroll) {
        member->print();
    }
    return 0;
}
