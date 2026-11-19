#include <iostream>
#include <memory>
#include <vector>

class Account {
public:
    virtual double rate() const {
        return 3.5;
    }

    virtual ~Account() = default;
};

class SeniorAccount : public Account {
    std::vector<double> history;

public:
    SeniorAccount() : history(100, 0.0) {}

    double rate() const override {
        return 4.0;
    }
};

int main() {
    std::vector<std::unique_ptr<Account>> accounts;

    accounts.push_back(std::make_unique<Account>());
    accounts.push_back(std::make_unique<SeniorAccount>());

    for (const auto& account : accounts) {
        std::cout << account->rate() << '\n';
    }
    return 0;
}
