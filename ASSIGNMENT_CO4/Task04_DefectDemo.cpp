// Diagnostic-only example: this program contains undefined behaviour.
// Do not use this defective pattern in submitted production code.
#include <iostream>

class Account {
public:
    double rate() const {
        return 3.5;
    }

    ~Account() {
        std::cout << "Account destructor\n";
    }
};

class SeniorAccount : public Account {
    double* history = new double[100];

public:
    double rate() const {
        return 4.0;
    }

    ~SeniorAccount() {
        std::cout << "SeniorAccount destructor\n";
        delete[] history;
    }
};

int main() {
    Account* p = new SeniorAccount;
    std::cout << p->rate() << '\n'; // Calls Account::rate(): non-virtual
    delete p;                       // Undefined behaviour: non-virtual base dtor
    return 0;
}
