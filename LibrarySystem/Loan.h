#ifndef LOAN_H
#define LOAN_H

#include <string>
#include "Entity.h"

class Book;
class Person;   // 前置声明：不管是 Reader 还是 Teacher，统一用 Person*

// Loan 继承 Entity（loanId 就是继承来的 id）
class Loan : public Entity {
private:
    std::string borrowDate;
    std::string dueDate;
    std::string returnDate;
    bool returned;
    Book* book;        // 关联：借的是哪本书
    Person* person;    // 关联：谁借的（学生或老师都行）
    int renewCount;          // 已续借次数
    static const int MAX_RENEW = 2;   // 最多续借2次

public:
    Loan();
    Loan(std::string loanId, Book* b, Person* p,
        std::string borrow, std::string due);

    Book* getBook() const;
    Person* getPerson() const;      // 改名叫 getPerson
    std::string getBorrowDate() const;
    std::string getDueDate() const;
    std::string getReturnDate() const;
    bool isReturned() const;

    void markReturned(const std::string& date);
    void display() const;
    void renew(int days);    // 续借：延长 days 天

    int getRenewCount() const;
    bool canRenew() const;
    void increaseRenewCount();
    double calcFine(const std::string& today) const;   // 计算逾期罚款

};

#endif // LOAN_H
