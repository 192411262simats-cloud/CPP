#include <iostream>
using namespace std;

class Passenger {
public:
    virtual int getDiscount() {
        return 0;
    }
};

class StudentPassenger : public Passenger {
public:
    int getDiscount() override {
        return 10;
    }
};

class SeniorPassenger : public Passenger {
public:
    int getDiscount() override {
        return 15;
    }
};

int main() {
    StudentPassenger student;
    SeniorPassenger senior;

    cout << "Student Discount: "
         << student.getDiscount() << "%" << endl;

    cout << "Senior Discount: "
         << senior.getDiscount() << "%" << endl;

    return 0;
}