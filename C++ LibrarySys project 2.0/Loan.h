#ifndef LOAN_H
#define LOAN_H

#include <string>

// 前向声明：只告诉编译器有这两个类，不包含头文件，避免循环依赖
class Book;
class Reader;

class Loan {
private:
    std::string loanId;
    std::string borrowDate;
    std::string dueDate;
    std::string returnDate;
    bool returned;

    // ===== 新增：直接持有关联对象的指针 =====
    Book* book;       // 这条借阅记录关联的书
    Reader* reader;   // 这条借阅记录关联的读者

public:
    Loan();
    Loan(std::string lid, Book* b, Reader* r,
        std::string borrow, std::string due);

    // Getter
    std::string getLoanId() const;
    Book* getBook() const;        // 返回 Book 指针
    Reader* getReader() const;    // 返回 Reader 指针
    std::string getBorrowDate() const;
    std::string getDueDate() const;
    std::string getReturnDate() const;
    bool isReturned() const;

    void markReturned(const std::string& actualReturnDate);
    void display() const;
};

#endif // LOAN_H
