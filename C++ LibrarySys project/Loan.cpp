#include "Loan.h"
#include <iostream>

Loan::Loan() : returned(false) {}

Loan::Loan(std::string lid, std::string bid, std::string rid,
    std::string borrow, std::string due)
    : loanId(lid), bookId(bid), readerId(rid),
    borrowDate(borrow), dueDate(due), returned(false) {
}

std::string Loan::getLoanId() const { return loanId; }
std::string Loan::getBookId() const { return bookId; }
std::string Loan::getReaderId() const { return readerId; }
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
    std::cout << "图书编号: " << bookId << "\n";
    std::cout << "读者编号: " << readerId << "\n";
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
