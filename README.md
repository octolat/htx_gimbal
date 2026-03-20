## setup
requires a 5v, 1.5a power supply.  
pan servo connected to the row of pins where the signal wire goes to D2.  
tilt servo connected to the row of pins where the signal wire goes to D5.  

## avaliable commands

the script in the esp waits for a command through serial and executes.  
the command should follow the following structure: `{SERVONAME}_{DEGREES}\n`  
for example, `pan_-90\n` will pan fully 90 degrees to the left.  

default baud rate is `115200`  

valid servonames are:
1. `pan`
2. `tilt`  

valid degree range is:  
`-90 to 90`   
note: it can theoridically go up more than -+ 90 degrees. the current corresponding pulse width for -90 is 520, but the actual minimum is 350. 90 is 2525, but the actual maximum is 2600. see editing the esp section.  

Additionally, you can send `debug_true` or `debug_false` to toggle incoming serial messages if your not looking to read them anyway. if debug is true, it is garunteed that there will be a '\n' incoming in the buffer after you send a message. (if the messages come funky please flush the buffer before reading new messages after toggleling)

## sending commands using python
see `sender_code/taichi.py`  
pointers:  
1. flush buffer right after opening the port
2. get yo baud rate right (and com port)
3. when sending message your string MUST have A '\n'. it acts as a message seperator.
4. if debug is true it is garunteed that there will be a '\n' incoming in the buffer after you send a message.

## editing the esp
the following parameters can be easily editied: (bracketed values are defaults)
1. number of servos (2)
2. servo names (pan, tilt)
3. servo pins (D2,D5)
4. pulse width limits sent to servo (520, 2525)
5. incoming command degree limits (-90 to 90)
6. terminate character ('/n') (for sending messages only)
7. seperator character ('_')
8. default debug value (True)
9. baudrate (115200)   

see `servo_controller/servo_controller.ino`

note: the CP210x driver is needed for the nodemcu. you need to download it to communicate with the mcu. additionally, the code is dependent on the arduino servo libary  

