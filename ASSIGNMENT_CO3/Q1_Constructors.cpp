#include <iostream>
#include <stdexcept>
#include <string>

class Book {
private:
    std::string title;
    std::string author;
    int copies;

public:
    Book() : Book("Untitled", "Unknown", 0) {}

    explicit Book(const std::string& bookTitle)
        : Book(bookTitle, "Unknown", 1) {}

    Book(const std::string& bookTitle,
         const std::string& bookAuthor, int copyCount)
        : title(bookTitle), author(bookAuthor), copies(copyCount) {
        if (copyCount < 0) {
            throw std::invalid_argument("Copies cannot be negative");
        }
    }

    void display() const {
        std::cout << "Title: " << title
                  << ", Author: " << author
                  << ", Copies: " << copies << '\n';
    }
};

int main() {
    try {
        Book emptyBook;
        Book donatedBook("The C++ Programming Language");
        Book fullBook("Clean Code", "Robert C. Martin", 5);

        emptyBook.display();
        donatedBook.display();
        fullBook.display();

        // Uncomment to test the exception:
        // Book invalidBook("Invalid", "Author", -2);
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
    }

    return 0;
}
