#ifndef BOOK_H
#define BOOK_H

#include <string>
#include "Entity.h"

// Book 继承 Entity（id 就是图书编号）
class Book : public Entity {
private:
    std::string title;
    std::string author;
    std::string publisher;
    int totalStock;
    int availableStock;

public:
    Book();
    Book(std::string id, std::string t, std::string a,
        std::string p, int stock);

    // Getter（bookId 直接用 Entity::getId()）
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getPublisher() const;
    int getTotalStock() const;
    int getAvailableStock() const;

    // Setter
    void setTitle(const std::string& t);
    void setAuthor(const std::string& a);
    void setPublisher(const std::string& p);
    void setAvailableStock(int stock);

    // 业务方法
    bool borrowOne();
    bool returnOne();
    void display() const;
};

#endif // BOOK_H
