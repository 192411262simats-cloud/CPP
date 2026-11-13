#include <iostream>
#include <string>
#include <stdexcept>

class Prescription {
private:
    int n;
    std::string* medicines;

public:
    explicit Prescription(int count)
        : n(count), medicines(count > 0 ? new std::string[count] : nullptr) {
        if (count < 0) {
            throw std::invalid_argument("Negative medicine count");
        }
    }

    // Deep-copy constructor
    Prescription(const Prescription& other)
        : n(other.n),
          medicines(other.n > 0 ? new std::string[other.n] : nullptr) {
        for (int i = 0; i < n; ++i) {
            medicines[i] = other.medicines[i];
        }
    }

    // Deep-copy assignment operator
    Prescription& operator=(const Prescription& other) {
        if (this == &other) {
            return *this;
        }

        std::string* fresh =
            other.n > 0 ? new std::string[other.n] : nullptr;

        for (int i = 0; i < other.n; ++i) {
            fresh[i] = other.medicines[i];
        }

        delete[] medicines;
        medicines = fresh;
        n = other.n;
        return *this;
    }

    // Destructor
    ~Prescription() {
        delete[] medicines;
    }

    void set(int i, const std::string& medicine) {
        if (i < 0 || i >= n) {
            throw std::out_of_range("Invalid index");
        }
        medicines[i] = medicine;
    }

    std::string get(int i) const {
        if (i < 0 || i >= n) {
            throw std::out_of_range("Invalid index");
        }
        return medicines[i];
    }
};

int main() {
    Prescription p(2);
    p.set(0, "Paracetamol");
    p.set(1, "ORS");

    Prescription q = p;       // Copy constructor
    q.set(1, "Cetirizine");

    Prescription r(1);
    r = p;                    // Copy assignment

    p.set(0, "Ibuprofen");

    std::cout << p.get(0) << ' ' << p.get(1) << " | "
              << q.get(0) << ' ' << q.get(1) << " | "
              << r.get(0) << ' ' << r.get(1) << '\n';

    // Self-assignment test
    p = p;

    return 0;
}
