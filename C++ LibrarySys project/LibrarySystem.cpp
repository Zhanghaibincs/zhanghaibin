#include "LibrarySystem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <limits>

using namespace std;

// ========== 构造与析构 ==========
LibrarySystem::LibrarySystem() {
    loadData();
}

LibrarySystem::~LibrarySystem() {
    saveData();
}

// ========== 内部工具 ==========
Book* LibrarySystem::findBookById(const string& id) {
    for (auto& b : bookList) {
        if (b.getBookId() == id) return &b;
    }
    return nullptr;
}

Reader* LibrarySystem::findReaderById(const string& id) {
    for (auto& r : readerList) {
        if (r.getReaderId() == id) return &r;
    }
    return nullptr;
}

Loan* LibrarySystem::findActiveLoan(const string& bookId, const string& readerId) {
    for (auto& l : loanList) {
        if (!l.isReturned() && l.getBookId() == bookId && l.getReaderId() == readerId) {
            return &l;
        }
    }
    return nullptr;
}

string LibrarySystem::todayString() const {
    time_t now = time(nullptr);
    struct tm t;
    localtime_s(&t, &now);
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
    t.tm_year = y - 1900;
    t.tm_mon = m - 1;
    t.tm_mday = d + days;
    time_t when = mktime(&t);
    struct tm out;
    localtime_s(&out, &when);
    ostringstream oss;
    oss << out.tm_year + 1900 << "-"
        << setw(2) << setfill('0') << out.tm_mon + 1 << "-"
        << setw(2) << setfill('0') << out.tm_mday;
    return oss.str();
}

// ========== 图书管理 ==========
void LibrarySystem::addBook() {
    string id, title, author, publisher;
    int stock;
    cout << "\n===== 添加图书 =====\n";
    cout << "图书编号: "; cin >> id;
    if (findBookById(id) != nullptr) {
        cout << ">> 该编号已存在，添加失败。\n";
        return;
    }
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
    cout << "输入要删除的图书编号: "; cin >> id;
    Book* b = findBookById(id);
    if (!b) { cout << ">> 未找到该图书。\n"; return; }
    if (b->getAvailableStock() != b->getTotalStock()) {
        cout << ">> 该书尚有未归还副本，无法删除。\n";
        return;
    }
    for (auto it = bookList.begin(); it != bookList.end(); ++it) {
        if (it->getBookId() == id) {
            bookList.erase(it);
            cout << ">> 删除成功。\n";
            return;
        }
    }
}

void LibrarySystem::searchBook() const {
    int choice;
    string key;
    cout << "\n===== 查询图书 =====\n";
    cout << "1. 按编号查询\n2. 按书名查询\n3. 按作者查询\n请选择: ";
    cin >> choice;
    cin.ignore();
    vector<Book*> results;
    if (choice == 1) {
        cout << "图书编号: "; getline(cin, key);
        for (auto& b : bookList) if (b.getBookId() == key) results.push_back(const_cast<Book*>(&b));
    }
    else if (choice == 2) {
        cout << "书    名: "; getline(cin, key);
        for (auto& b : bookList) if (b.getTitle().find(key) != string::npos) results.push_back(const_cast<Book*>(&b));
    }
    else if (choice == 3) {
        cout << "作    者: "; getline(cin, key);
        for (auto& b : bookList) if (b.getAuthor().find(key) != string::npos) results.push_back(const_cast<Book*>(&b));
    }
    else {
        cout << ">> 无效选择。\n";
        return;
    }
    if (results.empty()) { cout << ">> 未找到匹配图书。\n"; return; }
    for (auto* p : results) p->display();
}

void LibrarySystem::displayAllBooks() const {
    cout << "\n===== 全部图书 (共 " << bookList.size() << " 本) =====\n";
    for (const auto& b : bookList) b.display();
}

