#print("hello world")
import serial

ser = serial.Serial(
    port='COM6',\
    baudrate=9600,\
    parity=serial.PARITY_NONE,\
    stopbits=serial.STOPBITS_ONE,\
    bytesize=serial.EIGHTBITS,\
        timeout=0)

data=" "
stop=15
count=0

while stop!=165:
    for line in ser.read():
        if line!="\n":
            data=data+line
        else:
            print(data)
            #f.write(data+"\n")
            stop=int(data)
            data=" "

ser.close()
