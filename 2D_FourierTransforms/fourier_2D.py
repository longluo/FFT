import numpy as np
import matplotlib.pyplot as plt

print('1D Random Array: ', np.random.random(10))

print('\n 2D Random Array: ', np.random.random((2, 5)))

print('\n 2D Random Array: ', np.random.random((4, 4)))

x = np.linspace(1, 10, num=10)
y = np.linspace(2, 30, num=10)
print(x)
print(y)
plt.plot(x, y)
plt.show()

input = np.array([[1, 2, 3, 2, 1], [2, 4, 6, 4, 2], [3, 4, 5, 4, 3]])
ft = np.fft.fft2(input)
print('\n FFT Result: ', ft)

x = np.round(np.random.normal(10, 0.2, size=(1024, 1)), 2)
x2 = np.round(np.random.normal(15, 0.2, size=(1024, 1)), 2)

# 使成为二维数组
print(x.shape)
print(x)
print(x2.shape)
z = np.row_stack((x, x2))
print(z)
print(z.shape)
