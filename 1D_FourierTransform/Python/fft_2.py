import scipy.fft
import matplotlib.pyplot as plt
import numpy as np


N = 500
T = 1.0 / 600.0
x = np.linspace(0.0, N*T, N)
y = np.sin(60.0 * 2.0*np.pi*x) + 0.5*np.sin(90.0 * 2.0*np.pi*x)
y_f = scipy.fft.fft(y)
x_f = np.linspace(0.0, 1.0/(2.0*T), N//2)

plt.plot(x_f, 2.0/N * np.abs(y_f[:N//2]))
plt.show()

