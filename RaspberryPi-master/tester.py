from __future__ import print_function, division, absolute_import
import serial
import time
import struct
from Arduino import Arduino
from robust_serial import write_order, Order, write_i8, write_i16, read_i8, read_order
from robust_serial.utils import open_serial_port

ard1 = Arduino(port="/dev/ttyACM0",speed=9600)

while True:
    if ard1.conn.inWaitin()>0:
        inputValue = ard1.conn.read(1)
        print(ord(inputValue))