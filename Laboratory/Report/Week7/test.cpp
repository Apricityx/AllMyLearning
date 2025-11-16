#include <cstdlib> // 包含 system 函数
#include <iostream> // 包含输入输出流
#include <Windows.h> // 包含 Sleep 函数

int main() {
    std::cout << "Starting to ping www.bing.com continuously...\n";
    while (true) {
        // 执行 ping 命令，-t 表示持续 ping
        system("ping www.bing.com -t");
        // 如果 ping 命令意外退出，等待 1 秒后重试
        Sleep(1000);
    }
    return 0;
}