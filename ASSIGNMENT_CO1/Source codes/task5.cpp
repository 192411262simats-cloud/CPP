#include <iostream>
using namespace std;

int main() {
    int x = 5, y = 3;

    cout << "Addition: " << x + y << endl;
    cout << "Multiplication: " << x * y << endl;

    cout << "Precedence: " << x + y * 2 << endl;

    cout << "Comparison: " << (x > y) << endl;

    cout << "Modulus: " << x % y << endl;

    int a = x++ + ++y;

    cout << "Expression Result: " << a << endl;
    cout << "X: " << x << endl;
    cout << "Y: " << y << endl;

    return 0;
}