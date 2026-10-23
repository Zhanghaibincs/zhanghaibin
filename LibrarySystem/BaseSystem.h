#pragma once
#ifndef BASE_SYSTEM_H
#define BASE_SYSTEM_H

// 系统基类：所有管理系统的通用接口
class BaseSystem {
public:
    virtual ~BaseSystem() {}

    virtual void run() = 0;           // 启动主循环
    virtual void loadData() = 0;      // 加载数据
    virtual void saveData() = 0;      // 保存数据
};

#endif // BASE_SYSTEM_H
