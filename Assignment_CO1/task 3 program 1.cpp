#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double amount = 0.1 + 0.2;

    cout << setprecision(17);
    cout << "Floating Point: " << amount << endl;

    long long paise = 10 + 20;

    cout << "Integer Paise: "
         << paise << " paise" << endl;

    return 0;
}