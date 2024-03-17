# 将注释全部转换为英文
import sympy


# This algorithm is based on the assumption that the water level of the lake has not changed significantly
# Because the change in the water level of the lake is not large, the change in the radius of the lake can be ignored
def get_height_change(H, r, x):
    # This function is used to calculate the change in water level

    # Input data description: H, r is the height and radius of the lake at a certain moment, and x is the change in
    # water level x = sympy.Symbol("x") specifies x as a symbolic variable
    h = sympy.Symbol("h")  # Specifies h as a symbolic variable
    pi = 3.14159265358979323846  # Define pi
    equation = sympy.Eq((2 * pi * (r * h + ((h * h) / (2 * H)))) - x, 0)
    # Solve the equation
    result = sympy.solve(equation, h)
    # Return the positive solution
    for i in result:
        if i > 0:
            return i
    return result


def get_volume_change(H, r, h):
    # This function is used to calculate the change in water volume Input data description: H, r is the height and
    # radius of the lake at a certain moment, and h is the change in water level
    pi = 3.14159265358979323846  # Define pi
    # Calculate the volume change
    volume_change = pi * (r * h + ((h * h) / (2 * H))) * h
    return volume_change


print(get_volume_change(100, 1000, 1))

# import sympy
#
#
# # 此算法建立在湖的水位没有发生剧烈变化的情况下
# # 因为湖的水位变化量不大，所以可以忽略湖的半径变化
# def get_height_change(H, r, x):
#     # 此函数用于计算水位变化
#
#     # 输入数据说明：H，r为湖在某一时刻的高度与半径，x为水位变化量
#     # x = sympy.Symbol("x") 规定x为符号变量
#     h = sympy.Symbol("h")  # 规定h为符号变量
#     pi = 3.14159265358979323846  # 定义pi
#     equation = sympy.Eq((2 * pi * (r * h + ((h * h) / (2 * H)))) - x, 0)
#     # 解方程
#     result = sympy.solve(equation, h)
#     # 返回正解
#     for i in result:
#         if i > 0:
#             return i
#     return result
#
#
# def get_volume_change(H, r, h):
#     # 此函数用于计算水体体积变化
#     # 输入数据说明：H，r为湖在某一时刻的高度与半径，h为水位变化量
#     pi = 3.14159265358979323846  # 定义pi
#     # 计算体积变化
#     volume_change = pi * (r * h + ((h * h) / (2 * H))) * h
#     return volume_change
#
#
# print(get_volume_change(100, 1000, 1))
