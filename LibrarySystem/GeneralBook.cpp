#include "GeneralBook.h"
#include <iostream>

GeneralBook::GeneralBook() {}

GeneralBook::GeneralBook(std::string id, std::string t, std::string a,
    std::string p, int stock)
    : Book(id, t, a, p, stock) {
}

std::string GeneralBook::getType() const { return "普通图书"; }

void GeneralBook::print(std::ostream& os) const {
    os << "----------------------------------------\n";
    os << "图书编号: " << getId() << "\n";
    os << "类    型: 普通图书\n";
    os << "书    名: " << title << "\n";
    os << "作    者: " << author << "\n";
    os << "出 版 社: " << publisher << "\n";
    os << "总库存: " << totalStock << "    可借: " << availableStock << "\n";
    os << "借    期: " << getBorrowDays() << "天\n";
    os << "----------------------------------------\n";
}
