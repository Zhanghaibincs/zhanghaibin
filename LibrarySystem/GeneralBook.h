#ifndef GENERAL_BOOK_H
#define GENERAL_BOOK_H

#include "Book.h"

// 普通图书：直接继承 Book，用默认规则（借30天，可外借）
class GeneralBook : public Book {
public:
    GeneralBook();
    GeneralBook(std::string id, std::string t, std::string a,
        std::string p, int stock);

    std::string getType() const override;
    void print(std::ostream& os) const override;
};

#endif // GENERAL_BOOK_H
#pragma once
