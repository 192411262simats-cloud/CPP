#include <iostream>
#include <chrono>

class CircularHistory {
private:
    int* data;
    int capacity;
    int count;
    int start;

public:
    explicit CircularHistory(int cap)
        : data(new int[cap]{}), capacity(cap), count(0), start(0) {}

    ~CircularHistory() {
        delete[] data;
    }

    CircularHistory(const CircularHistory&) = delete;
    CircularHistory& operator=(const CircularHistory&) = delete;

    void add(int value) {
        if (count < capacity) {
            int position = (start + count) % capacity;
            data[position] = value;
            ++count;
        } else {
            data[start] = value;
            start = (start + 1) % capacity;
        }
    }

    void print() const {
        for (int i = 0; i < count; ++i) {
            int position = (start + i) % capacity;
            std::cout << data[position] << ' ';
        }
        std::cout << '\n';
    }
};

int main() {
    const int capacity = 10;
    CircularHistory history(capacity);

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
