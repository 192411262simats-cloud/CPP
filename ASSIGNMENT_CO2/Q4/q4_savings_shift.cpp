#include <iostream>
#include <string>

class SavingsAccount {
private:
    std::string accountNumber;
    double balance;
    double transactions[10]{};
    int count;

    void record(double amount) {
        if (count < 10) {
            transactions[count] = amount;
            ++count;
        } else {
            // Discard the oldest transaction by shifting the array.
            for (int i = 1; i < 10; ++i) {
                transactions[i - 1] = transactions[i];
            }
            transactions[9] = amount;
        }
    }

public:
    SavingsAccount(const std::string& number, double openingBalance)
        : accountNumber(number), balance(openingBalance), count(0) {}

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

    void miniStatement() const;
    double getBalance() const {
        return balance;
    }
};

void SavingsAccount::miniStatement() const {
    std::cout << "Account: " << accountNumber << '\n';
    std::cout << "Balance: " << balance << '\n';
    std::cout << "Recent transactions (oldest to newest):\n";

    for (int i = 0; i < count; ++i) {
        std::cout << transactions[i] << '\n';
    }
}

int main() {
    SavingsAccount account("SA1001", 5000.0);

    account.deposit(500);
    account.withdraw(200);
    account.deposit(1000);

    // Add enough transactions to demonstrate the 10-entry limit.
    for (int i = 1; i <= 9; ++i) {
        account.deposit(i * 100.0);
    }

    account.miniStatement();
    return 0;
}
