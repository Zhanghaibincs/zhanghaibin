#include "Book.h"
#include <iostream>

Book::Book() : totalStock(0), availableStock(0) {}

Book::Book(std::string id, std::string t, std::string a,
    std::string p, int stock)
    : Entity(id), title(t), author(a), publisher(p),
    totalStock(stock), availableStock(stock) {
}

std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
std::string Book::getPublisher() const { return publisher; }
int Book::getTotalStock() const { return totalStock; }
int Book::getAvailableStock() const { return availableStock; }


void Book::setAvailableStock(int stock) { availableStock = stock; }

bool Book::borrowOne() {
    if (availableStock > 0) {
        availableStock--;
        return true;
    }
    return false;
}

bool Book::returnOne() {
    if (availableStock < totalStock) {
        availableStock++;
        return true;
    }
    return false;
}

void Book::print(std::ostream& os) const {
    os << "----------------------------------------\n";
    os << "图书编号: " << getId() << "\n";
    os << "类    型: " << getType() << "\n";
    os << "书    名: " << title << "\n";
    os << "作    者: " << author << "\n";
    os << "出 版 社: " << publisher << "\n";
    os << "总库存: " << totalStock << "    可借: " << availableStock << "\n";
    os << "----------------------------------------\n";
}

std::ostream& operator<<(std::ostream& os, const Book& b) {
    b.print(os);   // 调用虚函数，自动按派生类类型输出
    return os;
}

