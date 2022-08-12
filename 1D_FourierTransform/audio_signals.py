import numpy as np
from matplotlib import pyplot as plt
from scipy.io.wavfile import write
from scipy.fft import fft, fftfreq

SAMPLE_RATE = 44100  # Hertz
DURATION = 5  # Seconds


def generate_sine_wave(freq, sample_rate, duration):
    x = np.linspace(0, duration, sample_rate * duration, endpoint=False)
    frequencies = x * freq
    # 2pi because np.sin takes radians
    y = np.sin((2 * np.pi) * frequencies)
    return x, y


# Generate a 2 hertz sine wave that lasts for 5 seconds
x, y = generate_sine_wave(2, SAMPLE_RATE, DURATION)
plt.plot(x, y, )
plt.xlabel('Time (x)')
plt.ylabel('Amplitude (y)')
plt.show()


# Pure Music Signal
_, music_tone = generate_sine_wave(440, SAMPLE_RATE, DURATION)

normalized_tone = np.int16((music_tone / music_tone.max()) * 32767)

plt.plot(normalized_tone[:1000])
plt.xlabel('Time (x)')
plt.ylabel('Amplitude (y)')
plt.title('Music 440Hz')
plt.show()

# Remember SAMPLE_RATE = 44100 Hz is our playback rate
write("440music.wav", SAMPLE_RATE, normalized_tone)



# Mixing Audio Signals
_, nice_tone = generate_sine_wave(440, SAMPLE_RATE, DURATION)
_, noise_tone = generate_sine_wave(4000, SAMPLE_RATE, DURATION)
noise_tone = noise_tone * 0.3

mixed_tone = nice_tone + noise_tone

normalized_tone = np.int16((mixed_tone / mixed_tone.max()) * 32767)

plt.plot(normalized_tone[:1000])
plt.xlabel('Time (x)')
plt.ylabel('Amplitude (y)')
plt.show()

# Remember SAMPLE_RATE = 44100 Hz is our playback rate
write("mysinewave.wav", SAMPLE_RATE, normalized_tone)

# FFT
# Number of samples in normalized_tone
N = SAMPLE_RATE * DURATION

yf = fft(normalized_tone)
xf = fftfreq(N, 1 / SAMPLE_RATE)

plt.plot(xf, np.abs(yf))
plt.xlabel('freq (w)')
plt.ylabel('Amplitude (y)')
plt.show()
