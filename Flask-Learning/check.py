# 读取全部文件，返回列表
import os

import pandas as pd


def read_all_file(path):
    file_list = []
    for root, dirs, files in os.walk(path):
        for file in files:
            file_list.append(os.path.join(root, file))
    return file_list


file = read_all_file('F:\破事\OneDrive\个人发展管理')
length = len(file)
for i in range(length):
    file[i] = file[i].split('\\')[-1][:3]

# 新建一个数组从062到120
file2 = []
for i in range(61, 121):
    file2.append(str(i).zfill(3))
# 求差集
file3 = list(set(file2).difference(set(file)))
# 去掉file3中的0
for i in range(len(file3)):
    file3[i] = int(file3[i])

# 读取当前目录Excel
import os

# 打开文件
path = '1.xlsx'
name = pd.read_excel(io='1.xlsx')
# 读取第一列，第二行的数据
# print(name.iloc[1, 0])

name_dict = {}
for i in range(60):
    name_dict[name.iloc[i, 1]] = name.iloc[i, 0]

count = 0
for i in range(len(file3)):
    if name_dict[file3[i]] != -1:
        if count % 6 == 0:
            print('')
        count += 1
        print('\t' + name_dict[file3[i]], end=' ')