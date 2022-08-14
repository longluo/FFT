import matplotlib.pyplot as plt
import numpy as np

SAMPLE_RATE = 44100  # Hertz
DURATION = 5  # Seconds

plt.style.use('seaborn-poster')


def generate_sine_wave(freq, sample_rate, duration):
    x = np.linspace(0, duration, sample_rate * duration, endpoint=False)
    frequencies = x * freq
    # 2pi because np.sin takes radians
    y = np.sin((2 * np.pi) * frequencies)
    return x, y

# Generate a 2 hertz sine wave that lasts for 5 seconds
x, y = generate_sine_wave(2, SAMPLE_RATE, DURATION)
plt.plot(x, y)
plt.xlabel('Time (x)')
plt.ylabel('Amplitude (y)')
plt.show()

x = np.linspace(0, 20, 201)
y = np.sin(x)

plt.figure(figsize=(8, 6))
plt.plot(x, y, 'b')
plt.xlabel('Location (x)')
plt.ylabel('Amplitude')

plt.show()

fig = plt.figure(figsize=(8, 8))

times = np.arange(5)

n = len(times)

for t in times:
    plt.subplot(n, 1, t + 1)
    y = np.sin(x + t)
    plt.plot(x, y, 'b')
    plt.plot(x[25], y[25], 'ro')
    plt.ylim(-1.1, 1.1)
    plt.ylabel('y')
    plt.title(f't = {t}')

plt.xlabel('location (x)')
plt.tight_layout()
plt.show()

# sampling rate
sr = 100.0
# sampling interval
ts = 1.0 / sr
t = np.arange(0, 1, ts)

# frequency of the signal
freq = 5
y = np.sin(2 * np.pi * freq * t)

plt.figure(figsize=(8, 8))
plt.subplot(211)
plt.plot(t, y, 'b')
plt.ylabel('Amplitude')

freq = 10
y = np.sin(2 * np.pi * freq * t)

plt.subplot(212)
plt.plot(t, y, 'b')
plt.ylabel('Amplitude')

plt.xlabel('Time (s)')
plt.show()

# frequency of the signal
freq = 5
y = 5 * np.sin(2 * np.pi * freq * t)

plt.figure(figsize=(8, 8))
plt.subplot(211)
plt.plot(t, y, 'b')
plt.ylabel('Amplitude')

y = 10 * np.sin(2 * np.pi * freq * t + 10)

plt.subplot(212)
plt.plot(t, y, 'b')
plt.ylabel('Amplitude')

plt.xlabel('Time (s)')
plt.show()
