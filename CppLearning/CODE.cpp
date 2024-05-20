#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream file;
    file.open("test.txt");
    if (!file) cout << "文件打开失败" << endl;
    string file_content;
    file >> file_content;
    cout << "内容为" << file_content << endl;
    // ifstream 和 ofstream 是文件输入输出流，用于读取和写入文件
    // ifstream对象只能用于读取文件 i 代表input, f 代表file
    return 0;
}