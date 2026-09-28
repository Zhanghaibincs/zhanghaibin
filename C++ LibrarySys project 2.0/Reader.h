#ifndef READER_H
#define READER_H

#include <string>

// 读者类：封装读者基本信息
class Reader {
private:
    std::string readerId;     // 读者编号（唯一）
    std::string name;         // 姓名
    std::string gender;       // 性别
    std::string phone;        // 联系电话
    int maxBorrowLimit;       // 最大可借数量
    int currentBorrowed;      // 当前已借数量

public:
    // 构造函数
    Reader();
    Reader(std::string id, std::string n, std::string g, std::string p, int limit = 5);

    // Getter
    std::string getReaderId() const;
    std::string getName() const;
    std::string getGender() const;
    std::string getPhone() const;
    int getMaxBorrowLimit() const;
    int getCurrentBorrowed() const;

    // Setter
    void setReaderId(const std::string& id);
    void setName(const std::string& n);
    void setGender(const std::string& g);
    void setPhone(const std::string& p);
    void setMaxBorrowLimit(int limit);

    // 业务方法
    bool canBorrow() const;                    // 是否还能继续借书
    bool increaseBorrowCount();                // 借书计数 +1
    bool decreaseBorrowCount();                // 还书计数 -1
    void display() const;                     // 打印读者信息
};

#endif // READER_H

