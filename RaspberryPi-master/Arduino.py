import serial
import time
import struct

class Arduino(object):

    #Initializer
    def __init__(self,port,speed=9600):
        self.port = port
        self.speed = speed
        self.is_connected = False
        self.conn = self.tryConnect()
        self.orderQueue = []

    def tryConnect(self):
        while not self.is_connected:
            try:
                conn = serial.Serial(port,speed)
                self.is_connected = True
            except:
                print("\nAttempting to connect with ", str(self))
            time.sleep(1)
        return conn
    #How the object will represent itself when called or printed
    def __repr__(self):
        return "Arduino object:\n\nArduino at port: %s\nspeed: %s" %(self.port,self.speed)
    

    
