#include <iostream>
using namespace std;

int main() {
    long long balance = 20000;
    long long totalFare = 0;

    int zones[] = {1, 2, 3, 1, 3};
    int hours[] = {12, 12, 18, 9, 14};

    for (int i = 0; i < 5; i++) {
        int fare;

        switch (zones[i]) {
            case 1: fare = 1000; break;
            case 2: fare = 2000; break;
            case 3: fare = 3000; break;
            default: continue;
        }

        if ((hours[i] >= 8 && hours[i] < 10) ||
            (hours[i] >= 17 && hours[i] < 20)) {
            fare += fare * 20 / 100;
        }

        if (balance - fare >= 5000) {
            balance -= fare;
            totalFare += fare;

            cout << "Journey " << i + 1
                 << ": Approved, Fare = "
                 << fare << endl;
        } else {
            cout << "Journey " << i + 1
                 << ": Denied" << endl;
        }
    }

    cout << "\nTotal Fare: " << totalFare << endl;
    cout << "Final Balance: " << balance << endl;

    return 0;
}