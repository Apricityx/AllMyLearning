import pandas as pd

df = pd.read_excel("src/Data.xlsx")
# 读取第一行数据
years = df.columns.values.tolist()
# 读取第2行数据
nums = df.iloc[0].values.tolist()
years = [years[i][:-1] for i in range(0, len(years))]
years = [years[i].replace("年", ".") for i in range(0, len(years))]
years = [float(years[i]) for i in range(0, len(years))]
# def get_beta(data):
#     lxx =
# 转换列表为字符串
print(years)
print(nums)


def get_test():
    return "test"


def get_years():
    return years


def get_nums():
    return nums


def get_alpha():
    return alpha


def get_beta1():
    return beta


def get_beta(listX, listY):
    def square(x):
        return x * x

    x_arv = sum(listX) / len(listX)
    y_arv = sum(listY) / len(listY)
    lxx = sum([square(listX[i] - x_arv) for i in range(0, len(listX))])

    lxy = sum([(listX[i] - x_arv) * (listY[i] - y_arv) for i in range(0, len(listX))])
    return lxy / lxx


beta = get_beta(years, nums)
x_arve = sum(years) / len(years)
y_arve = sum(nums) / len(nums)
print(x_arve)
print(y_arve)
alpha = y_arve - beta * x_arve
print(alpha)
print(beta)
