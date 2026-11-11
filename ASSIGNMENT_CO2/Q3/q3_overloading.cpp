#include <iostream>

struct Parcel {
    double weightKg;
    bool express;
    bool insured;
};

double calculate(double kg, bool express, bool insured) {
    double amount = kg * 40.0;

    if (express) {
        amount += 50.0;
    }

    if (insured) {
        amount += 20.0;
    }

    return amount;
}

// Weight is supplied in grams.
double charge(int grams, bool express = false, bool insured = false) {
    return calculate(grams / 1000.0, express, insured);
}

// Weight is supplied in kilograms.
double charge(double kg, bool express = false, bool insured = false) {
    return calculate(kg, express, insured);
}

// Parcel object overload.
double charge(const Parcel& parcel) {
    return calculate(parcel.weightKg, parcel.express, parcel.insured);
}

int main() {
    Parcel parcel{1.5, true, true};

    std::cout << "charge(2): " << charge(2) << '\n';
    std::cout << "charge(2.0f): " << charge(2.0f) << '\n';
    std::cout << "charge(2.0): " << charge(2.0) << '\n';
    std::cout << "charge(500, true): " << charge(500, true) << '\n';
    std::cout << "charge(1.5, false, true): "
              << charge(1.5, false, true) << '\n';
    std::cout << "charge(parcel): " << charge(parcel) << '\n';

    return 0;
}