// ========== 读者管理 ==========
void LibrarySystem::addReader() {
    string id, name, gender, phone;
    cout << "\n===== 添加读者 =====\n";
    cout << "读者编号: "; cin >> id;
    if (findReaderById(id) != nullptr) {
        cout << ">> 该编号已存在，添加失败。\n";
        return;
    }
    cin.ignore();
    cout << "姓    名: "; getline(cin, name);
    cout << "性    别: "; getline(cin, gender);
    cout << "联系电话: "; getline(cin, phone);
    readerList.push_back(Reader(id, name, gender, phone));
    cout << ">> 添加成功。\n";
}

void LibrarySystem::removeReader() {
    string id;
    cout << "\n===== 删除读者 =====\n";
    cout << "输入要删除的读者编号: "; cin >> id;
    Reader* r = findReaderById(id);
    if (!r) { cout << ">> 未找到该读者。\n"; return; }
    if (r->getCurrentBorrowed() > 0) {
        cout << ">> 该读者尚有未归还图书，无法删除。\n";
        return;
    }
    for (auto it = readerList.begin(); it != readerList.end(); ++it) {
        if (it->getReaderId() == id) {
            readerList.erase(it);
            cout << ">> 删除成功。\n";
            return;
        }
    }
}

void LibrarySystem::searchReader() const {
    string id;
    cout << "\n===== 查询读者 =====\n";
    cout << "读者编号: "; cin >> id;
    for (const auto& r : readerList) {
        if (r.getReaderId() == id) { r.display(); return; }
    }
    cout << ">> 未找到该读者。\n";
}

void LibrarySystem::displayAllReaders() const {
    cout << "\n===== 全部读者 (共 " << readerList.size() << " 人) =====\n";
    for (const auto& r : readerList) r.display();
}

// ========== 借阅管理 ==========
void LibrarySystem::borrowBook() {
    string bookId, readerId;
    cout << "\n===== 借书 =====\n";
    cout << "图书编号: "; cin >> bookId;
    cout << "读者编号: "; cin >> readerId;

    Book* b = findBookById(bookId);
    Reader* r = findReaderById(readerId);
    if (!b) { cout << ">> 图书不存在。\n"; return; }
    if (!r) { cout << ">> 读者不存在。\n"; return; }
    if (!r->canBorrow()) { cout << ">> 读者已达借书上限。\n"; return; }
    if (findActiveLoan(bookId, readerId) != nullptr) {
        cout << ">> 该读者已借过此书，不能重复借阅。\n"; return;
    }
    if (!b->borrowOne()) { cout << ">> 该书已全部借出，暂无可借副本。\n"; return; }

    string today = todayString();
    string due = addDays(today, 30);
    string loanId = "L" + to_string(loanList.size() + 1);
    loanList.push_back(Loan(loanId, bookId, readerId, today, due));
    r->increaseBorrowCount();
    cout << ">> 借书成功！应还日期: " << due << "\n";
}

void LibrarySystem::returnBook() {
    string bookId, readerId;
    cout << "\n===== 还书 =====\n";
    cout << "图书编号: "; cin >> bookId;
    cout << "读者编号: "; cin >> readerId;

    Loan* l = findActiveLoan(bookId, readerId);
    if (!l) { cout << ">> 未找到对应的未归还借阅记录。\n"; return; }

    Book* b = findBookById(bookId);
    Reader* r = findReaderById(readerId);
    if (b) b->returnOne();
    if (r) r->decreaseBorrowCount();
    l->markReturned(todayString());
    cout << ">> 还书成功。\n";
}

void LibrarySystem::displayAllLoans() const {
    cout << "\n===== 全部借阅记录 (共 " << loanList.size() << " 条) =====\n";
    for (const auto& l : loanList) l.display();
}

