#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Time {
private:
    int h, m, s;

    void normalize() {
        int total = h * 3600 + m * 60 + s;
        total = (total % 86400 + 86400) % 86400;

        h = total / 3600;
        m = (total % 3600) / 60;
        s = total % 60;
    }

public:
    Time(int hours = 0, int minutes = 0, int seconds = 0)
        : h(hours), m(minutes), s(seconds) {
        normalize();
    }

    Time& operator++() {           // Prefix
        ++s;
        normalize();
        return *this;
    }

    Time operator++(int) {         // Postfix
        Time old = *this;
        ++(*this);
        return old;
    }

    bool operator==(const Time& other) const {
        return h == other.h && m == other.m && s == other.s;
    }

    bool operator<(const Time& other) const {
        if (h != other.h) return h < other.h;
        if (m != other.m) return m < other.m;
        return s < other.s;
    }

    friend std::ostream& operator<<(std::ostream& out, const Time& t) {
        return out << t.h << ':'
                   << (t.m < 10 ? "0" : "") << t.m << ':'
                   << (t.s < 10 ? "0" : "") << t.s;
    }
};

class Playlist {
private:
    std::vector<std::string> tracks;

public:
    Playlist(std::initializer_list<std::string> list) : tracks(list) {}

    std::string& operator[](int index) {
        if (index < 0 || index >= static_cast<int>(tracks.size())) {
            throw std::out_of_range("Playlist index out of range");
        }
        return tracks[index];
    }

    const std::string& operator[](int index) const {
        if (index < 0 || index >= static_cast<int>(tracks.size())) {
            throw std::out_of_range("Playlist index out of range");
        }
        return tracks[index];
    }

    int size() const {
        return static_cast<int>(tracks.size());
    }
};

int main() {
    Time t(0, 59, 58);
    Time a = t++;
    Time b = ++t;

    std::cout << "a = " << a << ", b = " << b
              << ", t = " << t << '\n';

    Time last(0, 59, 59);
    ++last;
    std::cout << "After rollover: " << last << '\n';

    Playlist playlist{"Track One", "Track Two", "Track Three"};
    std::cout << playlist[1] << '\n';

    playlist[1] = "Updated Track";
    std::cout << playlist[1] << '\n';

    try {
        std::cout << playlist[-1] << '\n';
    }
    catch (const std::out_of_range& e) {
        std::cout << e.what() << '\n';
    }

    return 0;
}
