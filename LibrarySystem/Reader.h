#ifndef READER_H
#define READER_H

#include <string>
#include "Person.h"

// 学生读者，继承 Person
class Reader : public Person {
private:
    int currentBorrowed;    // 当前已借数量

public:
    Reader();
    Reader(std::string id, std::string n, std::string g, std::string p);

    int getCurrentBorrowed() const;

    // 实现 Person 的纯虚函数：学生借30天，最多5本
    int getBorrowDays() const override;
    int getMaxBorrowLimit() const override;

    // 业务方法
    bool canBorrow() const;
    bool increaseBorrowCount();
    bool decreaseBorrowCount();

    void display() const override;
};

#endif // READER_H
