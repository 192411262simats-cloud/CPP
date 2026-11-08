#include <iostream>
using namespace std;

enum class Zone {
    Inner,
    Middle,
    Outer,
    Airport
};

constexpr long long BASE_FARE[] = {
    1000, 2000, 3000, 6000
};

constexpr int PEAK_PERCENT = 20;
constexpr int WEEKEND_DISCOUNT = 10;
constexpr long long MIN_BALANCE = 5000;

class FareCalculator {
public:
    static long long calculateFare(
        Zone zone, int hour, bool weekend) {

        int index = static_cast<int>(zone);

        if (index < 0 || index >= 4)
            return -1;

        long long fare = BASE_FARE[index];

        if (weekend) {
            fare -= fare * WEEKEND_DISCOUNT / 100;
        }
        else if ((hour >= 8 && hour < 10) ||
                 (hour >= 17 && hour < 20)) {

            fare += fare * PEAK_PERCENT / 100;
        }

        return fare;
    }
};

class MonthlyPass {
private:
    bool selectedZones[4];

public:
    MonthlyPass(Zone z1, Zone z2) {
        for (int i = 0; i < 4; i++)
            selectedZones[i] = false;

        selectedZones[static_cast<int>(z1)] = true;
        selectedZones[static_cast<int>(z2)] = true;
    }

    bool allowsTravel(Zone zone) {
        int index = static_cast<int>(zone);

        return index >= 0 && index < 4 &&
               selectedZones[index];
    }
};

class SmartCard {
private:
    long long balance;

public:
    SmartCard(long long amount) {
        balance = amount;
    }

    bool deduct(long long fare) {
        if (fare >= 0 &&
            balance - fare >= MIN_BALANCE) {

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
    SmartCard card(20000);

    MonthlyPass pass(
        Zone::Inner,
        Zone::Middle
    );

    cout << "Namma Metro Smart Card System"
         << endl << endl;

    long long fare1 =
        FareCalculator::calculateFare(
            Zone::Airport, 18, false
        );

    cout << "Airport Peak Fare: "
         << fare1 << " paise" << endl;

    long long fare2 =
        FareCalculator::calculateFare(
            Zone::Airport, 18, true
        );

    cout << "Airport Weekend Fare: "
         << fare2 << " paise" << endl;

    if (pass.allowsTravel(Zone::Inner))
        cout << "Inner Zone: Pass Accepted" << endl;

    if (!pass.allowsTravel(Zone::Airport))
        cout << "Airport: Pass Not Valid" << endl;

    if (card.deduct(fare2))
        cout << "Journey Approved" << endl;
    else
        cout << "Journey Denied" << endl;

    cout << "Remaining Balance: "
         << card.getBalance() << " paise";

    return 0;
}