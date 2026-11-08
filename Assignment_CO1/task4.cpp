#include <iostream>
using namespace std;

int main() {
    int a = 7, b = 2;

    double c = a / b;
    double d = static_cast<double>(a) / b;

    cout << c << " " << d << endl;

    char ch = 'A' + 2;

    cout << ch << " " << ch + 1 << endl;

    bool flag = 5;

    cout << flag << " " << boolalpha << flag << endl;

    return 0;
}