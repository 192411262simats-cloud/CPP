#include <iostream>
#include <chrono>
#include <vector>

class ShiftingHistory {
private:
    int* data;
    int capacity;
    int count;

public:
    explicit ShiftingHistory(int cap)
        : data(new int[cap]{}), capacity(cap), count(0) {}

    ~ShiftingHistory() {
        delete[] data;
    }

    ShiftingHistory(const ShiftingHistory&) = delete;
    ShiftingHistory& operator=(const ShiftingHistory&) = delete;

    void add(int value) {
        if (count < capacity) {
            data[count++] = value;
        } else {
            for (int i = 1; i < capacity; ++i) {
                data[i - 1] = data[i];
            }
            data[capacity - 1] = value;
        }
    }

    void print() const {
        for (int i = 0; i < count; ++i) {
            std::cout << data[i] << ' ';
        }
        std::cout << '\n';
    }
};

int main() {
    const int capacity = 10;
    ShiftingHistory history(capacity);

    for (int i = 1; i <= 15; ++i) {
        history.add(i * 100);
    }

    std::cout << "Latest transactions: ";
    history.print();

    const int operations = 200000;
    const auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < operations; ++i) {
        history.add(i);
    }

    const auto finish = std::chrono::steady_clock::now();
    const double elapsed =
        std::chrono::duration<double, std::milli>(finish - start).count();

    std::cout << "Insertion benchmark (ms): " << elapsed << '\n';
    return 0;
}
