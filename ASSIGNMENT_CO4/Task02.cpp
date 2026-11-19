#include <iostream>
#include <string>

class Person {
protected:
    std::string name;
    int id;
    std::string phone;

public:
    Person(const std::string& n, int i, const std::string& p)
        : name(n), id(i), phone(p) {
        std::cout << "Person ";
    }
};

class Student : virtual public Person {
protected:
    std::string programme;
    double cgpa;

public:
    Student(const std::string& n, int i, const std::string& p,
            const std::string& prog, double c)
        : Person(n, i, p), programme(prog), cgpa(c) {
        std::cout << "Student ";
    }
};

class Staff : virtual public Person {
protected:
    std::string department;
    double salary;

public:
    Staff(const std::string& n, int i, const std::string& p,
          const std::string& dept, double s)
        : Person(n, i, p), department(dept), salary(s) {
        std::cout << "Staff ";
    }
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(const std::string& n, int i, const std::string& p,
                      const std::string& prog, double c,
                      const std::string& dept, double s)
        : Person(n, i, p),
          Student(n, i, p, prog, c),
          Staff(n, i, p, dept, s) {
        std::cout << "TA ";
    }
};

class ResearchScholar : public Student {
    double fellowship;

public:
    ResearchScholar(const std::string& n, int i, const std::string& p,
                    const std::string& prog, double c, double f)
        : Person(n, i, p),
          Student(n, i, p, prog, c),
          fellowship(f) {}
};

int main() {
    TeachingAssistant ta("Arun", 101, "9876543210",
                         "CSE", 8.5, "Computer Science", 45000);
    std::cout << '\n';
    return 0;
}
