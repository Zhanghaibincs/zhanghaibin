#include "Reader.h"
#include <iostream>

Reader::Reader() : currentBorrowed(0) {}

Reader::Reader(std::string id, std::string n, std::string g, std::string p)
    : Person(id, n, g, p), currentBorrowed(0) {
}

int Reader::getCurrentBorrowed() const { return currentBorrowed; }

int Reader::getBorrowDays() const { return 30; }       // 学生借30天
int Reader::getMaxBorrowLimit() const { return 5; }    // 学生最多5本

bool Reader::canBorrow() const {
    return currentBorrowed < getMaxBorrowLimit();
}

bool Reader::increaseBorrowCount() {
    if (canBorrow()) {
        currentBorrowed++;
        return true;
    }
    return false;
}

bool Reader::decreaseBorrowCount() {
    if (currentBorrowed > 0) {
        currentBorrowed--;
        return true;
    }
    return false;
}

void Reader::display() const {
    std::cout << "----------------------------------------\n";
    std::cout << "读者编号: " << getId() << "\n";
    std::cout << "姓    名: " << name << "\n";
    std::cout << "性    别: " << gender << "\n";
    std::cout << "电    话: " << phone << "\n";
    std::cout << "类    型: 学生读者\n";
    std::cout << "借书上限: " << getMaxBorrowLimit()
        << "    借期: " << getBorrowDays() << "天"
        << "    已借: " << currentBorrowed << "\n";
    std::cout << "----------------------------------------\n";
}
