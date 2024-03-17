import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(74, 190, 1000)
func1 = 7830.797 * x * x - 2874834.81 * x + 263854013
func2 = -23110.859 * x * x + 8176009.57 * x - 72131092
func3 = -420.923 * x * x + 148775.82 * x - 1313
func4 = 4269.429 * x * x - 637633.71 * x + 2384038

plt.plot(x, func1, label='Lake 1')
plt.plot(x, func2, label='Lake 2')
plt.plot(x, func3, label='Lake 3')
plt.plot(x, func4, label='Lake 4')

plt.xlabel('Water Level')
plt.ylabel('Token')
plt.legend()
plt.show()
