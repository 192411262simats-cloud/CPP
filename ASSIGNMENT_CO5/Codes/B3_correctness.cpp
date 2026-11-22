#include <iostream>
#include <memory>
#include <vector>

struct Base {
    virtual double total() const = 0;
    virtual ~Base() = default;
};

struct VOP : Base {
    double c, t;
    VOP(double a, double b) : c(a), t(b) {}
    double total() const override { return c + t; }
};

struct VIP : Base {
    int d;
    double r, s;
    VIP(int a, double b, double c) : d(a), r(b), s(c) {}
    double total() const override { return d * r + s; }
};

struct VDC : Base {
    double p, m;
    VDC(double a, double b) : p(a), m(b) {}
    double total() const override { return p + m; }
};

struct VEM : Base {
    double b, mins, r;
    VEM(double a, double x, double y) : b(a), mins(x), r(y) {}
    double total() const override { return b + mins * r; }
};

struct Record {
    int type;
    double a, b, c;

    double total() const {
        switch (type) {
            case 0: return a + b;
            case 1: return a * b + c;
            case 2: return a + b;
            default: return a + b * c;
        }
    }
};

int main() {
    const std::vector<Record> records = {
        {0,100,50,0}, {1,2,100,20}, {2,300,40,0}, {3,50,3,10},
        {0,200,80,0}, {1,1,250,30}, {2,400,60,0}, {3,100,2,20},
        {0,150,50,0}, {1,3,100,40}
    };

    std::vector<std::unique_ptr<Base>> virtualBills;
    virtualBills.push_back(std::make_unique<VOP>(100,50));
    virtualBills.push_back(std::make_unique<VIP>(2,100,20));
    virtualBills.push_back(std::make_unique<VDC>(300,40));
    virtualBills.push_back(std::make_unique<VEM>(50,3,10));
    virtualBills.push_back(std::make_unique<VOP>(200,80));
    virtualBills.push_back(std::make_unique<VIP>(1,250,30));
    virtualBills.push_back(std::make_unique<VDC>(400,60));
    virtualBills.push_back(std::make_unique<VEM>(100,2,20));
    virtualBills.push_back(std::make_unique<VOP>(150,50));
    virtualBills.push_back(std::make_unique<VIP>(3,100,40));

    double switchSum = 0.0;
    double virtualSum = 0.0;

    for (const auto& item : records)
        switchSum += item.total();
    for (const auto& item : virtualBills)
        virtualSum += item->total();

    std::cout << "Switch total: " << switchSum << '\n';
    std::cout << "Virtual total: " << virtualSum << '\n';

    return (switchSum == virtualSum) ? 0 : 1;
}
