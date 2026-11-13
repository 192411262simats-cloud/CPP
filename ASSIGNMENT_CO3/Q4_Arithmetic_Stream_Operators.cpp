#include <iomanip>
#include <iostream>

class Money {
private:
    long long paise;

public:
    Money(long long rupees = 0, int p = 0)
        : paise(rupees * 100 + p) {}

    Money operator+(const Money& other) const {
        Money result;
        result.paise = paise + other.paise;
        return result;
    }

    Money operator-(const Money& other) const {
        Money result;
        result.paise = paise - other.paise;
        return result;
    }

    Money& operator+=(const Money& other) {
        paise += other.paise;
        return *this;
    }

    bool operator==(const Money& other) const {
        return paise == other.paise;
    }

    bool operator<(const Money& other) const {
        return paise < other.paise;
    }

    friend std::ostream& operator<<(std::ostream& out,
                                    const Money& amount) {
        long long magnitude = amount.paise < 0
                            ? -amount.paise : amount.paise;

        if (amount.paise < 0) {
            out << "-";
        }

        out << "Rs " << magnitude / 100 << '.'
            << std::setw(2) << std::setfill('0')
            << magnitude % 100;
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Money& amount) {
        long long rupees;
        int p;

        if (in >> rupees >> p) {
            amount.paise = rupees * 100 + p;
        }
        return in;
    }
};

int main() {
    Money a(120, 75), b(79, 25);
    Money c = a + b;

    std::cout << c << '\n' << std::boolalpha
              << (c == Money(200)) << '\n';

    Money x(0, 75), y(0, 50);
    std::cout << (x + y) << '\n';

    Money refund = Money(2, 0) - Money(3, 50);
    std::cout << refund << '\n';

    return 0;
}
