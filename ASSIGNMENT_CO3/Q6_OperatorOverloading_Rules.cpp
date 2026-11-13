#include <cstring>
#include <iostream>

class Text {
private:
    char* data;

public:
    Text(const char* value = "") {
        if (value == nullptr) {
            value = "";
        }

        data = new char[std::strlen(value) + 1];
        std::strcpy(data, value);
    }

    // Deep-copy constructor
    Text(const Text& other) {
        data = new char[std::strlen(other.data) + 1];
        std::strcpy(data, other.data);
    }

    // Copy assignment operator
    Text& operator=(const Text& other) {
        if (this == &other) {
            return *this;
        }

        char* fresh = new char[std::strlen(other.data) + 1];
        std::strcpy(fresh, other.data);

        delete[] data;
        data = fresh;
        return *this;
    }

    ~Text() {
        delete[] data;
    }

    Text operator+(const Text& other) const {
        std::size_t n1 = std::strlen(data);
        std::size_t n2 = std::strlen(other.data);

        char* buffer = new char[n1 + n2 + 1];
        std::strcpy(buffer, data);
        std::strcat(buffer, other.data);

        Text result(buffer);
        delete[] buffer;
        return result;
    }

    bool operator==(const Text& other) const {
        return std::strcmp(data, other.data) == 0;
    }

    bool operator!=(const Text& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& out,
                                    const Text& value) {
        return out << value.data;
    }
};

int main() {
    Text a("Hello ");
    Text b("World");
    Text c = a + b;

    std::cout << c << '\n';
    std::cout << std::boolalpha
              << (c == Text("Hello World")) << '\n';

    Text empty;
    std::cout << "Empty=[" << empty << "]\n";

    a = a;  // Self-assignment test
    std::cout << a << '\n';

    Text longMessage("This is a longer SMS gateway message used for testing.");
    Text copy = longMessage;
    std::cout << copy << '\n';

    return 0;
}
