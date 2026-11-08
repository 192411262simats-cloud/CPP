#include <iostream>
using namespace std;

enum class Zone {
    Inner,
    Middle,
    Outer
};

constexpr long long BASE_FARE[] = {
    1000, 2000, 3000
};

constexpr int PEAK_SURCHARGE = 20;

constexpr long long MIN_BALANCE = 5000;

int main() {
    cout << "Metro Fare Configuration" << endl;

    cout << "Inner Fare: "
         << BASE_FARE[0] << endl;

    cout << "Middle Fare: "
         << BASE_FARE[1] << endl;

    cout << "Outer Fare: "
         << BASE_FARE[2] << endl;

    cout << "Peak Surcharge: "
         << PEAK_SURCHARGE << "%" << endl;

    cout << "Minimum Balance: "
         << MIN_BALANCE << endl;

    return 0;
}