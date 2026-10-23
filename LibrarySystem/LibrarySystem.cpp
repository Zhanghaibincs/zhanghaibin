#include "LibrarySystem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <limits>

using namespace std;

LibrarySystem::LibrarySystem() { loadData(); }
LibrarySystem::~LibrarySystem() { saveData(); }

// ========== 内部查找 ==========
Book* LibrarySystem::findBookById(const string& id) {
    for (auto& b : bookList) if (b.getId() == id) return &b;
    return nullptr;
}

Reader* LibrarySystem::findReaderById(const string& id) {
    for (auto& r : readerList) if (r.getId() == id) return &r;
    return nullptr;
}

Teacher* LibrarySystem::findTeacherById(const string& id) {
    for (auto& t : teacherList) if (t.getId() == id) return &t;
    return nullptr;
}

Loan* LibrarySystem::findActiveLoan(const string& bookId, const string& personId) {
    for (auto& l : loanList) {
        if (!l.isReturned() &&
            l.getBook()->getId() == bookId &&
            l.getPerson()->getId() == personId) {
            return &l;
        }
    }
    return nullptr;
}

string LibrarySystem::todayString() const {
    time_t now = time(nullptr);
    struct tm t; localtime_s(&t, &now);
    ostringstream oss;
    oss << t.tm_year + 1900 << "-"
        << setw(2) << setfill('0') << t.tm_mon + 1 << "-"
        << setw(2) << setfill('0') << t.tm_mday;
    return oss.str();
}

string LibrarySystem::addDays(const string& date, int days) const {
    int y = stoi(date.substr(0, 4));
    int m = stoi(date.substr(5, 2));
    int d = stoi(date.substr(8, 2));
    struct tm t = { 0 };
    t.tm_year = y - 1900; t.tm_mon = m - 1; t.tm_mday = d + days;
    time_t when = mktime(&t);
    struct tm out; localtime_s(&out, &when);
    ostringstream oss;
    oss << out.tm_year + 1900 << "-"
        << setw(2) << setfill('0') << out.tm_mon + 1 << "-"
        << setw(2) << setfill('0') << out.tm_mday;
    return oss.str();
}

// ========== 图书管理 ==========
void LibrarySystem::addBook() {
    string id, title, author, publisher; int stock;
    cout << "\n===== 添加图书 =====\n";
    cout << "图书编号: "; cin >> id;
    if (findBookById(id)) { cout << ">> 编号已存在。\n"; return; }
    cin.ignore();
    cout << "书    名: "; getline(cin, title);
    cout << "作    者: "; getline(cin, author);
    cout << "出 版 社: "; getline(cin, publisher);
    cout << "库存数量: "; cin >> stock;
    if (stock < 0) stock = 0;
    bookList.push_back(Book(id, title, author, publisher, stock));
    cout << ">> 添加成功。\n";
}

void LibrarySystem::removeBook() {
    string id;
    cout << "\n===== 删除图书 =====\n";
    cout << "图书编号: "; cin >> id;
    Book* b = findBookById(id);
    if (!b) { cout << ">> 未找到。\n"; return; }
    if (b->getAvailableStock() != b->getTotalStock()) {
        cout << ">> 有未归还副本，无法删除。\n"; return;
    }
    for (auto it = bookList.begin(); it != bookList.end(); ++it)
        if (it->getId() == id) { bookList.erase(it); cout << ">> 删除成功。\n"; return; }
}

void LibrarySystem::searchBook() const {
    int choice; string key;
    cout << "\n===== 查询图书 =====\n";
    cout << "1.按编号 2.按书名 3.按作者: "; cin >> choice; cin.ignore();
    for (const auto& b : bookList) {
        bool match = false;
        if (choice == 1 && b.getId() == key) { getline(cin, key); match = (b.getId() == key); }
        if (choice == 2) { cout << "书名: "; getline(cin, key); match = (b.getTitle().find(key) != string::npos); }
        if (choice == 3) { cout << "作者: "; getline(cin, key); match = (b.getAuthor().find(key) != string::npos); }
        if (match) b.display();
    }
}

