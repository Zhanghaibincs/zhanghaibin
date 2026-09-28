#include "Reader.h"
#include <iostream>

Reader::Reader() : maxBorrowLimit(5), currentBorrowed(0) {}

Reader::Reader(std::string id, std::string n, std::string g, std::string p, int limit)
    : readerId(id), name(n), gender(g), phone(p),
    maxBorrowLimit(limit), currentBorrowed(0) {
}

std::string Reader::getReaderId() const { return readerId; }
std::string Reader::getName() const { return name; }
std::string Reader::getGender() const { return gender; }
std::string Reader::getPhone() const { return phone; }
int Reader::getMaxBorrowLimit() const { return maxBorrowLimit; }
int Reader::getCurrentBorrowed() const { return currentBorrowed; }

void Reader::setReaderId(const std::string& id) { readerId = id; }
void Reader::setName(const std::string& n) { name = n; }
void Reader::setGender(const std::string& g) { gender = g; }
void Reader::setPhone(const std::string& p) { phone = p; }
void Reader::setMaxBorrowLimit(int limit) { maxBorrowLimit = limit; }

bool Reader::canBorrow() const {
    return currentBorrowed < maxBorrowLimit;
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
    std::cout << "读者编号: " << readerId << "\n";
    std::cout << "姓    名: " << name << "\n";
    std::cout << "性    别: " << gender << "\n";
    std::cout << "联系电话: " << phone << "\n";
    std::cout << "借书上限: " << maxBorrowLimit
        << "    已借: " << currentBorrowed << "\n";
    std::cout << "----------------------------------------\n";
}
