from copy import deepcopy


def echo(text):
    print(text)
    return text


class Topsis:
    # Topsis标准工作流：
    # 1. 读取数据
    # 2. 四种数据类型转换并归一化
    # 3. 计算比重p
    # 4. 计算信息熵E
    # 5. 计算权重W
    # 6. 拼接矩阵
    #
    # 7. 计算得分
    # 8. 获得最优解
    def __init__(self):
        pass

    def read_excel(self, file, column):
        import pandas as pd
        import openpyxl
        temp = pd.read_excel(file)
        return temp[column].tolist()

    def forward_type_transform(self, data):
        best = max(data)
        worst = min(data)

        def process(self, best, worst, num):
            return (num - worst) / (best - worst)

        for i in range(0, len(data)):
            data[i] = process(self, best, worst, data[i])
        return data

    def backward_type_transform(self, data):
        for i in range(0, len(data)):
            M = max(data)
            data[i] = M - data[i]
        data = self.forward_type_transform(data)
        return data

    def middle_type_transform(self, data, best):
        M = max([abs(data[i] - best) for i in range(0, len(data))])
        for i in range(0, len(data)):
            data[i] = 1 - abs((data[i] - best) / M)
        return data

    def range_type_transform(self, data, bestRange):
        Min = min(data)
        Max = max(data)
        a = bestRange[0]
        b = bestRange[1]
        M = max([a - Min, Max - b])
        for i in range(0, len(data)):
            if data[i] < a:
                data[i] = 1 - (a - data[i]) / M
            elif data[i] > b:
                data[i] = 1 - (data[i] - b) / M
            else:
                data[i] = 1
        return self.forward_type_transform(data)

    def get_E(self, data):
        import math
        S = sum(data)
        for i in range(0, len(data)):
            data[i] = data[i] / S
        for i in range(0, len(data)):
            if data[i] == 0:
                data[i] = 0
            else:
                data[i] = data[i] * math.log(data[i])
        return -1 * sum(data) * (1 / math.log(len(data)))

    def get_W(self, allData):
        E = [0 for j in range(0, len(allData))]
        W = [0 for j in range(0, len(allData))]
        for i in range(0, len(allData)):
            E[i] = self.get_E(allData[i])
        for i in range(0, len(E)):
            W[i] = (1 - E[i]) / (len(E) - sum(E))
        return W


topsis = Topsis()
ox = topsis.read_excel("src/Learning.xlsx", "含氧量(ppm)")
ox = topsis.forward_type_transform(ox)

ph = topsis.read_excel("src/Learning.xlsx", "PH值")
ph = topsis.middle_type_transform(ph, 7)

bacteria = topsis.read_excel("src/Learning.xlsx", "细菌总数(个/mL)")
bacteria = topsis.backward_type_transform(bacteria)

ppm = topsis.read_excel("src/Learning.xlsx", "植物性营养物量(ppm)")
ppm = topsis.range_type_transform(ppm, [10, 20])
# 至此，计算熵值E完毕，接下来计算权重w
data = [ox, ph, bacteria, ppm]
data_p = deepcopy(data)
W = topsis.get_W(data)
result = []
for i in range(0, len(data[0])):
    S = 0
    for j in range(0, len(W)):
        S = S + W[j] * data_p[j][i] * 100
    result.append(S)

print(result)
# 将result写入excel表的Result列
import pandas as pd
import openpyxl

df = pd.read_excel("src/Learning.xlsx")
df["Result"] = result
df.to_excel("src/Learning.xlsx", index=False)