void LibrarySystem::displayAllBooks() const {
    cout << "\n===== 全部图书 (" << bookList.size() << "本) =====\n";
    for (const auto& b : bookList) b.display();
}

// ========== 读者管理 ==========
void LibrarySystem::addReader() {
    string id, name, gender, phone;
    cout << "\n===== 添加学生读者 =====\n";
    cout << "读者编号: "; cin >> id;
    if (findReaderById(id)) { cout << ">> 编号已存在。\n"; return; }
    cin.ignore();
    cout << "姓    名: "; getline(cin, name);
    cout << "性    别: "; getline(cin, gender);
    cout << "电    话: "; getline(cin, phone);
    readerList.push_back(Reader(id, name, gender, phone));
    cout << ">> 添加成功（借期30天，上限5本）。\n";
}

void LibrarySystem::removeReader() {
    string id;
    cout << "\n===== 删除读者 =====\n";
    cout << "读者编号: "; cin >> id;
    Reader* r = findReaderById(id);
    if (!r) { cout << ">> 未找到。\n"; return; }
    for (auto it = readerList.begin(); it != readerList.end(); ++it)
        if (it->getId() == id) { readerList.erase(it); cout << ">> 删除成功。\n"; return; }
}

void LibrarySystem::searchReader() const {
    string id;
    cout << "\n===== 查询读者 =====\n读者编号: "; cin >> id;
    for (const auto& r : readerList) if (r.getId() == id) { r.display(); return; }
    cout << ">> 未找到。\n";
}

void LibrarySystem::displayAllReaders() const {
    cout << "\n===== 全部学生读者 (" << readerList.size() << "人) =====\n";
    for (const auto& r : readerList) r.display();
}

// ========== 教师管理 ==========
void LibrarySystem::addTeacher() {
    string id, name, gender, phone, dept;
    cout << "\n===== 添加教师 =====\n";
    cout << "工    号: "; cin >> id;
    if (findTeacherById(id)) { cout << ">> 工号已存在。\n"; return; }
    cin.ignore();
    cout << "姓    名: "; getline(cin, name);
    cout << "性    别: "; getline(cin, gender);
    cout << "电    话: "; getline(cin, phone);
    cout << "院    系: "; getline(cin, dept);
    teacherList.push_back(Teacher(id, name, gender, phone, dept));
    cout << ">> 添加成功（借期60天，上限10本）。\n";
}

void LibrarySystem::displayAllTeachers() const {
    cout << "\n===== 全部教师 (" << teacherList.size() << "人) =====\n";
    for (const auto& t : teacherList) t.display();
}

// ========== 借还管理 ==========
void LibrarySystem::borrowBook() {
    string bookId, personId;
    cout << "\n===== 借书 =====\n";
    cout << "图书编号: "; cin >> bookId;
    cout << "人员编号(学生学号/教师工号): "; cin >> personId;

    Book* b = findBookById(bookId);
    if (!b) { cout << ">> 图书不存在。\n"; return; }

    // 先找学生，再找老师，统一转成 Person*
    Reader* r = findReaderById(personId);
    Teacher* t = findTeacherById(personId);
    Person* p = nullptr;
    if (r) p = r;
    else if (t) p = t;
    else { cout << ">> 人员不存在。\n"; return; }

    // 多态：根据类型自动用对应的上限和借期
    bool canBorrow = r ? r->canBorrow() : t->canBorrow();
    if (!canBorrow) { cout << ">> 已达借书上限。\n"; return; }
    if (findActiveLoan(bookId, personId)) { cout << ">> 已借过此书。\n"; return; }
    if (!b->borrowOne()) { cout << ">> 库存不足。\n"; return; }

    string today = todayString();
    int days = p->getBorrowDays();       // 多态调用：学生30，老师60
    string due = addDays(today, days);
    string loanId = "L" + to_string(loanList.size() + 1);
    loanList.push_back(Loan(loanId, b, p, today, due));
    if (r) r->increaseBorrowCount();
    else t->increaseBorrowCount();
    p->addLoan(&loanList.back());   // 关键：把这条借阅记录挂到这个人身上

    cout << ">> 借书成功！借期" << days << "天，应还: " << due << "\n";
}

