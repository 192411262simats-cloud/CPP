#include <iostream>
#include <stdexcept>

void validate(double amount) {
    if (amount < 0.0)
        throw std::invalid_argument("negative");
    if (amount > 1e6)
        throw std::out_of_range("too large");
    std::cout << "ok ";
}

void process(double amount) {
    try {
        validate(amount);
    } catch (const std::out_of_range& e) {
        std::cout << "[log " << e.what() << "] ";
        throw; // Rethrow the original exception.
    }
}

int main() {
    for (double amount : {100.0, -5.0, 2e6}) {
        try {
            process(amount);
            std::cout << "done ";
        } catch (const std::exception& e) {
            std::cout << "caught " << e.what() << ' ';
        }
    }
    std::cout << '\n';
    return 0;
}
