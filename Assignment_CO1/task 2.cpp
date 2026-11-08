#include <iostream>
using namespace std;

enum class Zone {
    Inner,
    Middle,
    Outer
};

constexpr int INNER_FARE = 1000;
constexpr int MIDDLE_FARE = 2000;
constexpr int OUTER_FARE = 3000;

constexpr int PEAK_SURCHARGE = 20;

int main() {
    Zone z = Zone::Outer;

    cout << "Inner Fare: " << INNER_FARE << endl;
    cout << "Middle Fare: " << MIDDLE_FARE << endl;
    cout << "Outer Fare: " << OUTER_FARE << endl;

    cout << "Peak Surcharge: "
         << PEAK_SURCHARGE << "%" << endl;

    cout << "Selected Zone: "
         << static_cast<int>(z) + 1;

    return 0;
}