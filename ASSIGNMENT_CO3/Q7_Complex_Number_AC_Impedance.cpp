#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

class Complex {
private:
    double re, im;
    static constexpr double EPS = 1e-12;

public:
    Complex() : re(0.0), im(0.0) {}
    Complex(double real) : re(real), im(0.0) {}
    Complex(double real, double imag) : re(real), im(imag) {}

    double real() const { return re; }
    double imag() const { return im; }

    double magnitude() const {
        return std::sqrt(re * re + im * im);
    }

    Complex operator+(const Complex& z) const {
        return Complex(re + z.re, im + z.im);
    }

    Complex operator-(const Complex& z) const {
        return Complex(re - z.re, im - z.im);
    }

    Complex operator*(const Complex& z) const {
        return Complex(re * z.re - im * z.im,
                       re * z.im + im * z.re);
    }

    Complex operator/(const Complex& z) const {
        double denominator = z.re * z.re + z.im * z.im;

        if (denominator < EPS) {
            throw std::domain_error("Division by zero impedance");
        }

        return Complex((re * z.re + im * z.im) / denominator,
                       (im * z.re - re * z.im) / denominator);
    }

    bool operator==(const Complex& z) const {
        return std::abs(re - z.re) < EPS &&
               std::abs(im - z.im) < EPS;
    }

    friend std::ostream& operator<<(std::ostream& out,
                                    const Complex& z) {
        out << std::fixed << std::setprecision(4) << z.re;

        if (z.im >= 0) {
            out << " + j" << z.im;
        } else {
            out << " - j" << std::abs(z.im);
        }

        return out;
    }
};

int main() {
    const double PI = std::acos(-1.0);
    const double f = 50.0;
    const double w = 2.0 * PI * f;
    const double R = 10.0;
    const double L = 0.1;
    const double C = 100e-6;

    Complex ZR(R, 0.0);
    Complex ZL(0.0, w * L);
    Complex ZC(0.0, -1.0 / (w * C));

    Complex series = ZR + ZL + ZC;

    std::cout << "Series impedance: " << series
              << "\nMagnitude: " << series.magnitude()
              << " ohms\n";

    // Parallel combination of the three components
    Complex one(1.0, 0.0);
    Complex parallel = one / (one / ZR + one / ZL + one / ZC);

    std::cout << "Parallel impedance: " << parallel
              << "\nMagnitude: " << parallel.magnitude()
              << " ohms\n";

    try {
        Complex zero;
        Complex invalid = ZR / zero;
        std::cout << invalid << '\n';
    }
    catch (const std::domain_error& e) {
        std::cout << "Error: " << e.what() << '\n';
    }

    return 0;
}
