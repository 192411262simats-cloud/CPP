#include <chrono>
#include <cstdint>
#include <exception>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <variant>
#include <vector>

using Clock = std::chrono::steady_clock;

struct Base {
    virtual double total() const = 0;
    virtual ~Base() = default;
};
struct VOP : Base {
    double a, b;
    VOP(double x, double y) : a(x), b(y) {}
    double total() const override { return a + b; }
};
struct VIP : Base {
    double d, r, s;
    VIP(double x, double y, double z) : d(x), r(y), s(z) {}
    double total() const override { return d * r + s; }
};
struct VDC : Base {
    double a, b;
    VDC(double x, double y) : a(x), b(y) {}
    double total() const override { return a + b; }
};
struct VEM : Base {
    double a, m, r;
    VEM(double x, double y, double z) : a(x), m(y), r(z) {}
    double total() const override { return a + m * r; }
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

struct OP { double a, b; };
struct IP { double d, r, s; };
struct DC { double a, b; };
struct EM { double a, m, r; };
using Variant = std::variant<OP, IP, DC, EM>;

double variantTotal(const Variant& value) {
    return std::visit([](const auto& x) -> double {
        using T = std::decay_t<decltype(x)>;
        if constexpr (std::is_same_v<T, OP>) return x.a + x.b;
        else if constexpr (std::is_same_v<T, IP>) return x.d * x.r + x.s;
        else if constexpr (std::is_same_v<T, DC>) return x.a + x.b;
        else return x.a + x.m * x.r;
    }, value);
}

template <typename Function>
double measureMs(Function function) {
    const auto start = Clock::now();
    function();
    const auto stop = Clock::now();
    return std::chrono::duration<double, std::milli>(stop - start).count();
}

volatile double benchmarkSink = 0.0;

void runBillBenchmarks() {
    const std::vector<Record> records = {
        {0,100,50,0}, {1,2,100,20}, {2,300,40,0}, {3,50,3,10}
    };

    std::vector<std::unique_ptr<Base>> virtualBills;
    virtualBills.push_back(std::make_unique<VOP>(100,50));
    virtualBills.push_back(std::make_unique<VIP>(2,100,20));
    virtualBills.push_back(std::make_unique<VDC>(300,40));
    virtualBills.push_back(std::make_unique<VEM>(50,3,10));

    const std::vector<Variant> variants = {
        OP{100,50}, IP{2,100,20}, DC{300,40}, EM{50,3,10}
    };

    std::cout << "\nB3.2 – Bill dispatch benchmark\n";
    std::cout << "Iterations | Virtual ms | Switch ms | Variant ms | Checksums\n";

    for (std::uint64_t n : {1000ULL, 1000000ULL, 10000000ULL}) {
        double virtualSum = 0.0, switchSum = 0.0, variantSum = 0.0;

        const double virtualMs = measureMs([&] {
            for (std::uint64_t i = 0; i < n; ++i)
                virtualSum += virtualBills[static_cast<std::size_t>(i % 4)]->total();
        });
        const double switchMs = measureMs([&] {
            for (std::uint64_t i = 0; i < n; ++i)
                switchSum += records[static_cast<std::size_t>(i % 4)].total();
        });
        const double variantMs = measureMs([&] {
            for (std::uint64_t i = 0; i < n; ++i)
                variantSum += variantTotal(variants[static_cast<std::size_t>(i % 4)]);
        });

        benchmarkSink = virtualSum + switchSum + variantSum;
        std::cout << n << " | " << virtualMs << " | " << switchMs << " | "
                  << variantMs << " | " << virtualSum << ", " << switchSum
                  << ", " << variantSum << '\n';
    }
}

void validateReturnCode(double amount, int& status) {
    status = (amount >= 0.0 && amount <= 1e6) ? 0 : 1;
}

void validateException(double amount) {
    if (amount < 0.0)
        throw std::invalid_argument("negative");
    if (amount > 1e6)
        throw std::out_of_range("too large");
}

void runExceptionBenchmarks() {
    constexpr std::uint64_t n = 1000000;
    std::cout << "\nB3.3 – Validation benchmark (1,000,000 claims)\n";
    std::cout << "Invalid rate | Return-code ms | Exception ms | Rejected count\n";

    for (int invalidPercent : {0, 1, 50}) {
        std::uint64_t rejectedReturn = 0;
        std::uint64_t rejectedException = 0;

        const double returnMs = measureMs([&] {
            for (std::uint64_t i = 0; i < n; ++i) {
                const bool invalid = (i % 100) < static_cast<std::uint64_t>(invalidPercent);
                const double amount = invalid ? -1.0 : 100.0;
                int status = 0;
                validateReturnCode(amount, status);
                rejectedReturn += static_cast<std::uint64_t>(status != 0);
            }
        });

        const double exceptionMs = measureMs([&] {
            for (std::uint64_t i = 0; i < n; ++i) {
                const bool invalid = (i % 100) < static_cast<std::uint64_t>(invalidPercent);
                const double amount = invalid ? -1.0 : 100.0;
                try {
                    validateException(amount);
                } catch (const std::exception&) {
                    ++rejectedException;
                }
            }
        });

        benchmarkSink = static_cast<double>(rejectedReturn + rejectedException);
        std::cout << invalidPercent << "% | " << returnMs << " | " << exceptionMs
                  << " | " << rejectedReturn << " / " << rejectedException << '\n';
    }
}

int main() {
    std::cout << std::fixed << std::setprecision(3);
    runBillBenchmarks();
    runExceptionBenchmarks();
    std::cout << "\nUse these measured values only for the machine/compiler used for this run.\n";
    return 0;
}
