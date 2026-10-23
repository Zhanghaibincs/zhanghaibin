#ifndef PERIODICAL_H
#define PERIODICAL_H

#include "Book.h"

// 期刊杂志/多媒体光盘：借期短，只有3天，有期数和卷号
class Periodical : public Book {
private:
    std::string issue;    // 期数（如"2024年第5期"）
    std::string volume;   // 卷号（如"第12卷"）

public:
    Periodical();
    Periodical(std::string id, std::string t, std::string a,
        std::string p, int stock, std::string iss, std::string vol);

    std::string getIssue() const;
    std::string getVolume() const;

    // 重写：期刊借期只有3天
    int getBorrowDays() const override;
    std::string getType() const override;
    void print(std::ostream& os) const override;
};

#endif // PERIODICAL_H
#pragma once
