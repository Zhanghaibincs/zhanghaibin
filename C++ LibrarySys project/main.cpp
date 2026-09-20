// 图书馆借阅管理系统 - 主入口
#include "LibrarySystem.h"
#include <iostream>

int main() {
    // 设置控制台为 UTF-8，避免中文乱码
    system("chcp 936 > nul");

    LibrarySystem sys;
    sys.run();
    return 0;
}