void LibrarySystem::returnBook() {
    string bookId, personId;
    cout << "\n===== 还书 =====\n";
    cout << "图书编号: "; cin >> bookId;
    cout << "人员编号: "; cin >> personId;

    Loan* l = findActiveLoan(bookId, personId);
    if (!l) { cout << ">> 未找到记录。\n"; return; }

    l->getBook()->returnOne();
    // 通过 Person* 多态减少计数
    Person* p = l->getPerson();
    Reader* r = findReaderById(p->getId());
    Teacher* t = findTeacherById(p->getId());
    if (r) r->decreaseBorrowCount();
    else if (t) t->decreaseBorrowCount();

    l->markReturned(todayString());
    cout << ">> 还书成功。\n";
}

void LibrarySystem::displayAllLoans() const {
    cout << "\n===== 全部借阅记录 (" << loanList.size() << "条) =====\n";
    for (const auto& l : loanList) l.display();
}

void LibrarySystem::displayPersonLoans() const {
    string id;
    cout << "\n===== 查询某人借阅记录 =====\n人员编号: "; cin >> id;

    // 先找学生
    for (auto& r : readerList) {
        if (r.getId() == id) { r.showMyLoans(); return; }
    }
    // 再找老师
    for (auto& t : teacherList) {
        if (t.getId() == id) { t.showMyLoans(); return; }
    }
    cout << ">> 人员不存在。\n";
}


// ========== 数据持久化 ==========
void LibrarySystem::loadData() {
    ifstream bf(BOOK_FILE);
    if (bf.is_open()) {
        string id, title, author, publisher; int total, avail;
        while (bf >> id >> total >> avail) {
            bf.ignore();
            getline(bf, title); getline(bf, author); getline(bf, publisher);
            Book b(id, title, author, publisher, total);
            b.setAvailableStock(avail);
            bookList.push_back(b);
        }
        bf.close();
    }
    ifstream rf(READER_FILE);
    if (rf.is_open()) {
        string id, name, gender, phone; int cur;
        while (rf >> id >> cur) {
            rf.ignore();
            getline(rf, name); getline(rf, gender); getline(rf, phone);
            Reader r(id, name, gender, phone);
            for (int i = 0; i < cur; i++) r.increaseBorrowCount();
            readerList.push_back(r);
        }
        rf.close();
    }
    ifstream tf(TEACHER_FILE);
    if (tf.is_open()) {
        string id, name, gender, phone, dept; int cur;
        while (tf >> id >> cur) {
            tf.ignore();
            getline(tf, name); getline(tf, gender); getline(tf, phone); getline(tf, dept);
            Teacher t(id, name, gender, phone, dept);
            for (int i = 0; i < cur; i++) t.increaseBorrowCount();
            teacherList.push_back(t);
        }
        tf.close();
    }
    ifstream lf(LOAN_FILE);
    if (lf.is_open()) {
        string lid, bid, pid, bdate, ddate, rdate; int ret;
        while (lf >> lid >> bid >> pid >> bdate >> ddate >> ret >> rdate) {
            Book* pb = findBookById(bid);
            Reader* pr = findReaderById(pid);
            Teacher* pt = findTeacherById(pid);
            Person* pp = pr ? (Person*)pr : (Person*)pt;
            Loan l(lid, pb, pp, bdate, ddate);
            if (ret == 1) l.markReturned(rdate);
            loanList.push_back(l);
        }
        lf.close();
    }
}

