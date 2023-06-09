import time
from ulab import numpy as np # to get access to ulab numpy functions

# Make array of time
t = np.linspace(1,10, 1024)

# Make sum 3 sine wave
sin1 = 100*np.sin(0.3*t)
sin2 = 20*np.sin(10*(t-60))
sin3 = 0.3*np.sin(500*t)
sumSin = sin1 + sin2 + sin3

# Perform FFT
Fs = len(t)/t[-1] # sample rate
Ts = 1.0/Fs; # sampling interval
ts = np.arange(0,t[-1],Ts) # time vector
y = sumSin # the data to make the fft from
n = len(y) # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T # two sides frequency range
frq = frq[:len(frq)//2] # one side frequency range
Y = np.fft.fft(y)[0] # fft computing and normalization
Y = np.array(Y)/n
Y = Y[:len(Y)//2]

"""
#Plot sumSin
for i in range(50):
    print("("+str(sumSin[i*20])+",)")
    time.sleep(.01)
"""

#FFT Plot
for i in range(50):
    print("("+str(Y[i*10])+",)")
    time.sleep(.01)
