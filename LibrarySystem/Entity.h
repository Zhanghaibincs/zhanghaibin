#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <string>

// 最顶层基类：所有实体都有唯一编号
class Entity {
protected:
    std::string id;       // 唯一编号（Book的编号、Reader的学号、Loan的借阅号都用它）

public:
    Entity() {}
    Entity(std::string i) : id(i) {}
    virtual ~Entity() {}

    std::string getId() const { return id; }
    void setId(const std::string& i) { id = i; }
};

#endif // ENTITY_H
