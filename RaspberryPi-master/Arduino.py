import serial
import time
import struct
import threading
from queue import Queue
import time

class Arduino(object):

    #Initializer
    def __init__(self,port,speed=9600):
        self.port = port
        self.speed = speed
        self.is_connected = False
        self.conn = self.tryConnect()
        self.orderQueue = []

    def tryConnect(self):
        count = 1
        conn = None
        while not self.is_connected and count < 3:
            try:
                conn = serial.Serial(self.port,self.speed)
                self.is_connected = True
                print("Connected to:")
                print(self)
                return conn
            except:
                print("\nAttempting to connect with ", str(self))
                time.sleep(1)
                count += 1
        print("\nCould not connect to Arduino")
        return conn
    #How the object will represent itself when called or printed
    def __repr__(self):
        return "Arduino at port: %s\n" %(self.port)
    

    
