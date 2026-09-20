#ifndef LOAN_H
#define LOAN_H

#include <string>

// 借阅记录类：封装一条借书流水
class Loan {
private:
    std::string loanId;        // 借阅记录编号（唯一）
    std::string bookId;        // 所借图书编号
    std::string readerId;      // 借书读者编号
    std::string borrowDate;    // 借出日期
    std::string dueDate;       // 应还日期
    std::string returnDate;    // 实际归还日期，空串表示未还
    bool returned;             // 是否已归还

public:
    // 构造函数
    Loan();
    Loan(std::string lid, std::string bid, std::string rid,
        std::string borrow, std::string due);

    // Getter
    std::string getLoanId() const;
    std::string getBookId() const;
    std::string getReaderId() const;
    std::string getBorrowDate() const;
    std::string getDueDate() const;
    std::string getReturnDate() const;
    bool isReturned() const;

    // 业务方法
    void markReturned(const std::string& actualReturnDate);  // 标记为已归还
    void display() const;                                     // 打印借阅记录
};

#endif // LOAN_H