// ========== 数据持久化 ==========
void LibrarySystem::loadData() {
    // 读图书
    ifstream bf(BOOK_FILE);
    if (bf.is_open()) {
        string id, title, author, publisher;
        int total, avail;
        while (bf >> id >> total >> avail) {
            bf.ignore();
            getline(bf, title);
            getline(bf, author);
            getline(bf, publisher);
            Book b(id, title, author, publisher, total);
            b.setAvailableStock(avail);
            bookList.push_back(b);
        }
        bf.close();
    }
    // 读读者
    ifstream rf(READER_FILE);
    if (rf.is_open()) {
        string id, name, gender, phone;
        int limit, cur;
        while (rf >> id >> limit >> cur) {
            rf.ignore();
            getline(rf, name);
            getline(rf, gender);
            getline(rf, phone);
            Reader r(id, name, gender, phone, limit);
            for (int i = 0; i < cur; i++) r.increaseBorrowCount();
            readerList.push_back(r);
        }
        rf.close();
    }
    // 读借阅
    ifstream lf(LOAN_FILE);
    if (lf.is_open()) {
        string lid, bid, rid, bdate, ddate, rdate;
        int ret;
        while (lf >> lid >> bid >> rid >> bdate >> ddate >> ret >> rdate) {
            Loan l(lid, bid, rid, bdate, ddate);
            if (ret == 1) l.markReturned(rdate);
            loanList.push_back(l);
        }
        lf.close();
    }
}

void LibrarySystem::saveData() {
    // 存图书
    ofstream bf(BOOK_FILE, ios::trunc);
    if (bf.is_open()) {
        for (const auto& b : bookList) {
            bf << b.getBookId() << " " << b.getTotalStock() << " " << b.getAvailableStock() << "\n";
            bf << b.getTitle() << "\n";
            bf << b.getAuthor() << "\n";
            bf << b.getPublisher() << "\n";
        }
        bf.close();
    }
    // 存读者
    ofstream rf(READER_FILE, ios::trunc);
    if (rf.is_open()) {
        for (const auto& r : readerList) {
            rf << r.getReaderId() << " " << r.getMaxBorrowLimit() << " " << r.getCurrentBorrowed() << "\n";
            rf << r.getName() << "\n";
            rf << r.getGender() << "\n";
            rf << r.getPhone() << "\n";
        }
        rf.close();
    }
    // 存借阅
    ofstream lf(LOAN_FILE, ios::trunc);
    if (lf.is_open()) {
        for (const auto& l : loanList) {
            lf << l.getLoanId() << " " << l.getBookId() << " " << l.getReaderId() << " "
                << l.getBorrowDate() << " " << l.getDueDate() << " "
                << (l.isReturned() ? 1 : 0) << " " << l.getReturnDate() << "\n";
        }
        lf.close();
    }
}

// ========== 菜单 ==========
void LibrarySystem::showMenu() {
    cout << "\n";
    cout << "========================================\n";
    cout << "       图书馆借阅管理系统 v1.0\n";
    cout << "========================================\n";
    cout << "  1. 添加图书\n";
    cout << "  2. 删除图书\n";
    cout << "  3. 查询图书\n";
    cout << "  4. 显示全部图书\n";
    cout << "  5. 添加读者\n";
    cout << "  6. 删除读者\n";
    cout << "  7. 查询读者\n";
    cout << "  8. 显示全部读者\n";
    cout << "  9. 借书\n";
    cout << " 10. 还书\n";
    cout << " 11. 显示全部借阅记录\n";
    cout << "  0. 保存并退出\n";
    cout << "========================================\n";
    cout << "请输入选项: ";
}

void LibrarySystem::run() {
    int choice;
    while (true) {
        showMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ">> 输入无效，请重新输入数字。\n";
            continue;
        }
        if (choice == 0) {
            saveData();
            cout << ">> 数据已保存，感谢使用，再见！\n";
            break;
        }
        switch (choice) {
        case 1: addBook(); break;
        case 2: removeBook(); break;
        case 3: searchBook(); break;
        case 4: displayAllBooks(); break;
        case 5: addReader(); break;
        case 6: removeReader(); break;
        case 7: searchReader(); break;
        case 8: displayAllReaders(); break;
        case 9: borrowBook(); break;
        case 10: returnBook(); break;
        case 11: displayAllLoans(); break;
        default: cout << ">> 无效选项。\n"; break;
        }
    }
}
