#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
#include "Entity.h"

class Loan;   // 前向声明

// 中间层基类：人，继承 Entity（id），增加姓名/性别/电话
class Person : public Entity {
protected:
    std::string name;
    std::string gender;
    std::string phone;
    std::vector<Loan*> myLoans;    // 这个人自己的借阅记录


public:
    Person();
    Person(std::string id, std::string n, std::string g, std::string p);
    virtual ~Person() {}

    std::string getName() const;
    std::string getGender() const;
    std::string getPhone() const;

    void setName(const std::string& n);
    void setGender(const std::string& g);
    void setPhone(const std::string& p);

    virtual int getBorrowDays() const = 0;
    virtual int getMaxBorrowLimit() const = 0;
    virtual void display() const = 0;

    void addLoan(Loan* l);
    virtual void renewLoan(Loan* l);    // 续借：延长借期
    void showMyLoans() const;
};

#endif // PERSON_H
