#include <iostream>

void applyByValue(long long fee, int percent) {
    fee -= fee * percent / 100;
}

void applyConcession(long long& fee, int percent) {
    fee -= fee * percent / 100;
}

void applyByPointer(long long* fee, int percent) {
    if (fee != nullptr) {
        *fee -= (*fee) * percent / 100;
    }
}

int main() {
    long long valueFee = 45000;
    long long referenceFee = 45000;
    long long pointerFee = 45000;

    applyByValue(valueFee, 10);
    applyConcession(referenceFee, 10);
    applyByPointer(&pointerFee, 10);

    std::cout << "after call by value : " << valueFee << '\n';
    std::cout << "after call by reference: " << referenceFee << '\n';
    std::cout << "after call by pointer: " << pointerFee << '\n';

    return 0;
}
