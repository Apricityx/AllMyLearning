import numpy as np

arr = np.arange(1, 31)
arr1 = arr.reshape(5, 6)
arr_red = arr1[:, :2]
arr_blue = arr1[1:4, 2:5]
arr_green = arr1[3:5, 1:6]
# print(arr)
print(arr1)
print("\n")
print(arr_red)
print("\n")
print(arr_blue)
print("\n")
print(arr_green)
