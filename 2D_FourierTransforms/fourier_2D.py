import numpy as np

print('1D Random Array: ', np.random.random(10))

x = np.round(np.random.normal(10, 0.2, size=(1024, 1)), 2)
x2 = np.round(np.random.normal(15, 0.2, size=(1024, 1)), 2)

# 使成为二维数组
print(x.shape)
print(x)
print(x2.shape)
z = np.row_stack((x, x2))
print(z)
print(z.shape)
