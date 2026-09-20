#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H

#include "Book.h"
#include "Reader.h"
#include "Loan.h"
#include <vector>
#include <string>

// 图书馆管理系统主类：聚合图书、读者、借阅三大模块
class LibrarySystem {
private:
    std::vector<Book> bookList;          // 图书列表
    std::vector<Reader> readerList;      // 读者列表
    std::vector<Loan> loanList;          // 借阅记录列表

    // 数据文件路径
    const std::string BOOK_FILE = "data/books.txt";
    const std::string READER_FILE = "data/readers.txt";
    const std::string LOAN_FILE = "data/loans.txt";

    // 内部工具方法
    Book* findBookById(const std::string& id);
    Reader* findReaderById(const std::string& id);
    Loan* findActiveLoan(const std::string& bookId, const std::string& readerId);
    std::string todayString() const;
    std::string addDays(const std::string& date, int days) const;

public:
    LibrarySystem();
    ~LibrarySystem();

    // ========== 图书管理 ==========
    void addBook();
    void removeBook();
    void searchBook() const;
    void displayAllBooks() const;

    // ========== 读者管理 ==========
    void addReader();
    void removeReader();
    void searchReader() const;
    void displayAllReaders() const;

    // ========== 借阅管理 ==========
    void borrowBook();
    void returnBook();
    void displayAllLoans() const;

    // ========== 数据持久化 ==========
    void loadData();
    void saveData();

    // ========== 主菜单 ==========
    void showMenu();
    void run();
};

#endif // LIBRARY_SYSTEM_H

