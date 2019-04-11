from __future__ import print_function, division, absolute_import
import serial
import time
import struct
from Arduino import Arduino
from robust_serial import write_order, Order, write_i8, write_i16, read_i8, read_order

ard1 = Arduino(port="/dev/ttyACM0",speed=9600)

ser = ard1.conn
ser.reset_input_buffer()

# prompt = ser.readline()
# print(prompt)

# ser.reset_input_buffer()
# stringThing = '1'
# ser.write(stringThing.encode(encoding='UTF-8'))
# ser.reset_input_buffer()
is_connected = False
while not is_connected:
        print("Waiting for arduino...")
        write_order(ser, Order.HELLO)
        bytes_array = bytearray(ser.read(1))
        if not bytes_array:
            time.sleep(2)
            continue
        byte = bytes_array[0]
        if byte in [Order.HELLO.value, Order.ALREADY_CONNECTED.value]:
            is_connected = True
            print("Connected!!!!!")
write_order(ser, Order.HELLO)
write_order(ser, Order.MOTOR)
write_i8(ser, 1)
write_i8(ser, 90)
while True:
    bytes_array = bytearray(ser.read(1))
    if not bytes_array:
        time.sleep(2)
        print("no messages")
        continue
    byte = bytes_array[0]
    # byte = ser.read(1)
    print(byte)
    time.sleep(1)
    # write_order(ser, Order.MOTOR)
    # write_i8(ser, 1)
    # write_i8(ser, 90)
