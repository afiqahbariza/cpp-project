#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>


struct Book;

// External inventory provided by other group member
extern Book books[];    // Book array (e.g., Book books[100];) defined elsewhere
extern int bookCount;   // number of books currently in array

double totalSales = 0.0;

int findBookIndexByISBN(const std::string &isbn) {
    for (int i = 0; i < bookCount; ++i) {
        if (books[i].isbn == isbn) return i;
    }
    return -1;
}
void buyBook() {
    std::string isbn;
    int quantity = 0;
    char choice = 'N';
    double transactionTotal = 0.0;

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "\n===== BOOK PURCHASE =====\n";

    do {
        // Prompt ISBN
        std::cout << "\nEnter ISBN of book to buy: ";
        std::cin >> isbn;

        // Search for book
        int idx = findBookIndexByISBN(isbn);
        if (idx == -1) {
            std::cout << "Book not found for ISBN: " << isbn << "\n";
        } else {
            // Display basic book info
            std::cout << "Book found: " << books[idx].title
                      << " | Author: " << books[idx].author
                      << " | Price: RM " << books[idx].price
                      << " | Stock: " << books[idx].stock << "\n";

            // Prompt quantity with validation
            while (true) {
                std::cout << "Enter quantity to buy: ";
                if (!(std::cin >> quantity)) {
                    // Non-integer entered
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter a positive integer for quantity.\n";
                    continue;
                }
                if (quantity <= 0) {
                    std::cout << "Quantity must be greater than zero.\n";
                    continue;
                }
                break;
            }

            // Check stock
            if (quantity > books[idx].stock) {
                std::cout << "Insufficient stock. Available: " << books[idx].stock << "\n";
            } else {
                // Process sale: update stock and compute price
                books[idx].stock -= quantity;
                double lineTotal = books[idx].price * static_cast<double>(quantity);
                transactionTotal += lineTotal;

                std::cout << "Purchase accepted: " << books[idx].title
                          << " x" << quantity
                          << " | Line total: RM " << lineTotal << "\n";
            }
        }

        // Ask to continue purchasing
        std::cout << "\nDo you want to buy another book? (Y/N): ";
        std::cin >> choice;
        choice = static_cast<char>(std::toupper(static_cast<unsigned char>(choice)));

        // Normalize input: if invalid char, treat as 'N'
        if (choice != 'Y' && choice != 'N') choice = 'N';

    } while (choice == 'Y');

    // Finalize transaction
    if (transactionTotal > 0.0) {
        totalSales += transactionTotal;
    }

    // Transaction summary
    std::cout << "\n----- TRANSACTION SUMMARY -----\n";
    std::cout << "Total for this transaction : RM " << transactionTotal << "\n";
    std::cout << "Total sales today           : RM " << totalSales << "\n";
    std::cout << "-------------------------------\n";
}
