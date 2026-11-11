#include <iostream>
#include <cstdlib>

class Time {
private:
    int h;
    int m;

public:
    Time(int hh, int mm) : h(hh), m(mm) {}

    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
};

int minutesBetween(const Time& a, const Time& b) {
    int first = a.h * 60 + a.m;
    int second = b.h * 60 + b.m;
    return std::abs(first - second);
}

bool earlier(const Time& a, const Time& b) {
    if (a.h != b.h) {
        return a.h < b.h;
    }

    return a.m < b.m;
}

int main() {
    Time departure(9, 45);
    Time arrival(13, 10);

    std::cout << minutesBetween(departure, arrival) << ' '
              << std::boolalpha
              << earlier(arrival, departure) << '\n';

    Time beforeNoon(11, 50);
    Time afterNoon(12, 10);
    Time sameA(12, 30);
    Time sameB(12, 30);

    std::cout << minutesBetween(beforeNoon, afterNoon) << ' '
              << earlier(beforeNoon, afterNoon) << '\n';

    std::cout << minutesBetween(sameA, sameB) << ' '
              << earlier(sameA, sameB) << '\n';

    return 0;
}
