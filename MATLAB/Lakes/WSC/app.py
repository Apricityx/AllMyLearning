import Lakes.utility as utility
import matplotlib.pyplot as plt
import numpy as np

# 对第一个湖进行分析

EI1 = 0  # 环境因素的影响
DI1 = 0  # 人类控制大坝造成的影响
EI2 = 0
EI3 = 0
DI3 = 0
EI4 = 0
WL1 = 180  # 水位

init_WL1 = 180  # 初始水位
init_WL2 = 180
init_WL3 = 180
init_WL4 = 180
# 7830.797 * x * x - 2874834.81 * x + 263854013
# func2 = -23110.859 * x * x + 8176009.57 * x - 72131092
# func3 = -420.923 * x * x + 148775.82 * x - 1313
# func4 = 4269.429 * x * x - 637633.71 * x + 2384038


init_Lake1_radius = 1000
init_Lake2_radius = 1000
init_Lake3_radius = 1000
init_Lake4_radius = 1000
init_Lake1_height = 406 * 0.3
init_Lake2_height = 281 * 0.3
init_Lake3_height = 61 * 0.3
init_Lake4_height = 100 * 0.3


def func1(x):
    return 7830.797 * x * x - 2874834.81 * x + 263854013


def func2(x):
    return -23110.859 * x * x + 8176009.57 * x - 72131092


def func3(x):
    return -420.923 * x * x + 148775.82 * x - 1313


def func4(x):
    return 4269.429 * x * x - 637633.71 * x + 2384038


time = 60 * 60 * 24 * 30  # 一个月的秒数
WSC1 = EI1 + DI1 - func1(WL1) * time
WL2 = init_WL2 + utility.get_height_change(init_Lake1_radius, init_Lake1_height, WSC1)
WSC2 = EI2 - DI1 - func2(WL2) * time + func1(WL2) * time
WL3 = init_WL3 + utility.get_height_change(init_Lake2_radius, init_Lake2_height, WSC2)
WSC3 = EI3 + DI3 - func3(WL3) * time + func2(WL3) * time
WSC4 = EI4 - func4(WL3) * time + func3(WL3) * time - DI3
 