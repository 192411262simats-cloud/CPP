#include <iostream>
using namespace std;

int main() {
    int zone, hour;
    int fare = 0;

    cout << "Enter Zone (1-3): ";
    cin >> zone;

    cout << "Enter Hour (0-23): ";
    cin >> hour;

    switch (zone) {
        case 1:
            fare = 1000;
            break;

        case 2:
            fare = 2000;
            break;

        case 3:
            fare = 3000;
            break;

        default:
            cout << "Invalid Zone";
            return 0;
    }

    if (hour < 0 || hour > 23) {
        cout << "Invalid Time";
        return 0;
    }

    if ((hour >= 8 && hour < 10) ||
        (hour >= 17 && hour < 20)) {

        fare = fare + (fare * 20 / 100);
    }

    cout << "Total Fare: " << fare << " paise";

    return 0;
}