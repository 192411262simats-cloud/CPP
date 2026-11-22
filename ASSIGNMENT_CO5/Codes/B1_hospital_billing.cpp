#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class BillingError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class InvalidChargeError : public BillingError {
public:
    using BillingError::BillingError;
};

class UnknownPackageError : public BillingError {
public:
    using BillingError::BillingError;
};

class Bill {
protected:
    std::string patient;

    static void checkNonNegative(double value) {
        if (value < 0.0)
            throw InvalidChargeError("negative charge");
    }

public:
    explicit Bill(std::string patientName) : patient(std::move(patientName)) {}
    virtual double total() const = 0;
    virtual std::string type() const = 0;
    virtual ~Bill() = default;

    void print() const {
        std::cout << type() << ' ' << patient << ": " << total() << '\n';
    }
};

class OutPatient : public Bill {
    double consultation;
    double tests;

public:
    OutPatient(std::string p, double c, double t)
        : Bill(std::move(p)), consultation(c), tests(t) {
        checkNonNegative(c);
        checkNonNegative(t);
    }

    double total() const override { return consultation + tests; }
    std::string type() const override { return "OP"; }
};

class InPatient : public Bill {
    int days;
    double perDay;
    double surgery;

public:
    InPatient(std::string p, int d, double rate, double s)
        : Bill(std::move(p)), days(d), perDay(rate), surgery(s) {
        if (d < 0)
            throw InvalidChargeError("negative admission days");
        checkNonNegative(rate);
        checkNonNegative(s);
    }

    double total() const override { return days * perDay + surgery; }
    std::string type() const override { return "IP"; }
};

class DayCare : public Bill {
    double packageCost;
    double medicines;

public:
    DayCare(std::string p, double package, double medicineCost)
        : Bill(std::move(p)), packageCost(package), medicines(medicineCost) {
        checkNonNegative(package);
        checkNonNegative(medicineCost);
    }

    double total() const override { return packageCost + medicines; }
    std::string type() const override { return "DAYCARE"; }
};

class Emergency : public Bill {
    double baseCharge;
    double minutes;
    double rate;

public:
    Emergency(std::string p, double base, double mins, double perMinute)
        : Bill(std::move(p)), baseCharge(base), minutes(mins), rate(perMinute) {
        checkNonNegative(base);
        checkNonNegative(mins);
        checkNonNegative(perMinute);
    }

    double total() const override { return baseCharge + minutes * rate; }
    std::string type() const override { return "EMERGENCY"; }
};

class Payer {
public:
    virtual double amountCovered(const Bill& bill) const = 0;
    virtual std::string name() const = 0;
    virtual ~Payer() = default;
};

class SelfPay : public Payer {
public:
    double amountCovered(const Bill& bill) const override { return bill.total(); }
    std::string name() const override { return "SelfPay"; }
};

class Insurance : public Payer {
    double limit;
    double copayPercent;

public:
    Insurance(double policyLimit, double copay)
        : limit(policyLimit), copayPercent(copay) {
        if (limit < 0.0 || copayPercent < 0.0 || copayPercent > 100.0)
            throw InvalidChargeError("invalid insurance policy");
    }

    double amountCovered(const Bill& bill) const override {
        const double eligible = std::min(bill.total(), limit);
        return eligible * (1.0 - copayPercent / 100.0);
    }

    std::string name() const override { return "Insurance"; }
};

class GovernmentScheme : public Payer {
    std::map<std::string, double> rates;

public:
    explicit GovernmentScheme(std::map<std::string, double> packageRates)
        : rates(std::move(packageRates)) {
        for (const auto& item : rates)
            if (item.second < 0.0)
                throw InvalidChargeError("negative government package rate");
    }

    double amountCovered(const Bill& bill) const override {
        const auto it = rates.find(bill.type());
        if (it == rates.end())
            throw UnknownPackageError("unknown government package");
        return std::min(bill.total(), it->second);
    }

    std::string name() const override { return "GovernmentScheme"; }
};

int main() {
    try {
        std::vector<std::unique_ptr<Bill>> bills;
        bills.push_back(std::make_unique<OutPatient>("Ravi", 500, 1200));
        bills.push_back(std::make_unique<InPatient>("Meena", 3, 2500, 40000));
        bills.push_back(std::make_unique<DayCare>("Arun", 18000, 2000));
        bills.push_back(std::make_unique<Emergency>("Sara", 3000, 30, 100));

        SelfPay self;
        Insurance insurance(50000, 20);
        GovernmentScheme government({
            {"OP", 1500}, {"IP", 45000},
            {"DAYCARE", 19000}, {"EMERGENCY", 5000}
        });

        const std::vector<const Payer*> payers{&self, &insurance, &government};
        double grandTotal = 0.0;

        std::cout << std::fixed << std::setprecision(0);
        for (const auto& bill : bills) {
            bill->print();
            grandTotal += bill->total();

            for (const Payer* payer : payers) {
                try {
                    const double covered = payer->amountCovered(*bill);
                    std::cout << payer->name() << " covers " << covered
                              << " for " << bill->type() << '\n';
                } catch (const BillingError& e) {
                    std::cout << "payer error: " << e.what() << '\n';
                }
            }
        }
        std::cout << "Day total " << grandTotal << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Billing failed: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
