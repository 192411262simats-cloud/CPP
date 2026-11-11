#include <iostream>
#include <string>

class SavingsAccount {
private:
    static const int CAPACITY = 10;

    std::string accountNumber;
    double balance;
    double transactions[CAPACITY]{};
    int count;
    int start; // Physical index of the oldest transaction.

    void record(double amount) {
        if (count < CAPACITY) {
            int position = (start + count) % CAPACITY;
            transactions[position] = amount;
            ++count;
        } else {
            transactions[start] = amount;
            start = (start + 1) % CAPACITY;
        }
    }

public:
    SavingsAccount(const std::string& number, double openingBalance)
        : accountNumber(number), balance(openingBalance),
          count(0), start(0) {}

    void deposit(double amount) {
        if (amount <= 0) {
            std::cout << "Invalid deposit amount\n";
            return;
        }

        balance += amount;
        record(amount);
    }

    void withdraw(double amount) {
        if (amount <= 0 || amount > balance) {
            std::cout << "Invalid withdrawal amount\n";
            return;
        }

        balance -= amount;
        record(-amount);
    }

    void miniStatement() const {
        std::cout << "Account: " << accountNumber << '\n';
        std::cout << "Balance: " << balance << '\n';
        std::cout << "Recent transactions (oldest to newest):\n";

        for (int i = 0; i < count; ++i) {
            int position = (start + i) % CAPACITY;
            std::cout << transactions[position] << '\n';
        }
    }
};

int main() {
    SavingsAccount account("SA2001", 10000.0);

    // Fifteen deposits; only the latest ten should remain.
    for (int i = 1; i <= 15; ++i) {
        account.deposit(i * 100.0);
    }

    account.miniStatement();
    return 0;
}
