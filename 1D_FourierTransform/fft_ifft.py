import matplotlib.pyplot as plt
import numpy as np
from numpy.fft import fft, ifft

plt.style.use('seaborn-poster')

# sampling rate
SAMPLING_RATE = 2000

# sampling interval
ts = 1.0 / SAMPLING_RATE

t = np.arange(0, 1, ts)

freq = 1
x = 3 * np.sin(2 * np.pi * freq * t)

freq = 4
x += np.sin(2 * np.pi * freq * t)

freq = 7
x += 0.5 * np.sin(2 * np.pi * freq * t)

plt.figure(figsize=(16, 12))

plt.subplot(221)
plt.xlabel('Time (s)')
plt.ylabel('Amplitude')
plt.title('Signal')
plt.plot(t, x, 'r')

# FFT
X = fft(x)
N = len(X)
n = np.arange(N)
T = N / SAMPLING_RATE
freq = n / T

plt.subplot(222)
plt.stem(freq, np.abs(X), 'b', markerfmt=" ", basefmt="-b")
plt.xlim(0, 10)
plt.xlabel('Freq (Hz)')
plt.ylabel('FFT Amplitude |X(freq)|')
plt.title('FFT Spectrum')

# Freq Spectrum
plt.subplot(223)
plt.stem(freq, np.abs(X), 'b', markerfmt=" ", basefmt="-b")
plt.xlabel('Freq (Hz)')
plt.ylabel('FFT Amplitude |X(freq)|')
plt.xlim(0, 10)

# IFFT
plt.subplot(224)
plt.plot(t, ifft(X), 'r')
plt.xlabel('Time (s)')
plt.ylabel('Amplitude')
plt.title('IFFT ')
plt.tight_layout()

plt.show()
