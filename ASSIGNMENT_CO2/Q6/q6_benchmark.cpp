#include <iostream>
#include <chrono>

#ifdef USE_INLINE
inline int work(int x) {
    return (x * 3 + 7) % 997;
}
#else
#if defined(__GNUC__)
__attribute__((noinline))
#endif
int work(int x) {
    return (x * 3 + 7) % 997;
}
#endif

int main() {
    volatile long long sink = 0;
    const int repetitions = 10000000;

    const auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < repetitions; ++i) {
        sink = sink + work(i);
    }

    const auto finish = std::chrono::steady_clock::now();
    const double elapsed =
        std::chrono::duration<double, std::milli>(finish - start).count();

    std::cout << "Result: " << sink << '\n';
    std::cout << "Elapsed milliseconds: " << elapsed << '\n';

    return 0;
}
