import serial


class LedCom:
    __ser = None

    def __init__(self):
        self.__ser = serial.Serial("/dev/ttyUSB0", 9600)
        self.open()

    def open(self):
        if not self.__ser.is_open:
            self.__ser.open()

    def close(self):
        if self.__ser.is_open:
            self.__ser.close()

    def print(self, msg: str):
        self.write(msg.encode())

    def write(self, data):
        self.__ser.write(data)
