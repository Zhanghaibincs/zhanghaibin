#include "Teacher.h"
#include <iostream>

Teacher::Teacher() : currentBorrowed(0) {}

Teacher::Teacher(std::string id, std::string n, std::string g,
    std::string p, std::string dept)
    : Person(id, n, g, p), department(dept), currentBorrowed(0) {
}

std::string Teacher::getDepartment() const { return department; }
int Teacher::getCurrentBorrowed() const { return currentBorrowed; }

int Teacher::getBorrowDays() const { return 60; }      // 教师借60天
int Teacher::getMaxBorrowLimit() const { return 10; }  // 教师最多10本

bool Teacher::canBorrow() const {
    return currentBorrowed < getMaxBorrowLimit();
}

bool Teacher::increaseBorrowCount() {
    if (canBorrow()) {
        currentBorrowed++;
        return true;
    }
    return false;
}

bool Teacher::decreaseBorrowCount() {
    if (currentBorrowed > 0) {
        currentBorrowed--;
        return true;
    }
    return false;
}

void Teacher::display() const {
    std::cout << "----------------------------------------\n";
    std::cout << "工    号: " << getId() << "\n";
    std::cout << "姓    名: " << name << "\n";
    std::cout << "性    别: " << gender << "\n";
    std::cout << "电    话: " << phone << "\n";
    std::cout << "类    型: 教师\n";
    std::cout << "院    系: " << department << "\n";
    std::cout << "借书上限: " << getMaxBorrowLimit()
        << "    借期: " << getBorrowDays() << "天"
        << "    已借: " << currentBorrowed << "\n";
    std::cout << "----------------------------------------\n";
}
