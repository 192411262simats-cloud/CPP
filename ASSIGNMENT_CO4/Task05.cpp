#include <iomanip>
#include <iostream>
#include <string>

class Cart {
    std::string items[10];
    double prices[10];
    int n = 0;
    double discount = 0.0;

public:
    Cart& add(const std::string& item, double price) {
        if (n < 10) {
            items[n] = item;
            prices[n] = price;
            ++n;
        }
        return *this;
    }

    Cart& setDiscount(double value) {
        this->discount = value;
        return *this;
    }

    double total() const {
        double sum = 0.0;
        for (int i = 0; i < n; ++i) {
            sum += prices[i];
        }
        return sum * (100.0 - discount) / 100.0;
    }
};

class SimpleCart {
    double amount;

public:
    explicit SimpleCart(double value) : amount(value) {}
    double total() const { return amount; }
};

int main() {
    // (a) Direct object, (b) pointer, (c) reference, (d) dynamic object
    Cart direct;
    direct.add("Book", 100.0);
    std::cout << "Direct: " << direct.total() << '\n';

    Cart* ptr = &direct;
    std::cout << "Pointer: " << ptr->total() << '\n';

    Cart& ref = direct;
    std::cout << "Reference: " << ref.total() << '\n';

    Cart* dynamicCart = new Cart;
    dynamicCart->add("Bag", 200.0);
    std::cout << "Dynamic: " << dynamicCart->total() << '\n';
    delete dynamicCart;

    // Method chaining and completed TODOs
    Cart c;
    c.add("Rice", 60).add("Dal", 120).setDiscount(10);
    Cart* p = &c;
    p->add("Oil", 180);
    std::cout << std::fixed << std::setprecision(2)
              << "Discounted total: " << p->total() << '\n';

    // Array of pointers: find the cart with the highest total
    SimpleCart c1(250), c2(480), c3(390);
    SimpleCart* carts[] = {&c1, &c2, &c3};
    const int count = 3;

    int best = 0;
    for (int i = 1; i < count; ++i) {
        if (carts[i]->total() > carts[best]->total()) {
            best = i;
        }
    }
    std::cout << "Highest cart total: " << carts[best]->total() << '\n';
    return 0;
}
