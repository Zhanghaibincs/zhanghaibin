#include "Person.h"
#include <iostream>
#include "Loan.h"

Person::Person() {}

Person::Person(std::string id, std::string n, std::string g, std::string p)
    : Entity(id), name(n), gender(g), phone(p) {
}

std::string Person::getName() const { return name; }
std::string Person::getGender() const { return gender; }
std::string Person::getPhone() const { return phone; }

void Person::setName(const std::string& n) { name = n; }
void Person::setGender(const std::string& g) { gender = g; }
void Person::setPhone(const std::string& p) { phone = p; }

void Person::addLoan(Loan* l) {
    myLoans.push_back(l);
}

void Person::showMyLoans() const {
    if (myLoans.empty()) {
        std::cout << ">> 暂无借阅记录。\n";
        return;
    }
    std::cout << "\n----- " << name << " 的借阅记录 (" << myLoans.size() << "条) -----\n";
    for (const auto& l : myLoans) l->display();
}

void Person::renewLoan(Loan* l) {
    l->renew(getBorrowDays());
}
