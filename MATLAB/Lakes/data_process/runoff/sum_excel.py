import pandas as pd
import os

result = [i for i in range(12)]
data = []
temp = []
# 获取目录下所有文件名
file_list = os.listdir('src')
for file in file_list:
    # 读取csv文件
    df = pd.read_csv('src/' + file, sep='\t', header=0)
    # 读取每一行
    for i in range(len(df)):
        temp = df.iloc[i].values[0]
        # 删除temp中所有的空格
        temp = temp.replace(' ', '')
        temp = temp.split(',')
        if temp[0] == '2018':
            data.append(temp)
for obj in data:
    for i in range(12):
        result[i] += float(obj[i + 1])
print('径流如下：')
print(result)


