from __future__ import print_function, division, absolute_import
import serial
import time
import struct
from Arduino import Arduino
from robust_serial import write_order, Order, write_i8, write_i16, read_i8, read_order

def setup():
    ard1 = Arduino(port="/dev/ttyACM0",speed=9600)
    ard2 = Arduino(port="/dev/ttyACM1",speed=9600)
    ard3 = Arduino(port="/dev/ttyACM2",speed=9600)
    ard4 = Arduino(port="/dev/ttyACM3",speed=9600)
    ardList = [ard1,ard2,ard3,ard4]
    flag = True
    for ard in ardList:
        flag = flag and ard.is_connected
        print(ard.is_connected)
    # Initialize communication with Arduino
    for ard in ardList:
        while True:
            print("Waiting for arduino...")
            write_order(ard.conn, Order.HELLO)
            bytes_array = bytearray(ard.conn.read(1))
            if not bytes_array:
                time.sleep(2)
                continue
            byte = bytes_array[0]
            if byte in [Order.HELLO.value, Order.ALREADY_CONNECTED.value]:
                print("Connected to Arduino" + str(ard))
            break

    return ardList


# for ser in serList:
#     ser.flushInput()

