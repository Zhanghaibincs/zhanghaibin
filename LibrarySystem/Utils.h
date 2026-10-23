#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

// 泛型查找函数模板：在 vector<T> 中按 id 查找元素
// T 必须有 getId() 方法
template<typename T>
T* findById(std::vector<T>& container, const std::string& id) {
    for (auto& item : container) {
        if (item.getId() == id) {
            return &item;
        }
    }
    return nullptr;
}

// 泛型 const 版本：在 const vector<T> 中按 id 查找
template<typename T>
const T* findById(const std::vector<T>& container, const std::string& id) {
    for (const auto& item : container) {
        if (item.getId() == id) {
            return &item;
        }
    }
    return nullptr;
}

#endif // UTILS_H
#pragma once
