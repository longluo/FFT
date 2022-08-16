from math import *

import matplotlib.pyplot as plt
import numpy as np
from scipy.integrate import quad
from scipy.signal import square

x = np.arange(-2 * np.pi, 2 * np.pi, 0.001)
# x axis has been chosen from –2π to +2π,
# value of 1 smallest square along x axis is 0.001

y = square(x)
# defining square wave function
# 𝑦 =−1, 𝑓𝑜𝑟 −𝜋 ≤ 𝑥 ≤ 0
# y =+1, 𝑓𝑜𝑟 0 ≤ 𝑥 ≤ 𝜋

plt.figure(figsize = (12, 6))

plt.subplot(211)
plt.plot(x, y)
plt.title("Square Wave")

# define fuction

fc = lambda x: square(x) * cos(i * x)  # i: dummy index
fs = lambda x: square(x) * sin(i * x)

n = 50  # max value of I, not taken infinity, better result with high value

An = []  # defining array
Bn = []

sum = 0

for i in range(n):
    an = quad(fc, -np.pi, np.pi)[0] * (1.0 / np.pi)
    An.append(an)

for i in range(n):
    bn = quad(fs, -np.pi, np.pi)[0] * (1.0 / np.pi)
    Bn.append(bn)  # putting value in array Bn

for i in range(n):
    if i == 0.0:
        sum = sum + An[i] / 2
    else:
        sum = sum + (An[i] * np.cos(i * x) + Bn[i] * np.sin(i * x))

plt.subplot(212)
plt.plot(x, sum, 'g')
plt.plot(x, y, 'r--')
plt.title("Fourier Series for Square Wave")

plt.show()

