#ifndef BOOK_H
#define BOOK_H

#include <string>
#include "Entity.h"

// 基类：图书
class Book : public Entity {
protected:
    std::string title;
    std::string author;
    std::string publisher;
    int totalStock;
    int availableStock;

public:
    Book();
    Book(std::string id, std::string t, std::string a,
        std::string p, int stock);
    virtual ~Book() {}

    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getPublisher() const;
    int getTotalStock() const;
    int getAvailableStock() const;
    void setAvailableStock(int stock);

    // 虚函数：不同书类型规则不同，派生类重写
    virtual int getBorrowDays() const { return 30; }   // 默认借30天
    virtual bool canBorrow() const { return availableStock > 0; }  // 默认可借
    virtual std::string getType() const { return "普通图书"; }

    bool borrowOne();
    bool returnOne();
    virtual void print(std::ostream& os) const;


    friend std::ostream& operator<<(std::ostream& os, const Book& b);

};

#endif // BOOK_H
