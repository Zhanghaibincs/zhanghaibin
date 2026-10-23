#ifndef REFERENCE_BOOK_H
#define REFERENCE_BOOK_H

#include "Book.h"

// 参考工具书/古籍特藏：只能阅览，不能外借
class ReferenceBook : public Book {
private:
    std::string storageRoom;   // 藏室位置（如"特藏室A区"）

public:
    ReferenceBook();
    ReferenceBook(std::string id, std::string t, std::string a,
        std::string p, int stock, std::string room);

    std::string getStorageRoom() const;

    // 重写：参考工具书一律不能外借
    bool canBorrow() const override;
    std::string getType() const override;
    void print(std::ostream& os) const override;
};

#endif // REFERENCE_BOOK_H
#pragma once
