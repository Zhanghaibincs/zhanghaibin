#ifndef BOOK_H
#define BOOK_H

#include <string>

// 图书类：封装单本图书的基本信息
class Book {
private:
    std::string bookId;       // 图书编号（唯一）
    std::string title;        // 书名
    std::string author;       // 作者
    std::string publisher;    // 出版社
    int totalStock;           // 总库存
    int availableStock;       // 可借库存

public:
    // 构造函数
    Book();
    Book(std::string id, std::string t, std::string a, std::string p, int stock);

    // Getter
    std::string getBookId() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getPublisher() const;
    int getTotalStock() const;
    int getAvailableStock() const;

    // Setter
    void setBookId(const std::string& id);
    void setTitle(const std::string& t);
    void setAuthor(const std::string& a);
    void setPublisher(const std::string& p);
    void setTotalStock(int stock);
    void setAvailableStock(int stock);

    // 业务方法
    bool borrowOne();         // 借出一本，成功返回 true
    bool returnOne();         // 归还一本，成功返回 true
    void display() const;     // 打印图书信息
};

#endif // BOOK_H

