#include <iostream>
using namespace std;

long long balance = 10000;

void deductFare(long long fare) {
    if (balance - fare >= 5000) {
        balance -= fare;
        cout << "Procedural Journey Successful" << endl;
    } else {
        cout << "Insufficient Balance" << endl;
    }
}

class SmartCard {
private:
    long long balance;

public:
    SmartCard(long long b) {
        balance = b;
    }

    void deduct(long long fare) {
        if (balance - fare >= 5000) {
            balance -= fare;
            cout << "OOP Journey Successful" << endl;
        } else {
            cout << "Insufficient Balance" << endl;
        }
    }

    void display() {
        cout << "OOP Balance: " << balance << endl;
    }
};

int main() {
    deductFare(3000);

    cout << "Procedural Balance: "
         << balance << endl;

    SmartCard card(10000);

    card.deduct(3000);
    card.display();

    return 0;
}