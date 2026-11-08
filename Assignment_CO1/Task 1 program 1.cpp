#include <iostream>
using namespace std;

class SmartCard {
private:
    long long balance;

public:
    SmartCard(long long b) {
        balance = b;
    }

    bool canTravel(long long fare) {
        return balance - fare >= 5000;
    }

    bool deduct(long long fare) {
        if (canTravel(fare)) {
            balance -= fare;
            return true;
        }
        return false;
    }

    long long getBalance() {
        return balance;
    }
};

int main() {
    SmartCard card(10000);

    if (card.deduct(3000))
        cout << "Journey Successful" << endl;
    else
        cout << "Journey Denied" << endl;

    cout << "Remaining Balance: "
         << card.getBalance() << " paise";

    return 0;
}