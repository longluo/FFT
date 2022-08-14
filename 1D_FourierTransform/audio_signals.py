import numpy as np
from matplotlib import pyplot as plt
from scipy.io.wavfile import write
from scipy.fft import fft, fftfreq
from scipy.fft import rfft, rfftfreq
from scipy.fft import irfft

SAMPLE_RATE = 44100  # Hertz
DURATION = 5  # Seconds

N = SAMPLE_RATE * DURATION


def generate_sine_wave(freq, sample_rate, duration):
    x = np.linspace(0, duration, sample_rate * duration, endpoint=False)
    frequencies = x * freq
    # 2pi because np.sin takes radians
    y = np.sin((2 * np.pi) * frequencies)
    return x, y


# Use FFT to generate the Freq domain
# Number of samples in normalized_tone
def generate_spectrum_fft(normalized_tone):
    yf = fft(normalized_tone)
    xf = fftfreq(N, 1 / SAMPLE_RATE)
    plt.plot(xf, np.abs(yf))
    plt.xlabel('freq (w)')
    plt.ylabel('Amplitude (y)')
    plt.title('Spectrum')
    plt.show()


# Use RFFT to generate the Freq domain
def generate_spectrum_rfft(normalized_tone):
    yf = rfft(normalized_tone)
    xf = rfftfreq(N, 1 / SAMPLE_RATE)
    plt.plot(xf, np.abs(yf))
    plt.xlabel('freq (w)')
    plt.ylabel('Amplitude (y)')
    plt.title('Spectrum')
    plt.show()


def plot_picure(input, xlabel, ylabel, title):
    plt.plot(input[:1000])
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.title(title)
    plt.show()


# Generate a 2 hertz sine wave that lasts for 5 seconds
x, y = generate_sine_wave(2, SAMPLE_RATE, DURATION)
plt.plot(x, y)
plt.xlabel('Time (x)')
plt.ylabel('Amplitude (y)')
plt.show()

# Pure Music Signal
_, music_tone = generate_sine_wave(440, SAMPLE_RATE, DURATION)

normalized_tone = np.int16((music_tone / music_tone.max()) * 32767)

plot_picure(normalized_tone, 'Time (x)', 'Amplitude (y)', 'Music 440Hz')

# Remember SAMPLE_RATE = 44100 Hz is our playback rate
write("440music.wav", SAMPLE_RATE, normalized_tone)

generate_spectrum_fft(normalized_tone)

# Mixed Music Signal
_, music_tone_261 = generate_sine_wave(261, SAMPLE_RATE, DURATION)
_, music_tone_440 = generate_sine_wave(440, SAMPLE_RATE, DURATION)
_, music_tone_1046 = generate_sine_wave(1046, SAMPLE_RATE, DURATION)

music_tone = music_tone_261 + music_tone_440 + music_tone_1046

normalized_tone = np.int16((music_tone / music_tone.max()) * 32767)

plot_picure(normalized_tone, 'Time (x)', 'Amplitude (y)', 'Music (261Hz 440Hz 1046Hz)')

# Remember SAMPLE_RATE = 44100 Hz is our playback rate
write("mixed_music.wav", SAMPLE_RATE, normalized_tone)

generate_spectrum_fft(normalized_tone)

# Mixing Audio Signals
_, nice_tone = generate_sine_wave(440, SAMPLE_RATE, DURATION)
_, noise_tone = generate_sine_wave(4000, SAMPLE_RATE, DURATION)
noise_tone = noise_tone * 0.3

mixed_tone = nice_tone + noise_tone

normalized_tone = np.int16((mixed_tone / mixed_tone.max()) * 32767)

plot_picure(normalized_tone, 'Time (x)', 'Amplitude (y)', 'Mixed Music')

# Remember SAMPLE_RATE = 44100 Hz is our playback rate
write("musicNoise.wav", SAMPLE_RATE, normalized_tone)

generate_spectrum_fft(normalized_tone)
generate_spectrum_rfft(normalized_tone)

yf = rfft(normalized_tone)
xf = rfftfreq(N, 1 / SAMPLE_RATE)

# The maximum frequency is half the sample rate
points_per_freq = len(xf) / (SAMPLE_RATE / 2)

# Our target frequency is 4000 Hz
target_idx = int(points_per_freq * 4000)

yf[target_idx - 1: target_idx + 2] = 0

plt.plot(xf, np.abs(yf))
plt.show()

new_sig = irfft(yf)

plt.plot(new_sig[:1000])
plt.show()

norm_new_sig = np.int16(new_sig * (32767 / new_sig.max()))

write("clean.wav", SAMPLE_RATE, norm_new_sig)

