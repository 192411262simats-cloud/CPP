#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double total = 0.0;

    for (int i = 0; i < 1000000; i++) {
        total += 0.1;
    }

    cout << setprecision(17);
    cout << "Floating Point Total: "
         << total << endl;

    long long exactTotal = 0;

    for (int i = 0; i < 1000000; i++) {
        exactTotal += 10;
    }

    cout << "Integer Total: "
         << exactTotal << " paise" << endl;

    return 0;
}