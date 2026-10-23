#ifndef TEACHER_H
#define TEACHER_H

#include <string>
#include "Person.h"

// 教师，继承 Person
class Teacher : public Person {
private:
    std::string department;
    int currentBorrowed;

public:
    Teacher();
    Teacher(std::string id, std::string n, std::string g,
        std::string p, std::string dept);

    std::string getDepartment() const;
    int getCurrentBorrowed() const;

    // 实现 Person 的纯虚函数：教师借60天，最多10本
    int getBorrowDays() const override;
    int getMaxBorrowLimit() const override;

    bool canBorrow() const;
    bool increaseBorrowCount();
    bool decreaseBorrowCount();

    void display() const override;
};

#endif // TEACHER_H
