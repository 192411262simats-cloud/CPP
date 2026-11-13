#include <iostream>
#include <stdexcept>

class Event {
private:
    int rows, seats;
    char** map;
    int booked;

public:
    Event(int r, int s) : rows(r), seats(s), map(nullptr), booked(0) {
        if (r < 0 || s < 0) {
            throw std::invalid_argument("Negative dimensions");
        }

        if (rows == 0 || seats == 0) {
            std::cout << "Event created with an empty seat map\n";
            return;
        }

        map = new char*[rows]{};

        try {
            for (int i = 0; i < rows; ++i) {
                map[i] = new char[seats];
                for (int j = 0; j < seats; ++j) {
                    map[i][j] = 'O';
                }
            }
        }
        catch (...) {
            for (int i = 0; i < rows; ++i) {
                delete[] map[i];
            }
            delete[] map;
            map = nullptr;
            throw;
        }

        std::cout << "Event created: " << rows << " x " << seats << '\n';
    }

    bool book(int r, int s) {
        if (r < 0 || r >= rows || s < 0 || s >= seats) {
            throw std::out_of_range("Seat index out of range");
        }
        if (map[r][s] == 'B') {
            return false;
        }
        map[r][s] = 'B';
        ++booked;
        return true;
    }

    bool cancel(int r, int s) {
        if (r < 0 || r >= rows || s < 0 || s >= seats) {
            throw std::out_of_range("Seat index out of range");
        }
        if (map[r][s] == 'O') {
            return false;
        }
        map[r][s] = 'O';
        --booked;
        return true;
    }

    void display() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < seats; ++j) {
                std::cout << map[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }

    ~Event() {
        if (map != nullptr) {
            for (int i = 0; i < rows; ++i) {
                delete[] map[i];
            }
            delete[] map;
        }

        std::cout << "Event closed. Booked seats at closing: "
                  << booked << '\n';
    }
};

int main() {
    Event localEvent(2, 3);       // Stack object
    localEvent.book(0, 1);
    localEvent.book(1, 2);
    localEvent.cancel(0, 1);
    localEvent.display();

    {
        Event blockEvent(1, 2);   // Block-scope object
        blockEvent.book(0, 0);
    }                             // Destroyed here

    Event* heapEvent = new Event(2, 2);
    heapEvent->book(1, 1);
    delete heapEvent;             // Explicit destruction

    Event emptyEvent(0, 5);       // Zero-row test

    return 0;
}
