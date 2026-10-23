#include "Loan.h"
#include "Book.h"
#include "Person.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>

using namespace std;

Loan::Loan() : returned(false), book(nullptr), person(nullptr) {}

Loan::Loan(std::string loanId, Book* b, Person* p,
    std::string borrow, std::string due)
    : Entity(loanId), book(b), person(p),
    borrowDate(borrow), dueDate(due), returned(false) {
}

Book* Loan::getBook() const { return book; }
Person* Loan::getPerson() const { return person; }
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
    std::cout << "借阅编号: " << getId() << "\n";
    if (book)   std::cout << "书    名: " << book->getTitle() << "\n";
    if (person) std::cout << "借 阅 人: " << person->getName()
        << " (编号 " << person->getId() << ")\n";
    std::cout << "借出日期: " << borrowDate << "\n";
    std::cout << "应还日期: " << dueDate << "\n";
    if (returned)
        std::cout << "归还日期: " << returnDate << "  [已归还]\n";
    else
        std::cout << "状    态: 未归还\n";
    std::cout << "----------------------------------------\n";
}


void Loan::renew(int days) {
    // 解析当前 dueDate
    int y = stoi(dueDate.substr(0, 4));
    int m = stoi(dueDate.substr(5, 2));
    int d = stoi(dueDate.substr(8, 2));
    struct tm t = { 0 };
    t.tm_year = y - 1900; t.tm_mon = m - 1; t.tm_mday = d + days;
    time_t when = mktime(&t);
    struct tm out; localtime_s(&out, &when);
    ostringstream oss;
    oss << out.tm_year + 1900 << "-"
        << setw(2) << setfill('0') << out.tm_mon + 1 << "-"
        << setw(2) << setfill('0') << out.tm_mday;
    dueDate = oss.str();
}


