#include <iostream>

int& highestMark(int marks[], int size) {
    int highestIndex = 0;

    for (int i = 1; i < size; ++i) {
        if (marks[i] > marks[highestIndex]) {
            highestIndex = i;
        }
    }

    return marks[highestIndex];
}

int highestMarkIndex(const int marks[], int size) {
    int highestIndex = 0;

    for (int i = 1; i < size; ++i) {
        if (marks[i] > marks[highestIndex]) {
            highestIndex = i;
        }
    }

    return highestIndex;
}

int main() {
    int marks[] = {78, 91, 84, 88, 95};
    const int size = sizeof(marks) / sizeof(marks[0]);

    std::cout << "Highest before moderation: "
              << highestMark(marks, size) << '\n';

    highestMark(marks, size) += 2;

    std::cout << "Highest after moderation: "
              << highestMark(marks, size) << '\n';

    std::cout << "Updated array: ";
    for (int mark : marks) {
        std::cout << mark << ' ';
    }
    std::cout << '\n';

    int index = highestMarkIndex(marks, size);
    std::cout << "Highest mark index: " << index << '\n';

    return 0;
}
