#include "Book.h"
#include <iostream>

Book::Book() : totalStock(0), availableStock(0) {}

Book::Book(std::string id, std::string t, std::string a, std::string p, int stock)
    : bookId(id), title(t), author(a), publisher(p),
    totalStock(stock), availableStock(stock) {
}

std::string Book::getBookId() const { return bookId; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
std::string Book::getPublisher() const { return publisher; }
int Book::getTotalStock() const { return totalStock; }
int Book::getAvailableStock() const { return availableStock; }

void Book::setBookId(const std::string& id) { bookId = id; }
void Book::setTitle(const std::string& t) { title = t; }
void Book::setAuthor(const std::string& a) { author = a; }
void Book::setPublisher(const std::string& p) { publisher = p; }
void Book::setTotalStock(int stock) { totalStock = stock; }
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

void Book::display() const {
    std::cout << "----------------------------------------\n";
    std::cout << "图书编号: " << bookId << "\n";
    std::cout << "书    名: " << title << "\n";
    std::cout << "作    者: " << author << "\n";
    std::cout << "出 版 社: " << publisher << "\n";
    std::cout << "总库存: " << totalStock << "    可借: " << availableStock << "\n";
    std::cout << "----------------------------------------\n";
}
