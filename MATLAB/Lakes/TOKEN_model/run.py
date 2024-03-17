import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


def process_corridors():
    data = []
    divide = [0.4, 0.7]
    # 转换需要的类型为区间 定量
    df = pd.read_csv('src/requirement.csv', sep='\t', header=0)
    flag = 1
    for i in range(1, len(df) + 1):  # j为第几个湖，从1开始
        temp = df.iloc[i - 1].values[0]
        temp = temp.replace(' ', '')
        temp = temp.split(',')
        data.append(temp)
    for i in range(0, len(data)):  # i为第几个湖
        for j in range(1, len(data[0])):  # j指的是第几个值
            if data[i][j] == 'Low':
                data[i][j] = (0, divide[0])
            elif data[i][j] == 'Middle':
                data[i][j] = (divide[0], divide[1])
            else:
                data[i][j] = (divide[1], 1)
    for obj in data:
        # 删除第一个
        obj.pop(0)
    return data


preference = process_corridors()
print(preference)


def get_weight():
    df = pd.read_csv('src/weight.csv', sep='\t', header=0)
    weight = []
    for i in range(0, len(df)):
        temp = df.iloc[i].values[0]
        temp = temp.replace(' ', '')
        temp = temp.split(',')
        weight.append(temp)
    for i in range(0, len(weight)):
        for j in range(1, len(weight[0])):
            weight[i][j] = float(weight[i][j])
    for obj in weight:
        # 删除第一个
        obj.pop(0)
    return weight


weights = get_weight()
print(weights)


def get_token(check_nums):
    tokens_list = []
    for check_num in check_nums:
        tokens = []
        for i in range(0, len(preference)):
            token = 0
            for j in range(0, len(preference[0])):
                if preference[i][j][0] <= check_num < preference[i][j][1]:
                    token += weights[i][j] * 1
                elif preference[i][j][0] > check_num:
                    token += weights[i][j] * (1 - abs(preference[i][j][0] - check_num))
                elif preference[i][j][1] <= check_num:
                    token += weights[i][j] * (1 - abs(preference[i][j][1] - check_num))
            tokens.append(token)
        tokens_list.append(tokens[0])  # 第一个湖的token
    return tokens_list


# 开始绘图

x = np.linspace(0, 1, 100)
y = get_token(x)
plt.plot(x, y)
# 设置横坐标为水位
plt.xlabel('Water Level')
# 设置纵坐标为Token
plt.ylabel('Token')
# 设置label字体为宋体
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.show()
