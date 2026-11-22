#include <algorithm>
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

    static void check(double value) {
        if (value < 0.0)
            throw InvalidChargeError("negative charge");
    }

public:
    explicit Bill(std::string p) : patient(std::move(p)) {}
    virtual double total() const = 0;
    virtual std::string type() const = 0;
    virtual ~Bill() = default;

    void print() const {
        std::cout << type() << ' ' << patient << ": " << total() << '\n';
    }
};

class OutPatient : public Bill {
    double consultation, tests;
public:
    OutPatient(std::string p, double c, double t)
        : Bill(std::move(p)), consultation(c), tests(t) {
        check(c); check(t);
    }
    double total() const override { return consultation + tests; }
    std::string type() const override { return "OP"; }
};

class InPatient : public Bill {
    int days;
    double perDay, surgery;
public:
    InPatient(std::string p, int d, double rate, double s)
        : Bill(std::move(p)), days(d), perDay(rate), surgery(s) {
        if (d < 0) throw InvalidChargeError("negative days");
        check(rate); check(s);
    }
    double total() const override { return days * perDay + surgery; }
    std::string type() const override { return "IP"; }
};

class DayCare : public Bill {
    double packageCost, medicines;
public:
    DayCare(std::string p, double package, double medicineCost)
        : Bill(std::move(p)), packageCost(package), medicines(medicineCost) {
        check(package); check(medicineCost);
    }
    double total() const override { return packageCost + medicines; }
    std::string type() const override { return "DAYCARE"; }
};

class Emergency : public Bill {
    double baseCharge, minutes, rate;
public:
    Emergency(std::string p, double base, double mins, double perMinute)
        : Bill(std::move(p)), baseCharge(base), minutes(mins), rate(perMinute) {
        check(base); check(mins); check(perMinute);
    }
    double total() const override { return baseCharge + minutes * rate; }
    std::string type() const override { return "EMERGENCY"; }
};

// B4 extension: new bill type added without modifying existing bill classes.
class TelemedicineBill : public Bill {
    double consultation, platformFee;
public:
    TelemedicineBill(std::string p, double c, double fee)
        : Bill(std::move(p)), consultation(c), platformFee(fee) {
        check(c); check(fee);
    }
    double total() const override { return consultation + platformFee; }
    std::string type() const override { return "TELEMEDICINE"; }
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
    double limit, copay;
public:
    Insurance(double l, double c) : limit(l), copay(c) {
        if (l < 0.0 || c < 0.0 || c > 100.0)
            throw InvalidChargeError("invalid insurance policy");
    }
    double amountCovered(const Bill& bill) const override {
        return std::min(bill.total(), limit) * (1.0 - copay / 100.0);
    }
    std::string name() const override { return "Insurance"; }
};

class GovernmentScheme : public Payer {
    std::map<std::string, double> rates;
public:
    explicit GovernmentScheme(std::map<std::string, double> r) : rates(std::move(r)) {}
    double amountCovered(const Bill& bill) const override {
        const auto it = rates.find(bill.type());
        if (it == rates.end())
            throw UnknownPackageError("unknown package");
        return std::min(bill.total(), it->second);
    }
    std::string name() const override { return "GovernmentScheme"; }
};

// B4 extension: new payer type added through the existing Payer interface.
class CorporateTieUp : public Payer {
    double contributionPercent;
public:
    explicit CorporateTieUp(double percent) : contributionPercent(percent) {
        if (percent < 0.0 || percent > 100.0)
            throw InvalidChargeError("invalid corporate percentage");
    }
    double amountCovered(const Bill& bill) const override {
        return bill.total() * contributionPercent / 100.0;
    }
    std::string name() const override { return "CorporateTieUp"; }
};

int main() {
    try {
        std::vector<std::unique_ptr<Bill>> bills;
        bills.push_back(std::make_unique<OutPatient>("Ravi", 500, 1200));
        bills.push_back(std::make_unique<InPatient>("Meena", 3, 2500, 40000));
        bills.push_back(std::make_unique<DayCare>("Arun", 18000, 2000));
        bills.push_back(std::make_unique<Emergency>("Sara", 3000, 30, 100));
        bills.push_back(std::make_unique<TelemedicineBill>("Dheeraj", 800, 100));

        SelfPay self;
        Insurance insurance(50000, 20);
        GovernmentScheme government({
            {"OP",1500}, {"IP",45000}, {"DAYCARE",19000}, {"EMERGENCY",5000}
        });
        CorporateTieUp corporate(70);

        const std::vector<const Payer*> payers{&self, &insurance, &government, &corporate};

        for (const auto& bill : bills) {
            bill->print();
            for (const Payer* payer : payers) {
                try {
                    const double covered = payer->amountCovered(*bill);
                    std::cout << payer->name() << " covers " << covered
                              << "; patient balance " << bill->total() - covered << '\n';
                } catch (const BillingError& e) {
                    std::cout << payer->name() << " error: " << e.what() << '\n';
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Fatal billing error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
