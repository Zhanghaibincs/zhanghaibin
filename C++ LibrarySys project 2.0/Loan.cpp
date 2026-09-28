#include "Loan.h"
#include "Book.h"
#include "Reader.h"
#include <iostream>

Loan::Loan() : returned(false), book(nullptr), reader(nullptr) {}

Loan::Loan(std::string lid, Book* b, Reader* r,
    std::string borrow, std::string due)
    : loanId(lid), book(b), reader(r),
    borrowDate(borrow), dueDate(due), returned(false) {
}

std::string Loan::getLoanId() const { return loanId; }
Book* Loan::getBook() const { return book; }
Reader* Loan::getReader() const { return reader; }
std::string Loan::getBorrowDate() const { return borrowDate; }
std::string Loan::getDueDate() const { return dueDate; }
std::string Loan::getReturnDate() const { return returnDate; }
bool Loan::isReturned() const { return returned; }

void Loan::markReturned(const std::string& actualReturnDate) {
    returned = true;
    returnDate = actualReturnDate;
}

void Loan::display() const {
    std::cout << "----------------------------------------\n";
    std::cout << "借阅编号: " << loanId << "\n";
    // ===== 直接通过指针拿书名和读者名，不用再传 ID 去查 =====
    if (book)   std::cout << "书    名: " << book->getTitle() << "\n";
    if (reader) std::cout << "借 阅 人: " << reader->getName() << " (编号 " << reader->getReaderId() << ")\n";
    std::cout << "借出日期: " << borrowDate << "\n";
    std::cout << "应还日期: " << dueDate << "\n";
    if (returned) {
        std::cout << "归还日期: " << returnDate << "  [已归还]\n";
    }
    else {
        std::cout << "状    态: 未归还\n";
    }
    std::cout << "----------------------------------------\n";
}
