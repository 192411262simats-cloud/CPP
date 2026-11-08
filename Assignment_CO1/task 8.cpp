#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int zone, hour;
    long long balance = 10000;
    long long fare;

    cout << "Enter Zone: ";
    cin >> zone;

    cout << "Enter Hour: ";
    cin >> hour;

    if (hour < 0 || hour > 23) {
        cout << "Invalid Hour";
        return 0;
    }

    switch (zone) {
        case 1: fare = 1000; break;
        case 2: fare = 2000; break;
        case 3: fare = 3000; break;

        default:
            cout << "Invalid Zone";
            return 0;
    }

    bool peak = (hour >= 8 && hour < 10) ||
                (hour >= 17 && hour < 20);

    if (peak)
        fare += fare * 20 / 100;

    if (balance - fare >= 5000) {
        balance -= fare;

        cout << "\n----- JOURNEY REPORT -----" << endl;

        cout << "Fare: Rs "
             << fixed << setprecision(2)
             << fare / 100.0 << endl;

        cout << "Remaining Balance: Rs "
             << balance / 100.0 << endl;

        cout << "Journey Status: Approved";
    } else {
        cout << "Journey Denied";
    }

    return 0;
}