void LibrarySystem::saveData() {
    ofstream bf(BOOK_FILE, ios::trunc);
    for (const auto& b : bookList) {
        bf << b.getId() << " " << b.getTotalStock() << " " << b.getAvailableStock() << "\n";
        bf << b.getTitle() << "\n" << b.getAuthor() << "\n" << b.getPublisher() << "\n";
    }
    bf.close();
    ofstream rf(READER_FILE, ios::trunc);
    for (const auto& r : readerList) {
        rf << r.getId() << " " << r.getCurrentBorrowed() << "\n";
        rf << r.getName() << "\n" << r.getGender() << "\n" << r.getPhone() << "\n";
    }
    rf.close();
    ofstream tf(TEACHER_FILE, ios::trunc);
    for (const auto& t : teacherList) {
        tf << t.getId() << " " << t.getCurrentBorrowed() << "\n";
        tf << t.getName() << "\n" << t.getGender() << "\n" << t.getPhone() << "\n" << t.getDepartment() << "\n";
    }
    tf.close();
    ofstream lf(LOAN_FILE, ios::trunc);
    for (const auto& l : loanList) {
        string bid = l.getBook() ? l.getBook()->getId() : "UNKNOWN";
        string pid = l.getPerson() ? l.getPerson()->getId() : "UNKNOWN";
        lf << l.getId() << " " << bid << " " << pid << " "
            << l.getBorrowDate() << " " << l.getDueDate() << " "
            << (l.isReturned() ? 1 : 0) << " " << l.getReturnDate() << "\n";
    }
    lf.close();
}

// ========== 菜单 ==========
void LibrarySystem::showMenu() {
    cout << "\n========================================\n";
    cout << "       图书馆借阅管理系统 v2.0\n";
    cout << "========================================\n";
    cout << "  1. 添加图书\n  2. 删除图书\n  3. 查询图书\n  4. 显示全部图书\n";
    cout << "  5. 添加学生读者\n  6. 删除读者\n  7. 查询读者\n  8. 显示全部读者\n";
    cout << "  9. 添加教师\n 10. 显示全部教师\n";
    cout << " 11. 借书\n 12. 还书\n 13. 续借\n 14. 显示全部借阅记录\n 15. 查询某人借阅记录\n";
    cout << "  0. 保存并退出\n";
    cout << "========================================\n请输入选项: ";
}

void LibrarySystem::run() {
    int choice;
    while (true) {
        showMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ">> 输入无效。\n"; continue;
        }
        if (choice == 0) { saveData(); cout << ">> 已保存，再见！\n"; break; }
        switch (choice) {
        case 1: addBook(); break;
        case 2: removeBook(); break;
        case 3: searchBook(); break;
        case 4: displayAllBooks(); break;
        case 5: addReader(); break;
        case 6: removeReader(); break;
        case 7: searchReader(); break;
        case 8: displayAllReaders(); break;
        case 9: addTeacher(); break;
        case 10: displayAllTeachers(); break;
        case 11: borrowBook(); break;
        case 12: returnBook(); break;
        case 13: renewLoan(); break;
        case 14: displayAllLoans(); break;
        case 15: displayPersonLoans(); break;
        default: cout << ">> 无效选项。\n"; break;
        }
    }
}

void LibrarySystem::renewLoan() {
    string bookId, personId;
    cout << "\n===== 续借 =====\n";
    cout << "图书编号: "; cin >> bookId;
    cout << "人员编号: "; cin >> personId;

    Loan* l = findActiveLoan(bookId, personId);
    if (!l) { cout << ">> 未找到未归还记录。\n"; return; }

    Person* p = l->getPerson();
    p->renewLoan(l);    // 多态：学生延30天，老师延60天
    cout << ">> 续借成功！新的应还日期: " << l->getDueDate() << "\n";
}
