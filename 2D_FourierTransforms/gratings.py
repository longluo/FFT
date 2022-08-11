# gratings.py

import numpy as np
import matplotlib.pyplot as plt

x = np.arange(-500, 501, 1)

wavelength = 200
y = np.sin(2 * np.pi * x / wavelength)

plt.plot(x, y)
plt.show()

