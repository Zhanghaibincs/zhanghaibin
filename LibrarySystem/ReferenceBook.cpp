#include "ReferenceBook.h"
#include <iostream>

ReferenceBook::ReferenceBook() : storageRoom("") {}

ReferenceBook::ReferenceBook(std::string id, std::string t, std::string a,
    std::string p, int stock, std::string room)
    : Book(id, t, a, p, stock), storageRoom(room) {
}

std::string ReferenceBook::getStorageRoom() const { return storageRoom; }

bool ReferenceBook::canBorrow() const {
    return false;   // 只能阅览，不能外借
}

std::string ReferenceBook::getType() const { return "参考工具书/古籍特藏"; }

void ReferenceBook::print(std::ostream& os) const {
    os << "----------------------------------------\n";
    os << "图书编号: " << getId() << "\n";
    os << "类    型: 参考工具书/古籍特藏\n";
    os << "书    名: " << title << "\n";
    os << "作    者: " << author << "\n";
    os << "出 版 社: " << publisher << "\n";
    os << "藏    室: " << storageRoom << "\n";
    os << "总库存: " << totalStock << "    可借: " << availableStock << "\n";
    os << "借阅规则: 仅限馆内阅览，不外借\n";
    os << "----------------------------------------\n";
}
