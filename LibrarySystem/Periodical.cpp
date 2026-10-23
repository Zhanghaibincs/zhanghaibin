#include "Periodical.h"
#include <iostream>

Periodical::Periodical() : issue(""), volume("") {}

Periodical::Periodical(std::string id, std::string t, std::string a,
    std::string p, int stock, std::string iss, std::string vol)
    : Book(id, t, a, p, stock), issue(iss), volume(vol) {
}

std::string Periodical::getIssue() const { return issue; }
std::string Periodical::getVolume() const { return volume; }

int Periodical::getBorrowDays() const { return 3; }   // 期刊只借3天

std::string Periodical::getType() const { return "期刊杂志/多媒体光盘"; }

void Periodical::print(std::ostream& os) const {
    os << "----------------------------------------\n";
    os << "编号: " << getId() << "\n";
    os << "类  型: 期刊杂志/多媒体光盘\n";
    os << "名  称: " << title << "\n";
    os << "出版者: " << publisher << "\n";
    os << "卷  号: " << volume << "\n";
    os << "期  数: " << issue << "\n";
    os << "总库存: " << totalStock << "    可借: " << availableStock << "\n";
    os << "借  期: " << getBorrowDays() << "天\n";
    os << "----------------------------------------\n";
}
