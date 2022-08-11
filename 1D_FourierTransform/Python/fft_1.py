from scipy.fftpack import fft
import numpy as np
x = np.array([4.0, 2.0, 1.0, -3.0, 1.5])
y = fft(x)
print(y)

