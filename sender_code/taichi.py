import serial
import time

gimbal = serial.Serial(port='COM6',  baudrate=115200)
# clear buffer
while gimbal.in_waiting > 0:
    gimbal.read()

debug = True
while True:
    cmd = input("cmd: ") # like "pan_-90" or "tilt_45" or "debug_false"
    if cmd == "debug_false": debug = False
    elif cmd == "debug_true": debug = True
    cmd += "\n"
    gimbal.write(cmd.encode('utf-8'))

    #see whats coming back
    if debug:
        result = ""
        while True:
            char = gimbal.read().decode('utf-8')
            if char == '\n': break
            result += char
        print(result)
