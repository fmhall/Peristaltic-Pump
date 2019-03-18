from __future__ import print_function, division, absolute_import
import serial
import time
import struct
from Arduino import Arduino
from robust_serial import write_order, Order, write_i8, write_i16, read_i8, read_order
from robust_serial.utils import open_serial_port
if __name__ == '__main__':
    ard1 = Arduino(port="/dev/ttyUSB0",speed=9600)
    ard2 = Arduino(port="/dev/ttyUSB1",speed=9600)
    ard3 = Arduino(port="/dev/ttyUSB2",speed=9600)
    ard4 = Arduino(port="/dev/ttyUSB3",speed=9600)
    ardList = [ard1,ard2,ard3,ard4]

    for ard in ardList:
        print(ard.is_connected)
    # Initialize communication with Arduino
    for ard in ardList:
        print("Waiting for arduino...")
        write_order(ard.conn, Order.HELLO)
        bytes_array = bytearray(ard.conn.read(1))
        if not bytes_array:
            time.sleep(2)
            continue
        byte = bytes_array[0]
        if byte in [Order.HELLO.value, Order.ALREADY_CONNECTED.value]:
            is_connected = True

    print("Connected to Arduino")

# for ser in serList:
#     ser.flushInput()

