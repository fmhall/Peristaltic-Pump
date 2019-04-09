from __future__ import print_function, division, absolute_import
import serial
import time
import struct
from Arduino import Arduino
from robust_serial import write_order, Order, write_i8, write_i16, read_i8, read_order
from robust_serial.utils import open_serial_port

ard1 = Arduino(port="/dev/ttyACM0",speed=9600)

ser = ard1.conn
ser.reset_input_buffer()

prompt = ser.readline()
print(prompt)

ser.reset_input_buffer()
stringThing = '1'
ser.write(stringThing.encode(encoding='UTF-8'))
ser.reset_input_buffer()
while True:
    if ser.in_waiting > 0:
        inval = ser.read(1)
        print(ord(inval))
