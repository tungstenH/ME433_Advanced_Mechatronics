# chapter 28 in python

# sudo apt-get install python3-pip
# python3 -m pip install pyserial
# sudo apt-get install python3-matplotlib

import serial
import matplotlib.pyplot as plt
import numpy as np # for sine function

ser = serial.Serial('/dev/tty.usbserial-0232B082',230400)
print('Opening port: ')
print(ser.name)

read_samples = 10
ax = []
ay = []
az = []
gx = []
gy = []
gz = []
temp = []
print('Requesting data collection... ')
ser.write(b'\n')
while read_samples >1 :
    data_read = ser.read_until(b'\n', 200)
    data_text = str(data_read,'utf=8')
    data = [float(i) for i in data_text.split()]

    if(len(data)==8):
        read_samples = int(data[0])
        ax.append(data[1])
        ay.append(data[2])
        az.append(data[3])
        gx.append(data[4])
        gy.append(data[5])
        gz.append(data[6])
        temp.append(data[7])
print('Data collection complete')

# Plotting
t = range(len(ax))
plt.plot(t, ax, 'r*-', t, ay, 'b*-', t, az, 'k*-')
plt.ylabel('G Value')
plt.xlabel('Sample')
plt.show()

plt.plot(t, gx, 'r*-', t, gy, 'b*-', t, gz, 'k*-')
plt.ylabel('Omega Value')
plt.xlabel('Sample')
plt.show()

plt.plot(t, temp, 'r*-')
plt.ylabel('Temperature Value')
plt.xlabel('Sample')
plt.show()