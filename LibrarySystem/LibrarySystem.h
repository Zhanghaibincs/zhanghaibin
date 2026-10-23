#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H

#include "Book.h"
#include "Reader.h"
#include "Teacher.h"
#include "Loan.h"
#include "BaseSystem.h"
#include <vector>
#include <string>
#include "GeneralBook.h"
#include "ReferenceBook.h"
#include "Periodical.h"



class LibrarySystem : public BaseSystem {

private:
    std::vector<Book*> bookList;    // 多态：存指针，指向不同子类
    std::vector<Reader> readerList;
    std::vector<Teacher> teacherList;
    std::vector<Loan> loanList;

    const std::string BOOK_FILE = "data/books.txt";
    const std::string READER_FILE = "data/readers.txt";
    const std::string TEACHER_FILE = "data/teachers.txt";
    const std::string LOAN_FILE = "data/loans.txt";

    Book* findBookById(const std::string& id);
    Reader* findReaderById(const std::string& id);
    Teacher* findTeacherById(const std::string& id);
    Loan* findActiveLoan(const std::string& bookId, const std::string& personId);
    std::string todayString() const;
    std::string addDays(const std::string& date, int days) const;

public:
    LibrarySystem();
    ~LibrarySystem();

    // 图书管理
    void addBook();
    void removeBook();
    void searchBook() const;
    void displayAllBooks() const;

    // 读者管理
    void addReader();
    void removeReader();
    void searchReader() const;
    void displayAllReaders() const;

    // 教师管理
    void addTeacher();
    void displayAllTeachers() const;

    // 借还管理
    void borrowBook();
    void returnBook();
    void displayAllLoans() const;
    void displayPersonLoans() const;    // 新增：查询某人的借阅记录

    // 数据持久化
    void loadData();
    void saveData();

    void showMenu();
    void run();
    void renewLoan();

    void showOverdueLoans() const;

};

#endif // LIBRARY_SYSTEM_H
