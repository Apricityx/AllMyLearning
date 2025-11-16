import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
# from matplotlib import rcParams

# 设置字体为 SimHei（黑体）以支持中文
# rcParams['font.sans-serif'] = ['SimHei']  # 使用黑体
# rcParams['axes.unicode_minus'] = False  # 解决负号显示问题
# 读取数据
data = {
    "Number of values": [
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
        30,
        31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58,
        59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
        87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99
    ],
    "The height of the tree": [
        0, 1, 2, 3, 3, 4, 4, 4, 4, 6, 5, 5, 7, 6, 6, 7, 6, 6, 6, 7, 7, 7, 9, 9, 7, 8, 7, 10, 12, 8, 8, 11, 11, 8, 10, 8,
        10, 9, 8, 9, 10, 9, 14, 12, 10, 11, 11, 14, 10, 10, 10, 11, 11, 9, 10, 12, 12, 11, 10, 13, 12, 12, 12, 11, 12,
        13, 13, 12, 10, 12, 11, 11, 11, 10, 18, 12, 10, 15, 12, 12, 10, 13, 11, 13, 11, 13, 15, 12, 12, 15, 13, 11, 12,
        14, 16, 12, 11, 13, 13, 15,
    ]
}

df = pd.DataFrame(data)

# 提取元素个数和树高
x = df["Number of values"]
y = df["The height of the tree"]

# 绘制散点图
plt.figure(figsize=(10, 6))
plt.scatter(x, y, color='blue', label='Data')

# 拟合曲线 (使用二次多项式拟合)
coefficients = np.polyfit(x, y, 2)  # 二次多项式拟合
polynomial = np.poly1d(coefficients)

# 生成拟合曲线
x_fit = np.linspace(0, 100, 500)
y_fit = polynomial(x_fit)

# 绘制拟合曲线
plt.plot(x_fit, y_fit, color='red', label='The fitting curve')

# 图表标题和标签
plt.title("The relationship between the number of values and the height of the tree", fontsize=16)
plt.xlabel("Number of values", fontsize=14)
plt.ylabel("The height of the tree", fontsize=14)
plt.legend(fontsize=12)
plt.grid(True)

# 显示图表
plt.show()
